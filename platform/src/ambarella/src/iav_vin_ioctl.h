/*
 * iav_vin_ioctl.h
 *
 * History:
 *	2013/09/04 - [Cao Rongrong] Created file
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

#ifndef __IAV_VIN_IOCTL_H__
#define __IAV_VIN_IOCTL_H__

/*! @file iav_vin_ioctl.h
 *  @brief This file defines IAV Video Input Configuration IOCTL api.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==========================================================================*/
#include <linux/ioctl.h>
#include"iav_vin_common.h"

/*! @addtogroup iav-ioctl-vin-helper
 *  @{
 */

/* ==========================================================================*/
#define VINIOC_MAGIC				's'
#define VIN_IO(nr)				_IO(VINIOC_MAGIC, nr)
#define VIN_IOR(nr, size)			_IOR(VINIOC_MAGIC, nr, size)
#define VIN_IOW(nr, size)			_IOW(VINIOC_MAGIC, nr, size)
#define VIN_IOWR(nr, size)			_IOWR(VINIOC_MAGIC, nr, size)

enum {
	IOC_VIN_DEVINFO				= 0x01,	/*!< 0x01 */
	IOC_VIN_MODE				= 0x03,	/*!< 0x03 */
	IOC_VIN_FPS				= 0x04,	/*!< 0x04 */
	IOC_VIN_VIDEOINFO			= 0x05,	/*!< 0x05 */
	IOC_VIN_SHUTTER				= 0x06,	/*!< 0x06 */
	IOC_VIN_AGC				= 0x07,	/*!< 0x07 */
	IOC_VIN_AGC_SHUTTER			= 0x08,	/*!< 0x08 */
	IOC_VIN_DGAIN_RATIO			= 0x09,	/*!< 0x09 */
	IOC_VIN_MIRROR				= 0x0A,	/*!< 0x0A */
	IOC_VIN_EISINFO				= 0x0B,	/*!< 0x0B */
	IOC_VIN_REG				= 0x0C,	/*!< 0x0C */
	IOC_VIN_SHUTTER2ROW			= 0x0D,	/*!< 0x0D */
	IOC_VIN_WDR_AGAIN_INDEX			= 0x0E,	/*!< 0x0E */
	IOC_VIN_WDR_AGAIN_INDEX_GP		= 0x0F,	/*!< 0x0F */
	IOC_VIN_WDR_DGAIN_INDEX_GP		= 0x10,	/*!< 0x10 */
	IOC_VIN_WDR_SHUTTER_ROW_GP		= 0x11,	/*!< 0x11 */
	IOC_VIN_WDR_SHUTTER2ROW			= 0x12,	/*!< 0x12 */
	IOC_VIN_AAAINFO				= 0x13,	/*!< 0x13 */
	IOC_VIN_CHIP_STATUS			= 0x14,	/*!< 0x14 */
	IOC_VIN_WDR_ROW_GP			= 0x15,	/*!< 0x15 */
	IOC_VIN_SET_AE_CHECK			= 0x16,	/*!< 0x16 */
	IOC_VIN_PENDING_SHT_AGC 		= 0x17,	/*!< 0x17 */
	IOC_VIN_PENDING_SHT_AGC_SEQ 		= 0x18,	/*!< 0x18 */
	IOC_VIN_AAA_COMPENSATION		= 0x19,	/*!< 0x19 */
	IOC_VIN_SET_STREAM_MODE 		= 0x1A,	/*!< 0x1A */
	IOC_VIN_SET_LOW_LIGHT_MODE		= 0x1B,	/*!< 0x1B */
	IOC_VIN_SWITCH_VSRC_CTX 		= 0x1C,	/*!< 0x1C */
	IOC_VIN_LOCK_VSRC_CTX_FRAME_CNT 	= 0x1D,	/*!< 0x1D */
	IOC_VIN_UNLOCK_VSRC_CTX_FRAME_CNT 	= 0x1E,	/*!< 0x1E */
	IOC_VIN_WDR_SHUTTER2OFFSET		= 0x1F, /*!< 0x1F */
	IOC_VIN_SET_TP_MODE			= 0x20,	/*!< 0x20 */

