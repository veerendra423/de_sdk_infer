/**
 * @file ambarella.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#include <iostream>
#include <cstring>
#include <math.h>
#include <sys/ioctl.h>
#include "ambarella.h"
#include "cavalry_mem.h"
#include "cavalry_ioctl.h"
#include "nnctrl.h"
#include "iav_ioctl.h"
#include "vproc.h"
//#include "cstdfloat_cmath.hpp"

#define FIX8_MIN_ACCURACY 0.00390625f

#define FILENAME_LENGTH     (256)


using namespace std;


static int G_socket_id;
static int G_port = 27182;
static int fd_iav;
static int dsp_state;
static unsigned long phy_addr_base;
static int live_mode_flag = 1;
static char mean_name[FILENAME_LENGTH];
static int submean_flag = 0;
static int yuv2rgb_resize_only_flag = 0;
static float scale_factor = 1;
static int buffer_id = 0;
static int buffer_type = 0;
static int rgb_type = 1;
static unsigned long int frame_id = 0;
static int send_desc_flag = 1;
struct cv_mem {
	void *virt;
	unsigned long phys;
	unsigned long size;
};

struct cv_mem lib_mem;
struct cv_mem yuv2rgb_out_mem;
struct cv_mem rsz_out_mem;
struct cv_mem dtcvt_out_mem;
struct cv_mem submean_mean_mem;
struct cv_mem submean_out_mem;

struct io_match {
	uint32_t load_input : 1;
	uint32_t store_output : 1;
	uint32_t no_mem : 1;
	uint32_t reserved_0 : 29;

	cv_daddr_t dram_addr;
	uint32_t dram_size;

	char port_name[CAVALRY_IO_NAME_MAX];
	char file_name[FILENAME_LENGTH];
};

struct net_match {
	uint32_t verbose : 1; /* nerual network verbose */
	uint32_t reuse_mem : 1;
	uint32_t dump_en : 1;
	uint32_t reserved_0 : 29;

	uint32_t net_id;
	int iter_num;
	char net_name[FILENAME_LENGTH];
	char path_dump[FILENAME_LENGTH];

	struct net_mem net_m;

	uint32_t in_num;
	uint32_t out_num;
	struct io_match in_pair[MAX_IO_NUM];
	struct io_match out_pair[MAX_IO_NUM];
};

#define MAX_NET_NUM (16)

struct nnctrl_param {
	int fd_cav;

	uint32_t verbose : 1;  /* nnctrl library verbose */
	uint32_t cache_en : 1; /* 0: nocached; 1: cached */
	uint32_t reserved_0 : 30;

	uint32_t net_num;
	struct net_match net_pair[MAX_NET_NUM];
	struct net_mem ext_mem[MAX_NET_NUM];
};

static struct nnctrl_param G_nnctrl;


static int alloc_cv_mem(uint32_t *psize, cv_daddr_t *pphys, uint8_t **pvirt)
{
	void *virt = 0;
	unsigned long phys = 0, size = 0;

	size = *psize;
	if (cavalry_mem_alloc(&size, &phys, &virt, 1) < 0) {
		printf("cavalry_mem_alloc err\n");
		return -1;
	}
	*psize = size;
	*pphys = phys;
	//*pvirt = virt;

	return 0;
}

static void free_all_cv_mem(struct nnctrl_param *pctl)
{
	struct net_mem *pmem = NULL;
	int i = 0;

	for (i = 0; i < pctl->net_num; i++) {
		pmem = &pctl->net_pair[i].net_m;
		if (pmem->virt_addr && pmem->mem_size) {
			if (cavalry_mem_free(pmem->mem_size,
				pmem->phy_addr, pmem->virt_addr) < 0) {
				printf("cavalry_mem_free err\n");
			}
		}

		pmem = &pctl->ext_mem[i];
		if (pmem->virt_addr && pmem->mem_size) {
			if (cavalry_mem_free(pmem->mem_size,
				pmem->phy_addr, pmem->virt_addr) < 0) {
				printf("cavalry_mem_free err\n");
			}
		}
	}
}




static int set_net_io_cfg(struct net_match *pnet,
						struct net_input_cfg *net_in, struct net_output_cfg *net_out)
{
	uint32_t i = 0;

