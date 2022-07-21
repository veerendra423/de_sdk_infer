/*
 * ambas_imgproc_arch.h
 *
 * History:
 *	2012/10/10 - [Cao Rongrong] created file
 *	2013/12/12 - [Jian Tang] modified file
 *
 * Copyright (c) 2016 Ambarella International LP
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP.
 *
 * This file includes sample code and is only for internal testing and evaluation.  If you
 * distribute this sample code (whether in source, object, or binary code form), it will be
 * without any warranty or indemnity protection from Ambarella International LP or its affiliates.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __AMBAS_IMGPROC_ARCH_H__
#define __AMBAS_IMGPROC_ARCH_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

#define IMG_MAX_VIN_CHANNEL_NUM (8)
#define MAX_3A_STATS_SLICE_ROW	(2)
#define MAX_3A_STATS_SLICE_COL		(2)
#define	MAX_SLICE_FOR_STAT			(8)
#define MAX_STATS_FRAME_NUM				(2)

#define	INVALID_AAA_DATA_ENTRY		(0xFF)
#define	RGB_AAA_DATA_BLOCK			(2176)
#define	CFA_AAA_DATA_BLOCK			(12672)
#define	VIN_AAA_DATA_BLOCK			(2176)

#define	MAX_EXPOSURE_NUM		(3)

#define	SENSOR_HIST_ROW_NUM		(2)
#define	SENSOR_HIST_DATA_PITCH	(2080 * 2)
#define	SENSOR_HIST_DATA_BLOCK	(SENSOR_HIST_DATA_PITCH * SENSOR_HIST_ROW_NUM * 2)
#define VIN_HISTOGRAM_BIN_NUM	 (128)
#define HIST_BIN_NUM			(64)

#define COMP_LUT_ENTRY_NUM 		(45)
#define DECOMP_LUT_ENTRY_NUM 	(145)



typedef struct{
	// 1 u32
	u16 awb_tile_col_start;
	u16 awb_tile_row_start;
	// 2 u32
	u16 awb_tile_width;
	u16 awb_tile_height;
	// 3 u32
	u16 awb_tile_active_width;
	u16 awb_tile_active_height;
	//4 u32
	u16 awb_rgb_shift;
	u16 awb_y_shift;
	//5 u32
	u16 awb_min_max_shift;
	u16 ae_tile_col_start;
	//6 u32
	u16 ae_tile_row_start;
	u16 ae_tile_width;
	//7 u32
	u16 ae_tile_height;
	u16 ae_y_shift;
	//8 u32
	u16 ae_linear_y_shift;
	u16 ae_min_max_shift;

	//9 u32
	u16 af_tile_col_start;
	u16 af_tile_row_start;

	//10 u32
	u16 af_tile_width;
	u16 af_tile_height;

	//11 u32
	u16 af_tile_active_width;
	u16 af_tile_active_height;

	//12 u32
	u16 af_y_shift;
	u16 af_cfa_y_shift;

	//13 u32
	u8  awb_tile_num_col;
	u8  awb_tile_num_row;
	u8  ae_tile_num_col;
	u8  ae_tile_num_row;

	//14 u32
	u8  af_tile_num_col;
	u8  af_tile_num_row;
	u8 total_slices_x;
	u8 total_slices_y;

	//15 u32
	u8 slice_index_x;
	u8 slice_index_y;
	u16 slice_width;

	//16 u32
	u16 slice_height;
	u16 slice_start_x;

	//17 u32
	u32 slice_start_y : 16;
	u32 chan_index : 4;
	u32 fusion_ir_step : 1;
	u32 reserved : 11;

	//18
	u32 raw_pic_seq_num;  // sequence number of raw picture used in producing this block of AAA results
	//19
	u32 iso_config_tag;
	u32 reserved1[9];

	//NOTE: expanded by ARM to support PTS
	u64 mono_pts;
	u32 dsp_pts;
	u32 reserved2;  // max 128 bytes
}aaa_tile_info_t;

typedef struct
{
  u32 vin_stats_type : 8; /* 0: main; 1: hdr; 2: hdr2 */
  u32 chan_index : 3;
  u32 is_rgbir : 1;
  u32 fusion_ir_step : 1;
  u32 reserved_0 : 3;
  u32 total_exposures : 8;
  u32 blend_index : 8; /* exposure no. */

  u8  total_slice_in_x;
  u8  slice_index_x;
  u8  total_slice_in_y;
  u8  slice_index_y;

  u16 vin_stats_slice_left;
  u16 vin_stats_slice_width;

  u16 vin_stats_slice_top;
  u16 vin_stats_slice_height;

  u32 reserved[24];

  //NOTE: expanded by ARM to support PTS
  u64 mono_pts;
  u32 dsp_pts;
  u32 reserved2;  // max 128 bytes
}vin_stats_config_info_t ;