	IOC_VIN_GLOBAL_INFO 						= 0x80,	/*!< 0x80 */
	IOC_VIN_GLOBAL_MODE						= 0x81, /*!< 0x81 */
};
/*! @} */  /* End of iav-ioctl-vin-helper */

/*! @addtogroup iav-ioctl-vin-api
 *  @{
 */
/* ==========================================================================*/
/*!
 *  This API can be used to retrieve the global VIN info, including total video source number of all VIN controllers,
 *  video source bit map of each VIN controller and so on.
 */
#define IAV_IOC_VIN_GET_GLOBAL_INFO				VIN_IOR(IOC_VIN_GLOBAL_INFO, struct vin_global_info *)

/*!
 *  This API can be used to set multiple VIN mode at the same time. If the VIN source share the same VIN controller, the VIN mode will only set once.
 */
#define IAV_IOC_VIN_SET_GLOBAL_MODE				VIN_IOW(IOC_VIN_GLOBAL_MODE, struct vindev_mode_group *)

/*!
 *  This API can be used to retrieve the current active source identifier, the source type (sensor or YUV input), and the name of the source.
 */
#define IAV_IOC_VIN_GET_DEVINFO				VIN_IOR(IOC_VIN_DEVINFO, struct vindev_devinfo *)

/*!
 *  This API can be used to set the current active source mode.
 *  For video mode, @b AMBA_VIDEO_MODE_AUTO will detect the input format, and will select the default video mode for the sensor.
 *  Please refer to @link iav_common.h iav_common.h @endlink for more video modes.
 */
#define IAV_IOC_VIN_SET_MODE					VIN_IOW(IOC_VIN_MODE, struct vindev_mode *)

/*!
 *  This API can be used to get the current active source mode.
 *  For video mode, @b AMBA_VIDEO_MODE_AUTO will detect the input format, and will select the default video mode for the sensor.
 *  Please refer to @link iav_common.h iav_common.h @endlink for more video modes.
 */
#define IAV_IOC_VIN_GET_MODE					VIN_IOR(IOC_VIN_MODE, struct vindev_mode *)

/*!
 *  This API can be used to set the current active source video frame rate. This API is valid only when the source is RGB sensor input.
 *  The frame rate (frame length) can be directly compared with shutter time.
 *  Please refer to @link iav_common.h iav_common.h @endlink for more frame rate macro definitions.
 */
#define IAV_IOC_VIN_SET_FPS						VIN_IOW(IOC_VIN_FPS, struct vindev_fps *)

/*!
 *  This API can be used to get the current active source video frame rate. This API is valid only when the source is RGB sensor input.
 *  The frame rate (frame length) can be directly compared with shutter time.
 *  The parameter fps is expressed as frame length, or frame interval, in Q9 format, which is 512000000*time_in_sec. For example,
 *  30 fps can be expressed as DIV_ROUND(512000000, 30) = 17066667 = 0x1046aab.
 *  Please refer to @link iav_common.h iav_common.h @endlink for more frame rate macro definitions.
 */
#define IAV_IOC_VIN_GET_FPS					VIN_IOR(IOC_VIN_FPS, struct vindev_fps *)

/*!
 *  This API can be used to retrieve the current active source video information
 */
#define IAV_IOC_VIN_GET_VIDEOINFO				VIN_IOR(IOC_VIN_VIDEOINFO, struct vindev_video_info *)

/*!
 *  This API can be used to configure the current active sensor shutter time in Q9 format.
 *  The shutter time can be directly compared with the frame rate (frame length).
 */
#define IAV_IOC_VIN_SET_SHUTTER				VIN_IOW(IOC_VIN_SHUTTER, struct vindev_shutter *)

/*!
 *  This API can be used to get the current active sensor shutter time in Q9 format.
 *  The shutter time can be directly compared with the frame rate (frame length).
 */
#define IAV_IOC_VIN_GET_SHUTTER				VIN_IOR(IOC_VIN_SHUTTER, struct vindev_shutter *)