	net_in->in_num = pnet->in_num;
	net_out->out_num = pnet->out_num;
	for (i = 0; i < net_in->in_num; i++) {
		printf("in num = %d \n", net_in->in_num);
		if (i > MAX_IO_NUM) {
			printf("Overflow input num: %u, max: %u", i, MAX_IO_NUM);
			return -1;
		}
		net_in->in_desc[i].name = pnet->in_pair[i].port_name;
		if (pnet->in_pair[i].no_mem) {
			net_in->in_desc[i].no_mem = 1;
			net_in->in_desc[i].addr = pnet->in_pair[i].dram_addr;
			net_in->in_desc[i].size = pnet->in_pair[i].dram_size;
		}
	}
	for (i = 0; i < net_out->out_num; i++) {
		if (i > MAX_IO_NUM) {
			printf("Overflow output num: %u, max: %u", i, MAX_IO_NUM);
			return -1;
		}
		net_out->out_desc[i].name = pnet->out_pair[i].port_name;
	}

	return 0;
}

static int get_net_io_cfg(struct net_match *pnet,
						struct net_input_cfg *net_in, struct net_output_cfg *net_out)
{
	uint32_t i = 0;
	int rval = 0;

	for (i = 0; i < net_in->in_num; i++) {
		if (pnet->in_pair[i].no_mem == 0) {
			pnet->in_pair[i].dram_addr = net_in->in_desc[i].addr;
			pnet->in_pair[i].dram_size = net_in->in_desc[i].size;
			if ((net_in->in_desc[i].addr == 0) || (net_in->in_desc[i].size == 0)) {
				printf("Input [%u] [%s] get invalid addr: 0x%lx, size: 0x%x\n",
					i,
					net_in->in_desc[i].name,
					(unsigned long)net_in->in_desc[i].addr,
					net_in->in_desc[i].size);
				rval = -1;
				break;
			}
		}
		printf("Input [%u] [%s] dimension: %u, %u, %u, %u, pitch: %u, "
			"dram_format: %u, data_format: %u, %u, %u, %u\n",
			i,
			net_in->in_desc[i].name,
			net_in->in_desc[i].dim.plane,
			net_in->in_desc[i].dim.depth,
			net_in->in_desc[i].dim.height,
			net_in->in_desc[i].dim.width,
			net_in->in_desc[i].dim.pitch,
			net_in->in_desc[i].dim.dram_fmt,
			net_in->in_desc[i].data_fmt.sign,
			net_in->in_desc[i].data_fmt.size,
			net_in->in_desc[i].data_fmt.expoffset,
			net_in->in_desc[i].data_fmt.expbits);
	}

	for (i = 0; i < net_out->out_num; i++) {
		if ((net_out->out_desc[i].addr == 0) || (net_out->out_desc[i].size == 0)) {
			printf("Output [%u] [%s] get invalid addr: 0x%lx, size: 0x%x\n",
				i,
				net_out->out_desc[i].name,
				(unsigned long)net_out->out_desc[i].addr,
				net_out->out_desc[i].size);
			rval = -1;
			break;
		}
		pnet->out_pair[i].dram_addr = net_out->out_desc[i].addr;
		pnet->out_pair[i].dram_size = net_out->out_desc[i].size;
		printf("Output [%u] [%s] dimension: %u, %u, %u, %u, pitch: %u, "
			"dram_format: %u, data_format: %u, %u, %u, %u\n",
			i,
			net_out->out_desc[i].name,
			net_out->out_desc[i].dim.plane,
			net_out->out_desc[i].dim.depth,
			net_out->out_desc[i].dim.height,
			net_out->out_desc[i].dim.width,
			net_out->out_desc[i].dim.pitch,
			net_out->out_desc[i].dim.dram_fmt,
			net_out->out_desc[i].data_fmt.sign,
			net_out->out_desc[i].data_fmt.size,
			net_out->out_desc[i].data_fmt.expoffset,
			net_out->out_desc[i].data_fmt.expbits);
	}

	return rval;
}