struct af_stat {
	u16 sum_fy;
	u16 sum_fv1;
	u16 sum_fv2;
};

struct rgb_histogram_stat {
	u32 his_bin_y[HIST_BIN_NUM];
	u32 his_bin_r[HIST_BIN_NUM];
	u32 his_bin_g[HIST_BIN_NUM];
	u32 his_bin_b[HIST_BIN_NUM];
};

struct rgb_aaa_stat {
	aaa_tile_info_t		aaa_tile_info;
	u16			frame_id;
	struct af_stat		af_stat[96];
	u16			ae_sum_y[96];
	struct rgb_histogram_stat	histogram_stat;
	u8			reserved[249];
};


struct cfa_awb_stat {
	u16	sum_r;
	u16	sum_g;
	u16	sum_b;
	u16	count_min;
	u16	count_max;
};

struct cfa_ae_stat {
	u16	lin_y;
	u16	count_min;
	u16	count_max;
};

struct cfa_af_stat {
	u16	sum_fy;
	u16	sum_fv1;
	u16	sum_fv2;
};

struct cfa_histogram_stat {
	u32	his_bin_r[HIST_BIN_NUM];
	u32	his_bin_g[HIST_BIN_NUM];
	u32	his_bin_b[HIST_BIN_NUM];
	u32	his_bin_y[HIST_BIN_NUM];
};

struct cfa_aaa_stat {
	aaa_tile_info_t 	aaa_tile_info;
	u16       frame_id;
	struct cfa_awb_stat	awb_stat[1024];
	struct cfa_ae_stat	ae_stat[96];
	struct af_stat		af_stat[96];
	struct cfa_histogram_stat	histogram_stat;
	u8			reserved[121];
};

struct vin_hist_stat{
	u32 hist_bin_r[VIN_HISTOGRAM_BIN_NUM];
	u32 hist_bin_g[VIN_HISTOGRAM_BIN_NUM];
	u32 hist_bin_b[VIN_HISTOGRAM_BIN_NUM];
	u32 hist_bin_ir[VIN_HISTOGRAM_BIN_NUM];
};

struct vin_aaa_stat{
	vin_stats_config_info_t vin_stats_config_info;
	struct vin_hist_stat vin_histogram_stats;
};

struct contrast_enhance_info{
	u16	low_pass_radius;	// 0: 16x, 1: 32x, 2: 60x
	u16	enhance_gain;	// unit: 1024; 0 : off
};

struct img_extra_raw_info {
	u8 vinc_id;			/* Vin controller id*/
	u8 reserved[3];
	u32 pitch;			/* Pitch of extra raw data */
	u16 height;			/* Height of extra raw data */
	u8 top_lines;			/* Top lines of extra raw data */
	u8 bottom_lines;		/* Bottom lines of extra raw data */
	u32 dsp_pts;			/* Intermediate PTS from DSP */
	u64 mono_pts;			/* Monotonic PTS of the extra raw data */
	unsigned long data_addr_offset;		/* Data addr offset of extra raw data within IAV_PART_EXTRA_RAW */
};

struct img_statistics {
	u8	*enable_pts;
	u8	*rgb_data_valid;
	u8	*cfa_data_valid;
	u8	*sensor_data_valid;
	u8	*vin_data_valid;
	void	*rgb_statis;
	void	*cfa_statis;
	void	*sensor_statis;
	void	*vin_statis;
	u8	*resend_all_cfg;
	u8	*query_extra_raw;
	u8	*extra_raw_valid;
	void	*extra_raw;
};

struct idsp_retired_iso_cfg_tag {
	u32 tag[IMG_MAX_VIN_CHANNEL_NUM];
};

struct aaa_statistics_ex {
	u8 af_horizontal_filter1_mode;
	u8 af_horizontal_filter1_stage1_enb;
	u8 af_horizontal_filter1_stage2_enb;
	u8 af_horizontal_filter1_stage3_enb;
	s16 af_horizontal_filter1_gain[7];
	u16 af_horizontal_filter1_shift[4];
	u16 af_horizontal_filter1_bias_off;
	u16 af_horizontal_filter1_thresh;
	u16 af_vertical_filter1_thresh;
	u16 af_tile_fv1_horizontal_shift;
	u16 af_tile_fv1_vertical_shift;
	u16 af_tile_fv1_horizontal_weight;
	u16 af_tile_fv1_vertical_weight;

