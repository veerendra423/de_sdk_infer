/*
 * iav_vout_ioctl.h
 *
 * History:
 *	2008/04/02 - [Oliver Li] created file
 *	2011/06/10 - [Jian Tang] modified file
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
 * this Software to Ambarella International LP
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

#ifndef __IAV_VOUT_IOCTL_H__
#define __IAV_VOUT_IOCTL_H__

/*! @file iav_vout_ioctl.h
 *  @brief This file defines video output configuration ioctl
 */


#ifdef __cplusplus
extern "C" {
#endif

#include <linux/ioctl.h>
#include "iav_vout_common.h"

/*! @addtogroup iav-ioctl-vout-helper
 *  @{
 */
#define VOUTIOC_MAGIC				'v'

#define VOUT_IO(nr)				_IO(VOUTIOC_MAGIC, nr)
#define VOUT_IOR(nr, size)			_IOR(VOUTIOC_MAGIC, nr, size)
#define VOUT_IOW(nr, size)			_IOW(VOUTIOC_MAGIC, nr, size)
#define VOUT_IOWR(nr, size)			_IOWR(VOUTIOC_MAGIC, nr, size)
/*! @} */  /* End of iav-ioctl-vout-helper */

/*! @addtogroup iav-ioctl-vout-api
 *  @{
 */

/*!
 *  This API can be used to get the VOUT device format.
 */
#define IAV_IOC_VOUT_GET_MODE			VOUT_IOR(0x00, struct voutdev_format*)

/*!
 *  This API can be used to set the VOUT device format.
 */
#define IAV_IOC_VOUT_SET_MODE			VOUT_IOW(0x01, struct voutdev_format)

/*!
 *  This API can be used to get the params of VOUT.
 */
#define IAV_IOC_VOUT_GET_PARAMS			VOUT_IOR(0x02, struct vout_params)

/*!
 *  This API can be used to set the params of VOUT.
 */
#define IAV_IOC_VOUT_SET_PARAMS			VOUT_IOW(0x03, struct vout_params)

/*!
 *  This API can be used to turn on/off VOUT.
 */
#define IAV_IOC_VOUT_SWITCH_VIDEO		VOUT_IOW(0x04, struct vout_onoff)

/*!
 *  This API can be used to get vout controller ID by video output type.
 */
#define IAV_IOC_VOUT_GET_VOUTC_ID		VOUT_IOR(0x05, int)
/*! @} */  /* End of iav-ioctl-vout-api */
/*===========================================================================*/

/*! @addtogroup iav-ioctl-vout-helper
 *  @{
 */
/*
 * general APIs	- VOUTIOC_MAGIC
 */
enum {
	// For VOUT, from 0x20 to 0x3F
	IOC_VOUT_HALT = 0x20,
	IOC_VOUT_SELECT_DEV = 0x21,
	IOC_VOUT_CONFIGURE_SINK = 0x22,
	IOC_VOUT_SELECT_FB = 0x23,
	IOC_VOUT_ENABLE_VIDEO = 0x24,
	IOC_VOUT_FLIP_VIDEO = 0x25,
	IOC_VOUT_ROTATE_VIDEO = 0x26,
	IOC_VOUT_ENABLE_CSC = 0x27,
	IOC_VOUT_CHANGE_VIDEO_SIZE = 0x28,
	IOC_VOUT_CHANGE_VIDEO_OFFSET = 0x29,
	IOC_VOUT_FLIP_OSD = 0x2A,
	IOC_VOUT_ENABLE_OSD_RESCALER = 0x2B,
	IOC_VOUT_CHANGE_OSD_OFFSET = 0x2C,
	IOC_VOUT_GET_SINK_NUM = 0x2D,
	IOC_VOUT_GET_SINK_INFO = 0x2E,
	IOC_VOUT_SYNC_IMG_OSD = 0x2F,
	IOC_VOUT_GET_CVBS_INFO = 0x30,
	IOC_VOUT_SET_CVBS_COLORBAR = 0x31,
	IOC_VOUT_SET_CVBS_BLACKLEVEL = 0x32,
	IOC_VOUT_SET_CVBS_BLANKLEVEL = 0x33,
	IOC_VOUT_SET_CVBS_SYNCLEVEL = 0x34,
	IOC_VOUT_SET_CVBS_YGAIN = 0x35,
	IOC_VOUT_SET_CVBS_CGAIN = 0x36,
	IOC_VOUT_GET_MIPI_PARAMS = 0x37,
	IOC_VOUT_SET_MIPI_TXVCMSET = 0x38,
	IOC_VOUT_SET_MIPI_TXIBCTRL = 0x39,
	IOC_VOUT_SET_MIPI_TXPIB = 0x3a,
	IOC_VOUT_SET_MIPI_TXTERM = 0x3b,
};

#define _IAV_IO(IOCTL)			_IO(VOUTIOC_MAGIC, IOCTL)
#define _IAV_IOR(IOCTL, param)		_IOR(VOUTIOC_MAGIC, IOCTL, param)
#define _IAV_IOW(IOCTL, param)		_IOW(VOUTIOC_MAGIC, IOCTL, param)
#define _IAV_IOWR(IOCTL, param)		_IOWR(VOUTIOC_MAGIC, IOCTL, param)
/*! @} */   /* End of iav-ioctl-vout-helper */

/*! @addtogroup iav-ioctl-vout-api
 *  @{
 */
#define IAV_IOC_VOUT_HALT			_IAV_IOW(IOC_VOUT_HALT, int)
#define IAV_IOC_VOUT_SELECT_DEV		_IAV_IOW(IOC_VOUT_SELECT_DEV, int)
#define IAV_IOC_VOUT_CONFIGURE_SINK	_IAV_IOW(IOC_VOUT_CONFIGURE_SINK, struct amba_video_sink_mode *)
#define IAV_IOC_VOUT_SELECT_FB		_IAV_IOW(IOC_VOUT_SELECT_FB, struct iav_vout_fb_sel_s *)
#define IAV_IOC_VOUT_ENABLE_VIDEO	_IAV_IOW(IOC_VOUT_ENABLE_VIDEO, struct iav_vout_enable_video_s *)
#define IAV_IOC_VOUT_FLIP_VIDEO		_IAV_IOW(IOC_VOUT_FLIP_VIDEO, struct iav_vout_flip_video_s *)
#define IAV_IOC_VOUT_ROTATE_VIDEO	_IAV_IOW(IOC_VOUT_ROTATE_VIDEO, struct iav_vout_rotate_video_s *)
#define IAV_IOC_VOUT_ENABLE_CSC		_IAV_IOW(IOC_VOUT_ENABLE_CSC, struct iav_vout_enable_csc_s *)
#define IAV_IOC_VOUT_CHANGE_VIDEO_SIZE		_IAV_IOW(IOC_VOUT_CHANGE_VIDEO_SIZE, struct iav_vout_change_video_size_s *)
#define IAV_IOC_VOUT_CHANGE_VIDEO_OFFSET	_IAV_IOW(IOC_VOUT_CHANGE_VIDEO_OFFSET, struct iav_vout_change_video_offset_s *)
#define IAV_IOC_VOUT_FLIP_OSD		_IAV_IOW(IOC_VOUT_FLIP_OSD, struct iav_vout_flip_osd_s *)
#define IAV_IOC_VOUT_ENABLE_OSD_RESCALER	_IAV_IOW(IOC_VOUT_ENABLE_OSD_RESCALER, struct iav_vout_enable_osd_rescaler_s *)
#define IAV_IOC_VOUT_CHANGE_OSD_OFFSET		_IAV_IOW(IOC_VOUT_CHANGE_OSD_OFFSET, struct iav_vout_change_osd_offset_s *)
#define IAV_IOC_VOUT_SYNC_IMG_OSD	_IAV_IOR(IOC_VOUT_SYNC_IMG_OSD, struct iav_vout_sync_img_osd_s *)
#define IAV_IOC_VOUT_GET_SINK_NUM	_IAV_IOR(IOC_VOUT_GET_SINK_NUM, int *)
#define IAV_IOC_VOUT_GET_SINK_INFO	_IAV_IOR(IOC_VOUT_GET_SINK_INFO, struct amba_vout_sink_info *)
#define IAV_IOC_VOUT_CVBS_GET_PARAMS	_IAV_IOR(IOC_VOUT_GET_CVBS_INFO, struct cvbs_info)
#define IAV_IOC_VOUT_CVBS_SET_COLORBAR	_IAV_IOW(IOC_VOUT_SET_CVBS_COLORBAR, struct setval_s)
#define IAV_IOC_VOUT_CVBS_SET_BLACKLEVEL	_IAV_IOW(IOC_VOUT_SET_CVBS_BLACKLEVEL, struct setval_s)
#define IAV_IOC_VOUT_CVBS_SET_BLANKLEVEL	_IAV_IOW(IOC_VOUT_SET_CVBS_BLANKLEVEL, struct setval_s)
#define IAV_IOC_VOUT_CVBS_SET_SYNCLEVEL	_IAV_IOW(IOC_VOUT_SET_CVBS_SYNCLEVEL, struct setval_s)
#define IAV_IOC_VOUT_CVBS_SET_YGAIN	_IAV_IOW(IOC_VOUT_SET_CVBS_YGAIN, struct setval_s)
#define IAV_IOC_VOUT_CVBS_SET_CGAIN	_IAV_IOW(IOC_VOUT_SET_CVBS_CGAIN, struct setval_s)
#define IAV_IOC_VOUT_MIPI_GET_PARAMS	_IAV_IOR(IOC_VOUT_GET_MIPI_PARAMS, struct mipi_vout_info)
#define IAV_IOC_VOUT_MIPI_SET_TXVCMSET	_IAV_IOW(IOC_VOUT_SET_MIPI_TXVCMSET, struct setval_s)
#define IAV_IOC_VOUT_MIPI_SET_TXIBCTRL	_IAV_IOW(IOC_VOUT_SET_MIPI_TXIBCTRL, struct setval_s)
#define IAV_IOC_VOUT_MIPI_SET_TXPIB		_IAV_IOW(IOC_VOUT_SET_MIPI_TXPIB, struct setval_s)
#define IAV_IOC_VOUT_MIPI_SET_TXTERM		_IAV_IOW(IOC_VOUT_SET_MIPI_TXTERM, struct setval_s)
/*! @} */  /* End of iav-ioctl-vout-helper */


#define HDMIIOC_MAGIC				'h'

#define HDMI_IO(nr)				_IO(HDMIIOC_MAGIC, nr)
#define HDMI_IOR(nr, size)			_IOR(HDMIIOC_MAGIC, nr, size)
#define HDMI_IOW(nr, size)			_IOW(HDMIIOC_MAGIC, nr, size)
#define HDMI_IOWR(nr, size)			_IOWR(HDMIIOC_MAGIC, nr, size)

#define IOC_HDMI_GET_INFO			HDMI_IOR(0x00, struct hdmi_info)
#define IOC_HDMI_SET_PIB			HDMI_IOW(0x01, u32)
#define IOC_HDMI_SET_PIBIB			HDMI_IOW(0x02, u32)
#define IOC_HDMI_SET_PRET0			HDMI_IOW(0x03, u32)
#define IOC_HDMI_SET_POET1			HDMI_IOW(0x04, u32)
#define IOC_HDMI_SET_BIAS			HDMI_IOW(0x05, u32)
#define IOC_HDMI_SET_RCD			HDMI_IOW(0x06, u32)
#define IOC_HDMI_SET_AVMUTE			HDMI_IOW(0x07, u32)
#define IOC_HDMI_SET_TERM			HDMI_IOW(0x08, u32)
#define IOC_HDMI_SET_PRET1			HDMI_IOW(0x09, u32)
#define IOC_HDMI_SET_PRET2			HDMI_IOW(0x0a, u32)
#define IOC_HDMI_SET_DOUBLECUR			HDMI_IOW(0x0b, u32)

#ifdef __cplusplus
}
#endif

#endif // __IAV_IOCTL_ARCH_H__