/*!
 *  This API can be used to configure the current active sensor AGC information.
 */
#define IAV_IOC_VIN_SET_AGC					VIN_IOW(IOC_VIN_AGC, struct vindev_agc *)

/*!
 *  This API can be used to get the current active sensor AGC information.
 */
#define IAV_IOC_VIN_GET_AGC					VIN_IOR(IOC_VIN_AGC, struct vindev_agc *)

/*!
 *  This API can be used to configure the readout mode of the sensor. The mirror pattern decides whether to
 *  read the pixels from the default order or to reverse the order in row style or column style or both.
 *  The need for sensor mirroring has been diminished somewhat by the CV22's encoding rotation capability.
 *  Please refer to the @link IAV_IOC_SET_STREAM_CONFIG IAV_IOC_SET_STREAM_CONFIG(IAV_STMCFG_FORMAT) @endlink API
 */
#define IAV_IOC_VIN_SET_MIRROR				VIN_IOW(IOC_VIN_MIRROR, struct vindev_mirror *)

/*!
 *  This API can be used to get the read-out mode of the sensor. The mirror pattern decides whether to read
 *  the pixels from the default order or to reverse the order in a row or column style or both.
 */
#define IAV_IOC_VIN_GET_MIRROR				VIN_IOR(IOC_VIN_MIRROR, struct vindev_mirror *)

/*!
 *  This API can be used to get the 3A algorithm required information from the sensor driver.
 */
#define IAV_IOC_VIN_GET_AAAINFO				VIN_IOR(IOC_VIN_AAAINFO, struct vindev_aaa_info *)

/*!
 *  This API can be used to set the current active sensor AGC index to the AGC Table.
 */
#define IAV_IOC_VIN_SET_AGC_SHUTTER			VIN_IOW(IOC_VIN_AGC_SHUTTER, struct vindev_agc_shutter *)

/*!
 *  This API can be used to set the current active sensor Dgain.
 */
#define IAV_IOC_VIN_SET_DGAIN_RATIO			VIN_IOW(IOC_VIN_DGAIN_RATIO, struct vindev_dgain_ratio *)

/*!
 *  This API can be used to get the current active sensor Dgain.
 */
#define IAV_IOC_VIN_GET_DGAIN_RATIO			VIN_IOR(IOC_VIN_DGAIN_RATIO, struct vindev_dgain_ratio *)

/*!
 *  This API can be used to set the current active sensor EIS information.
 */
#define IAV_IOC_VIN_GET_EISINFO				VIN_IOR(IOC_VIN_EISINFO, struct vindev_eisinfo *)

/*!
 *  This API can be used to set the current active sensor register.
 */
#define IAV_IOC_VIN_SET_REG					VIN_IOW(IOC_VIN_REG, struct vindev_reg *)

/*!
 *  This API can be used to get the current active sensor register.
 */
#define IAV_IOC_VIN_GET_REG					VIN_IOR(IOC_VIN_REG, struct vindev_reg *)

/*!
 *  This API can be used to set the current active sensor chip status.
 */
#define IAV_IOC_VIN_GET_CHIP_STATUS			VIN_IOR(IOC_VIN_CHIP_STATUS, struct vindev_chip_status *)

/*!
 *  This API can be used to set the current active sensor AE check flag.
 */
#define IAV_IOC_VIN_SET_AE_CHECK				VIN_IOW(IOC_VIN_SET_AE_CHECK, struct vindev_ae_check *)

/*!
 *  This API can be used to set the current active sensor shutter row.
 */
#define IAV_IOC_VIN_SHUTTER2ROW				VIN_IOWR(IOC_VIN_SHUTTER2ROW, struct vindev_shutter_row *)

/*!
 *  This API can be used to get the current active WDR sensor shutter row.
 */
#define IAV_IOC_VIN_GET_WDR_SHUTTER_ROW_GP	VIN_IOR(IOC_VIN_WDR_SHUTTER_ROW_GP, struct vindev_wdr_gp_s *)