	u8 af_horizontal_filter2_mode;
	u8 af_horizontal_filter2_stage1_enb;
	u8 af_horizontal_filter2_stage2_enb;
	u8 af_horizontal_filter2_stage3_enb;
	s16 af_horizontal_filter2_gain[7];
	u16 af_horizontal_filter2_shift[4];
	u16 af_horizontal_filter2_bias_off;
	u16 af_horizontal_filter2_thresh;
	u16 af_vertical_filter2_thresh;
	u16 af_tile_fv2_horizontal_shift;
	u16 af_tile_fv2_vertical_shift;
	u16 af_tile_fv2_horizontal_weight;
	u16 af_tile_fv2_vertical_weight;
};
#if 0
#define DUMP_IDSP_0		0
#define DUMP_IDSP_1		1
#define DUMP_IDSP_2		2
#define DUMP_IDSP_3		3
#define DUMP_IDSP_4		4
#define DUMP_IDSP_5		5
#define DUMP_IDSP_6		6
#define DUMP_IDSP_7		7
#define DUMP_IDSP_100		100
#define DUMP_FPN		200
#define DUMP_VIGNETTE		201
#define MAX_DUMP_BUFFER_SIZE	256*1024
#endif
typedef struct idsp_config_info_s {
	u8*		addr;
	u32		addr_long;
	u32		id_section;
}idsp_config_info_t;


struct raw2enc_raw_feed_info
{
	u32 raw_daddr_offset;		/* offset from sensor raw start daddr to the start address of ik */
	u32 raw_hdec_daddr_offset;
	u32 preblend_daddr_offset;
	u32 raw_size;	/* offset from sensor_raw_start_daddr to the start address of the next frame in DRAM */
	u32 raw_hdec_size;
	u32 preblend_size;
	u32 raw_dpitch : 16;		/* buffer pitch in bytes */
	u32 raw_hdec_dpitch : 16;		/* buffer pitch in bytes */
	u32 preblend_dpitch : 16;		/* buffer pitch in bytes */
	u32 num_frames : 8;	/* num of frames stored in DRAM starting from sensor_raw_start_daddr */
	u32 reserved : 8;
};

typedef struct idsp_iso_config_update_flag_s {
	u32 iso_config_common_update : 1 ;
	u32 iso_config_color_update : 1 ;
	u32 iso_config_mctf_update : 1 ;
	u32 iso_config_step1_update : 1 ;
	u32 iso_config_aaa_update : 1 ; // AAA setup update
	u32 iso_config_extra_update : 1 ;
	u32 iso_config_motion_update : 1 ;
	u32 iso_config_exp_update : 1 ;
	u32 reserved : 24 ;
} idsp_iso_config_update_flag_t;

typedef struct idsp_iso_config_s {
	u32 ik_id;
	unsigned long iso_addr_offset;

	/* config update flags */
	union {
		idsp_iso_config_update_flag_t flag;
		u32 word;
	} loadcfg_type;
} idsp_iso_config_t;

typedef struct idsp_hdr_config_s {
	u32 raw_offset[MAX_EXPOSURE_NUM];
	u8 expo_num;
} idsp_hdr_config_t;

typedef enum {
	IDSP_CFG_TYPE_ISO = (1 << 0),
	IDSP_CFG_TYPE_HDR = (1 << 1),
	IDSP_CFG_TYPE_NUM = 2,
} IDSP_CFG_TYPE;

typedef struct idsp_config_s {
	u32 chan_id;
	u32 cfg_map;
	idsp_iso_config_t iso_cfg;
	idsp_hdr_config_t hdr_cfg;
} idsp_config_t;

typedef struct idsp_delay_info_s {
	u32 delay[IMG_MAX_VIN_CHANNEL_NUM]; // unit: vsync
} idsp_delay_info_t;

struct img_statistics_report_rate {
	u8 multi_factor[IMG_MAX_VIN_CHANNEL_NUM];
	u8 div_factor[IMG_MAX_VIN_CHANNEL_NUM];
};

typedef struct {
	u32 cfg_buf_addr;
	u32 cfg_buf_size;
} debug_cfg_info_t;

typedef struct {
	u32 y_addr;
	u32 uv_addr;
	u16 y_pitch;
	u16 y_width;
	u16 y_height;
	u16 uv_pitch;
	u16 uv_width;
	u16 uv_height;
} debug_yuv_info_t;