static int load_mean_binary(char *file, void *dst_addr, vect_desc_t *mean_file, unsigned long *size)
{
	FILE *fp = NULL;
	int rval = 0;
	int i, datasize;
	uint32_t plane, depth, height, width, pitch;
	unsigned long file_length;

	do {
		if ((fp = fopen(file, "rb")) == NULL) {
			perror(file);
			rval = -1;
			break;
		}

		if (fseek(fp, 0, SEEK_END) < 0) {
			perror("SEEK_END");
			rval = -1;
			break;
		}
		file_length = ftell(fp);

		if (fseek(fp, 0, SEEK_SET) < 0) {
			perror("SEEK_SET");
			rval = -1;
			break;
		}
		plane = mean_file->shape.p;
		depth = mean_file->shape.d;
		height = mean_file->shape.h;
		width = mean_file->shape.w;
		pitch = mean_file->pitch;
		datasize = 1 << mean_file->data_format.datasize;
		printf("load sub_mean mean file, file size = %ld, expect size = %d\n",
			file_length, plane * depth * height * ROUND_UP(datasize * width, CAVALRY_PORT_PITCH_ALIGN));

		if (file_length == *size) {
			if (fread(dst_addr, 1, file_length, fp) != file_length) {
				printf("file size mismatch, should be fp16, %d bytes!\n",
					plane * depth * height * ROUND_UP(datasize * width, CAVALRY_PORT_PITCH_ALIGN));
				rval = -1;
				break;
			}
		} else if (file_length == plane * depth * height * width * datasize) {
			if (pitch - width * datasize > 0) {
				printf("Pitch(%d) != width * datasize(%d), add pitch %d automatically\n",
					pitch, width * datasize, pitch - width * datasize);
				for (i = 0; i < plane * depth * height; i++) {
					if (fread(dst_addr + i * pitch, datasize, width, fp) != width) {
						printf("file size mismatch, should be fp16, %d bytes!\n",
							plane * depth * height * ROUND_UP(datasize * width, CAVALRY_PORT_PITCH_ALIGN));
						rval = -1;
						break;
					}
					memset(dst_addr + i * pitch + width * datasize,
						0, pitch - width * datasize);
				}
			} else {
				printf("Pitch < width * datasize, load mean file error\n");
				rval = -1;
				break;
			}
		} else {
			printf("file size mismatch, should be fp16, %d bytes, "
				"please check the mean file, input data format and file pitch alignment with %d bytes!\n",
				plane * depth * height * ROUND_UP(datasize * width, CAVALRY_PORT_PITCH_ALIGN), CAVALRY_PORT_PITCH_ALIGN);
			rval = -1;
			break;
		}
		fclose(fp);
		fp = NULL;
	} while (0);

	if (fp) {
		fclose(fp);
		fp = NULL;
	}

	return rval;
}