/*!
 *  This API can be used to get the current active WDR sensor AGC index.
 */
#define IAV_IOC_VIN_GET_WDR_AGAIN_INDEX_GP	VIN_IOR(IOC_VIN_WDR_AGAIN_INDEX_GP, struct vindev_wdr_gp_s *)

/*!
 *  This API can be used to get the current active WDR sensor Dgain.
 */
#define IAV_IOC_VIN_GET_WDR_DGAIN_INDEX_GP	VIN_IOR(IOC_VIN_WDR_DGAIN_INDEX_GP, struct vindev_wdr_gp_s *)

/*!
 *  This API can be used to set the current active WDR sensor shutter row.
 */
#define IAV_IOC_VIN_WDR_SHUTTER2ROW			VIN_IOWR(IOC_VIN_WDR_SHUTTER2ROW, struct vindev_wdr_gp_s *)

/*!
 *  This API can be used to set the current active WDR sensor parameters.
 */
#define IAV_IOC_VIN_SET_WDR_GP				VIN_IOW(IOC_VIN_WDR_ROW_GP, struct vindev_wdr_gp_info *)


#define IAV_IOC_VIN_SET_PENDING_SHT_AGC		VIN_IOW(IOC_VIN_PENDING_SHT_AGC, struct vindev_wdr_gp_info *)
#define IAV_IOC_VIN_SET_PENDING_SHT_AGC_SEQ	VIN_IOW(IOC_VIN_PENDING_SHT_AGC_SEQ, struct vindev_sht_agc_seq *)

/*!
 *  This API can be used to set the current active AAA compensation.
 */
#define IAV_IOC_VIN_AAA_COMPENSATION			VIN_IOWR(IOC_VIN_AAA_COMPENSATION, struct vindev_wdr_gp_info *)

/*!
 *  This API can be used to set the current active sensor into test stream mode.
 */
#define IAV_IOC_VIN_SET_STREAM_MODE			VIN_IOW(IOC_VIN_SET_STREAM_MODE, struct vindev_stream_mode *)

/*!
 *  This API can be used to set the current active sensor low light mode.
 */
#define IAV_IOC_VIN_SET_LOW_LIGHT_MODE		VIN_IOW(IOC_VIN_SET_LOW_LIGHT_MODE, struct vindev_low_light_info *)

/*!
 *  This API can be used to switch contexts for sensors with dual contexts supported like AR0230.
 */
#define IAV_IOC_VIN_SWITCH_VSRC_CTX			VIN_IOW(IOC_VIN_SWITCH_VSRC_CTX, struct vindev_switch_vsrc_ctx *)

/*!
 *  This API can be used to bind internal frame count to each vsrc context for sensors with dual contexts supported like AR0230.
 */
#define IAV_IOC_VIN_LOCK_VSRC_CTX_FRAME_CNT	VIN_IOW(IOC_VIN_LOCK_VSRC_CTX_FRAME_CNT, struct vindev_lock_vsrc_ctx_frame_cnt *)

/*!
 *  This API can be used to unbind internal frame count to each vsrc context.
 */
#define IAV_IOC_VIN_UNLOCK_VSRC_CTX_FRAME_CNT	VIN_IOW(IOC_VIN_UNLOCK_VSRC_CTX_FRAME_CNT, struct vindev_unlock_vsrc_ctx_frame_cnt *)

/*!
 *  This API can be used to convert shutter to RHS and raw offset in HDR mode.
 */
#define IAV_IOC_VIN_WDR_SHUTTER2OFFSET				VIN_IOWR(IOC_VIN_WDR_SHUTTER2OFFSET, struct vindev_wdr_gp_s *)

/*!
 *  This API can be used to set the current active sensor into test pattern mode.
 */
#define IAV_IOC_VIN_SET_TP_MODE			VIN_IOW(IOC_VIN_SET_TP_MODE, struct vindev_tp_mode *)
/* ==========================================================================*/
/*! @} */  /* End of iav-ioctl-vin-api */


#ifdef __cplusplus
}
#endif

#endif	//__IAV_VIN_IOCTL_H__