typedef struct {
	u32 addr;
	u16 pitch;
	u16 width;
	u16 height;
	u16 reserved;
} debug_buf_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t sec4_cfg;
	debug_cfg_info_t sec2_cfg;

	debug_yuv_info_t sec2_raw2yuv;
	debug_buf_info_t sec2_me1;
} debug_c2y_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t me1_smooth_sec2_cfg;
	debug_cfg_info_t me1_smooth_sec6_cfg;
	debug_cfg_info_t me1_smooth_sec5_cfg;

	debug_buf_info_t vwarp_me1;
    debug_buf_info_t me1_dn3;
} debug_me1_smooth_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t sec2_cfg[3]; /* 0: mda, 1: mdb, 2: mdc */
	debug_cfg_info_t sec6_cfg;
	debug_cfg_info_t sec5_cfg;
	debug_cfg_info_t mctf_cfg;

	debug_buf_info_t md_mb_b;
	debug_buf_info_t md_mb_c;
	debug_buf_info_t mo_asf;

    debug_cfg_info_t ALPHA_MO1_cfg;
    debug_cfg_info_t ALPHA_MO_cfg;

    debug_buf_info_t ALPHA_MO_B;
    debug_buf_info_t ALPHA_MO_C;
} debug_md_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t mctf_cfg;
	debug_cfg_info_t mcts_cfg;

	debug_buf_info_t sec3_me1;
	debug_yuv_info_t mctf;
	debug_yuv_info_t mcts;
	debug_buf_info_t mctf_2bit;
} debug_vwarp_mctf_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t C2Y_IR_ce_cfg;
	debug_cfg_info_t C2Y_IR_cfg;
	debug_cfg_info_t MonoDn1_cfg;
	debug_cfg_info_t MonoDn2_cfg;

	debug_buf_info_t C2Y_IR;
	debug_buf_info_t C2Y_IR_me1;
	debug_buf_info_t MonoDn2;
} debug_mono_1_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t C2Y_RGB_ce_cfg;
	debug_cfg_info_t C2Y_RGB_cfg;
	debug_cfg_info_t FusCDown_cfg;

	debug_yuv_info_t C2Y_RGB;
	debug_buf_info_t C2Y_RGB_me1;
	debug_buf_info_t FusCDown;
} debug_mono_2_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t RGB_Dn1_cfg;
	debug_cfg_info_t PadME1_cfg;
	debug_cfg_info_t FusEdge_mcts_cfg;
	debug_cfg_info_t FusEdgeDn1_cfg;
	debug_cfg_info_t FusEdgeDn2_cfg;
	debug_cfg_info_t Alpha1_cfg;

	debug_buf_info_t RGB_Dn1;
	debug_buf_info_t Alpha1;
} debug_mono_3_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t RGB_Dn2_cfg;
	debug_cfg_info_t RGB_Dn3_cfg;
	debug_cfg_info_t RGB_Smh_cfg;
	debug_cfg_info_t MonoDn3_cfg;
	debug_cfg_info_t MonoSmhUp_cfg;

	debug_buf_info_t RGB_Smh;
	debug_buf_info_t MonoSmhUp;
} debug_mono_4_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t Alpha2_cfg;
	debug_cfg_info_t ToUV_cfg;
	debug_cfg_info_t RGBUp_cfg;

	debug_buf_info_t Alpha2_Blend;
} debug_mono_5_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t C_FiltB_luma_cfg;
	debug_cfg_info_t C_FiltB_cfg;
	debug_cfg_info_t C_MCTFA_mctf_cfg;
	debug_cfg_info_t C_MCTFA_mcts_cfg;

	debug_buf_info_t C_up4VWarp;
} debug_mono_6_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t Alpha_cfg;
	debug_cfg_info_t Alpha_MCTF_mctf_cfg;
	debug_cfg_info_t Alpha_MCTF_mcts_cfg;

	debug_buf_info_t Alpha_MCTF_mctf;
	debug_buf_info_t Alpha_MCTF_mcts;
} debug_mono_7_info_t;

typedef struct {
	u32 cap_seq_no;

	debug_cfg_info_t Alpha_SmthUp_cfg;
	debug_cfg_info_t Freq_Blend_mctf_cfg;
	debug_cfg_info_t Freq_Blend_mcts_cfg;

	debug_buf_info_t Freq_Blend;
} debug_mono_8_info_t;