static int get_network_input(struct net_input_cfg *net_in)
{
	static int non_block_read = 1;
	static int vproc_init_flag = 1;
	static uint32_t last_dsp_pts;

	struct iav_querydesc query_desc;
	struct iav_yuv_cap *data_cap;

	static yuv2rgb_mat_t yuv2rgb_mat;
	static vect_desc_t y, uv, rgb;
	static vect_desc_t rsz_in, rsz_out;
	static vect_desc_t dtcvt_in, dtcvt_out;
	static vect_desc_t submean_in, submean_mean, submean_out;
	static vect_desc_t scale_in, scale_out;

	if (vproc_init_flag) {
		memset(&y, 0, sizeof(y));
		memset(&uv, 0, sizeof(uv));
		memset(&rgb, 0, sizeof(rgb));
		memset(&yuv2rgb_mat, 0, sizeof(yuv2rgb_mat));
		memset(&yuv2rgb_out_mem, 0, sizeof(yuv2rgb_out_mem));
		memset(&rsz_out_mem, 0, sizeof(rsz_out_mem));
		memset(&dtcvt_out_mem, 0, sizeof(dtcvt_out_mem));
		memset(&submean_mean_mem, 0, sizeof(submean_mean_mem));
		memset(&submean_out_mem, 0, sizeof(submean_out_mem));
		memset(&rsz_in, 0, sizeof(rsz_in));
		memset(&rsz_out, 0, sizeof(rsz_out));
		memset(&dtcvt_in, 0, sizeof(dtcvt_in));
		memset(&dtcvt_out, 0, sizeof(dtcvt_out));
		memset(&submean_in, 0, sizeof(submean_in));
		memset(&submean_mean, 0, sizeof(submean_mean));
		memset(&submean_out, 0, sizeof(submean_out));
		memset(&scale_in, 0, sizeof(scale_in));
		memset(&scale_out, 0, sizeof(scale_out));
		memset(&query_desc, 0, sizeof(query_desc));
	}

	if (buffer_type == 0) {
		query_desc.qid = IAV_DESC_CANVAS;
		query_desc.arg.canvas.canvas_id = buffer_id;
		if (!non_block_read) {
			query_desc.arg.canvas.non_block_flag &= ~IAV_BUFCAP_NONBLOCK;
		} else {
			query_desc.arg.canvas.non_block_flag |= IAV_BUFCAP_NONBLOCK;
		}
		if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
			if (errno != EINTR) {
				perror("IAV_IOC_QUERY_DESC");
				return -1;
			}
		}
		data_cap = &query_desc.arg.canvas.yuv;
		if (last_dsp_pts == data_cap->dsp_pts) {
			query_desc.arg.canvas.non_block_flag &= ~IAV_BUFCAP_NONBLOCK; //return next new frame
			if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
				if (errno != EINTR && errno != EAGAIN) {
					perror("IAV_IOC_QUERY_DESC");
					return -1;
				}
			}
			data_cap = &query_desc.arg.canvas.yuv;
		}
	} else if (buffer_type == 1) {
		query_desc.qid = IAV_DESC_PYRAMID;
		query_desc.arg.pyramid.chan_id = 0;
		if (!non_block_read) {
			query_desc.arg.pyramid.non_block_flag &= ~IAV_BUFCAP_NONBLOCK;
		} else {
			query_desc.arg.pyramid.non_block_flag |= IAV_BUFCAP_NONBLOCK;
		}

		if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
			if (errno != EINTR) {
				perror("IAV_IOC_QUERY_DESC");
				return -1;
			}
		}
		data_cap = &query_desc.arg.pyramid.layers[buffer_id];
		if (last_dsp_pts == data_cap->dsp_pts) {
			query_desc.arg.pyramid.non_block_flag &= ~IAV_BUFCAP_NONBLOCK; //return next new frame
			if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
				if (errno != EINTR && errno != EAGAIN) {
					perror("IAV_IOC_QUERY_DESC");
					return -1;
				}
			}
			data_cap = &query_desc.arg.pyramid.layers[buffer_id];
		}
	} else {
		printf("Unknown buffer type, should be 0/1\n");
		return -1;
	}

	if (data_cap->width % 2 == 1) {
		printf("image width should be even!\n");
		return -1;
	}
	last_dsp_pts = data_cap->dsp_pts;
	//////////////////////////////////////////////////////////////////////////////////
	y.shape.p = 1;
	y.shape.d = 1;
	y.shape.h = data_cap->height;
	y.shape.w = data_cap->width;
	y.data_format.sign = 0; // yuv2rgb only support Fix8 as input/output
	y.data_format.datasize = 0;
	y.data_format.exp_offset = 0;
	y.data_format.exp_bits = 0;
	y.pitch = data_cap->pitch;
	y.data_addr = phy_addr_base + data_cap->y_addr_offset;
	y.color_space = CS_NV12;

	uv.shape.p = 1;
	uv.shape.d = 2;
	uv.shape.h = data_cap->height / 2;
	uv.shape.w = data_cap->width / 2;
	uv.data_format.sign = 0;
	uv.data_format.datasize = 0;
	uv.data_format.exp_offset = 0;
	uv.data_format.exp_bits = 0;
	uv.pitch = data_cap->pitch;
	uv.data_addr = phy_addr_base + data_cap->uv_addr_offset;
	uv.color_space = CS_NV12;

	if (vproc_init_flag) {
		printf("===================================================\n");
		printf("Neural Network data pre-processing init...\n"
				"YUV data size = %d x %d, pitch = %d\n",
				data_cap->width, data_cap->height, data_cap->pitch);

		rgb.shape.p = 1;
		rgb.shape.d = 3;
		rgb.shape.h = y.shape.h;
		rgb.shape.w = y.shape.w;
		rgb.data_format.sign = 0;
		rgb.data_format.datasize = 0;
		rgb.data_format.exp_offset = 0;
		rgb.data_format.exp_bits = 0;
		rgb.pitch = ROUND_UP(rgb.shape.w * (1 << rgb.data_format.datasize), CAVALRY_PORT_PITCH_ALIGN);

		if (rgb_type) {
			rgb.color_space = CS_BGR;
		} else {
			rgb.color_space = CS_RGB;
		}
		printf("RGB data dimension: %d, %d, %d, %d, pitch: %d, data_format: "
			"%d, %d, %d, %d, color space: %s\n",
			rgb.shape.p,
			rgb.shape.d,
			rgb.shape.h,
			rgb.shape.w,
			rgb.pitch,
			rgb.data_format.sign,
			rgb.data_format.datasize,
			rgb.data_format.exp_offset,
			rgb.data_format.exp_bits,
			rgb.color_space == CS_BGR ? "BGR" : "RGB");
		yuv2rgb_mat.yc = 1;
		yuv2rgb_mat.rv = 1.402;
		yuv2rgb_mat.gu = 0.344136;
		yuv2rgb_mat.gv = 0.714136;
		yuv2rgb_mat.bu = 1.772;
		yuv2rgb_mat.yb = 0;

		yuv2rgb_out_mem.size = rgb.shape.p * rgb.shape.d * rgb.shape.h * rgb.pitch;
		if (cavalry_mem_alloc(&yuv2rgb_out_mem.size, &yuv2rgb_out_mem.phys,
							&yuv2rgb_out_mem.virt, 0) < 0) {
			printf("cavalry_mem_alloc err\n");
			return -1;
		}
		rgb.data_addr = yuv2rgb_out_mem.phys;
	}
	vproc_yuv2rgb_420(&y, &uv, &rgb, &yuv2rgb_mat);
	//////////////////////////////////////////////////////////////////////////////////
	if (vproc_init_flag) {
		rsz_in.shape.p = rgb.shape.p;
		rsz_in.shape.d = rgb.shape.d;
		rsz_in.shape.h = rgb.shape.h;
		rsz_in.shape.w = rgb.shape.w;
		rsz_in.data_format.sign = rgb.data_format.sign; // Resize only support Fix8 as input/output
		rsz_in.data_format.datasize = rgb.data_format.datasize;
		rsz_in.data_format.exp_offset = rgb.data_format.exp_offset;
		rsz_in.data_format.exp_bits = rgb.data_format.exp_bits;
		rsz_in.pitch = rgb.pitch;
		rsz_in.color_space = CS_RGB;
		rsz_in.data_addr = rgb.data_addr;

		rsz_out.shape.p = net_in->in_desc[0].dim.plane;
		rsz_out.shape.d = net_in->in_desc[0].dim.depth;
		rsz_out.shape.h = net_in->in_desc[0].dim.height;
		rsz_out.shape.w = net_in->in_desc[0].dim.width;
		rsz_out.data_format.sign = rsz_in.data_format.sign;
		rsz_out.data_format.datasize = rsz_in.data_format.datasize;
		rsz_out.data_format.exp_offset = rsz_in.data_format.exp_offset;
		rsz_out.data_format.exp_bits = rsz_in.data_format.exp_bits;
		rsz_out.pitch = ROUND_UP(rsz_out.shape.w * (1 << rsz_out.data_format.datasize), CAVALRY_PORT_PITCH_ALIGN);
		rsz_out.color_space = CS_RGB;
		printf("resize output data dimension: %d, %d, %d, %d, pitch: %d, data_format: "
			"%d, %d, %d, %d\n",
			rsz_out.shape.p,
			rsz_out.shape.d,
			rsz_out.shape.h,
			rsz_out.shape.w,
			rsz_out.pitch,
			rsz_out.data_format.sign,
			rsz_out.data_format.datasize,
			rsz_out.data_format.exp_offset,
			rsz_out.data_format.exp_bits);
		if (submean_flag == 0 &&
			net_in->in_desc[0].data_fmt.sign == 0 &&
			net_in->in_desc[0].data_fmt.size == 0 &&
			net_in->in_desc[0].data_fmt.expbits == 0 &&
			fabs((1 << net_in->in_desc[0].data_fmt.expoffset) * scale_factor - 1) <= FIX8_MIN_ACCURACY &&
			rsz_out.pitch == net_in->in_desc[0].dim.pitch){
				yuv2rgb_resize_only_flag = 1;
			}
		if (yuv2rgb_resize_only_flag) {
			rsz_out.data_addr = net_in->in_desc[0].addr;
			printf("===================================================\n");
		} else {
			rsz_out_mem.size = rsz_out.shape.p * rsz_out.shape.d * rsz_out.shape.h * rsz_out.pitch;
			if (cavalry_mem_alloc(&rsz_out_mem.size, &rsz_out_mem.phys, &rsz_out_mem.virt, 0) < 0) {
				printf("cavalry_mem_alloc rsz_out_mem err\n");
				return -1;
			}
			rsz_out.data_addr = rsz_out_mem.phys;
		}
	}
	vproc_resize(&rsz_in, &rsz_out);
	//////////////////////////////////////////////////////////////////////////////////
	if (yuv2rgb_resize_only_flag == 0) {
		if (vproc_init_flag) {
			dtcvt_in.shape.p = rsz_out.shape.p;
			dtcvt_in.shape.d = rsz_out.shape.d;
			dtcvt_in.shape.h = rsz_out.shape.h;
			dtcvt_in.shape.w = rsz_out.shape.w;
			dtcvt_in.data_addr = rsz_out.data_addr;
			dtcvt_in.data_format.sign = rsz_out.data_format.sign;
			dtcvt_in.data_format.datasize = rsz_out.data_format.datasize;
			dtcvt_in.data_format.exp_offset = rsz_out.data_format.exp_offset;
			dtcvt_in.data_format.exp_bits = rsz_out.data_format.exp_bits;
			dtcvt_in.pitch = rsz_out.pitch;

			dtcvt_out.shape.p = dtcvt_in.shape.p;
			dtcvt_out.shape.d = dtcvt_in.shape.d;
			dtcvt_out.shape.h = dtcvt_in.shape.h;
			dtcvt_out.shape.w = dtcvt_in.shape.w;
			dtcvt_out.data_format.sign = 1; // Convert fix8 to fp16
			dtcvt_out.data_format.datasize = 1;
			dtcvt_out.data_format.exp_offset = 0;
			dtcvt_out.data_format.exp_bits = 4;
			dtcvt_out.pitch = ROUND_UP((dtcvt_out.shape.w *
				(1 << dtcvt_out.data_format.datasize)), CAVALRY_PORT_PITCH_ALIGN);
			printf("scale1 output data dimension: %d, %d, %d, %d, pitch: %d, data_format: "
				"%d, %d, %d, %d\n",
				dtcvt_out.shape.p,
				dtcvt_out.shape.d,
				dtcvt_out.shape.h,
				dtcvt_out.shape.w,
				dtcvt_out.pitch,
				dtcvt_out.data_format.sign,
				dtcvt_out.data_format.datasize,
				dtcvt_out.data_format.exp_offset,
				dtcvt_out.data_format.exp_bits);
			dtcvt_out_mem.size = dtcvt_out.shape.p * dtcvt_out.shape.d * dtcvt_out.shape.h * dtcvt_out.pitch;
			if (cavalry_mem_alloc(&dtcvt_out_mem.size, &dtcvt_out_mem.phys,
				&dtcvt_out_mem.virt, 0) < 0) {
				printf("cavalry_mem_alloc dtcvt_out_mem err\n");
				return -1;
			}
			dtcvt_out.data_addr = dtcvt_out_mem.phys;
		}
		vproc_dtcvt(&dtcvt_in, &dtcvt_out); // Convert fix8 to fp16 for submean
		//////////////////////////////////////////////////////////////////////////////////
		if (vproc_init_flag) {
			submean_in.shape.p = dtcvt_out.shape.p;
			submean_in.shape.d = dtcvt_out.shape.d;
			submean_in.shape.h = dtcvt_out.shape.h;
			submean_in.shape.w = dtcvt_out.shape.w;
			submean_in.data_format.sign = dtcvt_out.data_format.sign;
			submean_in.data_format.datasize = dtcvt_out.data_format.datasize;
			submean_in.data_format.exp_offset = dtcvt_out.data_format.exp_offset;
			submean_in.data_format.exp_bits = dtcvt_out.data_format.exp_bits;
			submean_in.pitch = dtcvt_out.pitch;
			submean_in.data_addr = dtcvt_out.data_addr;

			submean_mean.shape.p = submean_in.shape.p;
			submean_mean.shape.d = submean_in.shape.d;
			submean_mean.shape.h = submean_in.shape.h;
			submean_mean.shape.w = submean_in.shape.w;
			submean_mean.data_format.sign = 1;
			submean_mean.data_format.datasize = 1;
			submean_mean.data_format.exp_offset = 0;
			submean_mean.data_format.exp_bits = 4;
			submean_mean.pitch = submean_in.pitch;
			submean_mean_mem.size = submean_mean.shape.p * submean_mean.shape.d * submean_mean.shape.h * submean_mean.pitch;
			printf("submean mean data dimension: %d, %d, %d, %d, pitch: %d, data_format: "
				"%d, %d, %d, %d\n",
				submean_mean.shape.p,
				submean_mean.shape.d,
				submean_mean.shape.h,
				submean_mean.shape.w,
				submean_mean.pitch,
				submean_mean.data_format.sign,
				submean_mean.data_format.datasize,
				submean_mean.data_format.exp_offset,
				submean_mean.data_format.exp_bits);

			if (cavalry_mem_alloc(&submean_mean_mem.size,
				&submean_mean_mem.phys, &submean_mean_mem.virt, 0) < 0) {
				printf("cavalry_mem_alloc err\n");
				return -1;
			}
			submean_mean.data_addr = submean_mean_mem.phys;
			if (strlen(mean_name) != 0) {
				if (load_mean_binary(mean_name, submean_mean_mem.virt,
					&submean_mean, &submean_mean_mem.size) < 0) {
					printf("load submean_mean input fails!\n");
					return -1;
				}
			}
			submean_out.shape.p = submean_in.shape.p;
			submean_out.shape.d = submean_in.shape.d;
			submean_out.shape.h = submean_in.shape.h;
			submean_out.shape.w = submean_in.shape.w;
			submean_out.data_format.sign = submean_in.data_format.sign;
			submean_out.data_format.datasize = submean_in.data_format.datasize;
			submean_out.data_format.exp_offset = submean_in.data_format.exp_offset;
			submean_out.data_format.exp_bits = submean_in.data_format.exp_bits;
			submean_out.pitch = submean_in.pitch;
			printf("submean output data dimension: %d, %d, %d, %d, pitch: %d, data_format: "
				"%d, %d, %d, %d\n",
				submean_out.shape.p,
				submean_out.shape.d,
				submean_out.shape.h,
				submean_out.shape.w,
				submean_out.pitch,
				submean_out.data_format.sign,
				submean_out.data_format.datasize,
				submean_out.data_format.exp_offset,
				submean_out.data_format.exp_bits);

			submean_out_mem.size = submean_out.shape.p * submean_out.shape.d * submean_out.shape.h * submean_out.pitch;
			if (cavalry_mem_alloc(&submean_out_mem.size,
				&submean_out_mem.phys, &submean_out_mem.virt, 0) < 0) {
				printf("cavalry_mem_alloc err\n");
				return -1;
			}
			submean_out.data_addr = submean_out_mem.phys;
		}
		vproc_submean(&submean_in, &submean_mean, &submean_out);
		//////////////////////////////////////////////////////////////////////////////////
		if (vproc_init_flag) {
			scale_in.shape.p = submean_out.shape.p;
			scale_in.shape.d = submean_out.shape.d;
			scale_in.shape.h = submean_out.shape.h;
			scale_in.shape.w = submean_out.shape.w;
			scale_in.data_format.sign = submean_out.data_format.sign;
			scale_in.data_format.datasize = submean_out.data_format.datasize;
			scale_in.data_format.exp_offset = submean_out.data_format.exp_offset;
			scale_in.data_format.exp_bits = submean_out.data_format.exp_bits;
			scale_in.pitch = submean_out.pitch;
			scale_in.data_addr = submean_out.data_addr;

			scale_out.shape.p = scale_in.shape.p;
			scale_out.shape.d = scale_in.shape.d;
			scale_out.shape.h = scale_in.shape.h;
			scale_out.shape.w = scale_in.shape.w;
			scale_out.data_format.sign = net_in->in_desc[0].data_fmt.sign;
			scale_out.data_format.datasize = net_in->in_desc[0].data_fmt.size;
			scale_out.data_format.exp_offset = net_in->in_desc[0].data_fmt.expoffset;
			scale_out.data_format.exp_bits = net_in->in_desc[0].data_fmt.expbits;
			scale_out.pitch = ROUND_UP(scale_out.shape.w *
				(1 << scale_out.data_format.datasize), CAVALRY_PORT_PITCH_ALIGN);
			scale_out.data_addr = net_in->in_desc[0].addr;
			printf("scale output data dimension: %d, %d, %d, %d, pitch: %d, data_format: "
				"%d, %d, %d, %d\n",
				scale_out.shape.p,
				scale_out.shape.d,
				scale_out.shape.h,
				scale_out.shape.w,
				scale_out.pitch,
				scale_out.data_format.sign,
				scale_out.data_format.datasize,
				scale_out.data_format.exp_offset,
				scale_out.data_format.exp_bits);
			if (scale_out.pitch != net_in->in_desc[0].dim.pitch) {
				printf("Error: Pitch(%d) != %d, please check cavalry binary input dim!\n",
						scale_out.pitch, net_in->in_desc[0].dim.pitch);
				return -1;
			}
			printf("===================================================\n");
		}
		vproc_scale_ext(&scale_in, &scale_out, scale_factor);
	}
	//////////////////////////////////////////////////////////////////////////////////
	vproc_init_flag = 0;
	return 0;
}