typedef struct {
	u32 chan_id : 8;
	u32 reserved : 24;
	debug_c2y_info_t c2y;
	debug_vwarp_mctf_info_t vwarp_mctf;
	debug_me1_smooth_info_t me1_smooth;
	debug_md_info_t md;
} liso_debug_info_t;

typedef struct {
	u32 chan_id : 8;
	u32 reserved : 24;
	debug_vwarp_mctf_info_t vwarp_mctf;
	debug_me1_smooth_info_t me1_smooth;
	debug_md_info_t md;
	debug_mono_1_info_t mono_1;
	debug_mono_2_info_t mono_2;
	debug_mono_3_info_t mono_3;
	debug_mono_4_info_t mono_4;
	debug_mono_5_info_t mono_5;
	debug_mono_6_info_t mono_6;
	debug_mono_7_info_t mono_7;
	debug_mono_8_info_t mono_8;
} fusion_debug_info_t;

typedef struct {
	u32 cap_seq_no;
	debug_cfg_info_t blend_cfg;
	debug_buf_info_t blend;
} debug_blend0_info_t;

typedef debug_blend0_info_t debug_blend1_info_t;

typedef struct {
	u32 cap_seq_no;
	debug_yuv_info_t yuv[2];
	debug_buf_info_t md_raw[6];
} debug_yuv_nn_info_t;

typedef struct {
	u32 cap_seq_no;
	debug_buf_info_t mo[2];
} debug_md_nn_info_t;

typedef struct {
	u32 chan_id : 8;
	u32 reserved : 24;
} ik_debug_header_t;


typedef struct {
	ik_debug_header_t header;
	debug_blend0_info_t blend0;
	debug_blend1_info_t blend1;
	debug_yuv_nn_info_t yuv_nn;
	debug_md_nn_info_t md_nn;
	debug_vwarp_mctf_info_t vwarp_mctf;
} ik_nn_debug_info_t;


struct img_idsp_debug_info {
	u32 chan_id;
	union {
		liso_debug_info_t debug_info;
		fusion_debug_info_t fusion_debug_info;
		ik_nn_debug_info_t nn_debug_info;
	};
};

typedef  enum {
	LISO_SHARE				= 0x00,
	LISO_CALIB				= 0x01,
	LISO_COLOR				= 0x02,
	LISO_RAW2YUV			= 0x03,
	LISO_EXTRA				= 0x04,
	LISO_FLOW				= 0x05,
	LISO_MCTF				= 0x06,
	LISO_ME1_SMOOTH			= 0x07,
	LISO_MD_A				= 0x08,
	LISO_MD_B				= 0x09,
	LISO_MD_C				= 0x0A,
	LISO_MD_MB				= 0x0B,
	LISO_HDR_CE				= 0x0C,
	LISO_EXPOSURE_0			= 0x0D,
	LISO_EXPOSURE_1			= 0x0E,
	LISO_EXPOSURE_2			= 0x0F,
	LISO_PREP_CE			= 0x10,
	LISO_VIN_STAT_CROP		= 0x11,
	MONO_STEP_1				= 0x12,
	MONO_STEP_1_PREP_CE		= 0x13,
	MONO_STEP_2				= 0x14,
	MONO_STEP_3				= 0x15,
	MONO_STEP_4				= 0x16,
	MONO_STEP_5				= 0x17,
	MONO_STEP_6				= 0x18,
	MONO_STEP_7				= 0x19,
	MONO_STEP_8				= 0x1A,
	MONO_CALIB				= 0x1B,
	MONO_COLOR				= 0x1C,
	MONO_RAW2YUV			= 0x1D,
	MONO_EXTRA				= 0x1E,
	MONO_EXPOSURE_0			= 0x1F,
	MONO_EXPOSURE_1			= 0x20,
	MONO_EXPOSURE_2			= 0x21,
	MONO_YUV				= 0x22,
	MONO_MCTF				= 0x23,
	POST_SHARPEN			= 0x24,
	PRE_NN_BLEND_STEP_1		= 0x25,
	PRE_NN_BLEND_STEP_2		= 0x26,
	CV2_LISO_CONFIG_ID_TOTAL= 0x27,
} LISO_CONFIG_ID;

struct img_idsp_debug_setup {
	u32 chan_id : 8;
	u32 report_enable : 1;
	u32 break_point_enable : 1;
	u32 reserved0 : 6;
	u32 break_point_cfg_id : 8;		/* enum LISO_CONFIG_ID */
	u32 reserved1 : 8;
	u32 break_point_frame_num;		/* 0xFFFFFFFF means next frame immediately */
};

#ifdef __cplusplus
}
#endif

#endif