static int start_neural_network(struct nnctrl_param *pctl)
{
	struct nnctrl_version ver;
	struct net_match *pnet;
	struct net_cfg net_cf;
	struct net_input_cfg net_in;
	struct net_output_cfg net_out;
	struct net_result net_ret;
	int net_id = 0;
	int rval = 0;
	memset((void *)&net_cf, 0, sizeof(struct net_cfg));
	memset((void *)&net_in, 0, sizeof(struct net_input_cfg));
	memset((void *)&net_out, 0, sizeof(struct net_output_cfg));
	memset((void *)&net_ret, 0, sizeof(struct net_result));

	if (nnctrl_get_version(&ver) < 0) {
		printf("nnctrl get version err");
		return -1;
	}

	if (nnctrl_init(pctl->fd_cav, pctl->verbose) < 0) {
		printf("nnctrl_init err\n");
		return -1;
	}

	pnet = &pctl->net_pair[0];
	net_cf.net_file = pnet->net_name;
	net_cf.verbose = pnet->verbose;
	net_cf.reuse_mem = pnet->reuse_mem;

	do {
		if (set_net_io_cfg(pnet, &net_in, &net_out) < 0) {
			rval = -1;
			break;
		}
		net_id = nnctrl_init_net(&net_cf, &net_in, NULL);
		if (net_id < 0) {
			printf("nnctrl_init_net err\n");
			rval = -1;
			break;
		} else {
			if (net_cf.net_mem_total == 0) {
				printf("nnctrl_init_net get total size is zero\n");
				rval = -1;
				break;
			} else {
				pnet->net_id = net_id;
			}
		}
		pnet->net_m.mem_size = net_cf.net_mem_total;
		if (alloc_cv_mem(&pnet->net_m.mem_size,
						&pnet->net_m.phy_addr, &pnet->net_m.virt_addr) < 0) {
			printf("alloc_cv_mem err\n");
			rval = -1;
			break;
		} else {
			if (pnet->net_m.virt_addr == NULL) {
				printf("alloc_cv_mem is NULL\n");
				rval = -1;
				break;
			}
		}
		if (nnctrl_load_net(net_id, &pnet->net_m, &net_in, &net_out) < 0) {
			printf("nnctrl_load_net err\n");
			rval = -1;
			break;
		}
		if (cavalry_mem_sync_cache(pnet->net_m.mem_size, pnet->net_m.phy_addr, 1, 0) < 0) {
			printf("cavalry_mem_sync_cache err\n");
		}
		if (get_net_io_cfg(pnet, &net_in, &net_out) < 0) {
			printf("get_net_io_cfg err\n");
			rval = -1;
			break;
		}

		while (live_mode_flag) {
			if (get_network_input(&net_in) < 0) {
				printf("get_network_input err\n");
				rval = -1;
				break;
			}
			rval = nnctrl_run_net(net_id, &net_ret, NULL, &net_in, NULL);
			if (rval < 0) {
				if (rval == -EAGAIN) {
					do {
						rval = nnctrl_resume_net(pnet->net_id, &net_ret);
						if (rval == -EINTR) {
							printf("interrupt by signal in resume\n");
							break;
						}
					} while (rval == -EAGAIN);
				} else if (rval == -EINTR) {
					printf("interrupt by signal in run\n");
					break;
				} else {
					printf("nnctrl_run_net failed at frame_id [%ld], ret: %d\n", frame_id, rval);
					rval = -1;
					break;
				}
			}

			/*if (frame_id == 0 && send_desc_flag) {
				if (send_network_output_desc(&net_out) < 0) {
					printf("send_network_output err\n");
					rval = -1;
					break;
				}
			}*/

			/*if (send_network_output(&net_out) < 0) {
				printf("send_network_output err\n");
				rval = -1;
				break;
			}*/
			printf("Frame_id = %ld, vp_time: %.5f ms\n", frame_id, net_ret.vp_time_us / 1000);
			frame_id++;
		}
		if (rval < 0) {
			printf("nnctrl_run_net err\n");
			break;
		}
	} while (0);

	if (nnctrl_exit_net(0) < 0) {
		printf("nnctrl_exit_net err\n");
		return -1;
	}

	return rval;
}



ambarella :: ambarella()
{
    return;
}

ambarella :: ~ambarella()
{
    return;
}

void ambarella :: set_device(deie_device device)
{
    if(device = DEIE_DEVICE_CPU)
    {
        dev = "CPU";
    }
    else if(device = DEIE_DEVICE_GPU)
    {
        dev = "GPU";
    }
    else
    {
        dev = "unknown";
        return;
    }
}
    
  
void ambarella :: set_video_file_input(deie_file_input *in)
{

}

void ambarella :: set_img_file_input(deie_file_input *in)
{       
    infer_in = in;
}

void ambarella :: set_camera_input()
{

}

void ambarella :: set_stream_input()
{

}

void ambarella :: prepare_model(deie_model_info minfo)
{
    std::string model_path = minfo.path;
    //std::string device = minfo.device_type;

    struct nnctrl_param *pctrl = &G_nnctrl;
    //struct vproc_version ver;
    uint32_t size = 0;

    if (start_neural_network(pctrl) < 0) {
            printf("start nets err\n");
    }

}

void ambarella :: run_inference(int *y, deie_io_desc *ptr[])
{

    cout<<"ambarella inference function"<<endl;
}

