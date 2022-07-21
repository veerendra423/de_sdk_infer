/*
 * iav_ioctl.h
 *
 * History:
 *	2013/03/12 - [Cao Rongrong] Created file
 *	2013/12/12 - [Jian Tang] Modified file
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

#ifndef __IAV_IOCTL_H__
#define __IAV_IOCTL_H__

/*! @file iav_ioctl.h
 *  @brief This file defines IAV driver ioctl api.
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "basetypes.h"
#include <linux/ioctl.h>
#include "config.h"

#include "iav_common.h"
#include "iav_vin_ioctl.h"
#include "iav_vout_ioctl.h"
#include "ambas_imgproc_arch.h"

#define CONFIG_AMBARELLA_MAX_CHANNEL_NUM 2

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
/*! @macros IAV_API_VER_MAJOR
 *	@brief define IAV API Major Version.
 */
#define IAV_API_VER_MAJOR			(1)

/*! @macros IAV_API_VER_MINOR
 *	@brief define IAV API Minor Version.
 */
#define IAV_API_VER_MINOR			(5)

/*! @macros IAV_API_VER_PATCH
 *	@brief define IAV API Patch Version.
 */
#define IAV_API_VER_PATCH			(1)

/*! @macros IAV_API_VER_MOD_TIME
 *	@brief define IAV API Modification/Update Time.
 */
#define IAV_API_VER_MOD_TIME		(0x20220307)

/*! @macros IAV_MAX_CHANNEL_NUM
 *  @brief define max channel number.
 */
#ifndef IAV_MAX_CHANNEL_NUM
#define IAV_MAX_CHANNEL_NUM			(8)
#endif

/*! @macros IAV_HEVC_TILE_NUM
 *  @brief define iav hevc encode tile number.
 */
#define IAV_HEVC_TILE_NUM			(3)

/*! @macros IAV_MAX_CANVAS_BUF_NUM
 *  @brief define iav max canvas buffer number.
 */
#define IAV_MAX_CANVAS_BUF_NUM		(12)

/*! @macros IAV_MAX_PYRAMID_LAYERS
 *  @brief define iav max pyramid layer number.
 */
#define IAV_MAX_PYRAMID_LAYERS		(6)

/*! @macros IAV_MAX_PASS_NUM
 *  @brief define iav max pass number for each channel. It's only used for the encode modes
 *  which can support multi-pass scaler functions, like encode mode 1 / 3 / 5.
 */
#define IAV_MAX_PASS_NUM			(2)

/*! @macros VIN_INSTANCES
 *  @brief define vin instance number, 6 real vinc + 1 virtual vinc.
 */
#define VIN_INSTANCES				(6 + 1)

/*! @macros VIN_CONTROLLER_NUM
 *  @brief define vin controller number, equal to VIN_INSTANCES.
 */
#define VIN_CONTROLLER_NUM			VIN_INSTANCES

/*! @macros IAV_MAX_EXTRA_RAW_LINES
 *  @brief define iav max extra raw cap lines.
 */
#define IAV_MAX_EXTRA_RAW_LINES		(8)

/*! @macros IAV_MAX_RAWSEQ_NUM
 *  @brief define max raw sequence numbers to get. It's used for some special
 *  use case, such as ToF sensor which need to read out continuous 8 (or 12)
 *  frames RAW data in one shot.
 */
#define IAV_MAX_RAWSEQ_NUM (12)

/*! @macros IAV_MIN_VP_DRAM_PRIORITY
 *  @brief define vp dram priority minimum value.
 */
#if defined(CONFIG_ARCH_CV2) || defined(CONFIG_ARCH_CV22) || defined(CONFIG_ARCH_CV25) || defined(CONFIG_ARCH_CV28)
#define IAV_MIN_VP_DRAM_PRIORITY	(2)
#else
#define IAV_MIN_VP_DRAM_PRIORITY	(0)
#endif

/*! @macros IAV_MAX_VP_DRAM_PRIORITY
 *  @brief define vp dram priority maximum value.
 */
#if defined(CONFIG_ARCH_CV2)
#define IAV_MAX_VP_DRAM_PRIORITY	(7)
#elif defined(CONFIG_ARCH_CV22) || defined(CONFIG_ARCH_CV25) || defined(CONFIG_ARCH_CV28)
#define IAV_MAX_VP_DRAM_PRIORITY	(5)
#else
#define IAV_MAX_VP_DRAM_PRIORITY	(0)
#endif

/*! @macros IAV_MAX_LENS_WARP_HI_EF_FACTOR
 *  @brief define max lens-warp high efficiency factor.
 */
#define IAV_MAX_LENS_WARP_HI_EF_FACTOR		(4)

/*! @macros LPDDR4_ALIGN
 *  @brief define lpddr4 align value.
 */
#define LPDDR4_ALIGN			(64)

/*! @macros UNIQUE_ID_SIZE
 *  @brief define unique ID size.
 */
#define UNIQUE_ID_SIZE	(32)

/*! @macros IAV_MAX_ENCODE_FRAMERATE_UPSAMPLING_RATIO
 *  @brief define encode framerate upsamling maximum ratio.
 */
#define IAV_MAX_ENCODE_FRAMERATE_UPSAMPLING_RATIO	(3)

/*! @macros IAV_DSP_MAX_FB_NUM_UPPER_LIMIT
 *  @brief define dsp max FB num upper limit.
 */
#define IAV_DSP_MAX_FB_NUM_UPPER_LIMIT		(230)

/*! @macros IAV_DSP_MAX_FB_NUM_LOWER_LIMIT
 *  @brief define dsp max FB num lower limit.
 */
#define IAV_DSP_MAX_FB_NUM_LOWER_LIMIT		(196)

/*! @macros IAV_MIN_EXT_MEM_BUF_NUM
 *  @brief define pyramid ext mem buf min limit.
 */
#define IAV_MIN_EXT_MEM_BUF_NUM				(4)

/*! @macros IAV_MAX_EXT_MEM_BUF_NUM
 *  @brief define pyramid ext mem buf max limit.
 */
#define IAV_MAX_EXT_MEM_BUF_NUM				(100)

/*! @macros IAV_MAX_IRQ_SKIP_CNT
 *  @brief define max DSP IRQ skip count limit.
 */
#define IAV_MAX_IRQ_SKIP_CNT	(120)

/*! @macros IAV_MIN_DEBUG_STITCH_SLICE_NUM
 *  @brief define min debug stitch slice num
 */
#define IAV_MIN_DEBUG_STITCH_SLICE_NUM	(3)

/*! @macros IAV_HP_FPS_FACTOR
 *  @brief define high precision fps factor.
 */
#define IAV_HP_FPS_FACTOR	(1000)

/*! @macros IAV_HP_FPS_MAX
 *  @brief define maximum high precision fps.
 */
#define IAV_HP_FPS_MAX	(480000)	/*!< 480fps */

/*! @macros IAV_Q9_FPS_MAX
 *  @brief define maximum fps in q9 format.
 */
#define IAV_Q9_FPS_MAX	(1066666)	/*!< 480fps */

/*! @macros IAV_HP_FPS_MIN
 *  @brief define minimum high precision fps.
 */
#define IAV_HP_FPS_MIN	(500)	/*!< 0.5fps */

/*! @macros IAV_Q9_FPS_MIN
 *  @brief define minimum fps in q9 format.
 */
#define IAV_Q9_FPS_MIN	(1024000000)	/*!< 0.5fps */

/*! @macros IAV_HP_FPS_INT
 *  @brief This is to convert integer fps into hp_fps
 */
#define IAV_HP_FPS_INT(x)	((x) * 1000U)

/*! @macros IAV_DIS_STATS_MAX_CACHED_ITEMS
 *  @brief define maximum cached items for DIS statistics.
 */
#define IAV_DIS_STATS_MAX_CACHED_ITEMS	(31)

/*! @macros IAV_DIS_STATS_MIN_CACHED_ITEMS
 *  @brief define minimum cached items for DIS statistics.
 */
#define IAV_DIS_STATS_MIN_CACHED_ITEMS	(3)

/*! @macros IAV_ENC_X_OFFSET_ALIGN
 *  @brief define encoding x offset align requirement.
 */
#define IAV_ENC_X_OFFSET_ALIGN	(2)

/*! @macros IAV_ENC_Y_OFFSET_ALIGN
 *  @brief define encoding y offset align requirement.
 */
#define IAV_ENC_Y_OFFSET_ALIGN	(4)

/*! @macros IAV_ENC_MJPEG_WIDTH_ALIGN
 *  @brief define MJPEG encoding width align requirement.
 */
#define IAV_ENC_MJPEG_WIDTH_ALIGN	(4)

/*! @macros IAV_ENC_MJPEG_HEIGHT_ALIGN
 *  @brief define MJPEG encoding height align requirement.
 */
#define IAV_ENC_MJPEG_HEIGHT_ALIGN	(4)

/*! @macros IAV_ENC_H26X_WIDTH_ALIGN
 *  @brief define H26X encoding width align requirement.
 */
#define IAV_ENC_H26X_WIDTH_ALIGN	(8)

/*! @macros IAV_ENC_H26X_HEIGHT_ALIGN
 *  @brief define H26X encoding height align requirement.
 */
#define IAV_ENC_H26X_HEIGHT_ALIGN	(4)

/*! @enum dsp_mode
 *  @brief DSP mode enum to list dsp mode state.
 */
enum dsp_mode {
	DSP_CURRENT_MODE 				= 0xFF,	/*!< 0xFF */
	DSP_NORMAL_ISO_MODE				= 0x0,	/*!< 0x0 */
	DSP_MULTI_REGION_WARP_MODE		= 0x1,		/*!< 0x1 */
	DSP_FUSION_MODE 				= 0x2,		/*!< 0x2 */
	DSP_MULTI_PASS_IDSP_ROTATE_MODE = 0x3,		/*!< 0x3 */
	DSP_MULTI_OUTPUT_FUSION_MODE	= 0x4,		/*!< 0x4 */
	DSP_HDR_LINE_INTERLEAVED_MODE	= 0x5,			/*!< 0x5 */
	DSP_MULTI_YUV_INPUT_MODE		= 0x6,			/*!< 0x6 */
	DSP_AISP_MODE					= 0x9,			/*!< 0x9 */
	DSP_ENCODE_MODE_TOTAL_NUM		= 0xA,		/*!< 0xA */
	DSP_ENCODE_MODE_NONE			= 0x7F,	/*!< 0x7F */
	DSP_ENCODE_MODE_AUTOMATIC		= 0x80,	/*!< 0x80 */
	DSP_ENCODE_MODE_FIRST			= DSP_NORMAL_ISO_MODE, /*!< DSP_NORMAL_ISO_MODE */
	DSP_ENCODE_MODE_LAST			= DSP_ENCODE_MODE_TOTAL_NUM, /*!< DSP_ENCODE_MODE_TOTAL_NUM */
};

/*! @enum dsp_vout_profile
 *  @brief DSP vout profile enumeration.
 */
enum dsp_vout_profile {
	DSP_VOUT_PROFILE_DEFAULT = 0,                   /*!< 0, vout0 no osd, vout1 with osd, stream osd */
	DSP_VOUT_PROFILE_4K_WITH_16BIT_OSD = 1,         /*!< 1, vout0 4k with osd, vout1 4k with osd */
	DSP_VOUT_PROFILE_VOUT0_D640_VOUT1_M720 = 2,     /*!< 2, vout0 640, vout1 720 with osd, stream osd */
	DSP_VOUT_PROFILE_VOUT1_720P_WITH_16BIT_OSD = 3, /*!< 3, vout0 default, vout1 720p with 16bit osd, stream osd */
	DSP_VOUT_PROFILE_VOUT0_720P_WITH_16BIT_OSD = 4, /*!< 4, vout1 default, vout0 720p with 16bit osd, stream osd */
	DSP_VOUT_PROFILE_VOUT0_1_1080P_WITH_32BIT_OSD = 5, /*!< 5, vout0 1080p with 32bit osd, vout1 1080p with 32bit osd */
	DSP_VOUT_PROFILE_VOUT0_1080P_WITH_8BIT_OSD_VOUT1_OFF = 6, /*!< 6, vout0 1080p with 8bit osd, vout1 off */
	DSP_VOUT_PROFILE_NUM /*!< 7 */
};

/*! @enum dsp_sync_first_vout_frame_mode
 *  @brief DSP sync first vout frame mode enumeration.
 */
enum dsp_sync_first_vout_frame_mode {
	DSP_SYNC_FIRST_VOUT_FRAME_MODE_OFF = 0, /*!< 0, first vout frame is not synced with idsp for both vout0 and vout1 */
	DSP_SYNC_FIRST_VOUT_FRAME_MODE_VOUT0 = 1, /*!< 1, first vout frame is synced with idsp for vout0 */
	DSP_SYNC_FIRST_VOUT_FRAME_MODE_VOUT1 = 2, /*!< 2, first vout frame is synced with idsp for vout1 */
	DSP_SYNC_FIRST_VOUT_FRAME_MODE_VOUT0_VOUT1 = 3, /*!< 3, first vout frame is synced with idsp for both vout0 and vout1 */
	DSP_SYNC_FIRST_VOUT_FRAME_MODE_NUM /*!< 4 */
};

/*! @enum dsp_api_thread_freq
 *  @brief DSP api thread frequency.
 */
enum dsp_api_thread_freq {
	DSP_API_THREAD_FREQ_MIN = 50,  /*!< 50 */
	DSP_API_THREAD_FREQ_MAX = 240, /*!< 240 */
	DSP_API_THREAD_FREQ_DEFAULT = 120, /*!< 120, default dsp api thread frequency */
};

/*! @enum hevc_perf_mode
 *  @brief HEVC performance mode enumeration.
 */
enum hevc_perf_mode {
	IAV_HEVC_PERF_MODE_DEFAULT = 0,
	IAV_HEVC_PERF_MODE_FAST = 1,
	IAV_HEVC_PERF_MODE_FASTEST = 2,
	IAV_HEVC_PERF_MODE_NUM = 3,
	IAV_HEVC_PERF_MODE_FIRST = IAV_HEVC_PERF_MODE_DEFAULT,
	IAV_HEVC_PERF_MODE_LAST = IAV_HEVC_PERF_MODE_NUM,
};

/*! @enum iav_chip_id
 *  @brief iav chip id enumeration.
 */
enum iav_chip_id {
	IAV_CHIP_ID_UNKNOWN			= -1, /*!< -1 */

	/* CV2 */
	IAV_CHIP_ID_CV2_55			= 0, /*!< 0 */
	IAV_CHIP_ID_CV2_66			= 1, /*!< 1 */
	IAV_CHIP_ID_CV2_66_TEST		= 2, /*!< 2 */
	IAV_CHIP_ID_CV2_88			= 3, /*!< 3 */
	IAV_CHIP_ID_CV2_99			= 4, /*!< 4 */
	IAV_CHIP_ID_CV2_LAST		= 5, /*!< 5 */
	IAV_CHIP_ID_CV2_FIRST		= IAV_CHIP_ID_CV2_55, /*!< IAV_CHIP_ID_CV2_55 */
	IAV_CHIP_ID_CV2_NUM		= IAV_CHIP_ID_CV2_LAST - IAV_CHIP_ID_CV2_FIRST, /*!< IAV_CHIP_ID_CV2_LAST - IAV_CHIP_ID_CV2_FIRST */

	/* CV2 Auto */
	IAV_CHIP_ID_CV2AQ_76		= 0x20, /*!< 0x20 */
	IAV_CHIP_ID_CV2AX_81		= 0x21, /*!< 0x21 */
	IAV_CHIP_ID_CV2AX_86		= 0x22, /*!< 0x22 */
	IAV_CHIP_ID_CV2AQ_81		= 0x23, /*!< 0x23 */
	IAV_CHIP_ID_CV2AQ_86		= 0x24, /*!< 0x24 */
	IAV_CHIP_ID_CV2AX_99		= 0x25, /*!< 0x25 */
	IAV_CHIP_ID_CV2AQ_99		= 0x26, /*!< 0x26 */
	IAV_CHIP_ID_CV2AUTO_LAST	= 0x27, /*!< 0x27 */
	IAV_CHIP_ID_CV2AUTO_FIRST	= IAV_CHIP_ID_CV2AQ_76, /*!< IAV_CHIP_ID_CV2AQ_76 */
	IAV_CHIP_ID_CV2AUTO_NUM		= IAV_CHIP_ID_CV2AUTO_LAST - IAV_CHIP_ID_CV2AUTO_FIRST, /*!< IAV_CHIP_ID_CV2AUTO_LAST - IAV_CHIP_ID_CV2AUTO_FIRST */

	/* CV22 */
	IAV_CHIP_ID_CV22_55			= 0, /*!< 0 */
	IAV_CHIP_ID_CV22_66			= 1, /*!< 1 */
	IAV_CHIP_ID_CV22_88			= 2, /*!< 2 */
	IAV_CHIP_ID_CV22_99			= 3, /*!< 3 */
	IAV_CHIP_ID_CV22_55N		= 4, /*!< 4 */
	IAV_CHIP_ID_CV22_66N		= 5, /*!< 5 */
	IAV_CHIP_ID_CV22_88N		= 6, /*!< 6 */
	IAV_CHIP_ID_CV22_99N		= 7, /*!< 7 */
	IAV_CHIP_ID_CV22_98		= 8, /*!< 8 */
	IAV_CHIP_ID_CV22_LAST		= 9, /*!< 9 */
	IAV_CHIP_ID_CV22_FIRST		= IAV_CHIP_ID_CV22_55, /*!< IAV_CHIP_ID_CV22_55 */
	IAV_CHIP_ID_CV22_NUM		= IAV_CHIP_ID_CV22_LAST - IAV_CHIP_ID_CV22_FIRST, /*!< IAV_CHIP_ID_CV22_LAST - IAV_CHIP_ID_CV22_FIRST */

	/* CV22 Auto */
	IAV_CHIP_ID_CV22AQ_16		= 0x20, /*!< 0x20 */
	IAV_CHIP_ID_CV22AQ_26		= 0x21, /*!< 0x21 */
	IAV_CHIP_ID_CV22AQ_36		= 0x22, /*!< 0x22 */
	IAV_CHIP_ID_CV22AQ_76		= 0x23, /*!< 0x23 */
	IAV_CHIP_ID_CV22AX_16		= 0x24, /*!< 0x24 */
	IAV_CHIP_ID_CV22AX_26		= 0x25, /*!< 0x25 */
	IAV_CHIP_ID_CV22AX_36		= 0x26, /*!< 0x26 */
	IAV_CHIP_ID_CV22AX_76		= 0x27, /*!< 0x27 */
	IAV_CHIP_ID_CV22A_16		= 0x28, /*!< 0x28 */
	IAV_CHIP_ID_CV22A_26		= 0x29, /*!< 0x29 */
	IAV_CHIP_ID_CV22A_36		= 0x2A, /*!< 0x2A */
	IAV_CHIP_ID_CV22A_76		= 0x2B, /*!< 0x2B */
	IAV_CHIP_ID_CV22A_99		= 0x2C, /*!< 0x2C */
	IAV_CHIP_ID_CV22AX_99		= 0x2D, /*!< 0x2D */
	IAV_CHIP_ID_CV22AQ_99		= 0x2E, /*!< 0x2E */

	IAV_CHIP_ID_CV22AUTO_LAST	= 0x2F, /*!< 0x2F */
	IAV_CHIP_ID_CV22AUTO_FIRST	= IAV_CHIP_ID_CV22AQ_16, /*!< IAV_CHIP_ID_CV22AQ_16 */
	IAV_CHIP_ID_CV22AUTO_NUM	= IAV_CHIP_ID_CV22AUTO_LAST - IAV_CHIP_ID_CV22AUTO_FIRST, /*!< IAV_CHIP_ID_CV22AUTO_LAST - IAV_CHIP_ID_CV22AUTO_FIRST */

	/* CV25 */
	IAV_CHIP_ID_CV25_33			= 0, /*!< 0 */
	IAV_CHIP_ID_CV25_66			= 1, /*!< 1 */
	IAV_CHIP_ID_CV25_99			= 2, /*!< 2 */
	IAV_CHIP_ID_CV25_33M		= 3, /*!< 3 */
	IAV_CHIP_ID_CV25_55M		= 4, /*!< 4 */
	IAV_CHIP_ID_CV25_99M		= 5, /*!< 5 */
	IAV_CHIP_ID_CV25_88		= 6, /*!< 6 */
	IAV_CHIP_ID_CV25_33MEX		= 7, /*!< 7 */
	IAV_CHIP_ID_CV25_55MEX		= 8, /*!< 8 */
	IAV_CHIP_ID_CV25_LAST		= 9, /*!< 9 */
	IAV_CHIP_ID_CV25_FIRST		= IAV_CHIP_ID_CV25_33, /*!< IAV_CHIP_ID_CV25_33 */
	IAV_CHIP_ID_CV25_NUM		= IAV_CHIP_ID_CV25_LAST - IAV_CHIP_ID_CV25_FIRST, /*!< IAV_CHIP_ID_CV25_LAST - IAV_CHIP_ID_CV25_FIRST */

	/* CV25 Auto */
	IAV_CHIP_ID_CV25AQ_16		= 0x20, /*!< 0x20 */
	IAV_CHIP_ID_CV25AQ_26		= 0x21, /*!< 0x21 */
	IAV_CHIP_ID_CV25AQ_36		= 0x22, /*!< 0x22 */
	IAV_CHIP_ID_CV25AQ_76		= 0x23, /*!< 0x23 */
	IAV_CHIP_ID_CV25AX_26		= 0x24, /*!< 0x24 */
	IAV_CHIP_ID_CV25AX_36		= 0x25, /*!< 0x25 */
	IAV_CHIP_ID_CV25AX_76		= 0x26, /*!< 0x26 */
	IAV_CHIP_ID_CV25AX_86		= 0x27, /*!< 0x27 */
	IAV_CHIP_ID_CV25A_26		= 0x28, /*!< 0x28 */
	IAV_CHIP_ID_CV25A_36		= 0x29, /*!< 0x29 */
	IAV_CHIP_ID_CV25A_76		= 0x2A, /*!< 0x2A */
	IAV_CHIP_ID_CV25A_86		= 0x2B, /*!< 0x2B */
	IAV_CHIP_ID_CV25A_99		= 0x2C, /*!< 0x2C */
	IAV_CHIP_ID_CV25AX_99		= 0x2D, /*!< 0x2D */
	IAV_CHIP_ID_CV25AQ_99		= 0x2E, /*!< 0x2E */
	IAV_CHIP_ID_CV25AX_16		= 0x2F, /*!< 0x2F */
	IAV_CHIP_ID_CV25A_16		= 0x30, /*!< 0x30 */
	IAV_CHIP_ID_CV25AX_26M		= 0x31, /*!< 0x31 */
	IAV_CHIP_ID_CV25AX_36M		= 0x32, /*!< 0x32 */
	IAV_CHIP_ID_CV25A_26M		= 0x33, /*!< 0x33 */
	IAV_CHIP_ID_CV25A_36M		= 0x34, /*!< 0x34 */
	IAV_CHIP_ID_CV25A_30M		= 0x35, /*!< 0x35 */

	IAV_CHIP_ID_CV25AUTO_LAST	= 0x36, /*!< 0x36 */
	IAV_CHIP_ID_CV25AUTO_FIRST	= IAV_CHIP_ID_CV25AQ_16, /*!< IAV_CHIP_ID_CV25AQ_16 */
	IAV_CHIP_ID_CV25AUTO_NUM	= IAV_CHIP_ID_CV25AUTO_LAST - IAV_CHIP_ID_CV25AUTO_FIRST, /*!< IAV_CHIP_ID_CV25AUTO_LAST - IAV_CHIP_ID_CV25AUTO_FIRST */

	/* S6LM */
	IAV_CHIP_ID_S6LM_22 		= 0, /*!< 0 */
	IAV_CHIP_ID_S6LM_33 		= 1, /*!< 1 */
	IAV_CHIP_ID_S6LM_55 		= 2, /*!< 2 */
	IAV_CHIP_ID_S6LM_99 		= 3, /*!< 3 */
	IAV_CHIP_ID_S6LM_22EX 		= 4, /*!< 4 */
	IAV_CHIP_ID_S6LM_LAST		= 5, /*!< 5 */
	IAV_CHIP_ID_S6LM_FIRST		= IAV_CHIP_ID_S6LM_22, /*!< IAV_CHIP_ID_S6LM_22 */
	IAV_CHIP_ID_S6LM_NUM		= IAV_CHIP_ID_S6LM_LAST - IAV_CHIP_ID_S6LM_FIRST, /*!< IAV_CHIP_ID_S6LM_LAST - IAV_CHIP_ID_S6LM_FIRST */

	/* H32 - S6Lm Auto */
	IAV_CHIP_ID_H32AX_26		= 0x20, /*!< 0x20 */
	IAV_CHIP_ID_H32AX_36		= 0x21, /*!< 0x21 */
	IAV_CHIP_ID_H32AX_76		= 0x22, /*!< 0x22 */
	IAV_CHIP_ID_H32A_26		= 0x23, /*!< 0x23 */
	IAV_CHIP_ID_H32A_36		= 0x24, /*!< 0x24 */
	IAV_CHIP_ID_H32A_76		= 0x25, /*!< 0x25 */
	IAV_CHIP_ID_H32AQ_16		= 0x26, /*!< 0x26 */
	IAV_CHIP_ID_H32AQ_26		= 0x27, /*!< 0x27 */
	IAV_CHIP_ID_H32AQ_36		= 0x28, /*!< 0x28 */
	IAV_CHIP_ID_H32AQ_76		= 0x29, /*!< 0x29 */

	IAV_CHIP_ID_H32_LAST 		= 0x2A, /*!< 0x2A */
	IAV_CHIP_ID_H32_FIRST		= IAV_CHIP_ID_H32AX_26, /*!< IAV_CHIP_ID_H32AX_26 */
	IAV_CHIP_ID_H32_NUM		= IAV_CHIP_ID_H32_LAST - IAV_CHIP_ID_H32_FIRST, /*!< IAV_CHIP_ID_H32_LAST - IAV_CHIP_ID_H32_FIRST */

	IAV_CHIP_ID_CV28_22M		= 0, /*!< 0 */
	IAV_CHIP_ID_CV28_33M		= 1, /*!< 1 */
	IAV_CHIP_ID_CV28_55M		= 2, /*!< 2 */
	IAV_CHIP_ID_CV28_66M		= 3, /*!< 3 */
	IAV_CHIP_ID_CV28_99M		= 4, /*!< 4 */
	IAV_CHIP_ID_CV28_22M_TEST	= 5, /*!< 5 */
	IAV_CHIP_ID_CV28_22MEX		= 6, /*!< 6 */
	IAV_CHIP_ID_CV28_26MEX		= 7, /*!< 7 */
	IAV_CHIP_ID_CV28_LAST		= 8, /*!< 8 */
	IAV_CHIP_ID_CV28_FIRST		= IAV_CHIP_ID_CV28_22M, /*!< IAV_CHIP_ID_CV28_22M */
	IAV_CHIP_ID_CV28_NUM		= IAV_CHIP_ID_CV28_LAST - IAV_CHIP_ID_CV28_FIRST, /*!< IAV_CHIP_ID_CV28_LAST - IAV_CHIP_ID_CV28_FIRST */

	IAV_CHIP_ID_CV28AX_26		= 0x20, /*!< 0x20 */
	IAV_CHIP_ID_CV28AX_36		= 0x21, /*!< 0x21 */
	IAV_CHIP_ID_CV28AX_76		= 0x22, /*!< 0x22 */
	IAV_CHIP_ID_CV28A_26		= 0x23, /*!< 0x23 */
	IAV_CHIP_ID_CV28A_36		= 0x24, /*!< 0x24 */
	IAV_CHIP_ID_CV28A_76		= 0x25, /*!< 0x25 */
	IAV_CHIP_ID_CV28AUTO_LAST	= 0x26, /*!< 0x26 */
	IAV_CHIP_ID_CV28AUTO_FIRST	= IAV_CHIP_ID_CV28AX_26, /*!< IAV_CHIP_ID_CV28AX_26 */
	IAV_CHIP_ID_CV28AUTO_NUM	= IAV_CHIP_ID_CV28AUTO_LAST - IAV_CHIP_ID_CV28AUTO_FIRST, /*!< IAV_CHIP_ID_CV28AUTO_LAST - IAV_CHIP_ID_CV28AUTO_FIRST */
};

/*! @enum iav_hp_fps
 *  @brief iav high precision fps enumeration.
 */
enum iav_hp_fps {
	IAV_HP_FPS_AUTO		= 0,		/*!< 0 */
	IAV_HP_FPS_3_125	= 3125,		/*!< 3125 = 3.125 * 1000 */
	IAV_HP_FPS_3_75		= 3750,		/*!< 3750 = 3.75 * 1000 */
	IAV_HP_FPS_6_25		= 6250,		/*!< 6250 = 6.25 * 1000 */
	IAV_HP_FPS_7_5		= 7500,		/*!< 7500 = 7.5 * 1000 */
	IAV_HP_FPS_12_5		= 12500,	/*!< 12500 = 12.5 * 1000 */
	IAV_HP_FPS_15		= 15000,	/*!< 15000 = 15 * 1000 */
	IAV_HP_FPS_23_976	= 23976,	/*!< 23976 = 23.976 * 1000 */
	IAV_HP_FPS_24		= 24000,	/*!< 24000 = 24 * 1000 */
	IAV_HP_FPS_25		= 25000,	/*!< 25000 = 25 * 1000 */
	IAV_HP_FPS_29_97	= 29970,	/*!< 29970 = 29.97 * 1000 */
	IAV_HP_FPS_30		= 30000,	/*!< 30000 = 30 * 1000 */
	IAV_HP_FPS_50		= 50000,	/*!< 50000 = 50 * 1000 */
	IAV_HP_FPS_59_94	= 59940,	/*!< 59940 = 59.94 * 1000 */
	IAV_HP_FPS_60		= 60000,	/*!< 60000 = 60 * 1000 */
	IAV_HP_FPS_120		= 120000,	/*!< 120000 = 120 * 1000 */
};

/*! @enum iav_aisp_nn_num
 *  @brief iav aisp network / interface number enumeration.
 */
enum iav_aisp_nn_num {
	IAV_MD_NN_MAX_NUM	= 1, /*!< There is only 1 md network in AISP mode */
	IAV_C2Y_NN_MAX_NUM	= 6, /*!< There are totally 6 c2y networks in AISP mode */

	IAV_AISP_NN_MAX_NUM	= (IAV_MD_NN_MAX_NUM + IAV_C2Y_NN_MAX_NUM),

	IAV_MD_NN_IF_MAX_NUM	= 2, /*!< There are 2 interfaces for each md network */
	IAV_C2Y_NN_IF_MAX_NUM	= 8, /*!< There are 8 interfaces for each c2y network */

	IAV_NN_IF_MAP_ID_MAX_NUM	= 16, /*!< Max index cnt of port map, poke map for each interface, each
		interface has a port map info and poke map info */
};

/*! @enum iav_aisp_nn_type
 *  @brief iav aisp network type enumeration.
 */
enum iav_aisp_nn_type {
	IAV_AISP_NN_TYPE_MD	= 0,
	IAV_AISP_NN_TYPE_C2Y	= 1,
};

/*! @enum iav_aisp_map_type
 *  @brief iav aisp interface map type enumeration.
 */
enum iav_aisp_map_type {
	IAV_AISP_MAP_TYPE_PORT	= 0,
	IAV_AISP_MAP_TYPE_POKE	= 1,
	IAV_AISP_MAP_TYPE_NUM,
};
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_driver_version {
	int arch;	/*!< Chip arch ID */
	int model;	/*!< Chip model ID */
	int major;	/*!< Major of the device driver version */
	int minor;	/*!< Minor of the device driver version */
	int patch;	/*!< Patch of the device driver version */
	u32 mod_time;	/*!< Last modification time of the device driver */
	char description[64];	/*!< Description of the device driver */
	u32 api_version;	/*!< DSP API version */
	u32 idsp_version;	/*!< IDSP version */
	u32 iav_api_version;	/*!< IAV API version */
	u32 iav_api_mode_time;	/*!< Last modification time of the IAV API */
};

struct iav_driver_dsp_info {
	struct iav_driver_version drv_ver; /*!< Driver version information */
	u32 dspid;	/*!< DSP Chip ID */
	u8 dspout[4];	/*!< Output hash ID */
	u8 dspin[8];	/*!< Input hash ID */
};

struct iav_dsp_hash {
	u8 input[32];	/*!< dsp hash input */
	u8 output[4];	/*!< dsp hash output */
};

struct iav_unique_id {
	u8 unique_id[UNIQUE_ID_SIZE]; /*!< dsp unique ID */
};

struct iav_dsp_auth_unique_id {
	u8 customer_name[32]; /*!< customer name */
	u8 customer_certificate[896]; /*!< customer certificate */
	u8 unique_id_signature[256]; /*!< unique ID's signature */
	u8 arm_nonce[32]; /*!< arm challenge (nonce) */
	u8 dsp_auth_result[32]; /*!< dsp responce */
	u8 dsp_out_nonce[32]; /*!< dsp challenge (nonce) */
};

struct iav_dsp_auth_arm {
	u8 arm_response[32]; /*!< arm responce */
};

struct iav_dsplog_setup {
	int cmd;	/*!< Not currently supported. */
	u32 args[8];	/*!< arg[0] is used to define module.
				arg[1] is its log level(0:MINIMAL 1:NORMAL 2:VERBOSE 3:DEBUG)
				arg[2] is its thread mask. */
	u32 reserved;
};

struct iav_dsp_vp_cfg {
	u32 vp_enable : 1;
	u32 reserved : 31;
	u32 cmd_addr;
	u32 cmd_size;
	u32 msg_addr;	// including msg queue info and msg queue
	u32 msg_size;
	u32 vp_algo_id;
};

struct iav_vp_nn_if_map {
	u8 dvi_id;	/*!< dag index.*/
	u8 start;	/*!< port / poke start index, the minimal value in id array.*/
	u8 cnt;		/*!< port / poke index array cnt.*/
	u8 reserved0;
	u8 id[IAV_NN_IF_MAP_ID_MAX_NUM];	/*!< port / poke index.*/
};

struct iav_vp_nn_if_info {
	struct iav_vp_nn_if_map map[IAV_AISP_MAP_TYPE_NUM];	/*!< map info for each interface,
		each interface has a port map info and a poke map info.*/
};

struct iav_aisp_md_info {
	u32 if_cnt : 4;	/*!< interface cnt of each md nn.*/
	u32 reserved : 28;
	struct iav_vp_nn_if_info if_info[IAV_MD_NN_IF_MAX_NUM]; /*!< each md network has 2 interfaces,
		each interface has a port map info and poke map info.*/
};

struct iav_aisp_c2y_info {
	u32 if_cnt : 4;	/*!< interface cnt of each c2y nn.*/
	u32 reserved : 28;
	struct iav_vp_nn_if_info if_info[IAV_C2Y_NN_IF_MAX_NUM]; /*!< each c2y network has 8 interfaces,
		each interface has a port map info and poke map info.*/
};

struct iav_aisp_cfg {
	u32 default_map_disable : 1;	/*!< Flag to choose DSP default network map or ARM configured new network map,
			0(Default) : choose DSP default map, 1 : ARM configure new map.*/
	u32 md_nn_cnt : 4;		/*!< md nn cnt.*/
	u32 c2y_nn_cnt : 4;	/*!< c2y nn cnt.*/
	u32 reserved : 23;
	u32 dag_addr[IAV_AISP_NN_MAX_NUM];	/*!< Specify AISP dag cmd addr, where stores the output info
			of each network after running cavalry. */
	struct iav_aisp_md_info md_info[IAV_MD_NN_MAX_NUM];
	struct iav_aisp_c2y_info c2y_info[IAV_C2Y_NN_MAX_NUM];
};

struct iav_dsp_boot_params {
	u8 vout_profile;		/*!< Specify VOUT profile to configure, @sa dsp_vout_profile */
	u8 osd_profile[VOUT_NUM];	/*!< Specify VOUT OSD profile to configure */
	u8 vout_profile_flag : 1;	/*!< Flag to config VOUT profile */
	u8 vout_osd_profile_flag : 1;	/*!< Flag to config VOUT OSD profile */
	u8 debug_chip_id_flag : 1;		/*!< Flag to config debug-chip-id */
	u8 dsp_private_dram_flag : 1;	/*!< Flag to config dsp private dram */
	u8 dsp_max_fb_num_flag : 1;		/*!< Flag to config dsp max FB num */
	u8 vout_underflow_prevention_flag : 1;	/*!< Flag to config VOUT underflow prevention */
	u8 support_vout_rotate_flag : 1;			/*!< Flag to config whether support VOUT rotate */
	u8 vout_back_pressure_margin_flag : 1;			/*!< Flag to config VOUT back pressure margin */
	u8 debug_chip_id;		/*!< Specify debug-chip-id to do simulation, @sa iav_chip_id
							It's ONLY for internal debug purpose and works ONLY on engineering chip samples. */
	u8 dsp_max_fb_num;		/*!< Specify dsp internal max FB(frame buffer) num. */
	u8 vout_underflow_prevention : 1;	/*!< Flag to enable VOUT underflow prevention. */
	u8 vout0_support_rotate : 1;				/*!< Flag to support VOUT0 rotate */
	u8 vout1_support_rotate : 1;				/*!< Flag to support VOUT1 rotate */
	u8 vout0_back_pressure_margin	: 2;    /*!< Specify IDSP VOUT0 back pressure margin */
	u8 vout1_back_pressure_margin	: 2;    /*!< Specify IDSP VOUT1 back pressure margin */
	u8 bsh_no_reset : 1;	/*!< DSP never reset the bits info queue anymore,
				until re-enter preview with this flag enabled. */
	u8 bsh_no_reset_flag : 1;	/*!< Flag to config bsh no reset */
	u8 dsp_max_dram_part_num_flag : 1;	/*!< Flag to config dsp internel max dram part number */
	u8 sync_first_vout_frame_mode_flag : 1;	/*!< Flag to config sync first vout frame mode */
	u8 aisp_fifo_flag : 1;		/*!< Flag to config AISP FIFO info to DSP in mode 9, including: fifo_addr,
			fifo_len, fifo_esize */
	u8 reserved0 : 4;
	u32 dsp_private_dram_addr;	/*!< Specify dsp private dram address to configure dsp. */
	u32 dsp_private_dram_size;	/*!< Specify dsp private dram size to configure dsp. */
	u8 dsp_max_dram_part_num;	/*!< Specify dsp internel max dram part number. */
	u8 sync_first_vout_frame_mode : 3;	/*!< Specify sync first vout frame mode, @sa dsp_sync_first_vout_frame_mode. */
	u8 reserved1 : 5;
	u8 reserved2[2];

	u32 aisp_fifo_addr;	/*!< Specify AISP fifo addr, cavalry memory layout, partion_id : CMD_IDSP. */
	u32 aisp_fifo_len;	/*!< Specify AISP fifo len, fifo_len x fifo_esize = size of CMD_IDSP partion. */
	u32 aisp_fifo_esize;	/*!< Specify AISP fifo esize. */
};

struct iav_idle_params {
	u8 poweroff_vin;			/*!< Flag to power off all VIN controller when DSP enter IDLE mode. */
	u8 reserved[3];
	struct iav_dsp_boot_params dsp_boot_params;	/*!< Parameters ONLY used in DSP boot stage */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_state {
	IAV_STATE_INIT 				= -1, /*!< -1 */
	IAV_STATE_IDLE				= 0, /*!< 0 */
	IAV_STATE_PREVIEW			= 1, /*!< 1 */
	IAV_STATE_ENCODING			= 2, /*!< 2 */
	IAV_STATE_STILL_CAPTURE		= 3, /*!< 3 */
	IAV_STATE_DECODING			= 4, /*!< 4 */
	IAV_STATE_TRANSCODING		= 5, /*!< 5 */
	IAV_STATE_DUPLEX			= 6, /*!< 6 */
	IAV_STATE_EXITING_PREVIEW	= 7, /*!< 7 */
};

enum iav_boot_mode {
	SYSTEM_NORMAL_BOOT	= 0, /*!< 0 */
	SYSTEM_FAST_BOOT	= 1, /*!< 1 */
};

enum iav_system_query_source {
	SYSTEM_PROCESS_GENERIC	= 0, /*!< 0 */
	SYSTEM_PROCESS_IMAGE	= 1, /*!< 1 */
};

enum iav_canvas_type {
	IAV_CANVAS_TYPE_OFF 		= 0, /*!< 0 */
	IAV_CANVAS_TYPE_ENCODE 		= 1, /*!< 1 */
	IAV_CANVAS_TYPE_PREVIEW 	= 2, /*!< 2 */
	IAV_CANVAS_TYPE_NUM 		= 3, /*!< 3 */
};

enum iav_canvas_state {
	IAV_CANVAS_STATE_UNKNOWN	= 0, /*!< 0 */
	IAV_CANVAS_STATE_IDLE		= 1, /*!< 1 */
	IAV_CANVAS_STATE_BUSY		= 2, /*!< 2 */
	IAV_CANVAS_STATE_ERROR		= 255, /*!< 255 */
};

enum iav_stream_state {
	IAV_STREAM_STATE_IDLE		= 0, /*!< 0 */
	IAV_STREAM_STATE_STARTING	= 1, /*!< 1 */
	IAV_STREAM_STATE_ENCODING	= 2, /*!< 2 */
	IAV_STREAM_STATE_STOPPING	= 3, /*!< 3 */
	IAV_STREAM_STATE_UNKNOWN	= 255, /*!< 255 */
};

enum iav_info_id {
	IAV_INFO_SYSTEM	= 0x00, /*!< 0x00 */
	IAV_INFO_DRIVER	= 0x01, /*!< 0x01 */
	IAV_INFO_CANVAS	= 0x02, /*!< 0x02 */
	IAV_INFO_STREAM	= 0x03, /*!< 0x03 */
	IAV_INFO_MASK	= 0x04, /*!< 0x04 */
	IAV_INFO_WAFER_ID	= 0x05, /*!< 0x05 */
	IAV_INFO_UNIQUE_ID	= 0x06, /*!< 0x06 */
	IAV_INFO_MULTI_COLOR_MASK	= 0x07, /*!< 0x07 */
	IAV_INFO_BSB_STATS = 0x08,	/*!< 0x08 */
	IAV_INFO_NUM	= 0x09,	/*!< 0x09 */
};

enum iav_dsp_auth_type {
	DSP_AUTH_UNIQUE_ID = 0, /*!< 0x00 */
	DSP_AUTH_ARM = 1, /*!< 0x01 */
};

enum iav_dsp_dump_cmd_query_type {
	IAV_DSP_DUMP_CMD_QUERY_TYPE_RESULT	= 0, /*!< 0 */
	IAV_DSP_DUMP_CMD_QUERY_TYPE_MEM		= 1, /*!< 1 */
};

enum iav_dsp_dump_cmd_ctrl_type {
	IAV_DSP_DUMP_CMD_CTRL_TYPE_DO_DUMP	= 0, /*!< 0 */
	IAV_DSP_DUMP_CMD_CTRL_TYPE_INFORM_PID	= 1, /*!< 1 */
};

enum iav_mask_type {
	IAV_SINGLE_COLOR_MASK	= 0, /*!< 0 */
	IAV_MULTI_COLOT_MASK	= 1, /*!< 1 */
};

enum iav_bsb_mode {
	IAV_SINGLE_BSB  = 0x0,	/*!< user app and DSP share the same BSB buffer */
	IAV_DUAL_BSB    = 0x1,	/*!< user app and DSP have their own BSB buffer separately */
};

/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_system_info {
	u16 query_source; /*!< Query Source ID, @sa iav_system_query_source */
	u16 boot_mode;    /*!< System Boot Mode, @sa iav_boot_mode */
	u16 reserved[2];
};

struct iav_canvas_info {
	u32 canvas_id : 8;	/*!< Canvas ID */
	u32 reserved0 : 24;
	enum iav_canvas_type type;		/*!< Canvas Type enumeration, @sa iav_canvas_type */
	enum iav_canvas_state state;	/*!< Canvas State enumeration, @sa iav_canvas_state */
	u32 reserved1;
	unsigned long mem_phys_addr;	/*!< Canvas memory partition base physical address */
	unsigned long mem_size;			/*!< Canvas memory partition size */
};

struct iav_stream_info {
	u32 id; /*!< Stream ID */
	enum iav_stream_state state;	/*!< Stream State enumeration, @sa iav_stream_state */
};

struct iav_privacy_mask_info {
	u8 channel_id;		/*!< Specify the channel ID to get privacy mask information */
	u8 multi_factor;	/*!< It only reports the Single Color Mask buffer to Main buffer scaling factor */
	u16 buffer_width;	/*!< It reports the Single Color Mask or Multi Color Mask buffer width */
	u16 buffer_height;	/*!< It reports the Single Color Mask or Multi Color Mask buffer height */
	u16 buffer_pitch;	/*!< It reports the Single Color Mask or Multi Color Mask buffer pitch */
};

struct iav_bsb_stats_info {
	u32 frame_drop_cnt;		/*!< dropped frame count of BSB */
	u32 frame_locked_cnt;		/*!< locked frame count of BSB */
	u32 free_kbytes;		/*!< free kbytes of BSB */
	enum iav_bsb_mode bsb_mode;	/*!< BSB mode. @ref iav_bsb_mode */
};

struct iav_queryinfo {
	enum iav_info_id qid;
	union {
		struct iav_system_info system_info;	/*!< Query system info */
		struct iav_driver_version driver;	/*!< Query driver version */
		struct iav_canvas_info canvas;		/*!< Query canvas info, such as state / type */
		struct iav_stream_info stream;		/*!< Query stream info, such as state */
		struct iav_privacy_mask_info mask_info;	/*!< Query single color or multi color mask info */
		struct iav_unique_id unique_id;	/*!< Query unique ID */
		u64 chip_wafer_id;	/*!< Query Chip Unique Wafer ID */
		struct iav_bsb_stats_info bsb_stats;	/*!< Query BSB statistic info */
	} arg;
};

struct iav_dsp_auth {
	enum iav_dsp_auth_type type;	/*!< DSP authentication type */
	union {
		struct iav_dsp_auth_unique_id auth_unique_id;	/*!< Authenticatoin for Unique ID */
		struct iav_dsp_auth_arm auth_arm;				/*!< Authentication for ARM */
	} auth;
};

struct iav_dsp_dump_cmd_query_mem {
	unsigned long phy_addr;	/*!< Memory address for saving dumped DSP commands */
};

struct iav_dsp_dump_cmd_query_result {
	u32 amount : 8;			/*!< Total amount of dumped DSP commands */
	u32 capacity : 8;		/*!< Maximum number of DSP commands can be dumped */
	u32 size : 10;			/*!< Size of single DSP command */
	u32 is_overflow : 1;	/*!< Whether it overflows. 0:not overflow; 1:overflow */
	u32 reserved : 5;
};

struct iav_dsp_dump_cmd_ctrl_dump {
	u32 do_dump;			/*!< Start or Stop dump. 0:stop dumping; 1:start dumping */
};

struct iav_dsp_dump_cmd_ctrl_mem {
	u32 pid;	/*!< Specify memory partition id */
};

struct iav_dsp_dump_cmd_query {
	u32 query_type;		/*!< Query type, @sa iav_dsp_dump_cmd_query_type */
	union {
		struct iav_dsp_dump_cmd_query_result result;
		struct iav_dsp_dump_cmd_query_mem mem;
	};
};

struct iav_dsp_dump_cmd_ctrl {
	u32 ctrl_type;		/*!< Control type, @sa iav_dsp_dump_cmd_ctrl_type */
	union {
		struct iav_dsp_dump_cmd_ctrl_dump dump;
		struct iav_dsp_dump_cmd_ctrl_mem mem;
	};
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_system_params {
	IAV_STREAM_MAX_NUM_IMPL		= 10, /*!< 10 */
	IAV_STREAM_MAX_NUM_EXTRA	= 3,  /*!< 3 */
	IAV_STREAM_MAX_NUM_ALL		= (IAV_STREAM_MAX_NUM_IMPL + IAV_STREAM_MAX_NUM_EXTRA), /*!< IAV_STREAM_MAX_NUM_IMPL + IAV_STREAM_MAX_NUM_EXTRA */
};

enum iav_hdr_type {
	HDR_TYPE_OFF			= 0, /*!< 0 */
	HDR_TYPE_BASIC			= 1, /*!< 1 */
	HDR_TYPE_ADV_WITH_CE		= 2, /*!< 2 */
	HDR_TYPE_TOTAL_NUM		= 3, /*!< 3 */
};

enum iav_iso_type {
	ISO_TYPE_LOW		= 0, /*!< 0 */
	ISO_TYPE_MIDDLE		= 1, /*!< 1 */
	ISO_TYPE_ADVANCED	= 2, /*!< 2 */
	ISO_TYPE_CISO		= 3, /*!< 3 */
	ISO_TYPE_HIGH		= 4, /*!< 4 */
	ISO_TYPE_FUSION		= 5, /*!< 5 */
	ISO_TYPE_AISP		= 6, /*!< 6 */
	ISO_TYPE_TOTAL_NUM	= 7, /*!< 7 */
	ISO_TYPE_FIRST		= ISO_TYPE_LOW, /*!< ISO_TYPE_LOW */
	ISO_TYPE_LAST		= ISO_TYPE_TOTAL_NUM, /*!< ISO_TYPE_TOTAL_NUM */
};

enum iav_max_vwarp_waitlines_count {
	VWARP_WAITLINES_MIN = 0, /*!< 0 */
	VWARP_WAITLINES_LDC_DEFAULT = 64, /*!< 64, ONLY for encode mode 0 */
	VWARP_WAITLINES_MAX = 1023, /*!< 1023 */
};

enum iav_max_vwarp_blk_height {
	VWARP_BLK_HEIGHT_MIN = 28, /*!< 28 */
	VWARP_BLK_HEIGHT_MAX = 64, /*!< 64 */
};

enum iav_eis_delay_count {
	EIS_DELAY_COUNT_OFF = 0, /*!< 0 */
	EIS_DELAY_COUNT_GOLDEN = 3,  /*!< 3 */
	EIS_DELAY_COUNT_MAX = 7, /*!< 7 */
};

enum iav_back_pressure_margin {
	BACK_PRESSURE_MARGIN_OFF	= 0, /*!< 0 */
	BACK_PRESSURE_MARGIN_MAX	= 3, /*!< 3 */
};

enum iav_me0_scale {
	ME0_SCALE_OFF		= 0, /*!< 0 */
	ME0_SCALE_8X		= 1, /*!< 1 */
	ME0_SCALE_16X		= 2, /*!< 2 */
	ME0_SCALE_TOTAL_NUM	= 3, /*!< 3 */
};

enum iav_debug_type {
	DEBUG_TYPE_STITCH				= (1 << 0), /*!< 1 << 0 */
	DEBUG_TYPE_CHIP_ID				= (1 << 1), /*!< 1 << 1 */
	DEBUG_TYPE_MAX_CHROMA_RADIUS	= (1 << 2), /*!< 1 << 2 */
	DEBUG_TYPE_SKIP_EFM_MB			= (1 << 3), /*!< 1 << 3 */
	DEBUG_TYPE_BREAK_POINT			= (1 << 4), /*!< 1 << 4 */
	DEBUG_TYPE_VP_DRAM_PRIORITY		= (1 << 5), /*!< 1 << 5 */
	DEBUG_TYPE_VSYNC_LOSS_TIMEOUT		= (1 << 6), /*!< 1 << 6 */
	DEBUG_TYPE_HEVC_ENC_MODE		= (1 << 7), /*!< 1 << 7 */
	DEBUG_TYPE_HEVC_HI_DRAM_EF_MODE		= (1 << 8), /*!< 1 << 8 */
	DEBUG_TYPE_RESET_SEQ_NUM_IN_IDLE	= (1 << 9), /*!< 1 << 9 */
};

/*! @enum iav vsync loss timeout
 *  @brief vsync loss timeout limitation on milli second unit.
 *  Usually, it's mainly used for debug purpose.
 */
enum iav_vsync_loss_timeout {
	IAV_VSYNC_LOSS_TIMEOUT_MIN		= 32,	/*!< 32 ms */
	IAV_VSYNC_LOSS_TIMEOUT_DEFAULT	= 2048,	/*!< 2048 ms */
	IAV_VSYNC_LOSS_TIMEOUT_MAX		= 4095,	/*!< 4095 ms */
};

/*! @enum iav extra raw dram buf
 *  @brief iav extra raw dram buffer limitation. Default is zero.
 *  Usually, it's mainly used for debug purpose. The larger extra buffer, DSP
 *  takes more DRAM footprint and can save more RAW images into memory.
 */
enum iav_extra_raw_dram_buf {
	IAV_EXTRA_RAW_DRAM_BUF_MIN		= 0,
	IAV_EXTRA_RAW_DRAM_BUF_MAX		= 128,
};

enum iav_enc_dummy_latency {
	IAV_ENC_DUMMY_LATENCY_MIN		= 0,
	IAV_ENC_DUMMY_LATENCY_MAX		= 8,
};

#define IAV_INVALID_CANVAS_ID	(0xFF)

enum iav_srcbuf_id {
	IAV_SRCBUF_MN			= 0,	/*!< 0, main buffer */
	IAV_SRCBUF_PC			= 1,	/*!< 1, 2nd buffer */
	IAV_SRCBUF_PB			= 2,	/*!< 2, 3rd buffer */
	IAV_SRCBUF_PA			= 3,	/*!< 3, 4th buffer */
	IAV_SRCBUF_PD			= 4,	/*!< 4, 5th buffer */
	IAV_SRCBUF_PE			= 5,	/*!< 5, 6th buffer */
	IAV_SRCBUF_PMN			= 6,	/*!< 6, virtual pre-main buffer, only for dewarp mode */
	IAV_SRCBUF_NUM			= 7,	/*!< 7 */

	IAV_SRCBUF_EFM			= 16,	/*!< 16, EFM buffer ID for starting EFM streams */
	IAV_SRCBUF_JS			= 17,	/*!< 17, JPEG service buffer ID for starting JPEG service stream */

	/* For user space convenience */
	IAV_SRCBUF_1			= IAV_SRCBUF_MN, /*!< IAV_SRCBUF_MN */
	IAV_SRCBUF_2			= IAV_SRCBUF_PC, /*!< IAV_SRCBUF_PC */
	IAV_SRCBUF_3			= IAV_SRCBUF_PB, /*!< IAV_SRCBUF_PB */
	IAV_SRCBUF_4			= IAV_SRCBUF_PA, /*!< IAV_SRCBUF_PA */
	IAV_SRCBUF_5			= IAV_SRCBUF_PD, /*!< IAV_SRCBUF_PD */
	IAV_SRCBUF_6			= IAV_SRCBUF_PE, /*!< IAV_SRCBUF_PE */

	IAV_SRCBUF_FIRST		= IAV_SRCBUF_MN, /*!< IAV_SRCBUF_MN */
	IAV_SRCBUF_LAST			= IAV_SRCBUF_PMN, /*!< IAV_SRCBUF_PMN */
	IAV_SRCBUF_LAST_PMN		= IAV_SRCBUF_PMN + 1, /*!< IAV_SRCBUF_PMN + 1 */
	IAV_SUB_SRCBUF_FIRST		= IAV_SRCBUF_PC, /*!< IAV_SRCBUF_PC */
	IAV_SUB_SRCBUF_LAST		= IAV_SRCBUF_PMN, /*!< IAV_SRCBUF_PMN */

	IAV_SRCBUF_INPUT_H_ALIGN		= 4,	/*!< 4 */
	IAV_SRCBUF_INPUT_V_ALIGN		= 2,	/*!< 2 */
	IAV_SRCBUF_INPUT_X_ALIGN		= 4,	/*!< 4 */
	IAV_SRCBUF_INPUT_Y_ALIGN		= 2,	/*!< 2 */
	IAV_SRCBUF_INPUT_WIDTH_ALIGN		= 4,	/*!< 4 */
	IAV_SRCBUF_INPUT_HEIGHT_ALIGN		= 8,	/*!< 8 */
	IAV_SRCBUF_OUTPUT_X_ALIGN	= 2,	/*!< 2 */
	IAV_SRCBUF_OUTPUT_Y_ALIGN	= 4,	/*!< 4 */
	IAV_SRCBUF_OUTPUT_WIDTH_ALIGN	= 32,	/*!< 32 */
	IAV_SRCBUF_OUTPUT_HEIGHT_ALIGN	= 16,	/*!< 16 */
};

enum iav_codec_option {
	IAV_CODEC_H265_H264_MJPEG	= 0x0, /*!< 0x0 */
	IAV_CODEC_H265_MJPEG		= 0x1, /*!< 0x1 */
	IAV_CODEC_H264_MJPEG		= 0x2, /*!< 0x2 */
	IAV_CODEC_MJPEG_ONLY		= 0x3, /*!< 0x3 */
	IAV_CODEC_TOTAL_NUM			= 0x4, /*!< 0x4 */
};

enum iav_srcbuf_state {
	IAV_SRCBUF_STATE_UNKNOWN	= 0, /*!< 0 */
	IAV_SRCBUF_STATE_IDLE		= 1, /*!< 1 */
	IAV_SRCBUF_STATE_BUSY		= 2, /*!< 2 */
	IAV_SRCBUF_STATE_ERROR		= 255, /*!< 255 */
};

enum iav_pyramid_scale {
	IAV_PYRAMID_SCALE_SQRT2		= 0,	/*!< 0, 1/sqrt(2) for each layers, both width and height */
	IAV_PYRAMID_SCALE_2X		= 1,	/*!< 1, 1/2 for each layers, both width and height */
	IAV_PYRAMID_SCALE_ARBITRARY = 2,	/*!< 2, arbitrary size for pyramid layer 1 */
};

enum iav_sync_type {
	IAV_FRAME_SYNC		= 0, /*!< 0 */
	IAV_STREAM_SYNC		= 1, /*!< 1 */
	IAV_IDSP_ENC_SYNC	= 2, /*!< 2 */
	IAV_NONE_SYNC		= 3, /*!< 3 */
	IAV_SYNC_TYPE_NUM	= 4, /*!< 4 */
};

/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_frame_tag {
	u32 value;	/*!< Frame tag pattern value. */
	u32 mask;	/*!< Frame tag pattern mask. */
};

struct iav_pyramid_cfg {
	u32 chan_id : 4;	/*!< input channel ID. */
	u32 enable : 1;		/*!< This is a flag to specify if the pyramid is enabled. */
	u32 reserved0 : 3;
	u32 input_buf_id : 8;	/*!< input source buffer ID. */
	u32 layers_map : 6;	/*!< bit map for pyramid layers, one bit for one layer, can be changed dynamically. */
	u32 manual_feed : 1;	/*!< bit flag to control manual feed mode. 1 means using manual feed, 0 means using internal buffer. */
	u32 set_min_unlocked_buf_num : 1;	/*!< bit flag to control whether use @min_unlocked_buf_num or not. 1: set; 0: not set. */
	u32 item_num : 8;	/*!< pyramid buffer item num for manual feed case. Only valid when @b manual_feed is set. */
	enum iav_pyramid_scale scale_type;	/*!< pyramid scale type, @sa iav_pyramid_scale. */
	unsigned long buf_addr;	/*!< External pyramid buffer addr. */
	u32 buf_size;			/*!< Pyramid buffer pool size. When manual_feed is set, user app can specify a fixed pyramid buffer pool size.
		Then it won't be reallocated any more. */
	u8 frame_rate;			/*!< Frame rate for the pyramid output layers. */
	u8 min_unlocked_buf_num; /*!< Pyramid minimum unlocked buf num. When users want to set min_unlocked_buf_num accordingly, user need
		enable @manual_feed and @set_min_unlocked_buf_num first. Meanwhile, @item_num > @min_unlocked_buf_num. */
	u8 max_layers_map : 6;	/*!< Max bit map for pyramid layers, one bit for one layer, can only be changed before preview. @layers_map
		should be within @max_layers_map. */
	u8 enable_frame_tag : 1;	/*!< This is a flag to enable / disable frame tag pattern. */
	u8 reserved1 : 1;
	u8 cached_items : 6;	/*!< The pyramid cached items for user to query with blocking call, default: 1. */
	u8 reserved2 : 2;
	struct iav_rect crop_win[IAV_MAX_PYRAMID_LAYERS];	/*!< Cropping window in each layer output coordinate. */
	struct iav_window rescale_size;	/*!< Rescale size for pyramid layer 1. The scale ratio of width or height from layer_0 to
		layer_1 must be in the range of <b>(1/8, 1](Downscale)</b>. The scale ratio from layer_N(N = 1 ~ 4) to layer_N+1 is
		fixed to 2X (Downscale). Only valid when <b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>. */
	struct iav_window max_rescale_size;	/*!< Max rescale size for pyramid layer 1. Used to set the max rescale size of pyramid layer 1,
		@rescale_size should be within @max_scale_size. Only valid when <b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>. */
	struct iav_frame_tag frame_tag;	/*!< Pyramid frame tag pattern. When the frame's RAW frame tag matches this pyramid frame tag pattern value,
		this frame data would be written into this pyramid. Otherwise, this frame data would be skipped for this pyramid. Only valid when
		enable_frame_tag = 1 and iav_system_source.enabled_canvas_frame_tag = 1.*/
	u32 frame_rate_hp;	/*!< High precision framerate. frame_rate_hp = 1000 * frame_rate. For setting, only valid when "enable_hp_flag" is 1.
		For getting, value is always valid. */
};

struct iav_buf_cfg {
	struct iav_rect input;	/*!< Source Buffer input offset and size */
	struct iav_rect output; /*!< Source Buffer output offset and size */
	u32 canvas_id : 8;	/*!< Canvas ID */
	u32 reserved : 24;
};

struct iav_dptz {
	u8 channel_id;	/*!< Channel ID */
	u8 pass_id;		/*!< Pass ID */
	u8 buf_id;		/*!< Source Buffer ID */
	u8 reserved;
	struct iav_buf_cfg buf_cfg; /*!< Source Buffer configuration */
};

struct iav_stream_resource {
	struct iav_window max_size;	/*!< The maximum resolution for encode streams, which is used for allocating memory in DSP. It is recommended not to exceed the main source buffer resolution. */
	struct iav_window efm_size;	/*!< The efm buffer size and only used when efm_enable is 1. */
	u32 max_M : 8;			/*!< The maximum GOP M for each streams. Streams will have B frames when M > 1. Stream A can have larger range of M from 1 to 3, while the other streams are limited to 1. */
	u32 fast_seek_enable : 1;	/*!< Fast seek enable flag for each stream. */
	u32 two_ref_enable : 1;		/*!< Two ref enable flag for each stream. */
	u32 max_svct_layers_minus_1 : 2;/*!< This is a flag to specify the value for the maximum SVCT layers minus 1. */
	u32 max_num_minus_1_ltrs : 1;	/*!< Maximum long term number minus 1 for stream */
	u32 codec_enable : 3;		/*!< Stream codec configuration @sa iav_codec_option */
	u32 stream_mv_statis_enable : 1;/*!< This is a flag to enable MV(motion vector) dump for each stream. */
	u32 efm_enable : 1;			/*!< This is a flag to enable / disable encoding from memory */
	u32 efm_buf_num : 4;		/*!< The efm buffer number in one efm buffer pool and only used when efm_enable is 1 */
	u32 efm_skip_waiting : 1;	/*!< The efm_skip_waiting skip waiting for encoding start/stop status when it's value is 1 and only used when efm_enable is 1 */
	u32 stream_pic_statis_enable : 1;/*!< This is a flag to enable picture statistic dump for each stream. */
	u32 efm_extern_src_enable : 1;	/*!< Enable to use EFM buffer of other streams' */
	u32 efm_extern_src_stream : 7;	/*!< Specify stream ID of shared EFM buffer */
	u16 possible_enc_src_map; /*!< This is to specify the possible encoding source canvas map for a stream. */
	u8 dis_enable : 1;		/*!< This is a flag to enable DIS mode stream. */
	u8 dis_cached_items : 7;	/*!< Specify DIS stream statistics cached items and only used when stream dis_enable is 1. */
	u8 js_enable : 1;	/*!< This is a flag to enable stream for JPEG service. 0(Default): normal stream; 1: JPEG service stream. */
	u8 reserved1 : 7;
	u32 reserved2[2];
};

struct iav_canvas_order {
	u32 id : 5;		/*!< Canvas ID */
	u32 valid : 1;		/*!< This is a flag to enable / disable Canvas Channel Order. */
	u32 chan_num : 4;	/*!< The total number of channels whose source buffers are on current Canvas. */
	u32 reserved : 22;
	u8 chan_order[IAV_MAX_CHANNEL_NUM]; /*!< Channel orders */
};

struct iav_canvas_fps {
	u32 id : 5;		/*!< Canvas ID */
	u32 zero_fps : 1; /*!< When zero_fps is 0, "frame_rate = 0" represents idsp_fps. When zero_fps = 1, "frame_rate = 0" is real 0 fps. */
	u32 reserved : 26;
	u32 frame_rate; /*!< Canvas frame rate */
	u32 frame_rate_hp;	/*!< High precision framerate. frame_rate_hp = 1000 * frame_rate. For setting, only valid when "enable_hp_flag" is 1.
		For getting, value is always valid. */
};

struct iav_canvas_cfg {
	struct iav_window max;	/*!< Canvas width and height */
	enum iav_canvas_type type; /*!< Canvas Type, @sa iav_canvas_type */
	s8 extra_dram_buf;	/*!< The extra dram buffer number for current Canvas. Valid range -3~4. */
	u8 vout_id : 1;		/*!< This is a flag to set VOUT ID. It is valid only when Canvas Type is IAV_CANVAS_TYPE_PREVIEW. */
	u8 vout_YUV422 : 1;	/*!< Specify VOUT YUV data format. 0: YUV420; 1: YUV422. It is valid only when Canvas Type is IAV_CANVAS_TYPE_PREVIEW. */
	u8 reserved0 : 6;
	u8 frame_rate;		/*!< Frame rate for the canvas containing sub source buffers. */
	u8 clear_background : 1;	/*!< Clear this canvas memory to blackground color after entering preview. */
	u8 enc_dummy_latency : 4;	/*!< The encode dummy latency buffer number for current Canvas. Valid range 0~8.
					Please make sure enc_dummy_latency option in struct iav_system_resource is 0 when using this option. */
	u8 dsp_priv_dram : 1;	/*!< Enable flag to move canvas buffer from DSP-ARM shared DRAM space into DSP private DRAM space. */
	u8 disable_yuv_dram : 1;	/*!< This is a flag to allow dsp allocate canvas yuv buffer or not. 0(Default): Allocate buffer; 1: Not allocate buffer. */
	u8 set_min_unlocked_buf_num : 1;	/*!< bit flag to control whether use @min_unlocked_buf_num or not. 1: set; 0: not set*/
	struct iav_canvas_order order;	/*!< Canvas Channel Order, @sa iav_canvas_order */
	u8 cached_items;	/*!< The cached canvas items for user to query with blocking call, Valid range: 1~@extra_dram_buf; Default: 1. */
	u8 min_unlocked_buf_num;	/*!< Canvas minimum unlocked buf num. When users want to set min_unlocked_buf_num accordingly, user need
		enable @manual_feed and @set_min_unlocked_buf_num first. Meanwhile, @feed_frame_num > @min_unlocked_buf_num */
	u8 enable_frame_tag : 1;	/*!< This is a flag to enable / disable frame tag pattern. */
	u8 zero_fps  : 1;	/*!< When zero_fps is 0, "frame_rate = 0" represents idsp_fps. When zero_fps = 1, "frame_rate = 0" is real 0 fps. */
	u8 is_broken : 1;	/*!< This is a flag to show this canvas is enabled or disabled according to
			its vsrc operation. 0(Default): enabled, 1: disabled. */
	u8 fps_locked_enable : 1;	/*< Keep canvas fps locked. When idsp fps is changed on the fly, it will not be changed proportionally
		when it is <= idsp fps.*/
	u8 reserved1 : 4;
	u8 manual_feed : 1;	/*!< bit flag to control manual feed mode. 1 means using manual feed, 0 means using internal buffer. */
	u8 feed_frame_num : 7;	/*!< canvas frame item num for manual feed case. Only valid when @b manual_feed is set. */
	struct iav_frame_tag frame_tag;	/*!< Canvas frame tag pattern. When the frame's RAW frame tag matches this canvas frame tag pattern value,
		this frame data would be written into this canvas. Otherwise, this frame data would be skipped for this
		canvas. Only valid when enable_frame_tag = 1 and iav_system_source.enabled_canvas_frame_tag = 1. */
	u32 frame_rate_hp;	/*!< High precision framerate. frame_rate_hp = 1000 * frame_rate. For setting, only valid when "enable_hp_flag" is 1.
		For getting, value is always valid. */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum IAV_BLEND_AREA {
	IAV_BLEND_LEFT_OR_TOP 	= 0, /*!< 0, This stands for left channel or top channel. */
	IAV_BLEND_RIGHT_OR_BOT 	= 1, /*!< 1, This stands for right channel or bottom channel. */
	IAV_BLEND_NUM		= 2, /*!< 2 */
	IAV_BLEND_INVALID	= 0xFF, /*!< 0xFF */
};

enum IAV_BLEND_PARAM {
	IAV_BLEND_NONBLOCK				= (1 << 0), /*!< 1 << 0 */
	IAV_BLEND_ALPHA_ADDR_INVALID	= 0xFFFFFFFF, /*!< 0xFFFFFFFF */
	IAV_BLEND_OVERLAP_AREA_MAX		= 0x7, /*!< 0x7. Maximum overlap area number. */
};

enum IAV_BLEND_TYPE {
	IAV_BLEND_TYPE_NONE = 0, /*!< 0 */
	IAV_BLEND_TYPE_HOR = 1, /*!< 1, This is to specify multi-channel stitched horizontally (Left & Right). */
	IAV_BLEND_TYPE_VER = 2, /*!< 2, This is to specify multi-channel stitched vertically (Top & Bottom). */
	IAV_BLEND_TYPE_NUM, /*!< 3 */

	IAV_BLEND_TYPE_FIRST = IAV_BLEND_TYPE_NONE, /*!< IAV_BLEND_TYPE_NONE */
	IAV_BLEND_TYPE_LAST = IAV_BLEND_TYPE_NUM, /*!< IAV_BLEND_TYPE_NUM */
};

#define IAV_CUSTOM_SEI_SIZE_MIN		(16)
#define IAV_CUSTOM_SEI_SIZE_MAX		(0x8000)

enum iav_yuv_format {
	IAV_YUV_FORMAT_YUV422	= 0, /*!< 0 */
	IAV_YUV_FORMAT_YUV420	= 1, /*!< 1 */
	IAV_YUV_FORMAT_YUV400	= 2, /*!< 2 */
};

#define IAV_IMG_SCALE_BUF_ALIGN				(4)
#define IAV_IMG_SCALE_BUF_PITCH_ALIGN		(64)
#define IAV_IMG_SCALE_Q_DEPTH_MAX	(16)
#define IAV_IMG_SCALE_Q_DEPTH_MIN	(8)

enum iav_chroma_radius_num {
	CHROMA_RADIUS_32		= 0, /*!< 0 */
	CHROMA_RADIUS_64		= 1, /*!< 1 */
	CHROMA_RADIUS_128		= 2, /*!< 2 */
	CHROMA_RADIUS_TOTAL_NUM,
};

/*! @enum iav_app_img_profile
 *  @brief Application image 3A profile enum.
 */
enum iav_app_img_profile {
	APP_IMG_PROFILE_IPC		= 0, /*!< 0 */
	APP_IMG_PROFILE_BWC		= 1, /*!< 1 */
	APP_IMG_PROFILE_ITS		= 2, /*!< 2 */
	APP_IMG_PROFILE_DVR		= 3, /*!< 3 */
	APP_IMG_PROFILE_DMS		= 4, /*!< 4 */
	APP_IMG_PROFILE_ADAS	= 5, /*!< 5 */
	APP_IMG_PROFILE_OMC		= 6, /*!< 6 */
	APP_IMG_PROFILE_EMIRROR	= 7, /*!< 7 */
	APP_IMG_PROFILE_STEREO	= 8, /*!< 8 */
	APP_IMG_PROFILE_BYPASS_ISP	= 9, /*!< 9 */
	APP_IMG_PROFILE_ROBOT		= 10, /*!< 10 */
	APP_IMG_PROFILE_NUM,
	APP_IMG_PROFILE_FIRST	= APP_IMG_PROFILE_IPC,	/*!< APP_IMG_PROFILE_IPC */
	APP_IMG_PROFILE_LAST	= APP_IMG_PROFILE_NUM,	/*!< APP_IMG_PROFILE_NUM */
};

/*! @enum iav_sys_cfg_id
 *  @brief System resource configure enum.
 */
enum iav_sys_cfg_id {
	IAV_SYS_CFG_GENERAL		= 0x00, /*!< 0x00 */
	IAV_SYS_CFG_CHANNEL		= 0x01, /*!< 0x01 */
	IAV_SYS_CFG_CANVAS		= 0x02, /*!< 0x02 */
	IAV_SYS_CFG_STREAM		= 0x03, /*!< 0x03 */
	IAV_SYS_CFG_IMGSCALE		= 0x04, /*!< 0x04 */
	IAV_SYS_CFG_DEBUG		= 0x05, /*!< 0x05 */
	IAV_SYS_CFG_NUM			= 0x06, /*!< 0x06 */
};

/*! @enum iav_mc_mask_buf_downscale_mode
 *  @brief Specify multi-color privacy mask buffer downscale mode enum.
 */
enum iav_mc_mask_buf_downscale_mode {
	IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_4X	= 0, /*!< multi-color privacy mask buf = VIN resolution / 4 */
	IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_16X	= 1, /*!< multi-color privacy mask buf = VIN resolution / 16 */
	IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_256X	= 2, /*!< multi-color privacy mask buf = VIN resolution / 256 */
	IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_MODE_NUM,
	IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_FIRST = IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_4X,
	IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_LAST = IAV_MULTI_COLOR_MASK_BUF_DOWNSCALE_MODE_NUM,
};

/*! @enum iav_raw_format
 *  @brief Specify cfa raw or hdec raw format enum.
 */
enum iav_raw_format {
	IAV_RAW_FORMAT_DEFAULT		= 0, /*!< For cfa raw, it is uncompressed unpacked raw;
		for hds raw, it follows cfa raw format. */
	IAV_RAW_FORMAT_PACKED		= 1, /*!< Uncompressed packed cfa raw or hdec raw.
		it is packed according to vin_format->bit_resolution. */
	IAV_RAW_FORMAT_COMPRESSED	= 2, /*!< Compressed cfa raw or hdec raw. */
	IAV_RAW_FORMAT_NUM,
};

/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_pass_cfg {
	u8 input_pass_id;	/*!< Input pass ID for current pass */
	u8 input_buf_id;	/*!< Input buffer ID for current pass, fixed from Main (0) only */
	u8 reserved[2];
};

struct iav_chan_cfg {
	u8 vsrc_id;					/*!< VIN Source ID from which current channel gets the raw data */
	u8 pass_num;				/*!< Total pass num for current channel */
	u16 amba_img_flow_mode : 4;	/*!< This is a flag to show 3A img flow mode. 0: Linear; 1: 2x HDR; 2: 3x HDR;
					3: 4x HDR; 15: WDR. @b Read @b Only. */
	u16 idsp_fps_locked_enable : 1;	/*!< Keep channel IDSP fps locked, not changed with VIN frame rate */
	u16 min_iso_retire_frames : 5;	/*!< Minimum iso cfg retire latency at frames. @b Read @b Only. */
	u16 is_broken : 1;	/*!< This is a flag to show this channel is enabled or disabled according to its vsrc
					operation. 0(Default): enabled; 1: disabled. @b Read @b Only. */
	u16 group_sync : 1;	/*!< Enable channel grouping synchronization. 0(default): disable; 1: enable */
	u16 eis_delay_count : 3;	/*!< This is a param to specify EIS delay frame num before IDSP pipeline for each channel. Valid range is 0~7. Default is 0. */
	u16 dis_enable : 1;	/*!< This is a flag to enable DIS mode. It is only valid when vcap_mode_flags is DSP_MULTI_YUV_INPUT_MODE. */
	struct iav_rect input;				/*!< The capture raw area from VIN. Currently always default to the whole VIN area. */
	struct iav_pass_cfg pass_cfg[IAV_MAX_PASS_NUM];
	struct iav_window buf_max[IAV_MAX_PASS_NUM][IAV_SRCBUF_NUM];	/*!< The maximum resolution(only width is needed)
					for source buffers, which is used for allocating line buffers in DSP. It is recommended not
					to exceed the sensor resolution. */
	u16 max_padding_width;		/*!< The maximum padding width for LDC stitching. It should only be set when @b lens_warp_enable = 1. */
	u16 max_main_input_width;	/*!< The maximum input width for main buffer. This param needs to be configured when user application
					wants to get a small main buffer input size like 720x480 with a large vin size like 3840x2160. If
					this param is set, main buffer input width cannot exceed it through run-time update during Prevew /
					Encoding state. Default is 0(equals to VIN raw width). */
	u8 lens_warp_hi_ef_factor : 3;	/*!< This is a param to specify lens warp high efficiency factor. Valid range 0~4.
					The larger the more DSP H/W resource will be costed. It is only valid when vcap_mode_flags = 0. */;
	u8 reserved1 : 5;
	u8 blend_left_or_top : 1;		/*!< This is a flag to enable / disable left / top channel blend. It's ONLY available when
								system is NOT IAV_BLEND_TYPE_NONE. */
	u8 blend_right_or_bot : 1;	/*!< This is a flag to enable / disable right / bot channel blend. It's ONLY available when
								system is NOT IAV_BLEND_TYPE_NONE. */
	u8 mctf_cmpr : 1;		/*!< This is a flag to enable / disable mctf compression. Default is 1. */
	u8 mctf_10bit_ref : 1;		/*!< This is a flag to enable / disable mctf 10-bit reference. Default is 0. */
	u8 main_burst_tile : 1; 	/*!< This is a flag to enable / disable main burst tile mode. Default is 1. */
	u8 vin_overflow_protection : 1; /*!< This is a flag to enable / disable VIN overflow protection. */
	u8 lens_warp_enable : 1;	/*!< This is a flag to enable / disable lens warp. It must be enabled if user want to test LDC function. */
	u8 use_vsrc_ctx_pattern : 1;	/*!< This is a flag to enable / disable vsrc_ctx pattern mode. */
	u8 img_stats_src_chan;		/*!< The source channel ID whose 3A statistic data is used to do 3A control for current channel.
					Generally, each channel uses its own 3A statistic data to do 3A control. While for application
					cases like multi-channel from single vin or stitching among different channels, all channels
					can use the same channel's 3A statistic data to do 3A control. */
	u8 vsrc_ctx;		/*!< Specify the sensor Context ID of vsrc_id for current channel.
					For dual-context supported sensors, vsrc_ctx can be set to 1. Else, only 0 is used. */
	u32 vsrc_ctx_pattern;	/*!< vsrc_ctx pattern. Only valid when use_vsrc_ctx_pattern = 1. */
	u32 vsrc_ctx_pattern_mask;	/*!< vsrc_ctx pattern mask. Only valid when use_vsrc_ctx_pattern = 1. */
	u32 sensor_ctrl : 1;		/*!< This is a flag to enable / disable setting shutter/agc control to current channel's
						VIN Source. When current channel is a virtual channel in multi-channel from single vin case,
						need to set this flag to 0. Default is 1. */
	u32 expo_num : 3;	/*!< Exposure number. Valid range is 1~4. By default, IAV driver sets expo_num
						according to hdr_mode in struct vindev_mode */
	u32 hdr_type : 2;		/*!< Current Channel's HDR mode. @b Read @b Only. */
	u32 low_delay_vin_vout : 1; 	/*!< This is a flag to enable / disable low delay vin / vout. Only valid in enc-mode 0. */
	u32 max_vwarp_wait_lines : 10;	/*!< Specify maximum vwarp wait lines for LDC and fisheye dewarp use case. */
	u32 invert_mode : 1;	/*!< This is a flag to enable / disable invert mode. Default is 0. */
	u32 packing_mode_enable : 1;	/*!< This is a flag to enable / disable VIN packing mode. Only valid when raw_capture_enable = 1. */
	u32 rotate_cw : 1;	/*!< Channel clockwise 90 degree rotation flag; 0: No clockwise rotation of 90; 1: A clockwise rotation of 90. */
	u32 hflip : 1;		/*!< Channel horizontal flip flag; 0: No horizontal flip; 1: Horizontal flip */
	u32 vflip : 1;		/*!< Channel vertical flip flag; 0: No vertical flip; 1: Vertical flip */
	u32 extra_downscale_enable : 1;	/*!< Enable extra downscale if downscale >= 6X. Default is 0. */
	u32 is_still_fusion_proc : 1;	/*!< This is a flag to specify whether current channel does still fusion or video fusion. */
	u32 vcap_mode_flags : 8;	/*!< This is to specify vcap_mode for each channel. Only valid when chan_vcap_mode_enable = 1.
								Vcap modes for different cases. @sa dsp_mode.
										0x00:  Advanced ISO mode. This is the mode for lowest latency from VIN to VOUT.
										0x01:  Multiple Region Warp mode. This is the mode for multi-region fisheye dewarp.
										0x02:  Sensor Fusion mode. This is the mode for Video or Image fusion.
										0x03:  Multiple Pass IDSP Rotation mode. This is the mode for multi-pass scale with rotation.
										0x04:  Multiple Output Fusion mode. This mode can be used for TML and RGB fusion.
										0x05:  Line interleaved HDR mode. This is the mode for 3X HDR and multi-pass scale.
										0x06:  Multiple YUV input mode. This is the mode for multiple YUV input, only available for CV2 & CV22.
										0x7F:  Mode none. This is the mode to skip ISP processing for current channel.
										0x80:  Automatic mode. This is the flag to let vcap_mode_flags follow encode_mode. */
	u16 max_warp_input_width;	/*!< The maximum warp input width. It's used when LDC or dewarp functions enabled. */
	u16 max_warp_output_width;	/*!< The maximum warp output width. It's used when LDC or dewarp functions enabled. */
	u32 max_vwarp_blk_height : 7;	/*!< Specify maximum vwarp block height for LDC use case. */
	u32 raw_capture : 1;	/*!< Individual raw capture enable flag. */
	u32 app_img_profile : 5;	/*!< The image 3A profile for different scenarios (IPC or Auto), @sa iav_app_img_profile. */
	u32 vsrc_region_num : 4;	/*!< The number of regions(line-interleaved) in a single vsrc. */
	u32 vsrc_region_map : 4;	/*!< The region index map for current channel. */
	u32 mc_mask_buf_ds : 3;	/*!< The multi-color mask downscale mode from VIN resolution. */
	u32 raw_vflip : 1; /*!< This is a flag to enable / disable raw vertical flip; 0: No vertical flip; 1: Vertical flip */
	u32 enable_tml_raw_packing : 1;	/*!< Enable tml raw packing. */
	u32 enable_tml_proc : 1;	/*!< Enable tml processing. */
	u32 enable_group : 1;	/*!< Enable channel grouping. The channels in same group must run same frame rate. */
	u32 group_idx : 2;	/*!< Group index. Range: 0~3. Only valid when enable_group = 1. */
	u32 is_mo_fusion_img_cfg_chan : 1;	/*!< This is a flag to show if current channel's ISO CFG will be used for multi-output fusion. @b Read @b Only. */
	u32 raw_dsp_priv_dram : 1;	/*!< Enable flag to move RAW buffer from DSP-ARM shared DRAM space into DSP private DRAM space. */
	u32 raw_manual_feed : 1;	/*!< This is a flag to enable / disable channel raw manual feed */
	u32 raw_feed_frame_num : 7;	/*!< Feed frame num for raw manual feed, only valid when raw_manual_feed is enabled */
	u32 srcbuf_to_skip_blend : 8;	/*!< This is a flag to skip sub source buffer blend pass in stitching. Main buffer
					always has blend pass, it cannot be skipped. It's ONLY available when system is NOT IAV_BLEND_TYPE_NONE.
					For example, 2nd srcbuf is to set bit[1], 3rd srcbuf is to set bit[2], ... */
	u32 raw_cached_items : 5;	/*!< The raw cached items for user to query with blocking call, default: 0. */
	u32 srcbuf_to_fusion : 3;	/*!< Specify source buffer id for TML fusion.
					By default, it is main buffer. ONLY valid for RGB channel. */
	u32 group_order_idx : 3;	/*!< This is the channel order idx inside the group with the group index "group_idx". */
	u32 hdec_raw_format : 2;	/*!< The hdec(ce) raw format, 0(default): follow raw compression, 1 : hdec raw compression disabled,
			2 : hdec raw compression enabled. */
	u32 mcts_crop_out_enable : 1;	/*!< This is a flag to enable mcts out cropping to fix vertical line issue in stitching area. */
	u32 reserved2 : 2;
	u32 idsp_fps_hp;	/*!< High precision framerate. idsp_fps_hp = 1000 * idsp_fps. For setting, only valid when "enable_hp_flag" is 1.
		For getting, value is always valid. */
	u32 orig_idsp_fps_hp; /*< Only used when idsp_fps_locked_enable = 1. Only for internal use.*/
	u32 debug_stitch_slice_num : 4;	/*!< This is a debug option to specify the stitch slice num. */
	u32 idsp_fps : 12;		/*!< IDSP output FPS. Since CV22 supports FPS downsampling, customers can use this parameter to select
					a channel FPS lower than VIN FPS. Default is 0(equals to VIN FPS). */
	u32 max_raw_height : 16; /*!< This is a option to specify height to support YUV420/422 raw encode with separated luma and chroma address. */
	u32 reserved3;
};

struct iav_img_scale_cfg {
	u8 enable : 1;	/*!< This is a flag to enable img scale */
	u8 reserved1 : 7;
	u8 src_buf_id;	/*!< Specify the src_buf_id used by img scale, 4: use fifth buffer; 5: use sixth buffer. */
	u8 job_queue_depth;	/*!< Specify the depth of scaling task queue inside DSP. */
	u8 reserved2;
	u16 max_input_width;	/*!< Specify max input width */
	u16 max_output_width;	/*!< Specify max output width */
	u32 reserved3[2];
};

struct iav_scale_buf_info {
	union {
		u32 pid;	/*!< Specify memory partition id. Only valid when use_phys = 0 */
		int dma_buf_fd;
	};
	u32 use_phys : 1;	/*!< This is a flag to specify if the buffer start address is physcial
						address (use_phys = 1) or offset within a memory partition (use_phys = 0). */
	u32 use_dma_buf_fd : 1;	/*!< This is a flag to specify whether @b dma_buf_fd or @b pid is used. */
	u32 reserved : 30;
	union {
		unsigned long y_offset;	/*!< Specify Y buffer offset within the memory partition. Only valid when use_phys = 0 */
		unsigned long y_addr;		/*!< Specify Y buffer physical address. Only valid when use_phys = 1 */
	};
	union {
		unsigned long uv_offset;	/*!< Specify UV buffer offset within the memory partition. Only valid when use_phys = 0 */
		unsigned long uv_addr;		/*!< Specify UV buffer physical address. Only valid when use_phys = 1 */
	};
	u16 pitch;	/*!< buffer pitch */
	u16 height;	/*!< buffer height */
};

struct iav_img_scale {
	enum iav_yuv_format format;		/*!< YUV format */

	struct iav_rect input;	/*!< input crop window in input_buf domain. */
	struct iav_window output;	/*!< output size in output_buf domain. */

	struct iav_scale_buf_info input_buf;	/*!< input YUV buffer. Y is planar format, UV is interleaved format. */
	struct iav_scale_buf_info output_buf;	/*!< output YUV buffer. Y is planar format, UV is interleaved format. */

	u32 non_block_flag : 1; /*!< non-blocking call flag */
	u32 input_skip_cache_sync : 1;	/*!< The input buffer cache will not be synced if this flag is enabled. */
	u32 output_skip_cache_sync : 1;	/*!< The output buffer cache will not be synced if this flag is enabled. */
	u32 reserved : 29;

	u64 task_id;		/*!< Output param: the unique task id of current image scaling task. */
};

struct iav_custom_pyramid_cfg {
	u16 enable : 1;	/*!< This is a flag to enable custom pyramid. */
	u16 max_layers_map : 6;	/*!< Max bit map for pyramid layers, one bit for one layer, can only be changed before preview. @layers_map
			should be within @max_layers_map. */
	u16 reserved0 : 1;
	u16 cached_items : 8;	/*!< The custom pyramid cached items for user to query with blocking call,
				default: 0. Custom pyramid didn't discard data if not set. */
	u16 buf_num : 8;	/*!< The maximum custom pyramid buf items user can used. */
	u16 job_queue_depth : 8;	/*!< Specify the depth of custom pyramid task queue inside DSP. */
	struct iav_window max_input_size;	/*!< Specify max input size */
	struct iav_window max_rescale_size;	/*!< Max rescale size for pyramid layer 1. Used to set the max rescale
						size of pyramid layer 1, Only valid when <b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>. */
	enum iav_pyramid_scale scale_type;	/*!< Specify pyramid scale type, @sa iav_pyramid_scale. */
};

struct iav_custom_pyramid_feed_cfg {
	enum iav_yuv_format format;		/*!< Specify YUV format for the input YUV buffer. */
	struct iav_rect input_win;	/*!< Specify input window for the input YUV. */
	struct iav_rect crop_win[IAV_MAX_PYRAMID_LAYERS];	/*!< Specify output window for pyramid layers. */
	struct iav_window rescale_size;	/*!< Specify rescale size for pyramid layer 1,
					Only valid when <b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>. */
	enum iav_pyramid_scale scale_type;	/*!< Specify pyramid scale type, @sa iav_pyramid_scale. */
	u32 layers_map : 6;	/*!< Specify bit map for pyramid layers, one bit for one layer, can be changed dynamically. */
	u32 reserved : 26;
};

struct iav_feed_custom_pyramid {
	struct iav_custom_pyramid_feed_cfg feed_cfg;	/*!< Specify feed custom pyramid config. Only valid when the feed_cfg_update flag enabled.
							Need to set it when first feed the custom pyramid. */
	struct iav_scale_buf_info input_buf;	/*!< Specify input YUV buffer. Only valid when the extern_input flag enabled. */
	u64 task_id;	/*!< task_id maintain by iav and user can use this id query the data. */
	u32 usr_magic_num;	/*!< Specify usr_magic_num. It will return directly when the data is ready.
			It used for identify the specific task. */
	u32 canvas_id : 8;		/*!< Specify the input from canvas. Only valid when the extern_input flag disabled. */
	u32 extern_input : 1;		/*!< Specify input from extern buf if this flag enabled. */
	u32 feed_cfg_update : 1;		/*!< Specify feed custom pyramid config update flag. Need to set it when first feed the custom pyramid. */
	u32 reserved : 22;
};

struct iav_mem_cfg_chan {
	u32 mask_possible : 1;			/*!< Whether Single-Color Privacy Mask memory is needed. */
	u32 mc_mask_possible : 1;	/*!< Whether Multi-Color Privacy Mask memory is needed. */
	u32 warp_possible : 1;			/*!< Whether WARP memory is needed for Dewarp/EIS/LDC. */
	u32 mask_buf_max_num : 6;		/*!< Max allocated Single-Color PM buffer num. 1 for user configuration, others for IAV/DSP usage. */
	u32 mc_mask_buf_max_num : 6;	/*!< Max allocated Multi-Color PM buffer num. 1 for user configuration, others for IAV/DSP usage. */
	u32 warp_buf_max_num : 6;		/*!< Max allocated WARP buffer num. 1 for user configuration, others for IAV/DSP usage. */
	u32 warp_area_max_num : 6;		/*!< Max WARP area num. 1 for LDC/EIS, Dewarp can be up to 12. */
	u32 mc_mask_buf_ds : 3;	/*!< Specify Multi-Color Privacy Mask memory downscale mode from VIN resolution. */
	u32 tfc_possible : 1;	/*!< Whether TML fusion clut memory is needed. */
	u32 reserved0 : 1;
	struct iav_window max_vin;		/*!< Max VIN size to decide the buffer allocation. */
	u32 tfc_buf_max_num : 4;	/*!< Max allocated TML fusion clut buffer num. 1 for user configuration, others for IAV/DSP usage. */
	u32 reserved1 : 28;
	u32 reserved2;
};

struct iav_mem_cfg_stream {
	u32 qpm_possible : 1;			/*!< Whether QP matrix memory is needed. */
	u32 qpm_max_matrix_num : 3;		/*!< Max QP matrix num per stream. 1: I/P share the same QP matrix;
								2: I use 1 QP matrix and P use the other one, max is 3. */
	u32 qpm_buf_max_num : 4;		/*!< Max allocated QP matrix buffer num. 1 for user configuration, others for IAV/DSP usage. */
	u32 reserved : 24;
	struct iav_window max_stream;	/*!< Max stream size to decide the buffer allocation. */
};

struct iav_mem_layout_resource {
	u32 max_chan_num : 5;			/*!< Max possible channel num for resource memory allocation. */
	u32 max_stream_num : 5;			/*!< Max possible stream num for resource memory allocation. */
	u32 reserved : 22;
	struct iav_mem_cfg_chan chan_mem_cfg[IAV_MAX_CHANNEL_NUM];	/*!< Channel memory configuration */
	struct iav_mem_cfg_stream stream_mem_cfg[IAV_STREAM_MAX_NUM_ALL];	/*!< Stream memory configuration */
};

struct iav_mem_layout {
	u32 offset;			/*!< Memory offset. */
	u32 size;			/*!< Memory size. */
	u32 unit_size;		/*!< Buffer unit size. */
	u32 unit_num : 8;	/*!< Buffer unit number. */
	u32 reserved0 : 24;
	u32 reserved1;
};

struct iav_mem_layout_chan {
	unsigned long phys_base;	/*!< Physical memory base address. */
	u32 total_user_size;		/*!< Total memory size for user configuration. */
	u32 total_size;				/*!< Total memory size. */
	struct iav_mem_layout buf_layout[IAV_MAX_CHANNEL_NUM];	/*!< Buffer layout info. */
};

struct iav_mem_layout_stream {
	unsigned long phys_base;	/*!< Physical memory base address. */
	u32 total_user_size;		/*!< Total memory size for user configuration. */
	u32 total_size;				/*!< Total memory size. */
	struct iav_mem_layout buf_layout[IAV_STREAM_MAX_NUM_ALL];	/*!< Buffer layout info. */
};

struct iav_mem_layout_info {
	u32 mem_layout_updated : 1;		/*!< Whether resource memory layout updated or not. */
	u32 reserved : 31;
	struct iav_mem_layout_chan mask_layout;		/*!< Single Color Privacy Mask memory layout. */
	struct iav_mem_layout_chan warp_layout;		/*!< WARP memory layout. */
	struct iav_mem_layout_stream qpm_layout;	/*!< QP matrix memory layout. */
	struct iav_mem_layout_chan mc_mask_layout;	/*!< Multi Color Privacy Mask memory layout. */
	struct iav_mem_layout_chan tfc_layout;	/*!< TML Fusion CLUT memory layout. */
};

struct iav_wait_img_scale {
	u64 task_id;		/*!< Unique image scaling task id */
};

struct iav_system_resource {
	u8 encode_mode;		/*!< Encode modes for different cases. @sa dsp_mode.
					0x00:  Advanced ISO mode. This is the mode for lowest latency from VIN to VOUT.
					0x01:  Multiple Region Warp mode. This is the mode for multi-region fisheye dewarp.
					0x02:  Sensor Fusion mode. This is the mode for Video or Image fusion.
					0x03:  Multiple Pass IDSP Rotation mode. This is the mode for multi-pass scale with rotation.
					0x04:  Multiple Output Fusion mode. This mode can be used for TML and RGB fusion.
					0x05:  Line interleaved HDR mode. This is the mode for 3X HDR and multi-pass scale.
					0x06:  Multiple YUV input mode. This is the mode for multiple YUV input, only available for CV2 & CV22.
					0x7F:  Mode none. This is the mode to skip ISP processing for current channel. Only available for @ref vcap_mode_flags.
					0x80:  Automatic mode. This is the flag to let vcap_mode_flags follow encode_mode. Only available for @ref vcap_mode_flags.
					0xFF:  Current encode mode. This is the mode to get current encode mode number. */

	u8 max_stream_num;	/*!< The maximum supported stream number in the specified encode mode */
	u8 canvas_num;		/*!< Canvas number. @sa IAV_MAX_CANVAS_BUF_NUM */
	u8 chan_num;		/*!< Channel number. @sa IAV_MAX_CHANNEL_NUM */

	/* Read only */
	u32 raw_pitch_in_bytes;		/*!< @b Read @b only. It indicates the raw pitch in bytes. */
	u32 total_memory_size : 8;	/*!< @b Read @b only. It indicates the total DRAM size used in the system. */
	u32 iso_type : 3;		/*!< @b Read @b only. This is a flag to specify the ISO type */
	u32 is_stitched : 1;		/*!< @b Read @b only. This is a flag to specify whether VIN is stitched or not */
	u32 vout_only : 1;		/*!< @b Read @b only. This is a flag to specify whether to use VOUT only or not */
	u32 reserved0 : 19;

	/* Writable for different configuration */
	u32 insert_blur_enable : 1;	/*!< This is a flag to enable / disable inserting stream blur */
	u32 mixer_a_enable : 1;		/*!< This is a flag to enable / disable mixer a */
	u32 mixer_b_enable : 1;		/*!< This is a flag to enable / disable mixer b */
	u32 osd_from_mixer_a : 1;	/*!< This is a flag to specify mixer a used for OSD / Multi-Color Privacy Mask */
	u32 osd_from_mixer_b : 1;	/*!< This is a flag to specify mixer b used for OSD / Multi-Color Privacy Mask */
	u32 vsync_detection_disable : 1;/*!< Disable vsync detection or not */
	u32 me0_scale : 2;		/*!< This is a flag to indicate ME0 scale factor, @sa iav_me0_scale */
	u32 enable_hp_fps : 1;	/*!< This is a flag to enable / disable high precision fps for idsp_fps, canvas, pyramid and stream fps. */
	u32 enable_vin_precise_sync : 1;	/*!< This is a flag to precisely adjust VIN frame rate according to VOUT frame rate. It's widely used for the cases which require accurate VIN-VOUT sync */
	u32 back_pressure_margin : 2;	/*!< Back pressure margin count */
	u32 hevc_off : 1;		/*!< Disable HEVC encoding */
	u32 insert_mc_mask_enable : 1;	/*!< This is a flag to enable / disable inserting multi-color mask */
	u32 enc_raw_rgb : 1;		/*!< This is a flag to enable / disable encoding from raw CFA data */
	u32 enc_raw_yuv : 1;		/*!< This is a flag to enable / disable encoding from raw YUV422 data */

	u32 emirror_vout_sync_enable : 1;/*!< This is a flag to enable / disable emirror vout sync. */
	u32 custom_sei : 1;		/*!< This is a flag to enable / disable allocating customized SEI buffer from DSP. */
	u32 blend_stitch_type : 2;	/*!< Specify blend type for multi-channel stitching, @sa IAV_BLEND_TYPE */
	u32 hevc_pjpeg_size_MB_per_tile : 4; /*!< Specify the DRAM size of HEVC and PJPEG encoding buffer. */
	u32 prev_bottom_repeat_disabled : 1; /*!< Disable preview buffer bottom repeat. Tell DSP to not repeat
										last line 8x times for the height alignment. This is ONLY used for
										the canvas composite from multi-channel preview buffers. */
	u32 vsync_loss_dummy_frame_enable : 1; /*!< When enabling this flag, DSP will use PM to cover the whole vysnc-loss channel. */
	u32 dynamic_slice : 1;	/*!< When enabling this flag, DSP might change slice number dynamically during source
							buffer DPTZ. It's mainly used for CV2 8Kp use case. */
	u32 enc_raw_nv12 : 1;		/*!< This is a flag to enable / disable encoding from raw YUV420 data */
	u32 chan_vcap_mode_enable : 1;	/*!< This is a flag to enable / disable using vcap_mode_flags of each channel. */
	u32 blur_vout_mixer : 1;	/*!< This is a flag to specify VOUT mixer for blur. 0: mixer a(VOUT0); 1: mixer b(VOUT1). */
	u32 enc_raw_fast_enable : 1;	/*!< This is a flag to enable /disable fast raw encode. When enabled,
									delays inside IAV are removed as much as possible to speed up the procedure.. */
	u32 enabled_canvas_frame_tag : 1;	/*!< This is a global flag to enable Canvas frame tag pattern. Only when this option is enabled,
								frame tag in iav_canvas_cfg structure is used to dispatch the frames into corresponding canvas
								via the frame tag pattern.*/
	struct iav_window raw_size;	/*!< @b Read @b only. The resolution of raw data.
								This is only valid when enc_raw_rgb or enc_raw_yuv is enabled. */

	u32 custom_sei_buf_size;	/*!< The buffer size of customized SEI. It is used for allocating memory in DSP.
							Only valid when @b custom_sei is enabled. */
	u16 custom_sei_buf_num;	/*!< The maximum number of customized SEI buffers can be requested
								from DSP. Only valid when @b custom_sei is enabled. */
	u16 enc_dummy_latency;		/*!< The latency of frame count before encode. Valid range 0~8. */
	u32 extra_raw_dram_buf_num : 8;	/*!< The number of extra raw dram buffer */
	u32 dsp_api_thread_freq : 10;	/*!< The frequency of dsp api thread */
	u32 eis_delay_count : 3; /*!< This param is for backward compatibility. It is to specify EIS delay frame num before IDSP pipeline */
	u32 low_delay_state_switch_enable : 1;	/*!< This is a flag to enable / disable low delay during iav state switch.
						This flag can be used in the efm, raw encode or other special case without the idsp
						interrupt. When enabled, delays inside IAV are removed as much as possible to speed
						up the procedure during the iav state switch. */
	u32 report_img_stats_from_vcap : 1;	/*!< This is a flag to enable / disable reporting image stats through VCAP ISR. If enabled, it can shorten
						the latency from being generated to being reported to ARM. 1: through VCAP ISR; 0: through VAPI ISR(by default). */
	u32 reserved3 : 9;
	u32 reserved4[3];

	struct iav_stream_resource stream[IAV_STREAM_MAX_NUM_ALL]; /*!< Stream Resource */
	struct iav_chan_cfg chan_cfg[IAV_MAX_CHANNEL_NUM]; /*!< Channel configuration */
	struct iav_canvas_cfg canvas_cfg[IAV_MAX_CANVAS_BUF_NUM]; /*!< Canvas configuration */
	struct iav_img_scale_cfg img_scale_cfg;	/*!< img scale configuration */

	/* Debug only */
	u32 debug_enable_map;		/*!< This is a bit map to specify debug options. @sa iav_debug_type
					     Bit 0: Enable / Disable debug stitch option
					     Bit 1: Enable / Disable debug chip ID option
					     Bit 2: Enable / Disable debug maximum chroma radius
					     Bit 3: Enable / Disable debug skip macro block calculation for EFM streams
					     Bit 4: Enable / Disable debug break point for ISP
					     Bit 5: Set debug vp dram priority
					     Bit 6: Set debug vsync loss timeout time
					     Bit 7: Set debug hevc encode mode
					     Bit 8: Set debug hevc high DRAM efficiency mode
					     Bit 9: Enable / Disable debug reset seq num in idle state*/
	u32 debug_stitched : 1;		/*!< This is a debug flag to specify the debug stitched option */
	u32 debug_chip_id : 6;		/*!< This is a debug option to specify the debug chip ID */
	u32 debug_max_chroma_radius : 2; /*!< This is a debug option to specify the maximum chroma radius, @sa iav_chroma_radius_num */
	u32 debug_skip_efm_mb : 1;	/*!< This is a debug flag to specify the debug skip efm MB in total MB calculation */
	u32 debug_break_point : 1;	/*!< This is a debug flag to specify IK debug point or not. 0: Disable, 1: Enable */
	u32 debug_hevc_enc_mode : 3;	/*!< This is debug flag to specify HEVC encode mode. */
	u32 debug_vp_dram_priority : 3;	/*!< This is a debug option to specify the DRAM R/W priority of VP.*/
	u32 debug_vsync_loss_timeout : 12;	/*!< This is a debug option to specify the vsync loss timeout time (ms).*/
	u32 debug_hevc_hi_dram_ef_mode : 1;	/*!< This is a debug option to enable high dram efficiency mode for HEVC streaming.
						When it is enabled, more DSP HW resource will be used. */
	u32 debug_reset_seq_num_in_idle : 1;	/*!< This is a debug option to enable reset seq num in idle state.*/
	u32 reserved5 : 1;
};

struct iav_enc_mode_cap {
	struct iav_window min_main;		/*!< The min resolution for main buffer */
	struct iav_window max_main;		/*!< The max resolution for main buffer */
	struct iav_window min_enc;		/*!< The min resolution for encoding */
	u8 encode_mode;				/*!< Encode modes for different cases, refers to enum @ref dsp_mode */
	u8 max_streams_num;			/*!< Maximum supported stream number */
	u8 max_chroma_radius            : 2;	/*!< Maximum chroma radius, @sa iav_chroma_radius_num */
	u8 max_wide_chroma_radius       : 2;	/*!< Maximum wide chroma radius, @sa iav_chroma_radius_num */
	u8 reserved0                    : 4;
	u8 reserved1;
	u32 max_encode_MB;			/*!< The maximum encode macro blocks for all codec,
							including H.264/H.265/JPEG*/
	u32 raw_cap_possible            : 1;	/*!< Possibility to enable raw picture capture */
	u32 vout_swap_possible          : 1;	/*!< Possibility to support swap VOUT function */
	u32 lens_warp_possible          : 1;	/*!< Possibility to support lens warp */
	u32 iso_type_possible           : 3;	/*!< Possibility of supported ISO types */
	u32 enc_raw_rgb_possible        : 1;	/*!< Possibility to support encode from raw CFA data input
							function. It's not available and it's for internal debug only. */
	u32 high_mp_possible            : 1;	/*!< Possibility to support high mega pixels encoding */
	u32 linear_possible             : 1;	/*!< Possibility to support sensor Linear mode */
	u32 hdr_2x_possible             : 2;	/*!< Possibility of support HDR 2X types */
	u32 hdr_3x_possible             : 2;	/*!< Possibility of support HDR 3X types */
	u32 wcr_possible                : 1;	/*!< Possibility to support wide chroma noise filter */
	u32 me0_possible                : 2;	/*!< Possibility to support ME0 scale factor */
	u32 enc_from_mem_possible       : 1;	/*!< Possibility to support encode from memory */
	u32 enc_raw_yuv_possible        : 1;	/*!< Possibility to support encode from raw YUV data input
							function. It's not available and it's for internal debug only. */
	u32 ce_possible                 : 1;	/*!< Possibility to support CE function */
	u32 stitch_hor_possible         : 1;	/*!< Possibility to support horizontal stitching. */
	u32 stitch_ver_possible         : 1;	/*!< Possibility to support vertical stitching. */
	u32 eis_delay_cnt_possible      : 1;	/*!< Possibility to support eis delay. */
	u32 dvr_possible                : 1;	/*!< Possibility to support digital video recording. */
	u32 vwarp_wait_lines_possible   : 1;	/*!< Possibility to support vwarp wait lines. */
	u32 multi_pass_possible         : 1;	/*!< Possibility to support multiple scaler pass. */
	u32 chan_rotate_possible        : 1;	/*!< Possibility to support channel rotation and flip. */
	u32 multi_yuv_input_possible    : 1;	/*!< Possibility to support multiple YUV inputs. */
	u32 canvas_manual_feed_possible : 1;	/*!< Possibility to support canvas manual feed. */
	u32 mc_mask_possible            : 1;	/*!< Possibility to support multi color privacy mask. */
	u32 raw_manual_feed_possible    : 1;	/*!< Possibility to support channel raw manual feed. */
	u32 reserved_possible           : 2;
	u32 max_h26x_encode_MB;			/*!< The maximum encode macro blocks for H.264/H.265 codec */

};

struct iav_enc_buf_cap {
	u8 buf_id;		 /*!< @sa iav_srcbuf_id */
	u8 pass_id;		 /*!< Pass ID */
	u8 reserved0[2];
	struct iav_window max;			/*!< The maximum resolution of the buffer */
	u16 max_zoom_in_factor;			/*!< Maximum supported zoom in factor */
	u16 max_zoom_out_factor;		/*!< Maximum supported zoom out factor */
	u16 max_stitch_zoom_out_factor;	/*!< Maximum supported zoom out factor for stitched case */
	u16 reserved1;
};

struct iav_sys_cfg_general {
	/* Read only */
	u32 raw_pitch_in_bytes;		/*!< @b Read @b only. It indicates the raw pitch in bytes. */
	u32 total_memory_size : 8;	/*!< @b Read @b only. It indicates the total DRAM size used in the system. */
	u32 iso_type : 3;		/*!< @b Read @b only. This is a flag to specify the ISO type */
	u32 is_stitched : 1;		/*!< @b Read @b only. This is a flag to specify whether VIN is stitched or not */
	u32 vout_only : 1;		/*!< @b Read @b only. This is a flag to specify whether to use VOUT only or not */
	u32 reserved0 : 19;

	/* Writable for different configuration */
	u32 insert_blur_enable : 1;	/*!< This is a flag to enable / disable inserting stream blur */
	u32 mixer_a_enable : 1;		/*!< This is a flag to enable / disable mixer a */
	u32 mixer_b_enable : 1;		/*!< This is a flag to enable / disable mixer b */
	u32 osd_from_mixer_a : 1;	/*!< This is a flag to specify mixer a used for OSD / Multi-Color Privacy Mask */
	u32 osd_from_mixer_b : 1;	/*!< This is a flag to specify mixer b used for OSD / Multi-Color Privacy Mask */
	u32 vsync_detection_disable : 1;/*!< Disable vsync detection or not */
	u32 me0_scale : 2;		/*!< This is a flag to indicate ME0 scale factor, @sa iav_me0_scale */
	u32 enable_hp_fps : 1;	/*!< This is a flag to enable / disable high precision fps for idsp_fps, canvas, pyramid and stream fps. */
	u32 enable_vin_precise_sync : 1;	/*!< This is a flag to precisely adjust VIN frame rate according to VOUT frame rate. It's widely used for the cases which require accurate VIN-VOUT sync */
	u32 back_pressure_margin : 2;	/*!< Back pressure margin count */
	u32 hevc_off : 1;		/*!< Disable HEVC encoding */
	u32 insert_mc_mask_enable : 1;	/*!< This is a flag to enable / disable inserting multi-color mask */
	u32 enc_raw_rgb : 1;		/*!< This is a flag to enable / disable encoding from raw CFA data */
	u32 enc_raw_yuv : 1;		/*!< This is a flag to enable / disable encoding from raw YUV422 data */

	u32 emirror_vout_sync_enable : 1;/*!< This is a flag to enable / disable emirror vout sync. */
	u32 custom_sei : 1;		/*!< This is a flag to enable / disable allocating customized SEI buffer from DSP. */
	u32 blend_stitch_type : 2;	/*!< Specify blend type for multi-channel stitching, @sa IAV_BLEND_TYPE */
	u32 hevc_pjpeg_size_MB_per_tile : 4; /*!< Specify the DRAM size of HEVC and PJPEG encoding buffer. */
	u32 prev_bottom_repeat_disabled : 1; /*!< Disable preview buffer bottom repeat. Tell DSP to not repeat
										last line 8x times for the height alignment. This is ONLY used for
										the canvas composite from multi-channel preview buffers. */
	u32 vsync_loss_dummy_frame_enable : 1; /*!< When enabling this flag, DSP will use PM to cover the whole vysnc-loss channel. */
	u32 dynamic_slice : 1;	/*!< When enabling this flag, DSP might change slice number dynamically during source
							buffer DPTZ. It's mainly used for CV2 8Kp use case. */
	u32 enc_raw_nv12 : 1;		/*!< This is a flag to enable / disable encoding from raw YUV420 data */
	u32 chan_vcap_mode_enable : 1;	/*!< This is a flag to enable / disable using vcap_mode_flags of each channel. */
	u32 blur_vout_mixer : 1;	/*!< This is a flag to specify VOUT mixer for blur. 0: mixer a(VOUT0); 1: mixer b(VOUT1). */
	u32 enc_raw_fast_enable : 1;	/*!< This is a flag to enable /disable fast raw encode. When enabled,
									delays inside IAV are removed as much as possible to speed up the procedure.. */
	u32 enabled_canvas_frame_tag : 1;		/*!< This is a global flag to enable Canvas frame tag pattern. Only when this option is enabled,
									frame tag in iav_canvas_cfg structure is used to dispatch the frames into corresponding canvas
									via the frame tag pattern.*/

	struct iav_window raw_size;	/*!< @b Read @b only. The resolution of raw data.
								This is only valid when enc_raw_rgb or enc_raw_yuv is enabled. */

	u32 custom_sei_buf_size;	/*!< The buffer size of customized SEI. It is used for allocating memory in DSP.
							Only valid when @b custom_sei is enabled. */
	u16 custom_sei_buf_num;	/*!< The maximum number of customized SEI buffers can be requested
								from DSP. Only valid when @b custom_sei is enabled. */
	u16 enc_dummy_latency;		/*!< The latency of frame count before encode */
	u32 extra_raw_dram_buf_num : 8;	/*!< The number of extra raw dram buffer */
	u32 dsp_api_thread_freq : 10;	/*!< The frequency of dsp api thread */
	u32 eis_delay_count : 3;	/*!< This param is for backward compatibility. It is to specify EIS delay frame num before IDSP pipeline */
	u32 low_delay_state_switch_enable : 1;	/*!< This is a flag to enable / disable low delay during iav state switch.
						This flag can be used in the efm, raw encode or other special case without the idsp
						interrupt. When enabled, delays inside IAV are removed as much as possible to speed
						up the procedure during the iav state switch. */
	u32 report_img_stats_from_vcap : 1; /*!< This is a flag to enable / disable reporting image stats through VCAP ISR. If enabled, it can shorten
						the latency from being generated to being reported to ARM. 1: through VCAP ISR; 0: through VAPI ISR(by default). */
	u32 reserved3 : 9;
	u32 reserved4[4];
};

struct iav_sys_cfg_channel {
	u8 chan_num;		/*!< Channel number. @sa IAV_MAX_CHANNEL_NUM */
	u8 reserved[3];
	struct iav_chan_cfg channel[IAV_MAX_CHANNEL_NUM]; /*!< Channel configuration */
};

struct iav_sys_cfg_canvas {
	u8 canvas_num;		/*!< Canvas number. @sa IAV_MAX_CANVAS_BUF_NUM */
	u8 reserved[3];
	struct iav_canvas_cfg canvas[IAV_MAX_CANVAS_BUF_NUM]; /*!< Canvas configuration */
};

struct iav_sys_cfg_stream {
	u8 max_stream_num;	/*!< The maximum supported stream number in the specified encode mode */
	u8 reserved[3];
	struct iav_stream_resource stream[IAV_STREAM_MAX_NUM_ALL]; /*!< Stream Resource */
};

struct iav_sys_cfg_debug {
	u32 debug_enable_map;		/*!< This is a bit map to specify debug options. @sa iav_debug_type
					     Bit 0: Enable / Disable debug stitch option
					     Bit 1: Enable / Disable debug chip ID option
					     Bit 2: Enable / Disable debug maximum chroma radius
					     Bit 3: Enable / Disable debug skip macro block calculation for EFM streams
					     Bit 4: Enable / Disable debug break point for ISP
					     Bit 5: Set debug vp dram priority
					     Bit 6: Set debug vsync loss timeout time
					     Bit 7: Set debug hevc encode mode
					     Bit 8: Set debug hevc high DRAM efficiency mode
					     Bit 9: Enable / Disable debug reset seq num in idle state*/
	u32 debug_stitched : 1;		/*!< This is a debug flag to specify the debug stitched option */
	u32 debug_chip_id : 6;		/*!< This is a debug option to specify the debug chip ID */
	u32 debug_max_chroma_radius : 2; /*!< This is a debug option to specify the maximum chroma radius, @sa iav_chroma_radius_num */
	u32 debug_skip_efm_mb : 1;	/*!< This is a debug flag to specify the debug skip efm MB in total MB calculation */
	u32 debug_break_point : 1;	/*!< This is a debug flag to specify IK debug point or not. 0: Disable, 1: Enable */
	u32 debug_hevc_enc_mode : 3;	/*!< This is debug flag to specify HEVC encode mode. */
	u32 debug_vp_dram_priority : 3;	/*!< This is a debug option to specify the DRAM R/W priority of VP.*/
	u32 debug_vsync_loss_timeout : 12;	/*!< This is a debug option to specify the vsync loss timeout time (ms).*/
	u32 debug_hevc_hi_dram_ef_mode : 1;	/*!< This is a debug option to enable high dram efficiency mode for HEVC streaming.
						When it is enabled, more DSP HW resource will be used. */
	u32 debug_reset_seq_num_in_idle : 1;	/*!< This is a debug option to enable reset seq num in idle state.*/
	u32 reserved : 1;
};

struct iav_sys_cfg {
	enum iav_sys_cfg_id cid;  /*!< system config item ID, @sa iav_sys_cfg_id */
	u8 encode_mode;		/*!< Encode modes for different cases. @sa dsp_mode.
					0x00:  Advanced ISO mode. This is the mode for lowest latency from VIN to VOUT.
					0x01:  Multiple Region Warp mode. This is the mode for multi-region fisheye dewarp.
					0x02:  Sensor Fusion mode. This is the mode for Video or Image fusion.
					0x03:  Multiple Pass IDSP Rotation mode. This is the mode for multi-pass scale with rotation.
					0x04:  Multiple Output Fusion mode. This mode can be used for TML and RGB fusion.
					0x05:  Line interleaved HDR mode. This is the mode for 3X HDR and multi-pass scale.
					0x06:  Multiple YUV input mode. This is the mode for multiple YUV input, only available for CV2 & CV22.
					0xFF:  Current encode mode. This is the mode to get current encode mode number. */
	u8 reserved[11];
	union {
		struct iav_sys_cfg_general general_cfg; /*!< general system config */
		struct iav_sys_cfg_channel channel_cfg; /*!< channel system config */
		struct iav_sys_cfg_canvas canvas_cfg; /*!< canvas system config */
		struct iav_sys_cfg_stream stream_cfg; /*!< stream system config */
		struct iav_img_scale_cfg img_scale_cfg; /*!< img scale system config */
		struct iav_sys_cfg_debug debug_cfg; /*!< debug system config */
	};
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper */
/*  @{
 */
enum iav_mem_part_id {
	IAV_PART_DSP			= 0, /*!< 0, Partition ID for DSP partition */
	IAV_PART_BSB			= 1, /*!< 1, Partition ID for bit stream partition */
	IAV_PART_USR			= 2, /*!< 2, Partition ID for user data partition */
	IAV_PART_MV				= 3, /*!< 3, Partition ID for motion vector partition */
	IAV_PART_OVERLAY		= 4, /*!< 4, Partition ID for overlay partition */
	IAV_PART_QPMATRIX		= 5, /*!< 5, Partition ID for QP ROI matrix partition */
	IAV_PART_WARP			= 6, /*!< 6, Partition ID for warp vector partition */
	IAV_PART_QUANT			= 7, /*!< 7, Partition ID for JPEG quant matrix table partition */
	IAV_PART_IMG			= 8, /*!< 8, Partition ID for image partition */
	IAV_PART_MASK			= 9, /*!< 9, Partition ID for single color mask partition */
	IAV_PART_FB_DATA		= 10, /*!< 10, Partition ID for fast boot data partition */
	IAV_PART_FB_AUDIO		= 11, /*!< 11, Partition ID for fast boot audio partition */
	IAV_PART_INTRA_PB		= 12, /*!< 12, Partition ID for INTRA PB partition */
	IAV_PART_STAT			= 13, /*!< 13, Partition ID for picture statistics */
	IAV_PART_BLEND_ALPHA	= 14, /*!< 14, Partition ID for blend alpha buffer */
	IAV_PART_BSH			= 15, /*!< 15, for internal use */
	IAV_PART_DSP_DEF_CMD	= 16, /*!< 16, for internal use */
	IAV_PART_DSP_UCODE		= 17, /*!< 17, Partition ID for UCODE partition */
	IAV_PART_DSP_LOG		= 18, /*!< 18, for internal use */
	IAV_PART_DSP_FIFO		= 19, /*!< 19, for internal use */
	IAV_PART_DSP_RSV		= 20, /*!< 20, for internal use */
	IAV_PART_IAV_RSV		= 21, /*!< 21, for internal use */
	IAV_PART_PREALLOC		= 22, /*!< 22, for internal use */
	IAV_PART_PREALLOC2		= 23, /*!< 23, for internal use */
	IAV_PART_PYRAMID_POOL	= 24, /*!< 24, Partition ID for Pyramid buffer pool in Pyramid manual-feed mode or in decode mode */
	IAV_PART_QPMATRIX_RAW	= 25, /*!< 25, Partition ID for QPMATRIX_RAW partition */
	IAV_PART_CANVAS_POOL	= 26, /*!< 26, Partition ID for canvas buffer pool in manual-feed mode */
	IAV_PART_BLUR			= 27, /*!< 27, Partition ID for blur partition */
	IAV_PART_HEVC_SCALELIST	= 28, /*!< 28, Partition ID for hevc scalelist partition */
	IAV_PART_MULTI_COLOR_MASK	= 29, /*!< 29, Partition ID for Multi Color Mask partition */
	IAV_PART_INT_BSB			= 30, /*!< 30, Partition ID for internal used bit stream partition */
	IAV_PART_ARB_BLUR		= 31, /*!< 31, Partition ID for custom blur partition */
	IAV_PART_EXTRA_RAW		= 32, /*!< 32, Partition ID for extra raw partition */
	IAV_PART_TFC			= 33, /*!< 33, Partition ID for TML fusion clut partition */
	IAV_PART_RAW_POOL		= 34, /*!< 34, Partition ID for raw buffer pool in raw manual-feed mode */
	IAV_PART_DIS_CTB_STATIS	= 35, /*!< 35, Partition ID for DIS CTB Statistic */
	IAV_PART_NUM,	/*!< 36, total number of memory partition */
	IAV_PART_FIRST			= IAV_PART_DSP, /*!< IAV_PART_DSP */
	IAV_PART_LAST			= IAV_PART_NUM, /*!< IAV_PART_NUM */

	IAV_PART_USR_CUSTOM_ID_FIRST	= 192, /*!< 192, First customer ID for user memory partition */
	IAV_PART_USR_CUSTOM_ID_LAST		= 255, /*!< 255, Last customer ID for user memory partition */
};

enum iav_sync_cache_mem_part_opt {
	IAV_CACHE_CLEAN = 0, /*!< Flush data from cache to physical memory.*/
	IAV_CACHE_INVALIDATE, /*!< Discard cache data in order to let it reload data from memory.*/
};

enum iav_mem_id {
	IAV_MEM_PARTITION	= 0x00, /*!< 0x00 */
	IAV_MEM_CANVAS		= 0x01, /*!< 0x01 */
	IAV_MEM_NUM			= 0x02, /*!< 0x02 */
};
/*! @} */ /*End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_mem_info {
	unsigned long addr;  /*!< Start address of memory partition */
	unsigned long length;  /*!< Size of the memory partition. */
	unsigned long offset;  /*!< Offset related to start address. */
};

struct iav_mem_part_info {
	u32 pid; /*!< Memory partiton item ID, @sa iav_mem_part_id */
	struct iav_mem_info mem; /*!< Memory partition description. */
};

struct iav_alloc_mem_part {
	u32 pid;		 /*!< The IAV/DSP sub-partition ID to be allocated, @sa iav_mem_part_id.
				      For anonymous memory partition allocation, pid is the output parameter
				      and an unique ID that represents this allocated memory partition. */
	u32 enable_cache : 1;	/*!< This flag enables or disables the cache when the memory partition is mapped to the user space. */
	u32 reserved0 : 31;
	unsigned long length;	 /*!< As input: the mem part size to be allocated.
				      As output: the real size of the allocated mem part. */
	unsigned long offset;	 /*!< the physical address of the allocated mem part. */
};

struct iav_anon_mem_part {
	u32 pid;		/*< Anonymous pid for register / unregister. */
};

struct iav_alloc_mem_part_fd {
	u32 enable_cache : 1;	/*!< This flag enables or disables the cache when the memory partition is mapped to the user space. */
	u32 reserved0 : 31;
	unsigned long length;	/*!< the mem part size to be allocated. */
	int dma_buf_fd;			/*!< Output param: dma-buf:fd of this memory partition. */
};

struct iav_free_mem_part {
	u32 pid;		/*!< The mem part to be freed, @sa iav_mem_part_id */
};

struct iav_feed_raw {
	u8 chan_id;		/*!< Specifies the channel ID that needs to feed the raw buffer. */
	u8 reserved0[3];
};

struct iav_feed_pyramid {
	u8 chan_id;		/*!< Specifies the channel ID that needs to feed the pyramid buffer. */
	u8 reserved0[3];
};

struct iav_feed_canvas {
	u8 canvas_id;		/*!< Specifies the canvas ID that needs to feed the canvas buffer. */
	u8 reserved0[3];
};

struct iav_mem_canvas_info {
	u32 id_map; /*!< The canvas id map for the queried canvases' memory blocks. */
	struct iav_mem_info yuv[IAV_MAX_CANVAS_BUF_NUM]; /*!< The memory partition information of YUV buffer. */
	struct iav_mem_info me[IAV_MAX_CANVAS_BUF_NUM]; /*!< The memory partition information of ME buffer. */
};

struct iav_sync_cache_mem_part {
	u32 pid; /*!< mem part buf id. */
	enum iav_sync_cache_mem_part_opt opt; /*!< sync operation: invalidate or clean. */
	unsigned long offset; /*!< mem part buf address offset. */
	unsigned long length; /*!< mem part buf length. */
};

struct iav_querymem {
	enum iav_mem_id mid;  /*!< Query memory block item ID, @sa iav_mem_id */
	union {
		struct iav_mem_part_info partition;
		struct iav_mem_canvas_info canvas;
	} arg;
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper */
#define IAV_GDMA_MAX_WIDTH		(4096)

/*! @addtogroup iav-ioctl-general-struct */
struct iav_gdma_copy {
	union {
		unsigned long src_offset;	/*!< The offset of the source, based on the start address of its memory partition.
						     Use this parameter is only when @b src_use_phys = 0 and @b src_mmap_type are set properly. */
		unsigned long src_addr;	/*!< The physical address of the source. This parameter is used only when @b src_use_phys = 1. */
	};
	union {
		unsigned long dst_offset;	/*!< The offset of the destination based on the memory partition start address.
						     This parameter is used only when @b dst_use_phys = 0 and @b dst_mmap_type are set properly. */
		unsigned long dst_addr;	/*!< The physical address of the destination. This parameter is used only when @b dst_use_phys = 1. */
	};
	u16 src_pitch;		/*!< Data pitch of the source */
	u16 dst_pitch;		/*!< Data pitch of the destination */
	u16 src_use_phys : 1;	/*!< A flag that determines whether @b src_addr or @b src_offset is used. */
	u16 dst_use_phys : 1;	/*!< A flag that determines whether @b dst_addr or @b dst_offset is used. */
	u16 src_use_dma_buf_fd : 1;	/*!< A flag that determines whether @b src_dma_buf_fd or @b src_mmap_type is used. */
	u16 dst_use_dma_buf_fd : 1;	/*!< A flag that determines whether @b dst_dma_buf_fd or @b dst_mmap_type is used. */
	u16 src_skip_cache_sync : 1;	/*!< The src buffer cache will not be synced if this flag is enabled. */
	u16 dst_skip_cache_sync : 1;	/*!< The dst buffer cache will not be synced if this flag is enabled. */
	u16 reserved : 10;
	u16 width;		/*!< The width of the memory copy region */
	u32 height;		/*!< The height of the memory copy region */
	union {
		u32 src_mmap_type;	/*!< The memory partition ID of the source */
		int src_dma_buf_fd;	/*!< The dma-buf:fd of the source */
	};
	union {
		u32 dst_mmap_type;	/*!< The memory partition ID of the destination */
		int dst_dma_buf_fd;	/*!< The dma-buf:fd of the destination */
	};
};

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_desc_id {
	IAV_DESC_FRAME		= 0,	/*!< 0, Query frame info after encoding */
	IAV_DESC_STATIS		= 1,	/*!< 1 */
	IAV_DESC_RAW		= 2,	/*!< 2 */
	IAV_DESC_SLICE		= 3,	/*!< 3 */
	IAV_DESC_PRE_FRAME	= 4,	/*!< 4 */
	IAV_DESC_PRE_COUNT	= 5,	/*!< 5 */
	IAV_DESC_CANVAS		= 6,	/*!< 6 */
	IAV_DESC_BLEND_YUV	= 7,	/*!< 7 */
	IAV_DESC_PYRAMID	= 8,	/*!< 8 */
	IAV_DESC_RAWSEQ		= 9,	/*!< 9 */
	IAV_DESC_CANVASGRP	= 10,	/*!< 10 */
	IAV_DESC_TML		= 11,	/*!< 11 */
	IAV_DESC_POLL		= 12,	/*!< 12 */
	IAV_DESC_DIS_STATIS	= 13,	/*!< 13 */
	IAV_DESC_JS_FRAME	= 14,	/*!< 14, Query JPEG service frame info after encoding */
	IAV_DESC_NUM,
	IAV_DESC_FIRST		= IAV_DESC_FRAME, /*!< IAV_DESC_FRAME */
	IAV_DESC_LAST		= IAV_DESC_NUM, /*!< IAV_DESC_NUM */
};

enum iav_stream_type {
	IAV_STREAM_TYPE_NONE	= 0x0, /*!< 0x0 */
	IAV_STREAM_TYPE_H264	= 0x1, /*!< 0x1 */
	IAV_STREAM_TYPE_MJPEG	= 0x2, /*!< 0x2 */
	IAV_STREAM_TYPE_H265	= 0x3, /*!< 0x3 */
	IAV_STREAM_TYPE_NUM		= 0x4, /*!< 0x4 */
	IAV_STREAM_TYPE_INVALID	= 0xFF, /*!< 0xFF */
};

enum iav_pic_type {
	IAV_PIC_TYPE_MJPEG_FRAME		= 0, /*!< 0 */
	IAV_PIC_TYPE_IDR_FRAME			= 1, /*!< 1 */
	IAV_PIC_TYPE_I_FRAME			= 2, /*!< 2 */
	IAV_PIC_TYPE_P_FRAME			= 3, /*!< 3 */
	IAV_PIC_TYPE_B_FRAME			= 4, /*!< 4 */
	IAV_PIC_TYPE_P_FAST_SEEK_FRAME	= 5, /*!< 5 */
	/* Value 6 is reseved for furture extension */
	IAV_PIC_TYPE_END_FRAME			= 7, /*!< 7 */
};

enum iav_statis_type {
	IAV_ENC_STATIS_MV		= 0x0, /*!< 0x0 */
	IAV_ENC_STATIS_HEVC		= 0x1, /*!< 0x1 */
	IAV_ENC_STATIS_AVC		= 0x2, /*!< 0x2 */
	IAV_ENC_STATIS_NUM		= 0x3, /*!< 0x3 */
	IAV_ENC_STATIS_FIRST	= IAV_ENC_STATIS_MV, /*!< IAV_ENC_STATIS_MV */
	IAV_ENC_STATIS_LAST		= IAV_ENC_STATIS_NUM, /*!< IAV_ENC_STATIS_NUM */
};

#define IAV_VIN_REGS_SIZE	(0x48)
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_framedesc {
	u32 id;				 /*!< Stream ID, -1 for read bits of all streams */
	u32 time_ms;			 /*!< timeout in ms. -1 (0xFFFFFFFF) means non-blocking, 0 means blocking */
	enum iav_stream_type stream_type; /*!< Stream type of the frame */
	u32 pic_type		: 3;	 /*!< Picture type of the frame */
	u32 stream_end		: 1;	 /*!< Flag for stream end */
	u32 reserved0		: 4;
	u32 jpeg_quality	: 8;	 /*!< Quality value for MJPEG. Valid range [0~100]. */
	u32 bitrate_kbps	: 16;	 /*!< Real bitrate in kbps for H264 / H265 */
	u32 js_frame_uuid;		 /*!< uuid of JPEG service frame */
	u32 session_id;			 /*!< Session ID of the stream for each frame */
	u32 size;			 /*!< Coded bits size for the frame */
	u32 slice_id : 8;		 /*!< Slice ID */
	u32 slice_num : 8;		 /*!< Total slice number */
	u32 tile_id : 2;		 /*!< Tile ID */
	u32 tile_num : 2;		 /*!< Total tile number */
	u32 is_ltr_frame : 1;		 /*!< Is long term reference frame or not */
	u32 force_frame_skip : 1;	 /*!< Is the frame skipped */
	u32 reserved1 : 10;
	u64 arm_pts;			 /*!< System PTS for the frame */
	u64 dsp_pts;			 /*!< DSP PTS for the frame */
	u64 enc_done_ts;		 /*!< The encode done time stamp for the frame */
	struct iav_window reso;		 /*!< Resolution of the encoded frame */
	unsigned long data_addr_offset;	 /*!< Address offset for frame coded bits */
	unsigned long mv_data_offset;	 /*!< Byte offset for MV data, @sa iav_mv */
	u16 sliceheader_offset;		/*!< Byte offset for the bit stream content data from each frame */
	u16 reserved2[2];
	u16 encoded_frame_num;		/*!< 16 bit frame number of the frame in encode order */
	u64 frame_num;			 /*!< 64 bit frame number of the frame in display order */
};

struct iav_slicedesc {
	u32 id;				/*!< Stream ID, -1 for read bits of all streams */
	u32 time_ms;			/*!< timeout in ms; -1 (0xFFFFFFFF) means non-blocking, 0 means blocking */
	enum iav_stream_type stream_type;/*!< Stream type of the frame */
	u32 pic_type		: 3;	/*!< Picture type of the frame */
	u32 stream_end		: 1;	/*!< Flag for stream end */
	u32 reserved1		: 4;
	u32 jpeg_quality	: 8;	/*!< Quality value for MJPEG. Valid range [0~100]. */
	u32 bitrate_kbps	: 16;	/*!< Real bitrate in kbps for H264 / H265 */
	u16 encoded_frame_num;		/*!< 16 bit frame number of the frame in encode order */
	u16 reserved2;
	u32 session_id;			/*!< Session ID of the stream for the frame */
	u64 arm_pts;			/*!< System PTS for the frame */
	u64 dsp_pts;			/*!< DSP PTS for the frame */
	u64 enc_done_ts;		/*!< The encode done timestamp for the frame */
	struct iav_window reso;		/*!< Resolution of the encoded frame */
	u32 slice_id : 4;		/*!< Slice ID */
	u32 slice_num : 4;		/*!< Total slice number */
	u32 tile_id : 2;		/*!< Tile ID */
	u32 tile_num : 2;		/*!< Total tile number */
	u32 reserved3 : 20;
	u32 size[IAV_HEVC_TILE_NUM];	/*!< Coded bits size for the slice */
	unsigned long data_addr_offset[IAV_HEVC_TILE_NUM]; /*!< Address offset for slice coded bits */
	u64 frame_num;			/*!< 64 bit frame number of the frame in display order */
};

/* mv descriptor reported by DSP */
struct iav_mv {
	s32 x : 15;	/*!< Bit [14:0] is the x component in signed 15-bit format. */
	s32 y : 12;	/*!< Bit [26:15] is the y component in signed 12-bit format. */
	s32 reserved : 5;
};

struct iav_statisdesc {
	u32 id;		/*!< Stream ID, can't be -1 */
	u32 time_ms;	/*!< timeout in ms; -1 (0xFFFFFFFF) means non-blocking, 0 means blocking */
	u32 width;	/*!< Width offset for frame */
	u32 height;	/*!< Height offset for frame */
	u32 pitch;	/*!< Pitch offset for frame */
	u32 dsp_pts;	/*!< DSP PTS for the frame */
	u64 arm_pts;	/*!< ARM PTS for the frame */
	u32 frame_num;	/*!< Frame number of the frame */
	u32 session_id;	/*!< Session ID */
	u32 size;	/*!< Unit size of the frame MV dump data */
	enum iav_statis_type statis_type; /*!< Statis type */
	unsigned long data_addr_offset; /*!< Address offset for frame statistic data */
};

struct iav_pre_framedesc {
	u16 stream_id : 8;	/*!< Stream ID, -1 for read bits of all streams */
	u16 pic_type : 3;	/*!< Frame type as I, P, B */
	u16 is_ltr : 1;		/*!< Long term reference P frame flag */
	u16 get_latest : 1;	/*!< 0: get the oldest from the frame queue; 1: always get the latest frame */
	u16 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u16 reserved : 2;
	u16 y_pitch;		/*!< YUV data pitch */
	u16 me1_pitch;		/*!< ME1 data Pitch */
	u16 me0_pitch;		/*!< ME0 data Pitch */
	u64 frame_no;		/*!< Frame number */
	unsigned long y_addr_offset; /*!< Y data offset */
	unsigned long uv_addr_offset;/*!< UV data offset */
	unsigned long me1_addr_offset; /*!< ME1 data offset */
	unsigned long me0_addr_offset; /*!< ME0 data offset */
	struct iav_window yuv_reso; /*!< YUV resolution */
	struct iav_window me1_reso; /*!< ME1 resolution */
	struct iav_window me0_reso; /*!< ME0 resolution */
	u32 dsp_pts;		/*!< Intermediate PTS from DSP */
	u32 reserved1;
	u64 mono_pts;		/*!< Monotonic PTS of the frame data  */
};

struct iav_pre_countdesc {
	u32 non_block_flag : 1;	/*!< Query without block flag */
	u32 reserved : 31;
	u8 stream_cap_count[IAV_STREAM_MAX_NUM_ALL]; /*!< Frame information count for every stream */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum IAV_BUFCAP_FLAG {
	IAV_BUFCAP_NONBLOCK	= (1 << 0), /*!< 1 << 0 */
};

enum IAV_RAW_FORMAT {
	IAV_RAW_FORMAT_RGB = 0,	/*!<0 */
	IAV_RAW_FORMAT_YUV422 = 1,	/*!< 1 */
	IAV_RAW_FORMAT_YUV420 = 2,	/*!< 2 */
};
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */

struct iav_rawbufdesc {
	u32 width;		/*!< Width of the raw picture. When raw_capture of @ref iav_chan_cfg is enabled,
					it is 1/2 of @ref width_in_byte. When raw_capture of @ref iav_chan_cfg is disabled,
					it is equal to @ref width_in_byte. */
	u32 height;		/*!< Height of the raw picture */
	u32 pitch;		/*!< Pitch size of the raw picture */
	u32 non_block_flag : 1;	/*!< Block read flag of the raw picture */
	u32 is_dsp_hw_pts : 1; /*!< When set, dsp_pts is hw_pts from dsp, otherwise sw_pts. */
	u32 format : 3;	/*!< raw data format. */
	u32 raw_compressed : 1;	/*!< raw data compress flag. */
	u32 packed : 1;	/*!< raw data bits pack flag. */
	u32 bits_per_pixel : 5;	/*!< raw data pixel bits number. */
	u32 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u32 reserved1 : 11;
	u32 vin_id : 8;		/*!< VIN controller ID */
	u64 mono_pts;		/*!< Monotonic PTS of the raw picture */
	unsigned long raw_addr_offset; /*!< Address offset for frame raw picture */
	u32 dsp_pts;		/*!< DSP PTS of the raw picture */
	u32 ce_addr_offset;	/*!< Contrast enhance image addr */
	u16 ce_pitch;	/*!< Contrast enhance image pitch. */
	u16 ce_width;	/*!< Contrast enhance image width. When raw_capture of @ref iav_chan_cfg is enabled,
					it is 1/2 of @ref ce_width_in_byte. When raw_capture of @ref iav_chan_cfg is disabled,
					it is equal to @ref ce_width_in_byte. */
	u32 seq_num;	/*!< Sequence number of the raw data. */
	u64 feed_seq_num;	/*!< The sequence number of current raw buffer for manual feed.
						For IAV_IOC_RELEASE_RAW_BUF, when feed_seq_num is specified to -1(0xFFFFFFFFFFFFFFFF),
						it will release all locked raw buffers. */
	u16 width_in_pixel;	/*!< Raw picture width in pixel */
	u16 ce_width_in_pixel;	/*!< Contrast enhance image width in pixel */
	u16 width_in_byte;	/*!< Raw picture width in byte */
	u16 ce_width_in_byte;	/*!< Contrast enhance image width in byte */
};

struct iav_rawseqdesc {
	u32 width;		/*!< Width of the raw picture */
	u32 height;		/*!< Height of the raw picture */
	u32 pitch;		/*!< Pitch size of the raw picture */
	u32 non_block_flag : 1;	/*!< Block read flag of the raw picture */
	u32 reserved1 : 23;
	u32 vin_id : 8;		/*!< VIN controller ID */
	unsigned long seq_pts[IAV_MAX_RAWSEQ_NUM];		/*!< DSP PTS of each frame from RAW sequence */
	unsigned long seq_addr_offset[IAV_MAX_RAWSEQ_NUM]; /*!< Address offset of each frame from RAW sequence */
};

struct iav_tmlbufdesc {
	u32 chan_id : 8;		/*!< Channel id */
	u32 non_block_flag : 1;	/*!< Block read flag of the tml buffer info */
	u32 is_dsp_hw_pts : 1;	/*!< When set, @ref dsp_pts is hw_pts from dsp, otherwise sw_pts. */
	u32 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u32 reserved : 21;

	u32 dsp_pts;		/*!< DSP PTS of the tml buffer info. Its type depends on @ref is_dsp_hw_pts. */
	u64 mono_pts;		/*!< Monotonic PTS of the tml buffer info */

	u16 packed_raw_width;	/*!< Width of the packed raw */
	u16 packed_raw_pitch;	/*!< Pitch of the packed raw */
	u16 packed_raw_height;	/*!< Height of both the packed raw and hds */
	u16 subtract_out_raw_width;	/*!< Width of the subtracted output */
	u16 subtract_out_raw_pitch;	/*!< Pitch of the subtracted output */
	u16 subtract_out_raw_height;	/*!< Height of the subtracted output */

	unsigned long packed_raw_offset;	/*!< Address offset for the packed raw */
	unsigned long subtract_out_raw_offset;	/*!< Address offset for the subtracted output */
};

struct iav_yuv_cap {
	u32 width;	/*!< Width of the YUV data */
	u32 height;	/*!< Height of the YUV data */
	u32 pitch;	/*!< Pitch size of the YUV data */
	u32 seq_num;	/*!< Sequence number of the YUV data */
	u32 format;	/*!< Format of the YUV data */
	u32 dsp_pts;	/*!< Intermediate PTS from DSP */
	u64 mono_pts;	/*!< Monotonic PTS of the YUV data */
	unsigned long y_addr_offset; /*!< Address offset for frame Y data */
	unsigned long uv_addr_offset;/*!< Address offset for frame UV data */
};

struct iav_me_cap {
	u32 width;	/*!< Width of the frame ME data */
	u32 height;	/*!< Height of the frame ME data */
	u32 pitch;	/*!< Pitch size of the frame ME data */
	u32 seq_num;	/*!< Sequence number of the frame ME data */
	u32 dsp_pts;	/*!< Intermediate PTS from DSP */
	u64 mono_pts;	/*!< Monotonic PTS of the frame ME data */
	unsigned long data_addr_offset; /*!< Address offset for frame ME data */
};

struct iav_extra_raw_cap {
	u8 vinc_id;			/*!< Vin controller id*/
	u8 reserved[3];
	u32 pitch;			/*!< Pitch of extra raw data */
	u16 height;			/*!< Height of extra raw data */
	u8 top_lines;			/*!< Top lines of extra raw data */
	u8 bottom_lines;		/*!< Bottom lines of extra raw data */
	u32 dsp_pts;			/*!< Intermediate PTS from DSP */
	u64 mono_pts;			/*!< Monotonic PTS of the frame ME data */
	unsigned long data_addr_offset;	/*!< Data addr offset of extra raw data */
};

struct iav_canvasdesc {
	u32 non_block_flag : 1;	/*!< Block flag */
	u32 canvas_id : 8;	/*!< Canvas ID */
	u32 is_dsp_hw_pts : 1;	/*!< When set, dsp_pts is hw_pts from dsp, otherwise sw_pts. */
	u32 led_enable : 1;	/*!< LED enable or disable flag */
	u32 yuv_use_dma_buf_fd : 1; /*!< When set, dma-buf:fd will be used to describe YUV data. */
	u32 me_use_dma_buf_fd : 1;	/*!< When set, dma-buf:fd will be used to describe ME data. */
	u32 query_extra_raw : 1;	/*!< This is to specify if querying extra raw info */
	u32 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u32 discard_cached_items : 1;	/*!< When set, discard cached items and wait for the next coming one.
						Only valid when non_block_flag is 0. */
	u32 reserved : 16;
	struct iav_yuv_cap yuv; /*!< YUV descriptor item */
	struct iav_me_cap me1;	/*!< ME1 descriptor item */
	struct iav_me_cap me0;	/*!< ME0 descriptor item */
	u64 feed_seq_num;		/*!< The sequence number of current canvas buffer for manual feed.
							For IAV_IOC_RELEASE_CANVAS_BUF, when feed_seq_num is specified to -1(0xFFFFFFFFFFFFFFFF),
							it will release all locked canvas buffers. */
	int yuv_dma_buf_fd;		/*!< The dma-buf:fd of YUV data, only valid when yuv_use_dma_buf_fd is set */
	int me_dma_buf_fd;		/*!< The dma-buf:fd of ME data (ME0 and ME1 share the same dma-buf:fd),
							only valid when me_use_dma_buf_fd is set */
	struct iav_extra_raw_cap extra_raw;	/*!< Extra raw data descriptor item */
};

struct iav_canvasgrpdesc {
	u16 canvas_id_map;	/*!< As input param, specify the canvas id map for querying. As output param, return the actually queried canvas id map. */
	u16 is_dsp_hw_pts : 1; /*!< When set, dsp_pts is hw_pts from dsp, otherwise sw_pts. */
	u16 non_block_flag : 1; /*!< Block flag */
	u16 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u32 yuv_use_dma_buf_fd : 1; /*!< When set, dma-buf:fd will be used to describe YUV data. */
	u32 me_use_dma_buf_fd : 1;	/*!< When set, dma-buf:fd will be used to describe ME data. */
	u32 discard_cached_items : 1;	/*!< When set, discard cached items and wait for the next coming one.
						Only valid when non_block_flag is 0. */
	u16 reserved : 10;
	struct iav_yuv_cap yuv[IAV_MAX_CANVAS_BUF_NUM]; /*!< YUV descriptor item */
	struct iav_me_cap me1[IAV_MAX_CANVAS_BUF_NUM];	/*!< ME1 descriptor item */
	struct iav_me_cap me0[IAV_MAX_CANVAS_BUF_NUM];	/*!< ME0 descriptor item */
	int yuv_dma_buf_fd[IAV_MAX_CANVAS_BUF_NUM];		/*!< The dma-buf:fd of YUV data, only valid when yuv_use_dma_buf_fd is set */
	int me_dma_buf_fd[IAV_MAX_CANVAS_BUF_NUM];		/*!< The dma-buf:fd of ME data (ME0 and ME1 share the same dma-buf:fd),
													only valid when me_use_dma_buf_fd is set */
};

struct iav_blenddesc {
	u32 non_block_flag : 1; /*!< Block read flag of the blend description */
	u32 is_dsp_hw_pts : 1; /*!< When set, dsp_pts is hw_pts from dsp, otherwise sw_pts. */
	u32 reserved : 30;
	struct iav_yuv_cap yuv[IAV_BLEND_OVERLAP_AREA_MAX][IAV_BLEND_NUM]; /*!< YUV buffer information of overlapped areas */
};

/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
#define AVC_HIST_X				(16)

#define HEVC_MV_HIST_X			(2)
#define HEVC_MV_HIST_Y			(2)
#define HEVC_MV_HIST_K			(128)
#define HEVC_QP_HIST_X			(64)
#define HEVC_INTER_CNT_U8_X		(5)
#define HEVC_INTER_CNT_U16_X	(3)
#define HEVC_INTER_CNT_U32_X	(3)
#define MAX_POLL_EVENT			(16)
#define POLL_EVENT_INDEX(bit)	(1 << bit)
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_pic_stats_avc {
	/* h264_xfHisto_t */
	u32 rsvd[16];
	u16 xfMbCatHisto[AVC_HIST_X];	/*!< Macro blocks number with corresponding QP value */
	u32 rsvd1;

	/* Nom QP Table */
	u8 qp[AVC_HIST_X];	/*!< QP values used in one encoded frame*/
	u32 reserved[1059];

};

struct iav_pic_stats_hevc {
	u32 mv_histogram[HEVC_MV_HIST_X][HEVC_MV_HIST_Y][HEVC_MV_HIST_K];         // [L0/L1][x/y][abs_mv at CU8 granularity]
	u32 reserved_0[30];
	u32 qp_histogram[HEVC_QP_HIST_X];                // [QP value at CU8 granularity]
	u32 intra_counter_pu4;
	u32 intra_counter_pu8;
	u32 intra_counter_pu16;
	u32 intra_counter_pu32;
	u32 inter_counter_cu8[HEVC_INTER_CNT_U8_X];           // indexed by (skip/tu4_merge/tu4_mvp/tu8_merge/tu8_mvp)
	u32 inter_counter_cu16[HEVC_INTER_CNT_U16_X];           // indexed by (skip/merge/mvp)
	u32 inter_counter_cu32[HEVC_INTER_CNT_U32_X];           // indexed by (skip/merge/mvp)
	u32 pcm_counter_cu32;
	u32 reserved_1[466];
};

struct iav_pyramiddesc {
	u32 chan_id : 8;	/*!< Channel ID */
	u32 non_block_flag : 1;	/*!< Block read flag of the pyramid description */
	u32 layers_map : 6;	/*!< Layer bit map. Each bit stands for one layer. 1 means enable this layer, 0 means disable this layer. */
	u32 is_dsp_hw_pts : 1; /*!< When set, dsp_pts is hw_pts from dsp, otherwise sw_pts. */
	u32 use_dma_buf_fd : 1; /*!< When set, dma-buf:fd will be used to describe pyramid frame.
							NOTE: it is only valid for querying pyramid data in manual-feed mode. */
	u32 query_extra_raw : 1;/*!< This is to specify if querying extra raw info */
	u32 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u32 use_task_id : 1;	/*!< When set, need to specify task id to query pyramid data.
			It is enabled only when custom pyramid is enabled. */
	u32 reserved : 12;
	struct iav_yuv_cap layers[IAV_MAX_PYRAMID_LAYERS]; /*!< YUV buffer information of enabled pyramid layers */
	u64 seq_num;		/*!< The sequence number of current pyramid description.
						For IAV_IOC_RELEASE_PYRAMID_BUF, when seq_num is specified to -1(0xFFFFFFFFFFFFFFFF),
						it will release all locked pyramid buffers. */
	int dma_buf_fd; /*!< dma-buf:fd of current pyramid frame. Only valid when @b use_dma_buf_fd = 1 */
	struct iav_extra_raw_cap extra_raw;	/*!< Extra raw data descriptor item */
	u64 task_id;	/*!< The task id to query the pyramid data if use_task_id flag set.
			It is used only when custom pyramid is enabled. */
	u32 usr_magic_num;	/*!< The magic num specified by the user and return to the user when data is ready.
			It is used only when custom pyramid is enabled. */
};

struct iav_framedesc_event {
	u32 stream_id; /*!< Stream ID, -1 for read bits of all streams */
};

struct iav_statisdesc_event {
	u32 stream_id;						/*!< Stream ID, -1 for read bits of all streams */
	enum iav_statis_type statis_type;	/*!< Statis type */
};

struct iav_rawbufdesc_event {
	u8 vin_id; /*!< VIN controller ID */
	u8 reserved[3];
};

struct iav_rawseqdesc_event {
	u8 vin_id; /*!< VIN controller ID */
	u8 reserved[3];
};

struct iav_canvasdesc_event {
	u8 canvas_id; /*!< Canvas ID */
	u8 reserved[3];
};

struct iav_pyramiddesc_event {
	u8 chan_id; /*!< Channel ID */
	u8 reserved[3];
};

struct iav_slicedesc_event {
	u32 stream_id; /*!< Stream ID, -1 for read bits of all streams */
};

struct iav_querydesc_event {
	enum iav_desc_id qid;						/*!< query desc id */
	union {
		struct iav_framedesc_event frame;		/*!< query frame event */
		struct iav_statisdesc_event statis;		/*!< query encoding statis event */
		struct iav_rawbufdesc_event rawbuf;		/*!< query single raw image event */
		struct iav_rawseqdesc_event rawseq;		/*!< query raw image sequence event */
		struct iav_canvasdesc_event canvas;		/*!< query single canvas event */
		struct iav_pyramiddesc_event pyramid;	/*!< query pyramid event */
		struct iav_slicedesc_event slice;		/*!< query slice event */
	} arg;
};

struct iav_poll_event_config {
	u8 valid_num; /*!< query event num */
	u8 reserved[3];
	struct iav_querydesc_event desc_event[MAX_POLL_EVENT]; /*!< detailed event */
};

struct iav_dis_ctb_result
{
	u16 intra; /*!< Intra flags at CU8 granularity */
	u16 intra_pu4; /*!< CU8 NxN pred flags */
	u32 cu16_split :4; /*!< CU16 split flags */
	u32 reserved_0 :4;
	u32 cu32_split :1; /*!< CU32 split flag */
	u32 reserved_1 :7;
	u32 cat_cu16_0 :4; /*!< Category at CU16 granularity */
	u32 cat_cu16_1 :4; /*!< Category at CU16 granularity */
	u32 cat_cu16_2 :4; /*!< Category at CU16 granularity */
	u32 cat_cu16_3 :4; /*!< Category at CU16 granularity */
	u16 act_cu16[4]; /*!< Activity >> 8 at CU16 granularity */
	u8 qp_cu16[4]; /*!< QP at CU16 granularity */
};

struct iav_dis_mv {
	s32 x : 15; /*!< X offset */
	s32 y : 12; /*!< Y offset */
	s32 reserved2 : 5;
	u32 reserved1[11];
};

struct iav_disdesc {
	u32 id; /*!< Stream ID */
	u32 coloc_mv_offset; /*!< Address offset for coloc MV. It is within IAV_PART_DSP. */
	u32 ctb_results_offset; /*!< Address offset for CTB results. It is within IAV_PART_DIS_CTB_STATIS. */
	u16 coloc_dpitch; /*!< Pitch of the coloc MV. */
	u16 ctb_results_dpitch; /*!< Pitch of CTB results. */
	u16 width_in_mb; /*!< Stream Width in MB. */
	u16 height_in_mb; /*!< Stream Height in MB. */
	u32 hw_pts; /*!< hardware PTS. */
};

struct iav_querydesc {
	enum iav_desc_id qid;	/*!< query desc id */
	union {
		struct iav_framedesc frame;			/*!< query frame */
		struct iav_statisdesc statis;		/*!< query encoding statis */
		struct iav_rawbufdesc raw;			/*!< query single raw image */
		struct iav_rawseqdesc rawseq;		/*!< query raw image sequence */
		struct iav_canvasdesc canvas;		/*!< query single canvas */
		struct iav_canvasgrpdesc canvasgrp;	/*!< query group of canvas */
		struct iav_slicedesc slice;
		struct iav_pre_framedesc pre_frame;
		struct iav_pre_countdesc pre_count;
		struct iav_blenddesc blend;
		struct iav_pyramiddesc pyramid;		/*!< query pyramid */
		struct iav_tmlbufdesc tml;		/*!< query tml info */
		struct iav_disdesc dis;			/*!< query DIS statis */
	} arg;
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_stream_op {
	IAV_STREAM_OP_STOP	= 0, /*!< 0 */
	IAV_STREAM_OP_START	= 1, /*!< 1 */
};

enum iav_chroma_format {
	H264_CHROMA_YUV420	= 0, /*!< 0 */
	H264_CHROMA_MONO	= 1, /*!< 1 */

	JPEG_CHROMA_MONO	= 0, /*!< 0 */
	JPEG_CHROMA_YUV420	= 1, /*!< 1 */
	JPEG_CHROMA_YUV422	= 2, /*!< 2 */
};
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_stream_fps {
	u32 fps_multi;		/*!< Multiple value for fps configuration */
	u32 fps_div;		/*!< Divisor value for fps configuration */
	u32 abs_fps : 8;	/*!< Absolute frame rate value. Only valid when @b abs_fps_enable is set. */
	u32 abs_fps_enable : 1; /*!< Flag to enable / disable abs FPS */
	u32 is_update_frame_rate_to_next_GOP: 1;	/*!< Flag to update frame rate to next GOP. */
	u32 reserved : 22;
	u32 abs_fps_hp;	/*!< High precision framerate. abs_fps_hr = 1000 * abs_fps. For setting, only valid when "enable_hp_flag" is 1.
		For getting, value is always valid.*/
};

struct iav_stream_flip {
	u32 h : 1;		/*!< Horizontal flip flag */
	u32 v : 1;		/*!< Vertical flip flag */
	u32 reserved : 30;
};

struct iav_stream_format {
	enum iav_stream_type type;/*!< @sa iav_stream_type */
	struct iav_rect enc_win;/*!< Encode window from source buffer */
	u32 duration : 16;	/*!< Encode duration (in frames) for the stream */
	u32 enc_src_id : 8;	/*!< Encode source canvas id, 0~10: Canvas 0~10, 16: EFM, 17: JPEG service */
	u32 hflip : 1;		/*!< Stream horizontal flip flag. 0: No horizontal flip; 1: Horizontal flip */
	u32 vflip : 1;		/*!< Stream vertical  flip flag. 0: No vertical flip; 1: Vertical flip */
	u32 rotate_cw : 1;	/*!< Stream clockwise 90 rotation flag.
						0: No clockwise rotation of 90; 1: Clockwise rotation of 90. */
	u32 use_enc_src_map : 1;	 /*!< Flag to use enc_src_id or enc_src_map. 0: use enc_src_id; 1: use enc_src_map */
	u32 fake_avg_pts : 1;	/*!< Flag to enable the faked average PTS or not, default is disabled (0).
						This feature is ONLY used when IDSP fps is upsampled from VIN frame rate.*/
	u32 reserved1 : 3;
	u32 efm_customize_fps;	/*!< Specify the arbitrary frame rate for EFM stream */
	u32 session_id;			/*!< Specify the session id for the stream.
							0: generate session id automatically; Non-zero: should be unique for each stream. */
	u16 enc_src_map;		/*!< Encode source canvas bit map. Stream can be encoded from multi-canvas with same resolution and offset. */
	u16 reserved2;
};

struct iav_fps_suggest {
	u32 fps_keep_map;	/*!< Bit map for stream fps keep or not: 1: Keep; 0: Not keep */
	u32 stream_exclude_map;	/*!< Bit map for stream exclusion: 1: Exclude; 0: Not exclude */
	u32 stream_fps_suggest[IAV_STREAM_MAX_NUM_ALL]; /*!< Stream FPS suggest result in 16.16 Format */
	u32 vin_target_fps[VIN_INSTANCES]; /*!< VIN target fps in 16.16 Format */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */

enum GOP_IDR_INTV {
	MIN_IDR_INTV	= 1, /*!< 1 */
	MAX_IDR_INTV	= 128, /*!< 128 */
};

#define IAV_MJPEG_MAX_SLICE_NUM					(16)
#define IAV_MJPEG_MAX_SLICE_MB_NUM					(0x10000)
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_h26x_gop {
	u32 id;		/*!< Related stream id. */
	u32 N;		/*!< GOP length. */
	u32 idr_interval;	/*!< GOP number between two idr.*/
	u32 is_update_N_to_next_GOP;	/*!< Flag to GOP length update mode. 0: Update immediately. 1: Update at next gop. */
};

struct iav_bitrate {
	u32 id;			/*!< Stream ID */
	u32 average_bitrate;	/*!< The target average bitrate */
	u32 vbr_setting : 8;	/*!< 1: IAV_BRC_CBR (obsolete); 2: IAV_BRC_PCBR (obsolete); 3: IAV_BRC_VBR (obsolete);
				     4: IAV_BRC_SCBR; 5: IAV_BRC_SVBR (obsolete). This field must always be set to IAV_BRC_SCBR (Smart Constant Bitrate Control). */
	u32 qp_min_on_I : 8;	/*!< This field specifies the minimum QP allowed for I picture. The valid range is 0 to 51 (inclusive).
				     The default value is 1. */
	u32 qp_max_on_I : 8;	/*!< This field specifies the maximum QP allowed for I picture. The valid range is 0 to 51 (inclusive).
				     The default value is 51. */
	u32 qp_min_on_P : 8;	/*!< This field specifies the minimum QP allowed for P picture. The valid range is 0 to 51 (inclusive).
				     The default value is 1. */
	u32 qp_max_on_P : 8;	/*!< This field specifies the maximum QP allowed for P picture. The valid range is 0 to 51 (inclusive).
				     The default value is 51. */
	u32 qp_min_on_B : 8;	/*!< This field specifies the minimum QP allowed for B picture. Not supported yet. */
	u32 qp_max_on_B : 8;	/*!< This field specifies the maximum QP allowed for B picture. Not supported yet. */
	u32 i_qp_reduce : 8;	/*!< This field specifies how much better to make I QP relative to P QP. To increase the ratio of I QP/ P QP,
				     use a small value. To reduce the ratio of I QP/ P QP, use a large value. The valid range is 1 to 10 (inclusive).
				     The default value is 1. */
	u32 p_qp_reduce : 8;	/*!< This field specifies how much better to make P QP relative to B QP. To increase the ratio of P QP/ B QP,
				     use a small value. To reduce the ratio of P QP/ B QP, use a large value. The valid range is 1 to 5 (inclusive).
				     The default value is 1. */
	u32 adapt_qp : 8;	/*!< This field specifies the strength of adaptive quantization. The valid range is 0 to 4 (inclusive).
				     The default value is 0. */
	u32 skip_flag : 8;	/*!< When smart RC is used (bitrate_control = 4), this field specifies the criteria for RC to skip frames.(Bitwise OR)
				     Bit 0:  RC will skip the frame based on the size of the compressed picture.
				     Bit 1:  RC will skip the frame based on CPB size.
				     Bit 2:  RC will skip the frame when the target bit rate is to be exceeded and the maximum QP is reached.
				     The default value is 0 (no frame skipping). */
	u32 q_qp_reduce : 8;	/*!< Relative to P frame */
	u32 qp_max_on_Q : 8;	/*!< Maximum QP allowed for Q frame */
	u32 qp_min_on_Q : 8;	/*!< Minimum QP allowed for Q frame */
	u32 log_q_num_minus_1 : 3; /*!< 128 */
	u32 skip_flag_mode : 1; /*!< skip mode flag. 0: handle skip frame through drop frame. 1: through repeat frame.*/
	u32 reserved0 : 12;
	u32 max_i_size_KB;	/*!< Maximum I frame size */
	u32 qp_min_on_C : 8;	/*!< This field specifies the minimum QP allowed for C picture. The valid range is 0 to 51 (inclusive).
				     The default value is 1. */
	u32 qp_max_on_C : 8;	/*!< This field specifies the maximum QP allowed for C picture. The valid range is 0 to 51 (inclusive).
				     The default value is 51. */
	u32 qp_min_on_D : 8;	/*!< This field specifies the minimum QP allowed for D picture. The valid range is 0 to 51 (inclusive).
				     The default value is 1. */
	u32 qp_max_on_D : 8;	/*!< This field specifies the maximum QP allowed for D picture. The valid range is 0 to 51 (inclusive).
				     The default value is 51. */
	u32 b_qp_reduce : 8;	/*!< This field specifies how much better to make b QP relative to B QP. To increase the ratio of b QP/ P-QP,
				     use a small value. To reduce the ratio of B QP/ P QP, use a large value. The valid range is 1 to 10 (inclusive).
				     The default value is 1. */
	u32 c_qp_reduce : 8;	/*!< This field specifies how much better to make c QP relative to B QP. To increase the ratio of b QP/ P-QP,
				     use a small value. To reduce the ratio of C QP/ P QP, use a large value. The valid range is 1 to 10 (inclusive).
				     The default value is 1. */
	u32 svbr_ness : 10;	/*!< obsolete */
	u32 cbr_stable_br_adjust : 4; /*!< This field specifies how much stable encoder tries to keep the real bitrate around average_bitrate.
									The valid range is 0 to 10 (inclusive). 0: disable; 1: the most stable; 10: the least stable. */
	u32 reserved1 : 2;
	u32 vbr_min_bitrate;	/*!< obsolete */
	u32 vbr_max_bitrate;	/*!< obsolete */
};

struct iav_h26x_weighted_pred {
	u16 wp_enable;			/*!< Enable Weighted Prediction */
	u16 luma_log2_weight_denom;	/*!< Specify luma-log2-wegiht-denom */
	s16 luma_weight[2];		/*!< Set luma-weight[0]/luma-weight[1] */
	s16 luma_offset[2];		/*!< Set luma-offset[0]/luma-offset[1] */
};

struct iav_custom_sei {
	u16 enable : 1;			/*!< Enable customized SEI */
	u16 repeat : 1;			/*!< Repeat customized SEI in latter encoded frames */
	u16 force_idr : 1;		/*!< Insert force idr when add customized SEI */
	u16 reserved : 13;
	u16 frame_idx;			/*!< Frame index of customized SEI buffer that will be fed to DSP */
	u32 size;				/*!< Real size of customized SEI data */
};

struct iav_rc_strategy {
	u32 abs_br_flag : 1; /*!< Flag for abs_br */
	u32 reserved : 31;
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
typedef enum {
	QP_FRAME_I			= 0, /*!< 0 */
	QP_FRAME_P			= 1, /*!< 1 */
	QP_FRAME_B			= 2, /*!< 2 */
	QP_FRAME_TYPE_NUM	= 3, /*!< 3 */
} QP_FRAME_TYPES;

typedef enum {
	QPROI_TYPE_CATEGORY		= 0, /*!< 0 */
	QPROI_TYPE_QP_OFFSET	= 1, /*!< 1 */
} QPROI_TYPE;

typedef enum {
	MD_CAT_LUT_TYPE_DEFAULT			= 0, /*!< 0, For this CTB, it's coded as default option from DSP internal RC. */
	MD_CAT_LUT_TYPE_FORCED_ZMV		= 1, /*!< 1, For this CTB, it's forced to code with Zero Motion Vector (ZMV). */
	MD_CAT_LUT_TYPE_FORCED_INTRA	= 2, /*!< 2, For this CTB, it's forced to code as intra. */
	MD_CAT_LUT_TYPE_UNCOVERED_AREA	= 3, /*!< 3, For this CTB, it's detected to be uncovered and is not expected to
    											get good prediction from any of its references. It will be coded as intra.
    											In conjunction, ARM should config a negative QP adjust value for these
    											CTBs so that they are coded as high quality. */
	MD_CAT_LUT_TYPE_BIAS_SKIP		= 4, /*!< 4, For this CTB, it's bias heavily towards skipped. */
	/* more to come */
	MD_CAT_LUT_NUM					= 5, /*!< 5 */
	MD_CAT_LUT_FIRST				= MD_CAT_LUT_TYPE_DEFAULT, /*!< MD_CAT_LUT_TYPE_DEFAULT */
	MD_CAT_LUT_LAST					= MD_CAT_LUT_NUM, /*!< MD_CAT_LUT_NUM */

	MD_CAT_MAX_NUM					= 8, /*!< 8 */
} MD_CAT_LUT_TYPE;

#define IAV_MAX_CU_BIAS_LEVEL 6

typedef enum {
	HEVC_SCALELIST_OFF		= 0, /*!< 0 */
	HEVC_SCALELIST_DEFAULT	= 1, /*!< 1 */
	HEVC_SCALELIST_CUSTOM	= 2, /*!< 2 */
	HEVC_SCALELIST_TYPE_NUM	= 3, /*!< 3 */
} HEVC_SCALELIST_TYPE;
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_h264_qproi_data {
	u8 category;		/*!< Macroblock level control for user_class */
	s8 qp_adjust;		/*!< Macroblock level control for qp_offset. The qp_offset is added onto
				     the existing QP already calculated by RC and User class bin. The final
				     QP from RC + qp_offset is then used for this MB. */
	u8 zmv_threshold_val;	/*!< Macroblock level control of threshold for zero MV. If MB's sum of Mvs
				     is less than this value, skip mode is encouraged. Value 8 can be used
				     for low bit rate at good lighting. Value 24 can be used for low bit
				     rate at low lighting (high noise). */
	u8 force_zmv_ref0 : 1;	/*!< Macroblock level control to force zmv on reference candidate 0. When
				     this flag is on, force zero MV will be adopted for the target MB, if
				     reference 0 is used. */
	u8 force_zmv_ref1 : 1;	/*!< Macroblock level control to force zmv on reference candidate 1. When
				     this flag is on, force zero MV will be adopted for the target MB, if
				     reference 1 is used. */
	u8 reserved : 6;
};

struct iav_h265_qproi_data {
	union {
		struct {
			u32 cu16_0 : 3;	/*!< Select md_category for 16x16 CU[0]. 0: default; 1: used as force zmv flag. */
			u32 cu16_1 : 3;	/*!< Select md_category for 16x16 CU[1]. 0: default; 1: used as force zmv flag. */
			u32 cu16_2 : 3;	/*!< Select md_category for 16x16 CU[2]. 0: default; 1: used as force zmv flag. */
			u32 cu16_3 : 3;	/*!< Select md_category for 16x16 CU[3]. 0: default; 1: used as force zmv flag. */
			u32 cu32   : 3;	/*!< Select md_category for 32x32 CU. 0: default; 1: used as force zmv flag. */
			u32 reserved_0 : 17;
		};
		u32 dword1;
	} category;
	union {
		struct {
			s32 reserved_1 : 8;
			s32 cu32 : 7; /*!< qp_adjust value for 32x32 CU. Valid range of -51 to 51 inclusive. */
			s32 reserved_2 : 17;
		};
		u32 dword2;
	} qp_adjust_32;
	union {
		struct {
			s32 cu16_0 : 7; /*!< qp_adjust value for 16x16 CU[0]. Valid range of -51 to 51 inclusive. */
			s32 reserved_3 : 1;
			s32 cu16_1 : 7; /*!< qp_adjust value for 16x16 CU[1]. Valid range of -51 to 51 inclusive. */
			s32 reserved_4 : 1;
			s32 cu16_2 : 7; /*!< qp_adjust value for 16x16 CU[2]. Valid range of -51 to 51 inclusive. */
			s32 reserved_5 : 1;
			s32 cu16_3 : 7; /*!< qp_adjust value for 16x16 CU[3]. Valid range of -51 to 51 inclusive. */
			s32 reserved_6 : 1;
		};
		u32 dword3;
	} qp_adjust_16;
};

struct iav_qpmatrix {
	u32 id;			/*!< Stream ID */
	u32 enable : 1;		/*!< whether qp matrix is enabled */
	u32 qpm_no_update : 1;	/*!< 1: No need from app to set the QP matrix data to IAV/DSP, just configure some other parameters.
				     0: App needs to set the QP matrix data (already configured at app side) to IAV/DSP. */
	u32 qpm_no_check : 1;	/*!< 1: No need for IAV to check the QP matrix data to IAV/DSP, app already guarantees the validness
					for the qp matrix data.
				     0: IAV needs to check the QP matrix data (already configured at app side) to IAV/DSP. */
	u32 init_qpm : 1;	/*!< Init QP matrix flag to set OP */
	u32 qpm_raw : 1;	/*!< QP matrix raw mapped flag for get/set op */
	u32 reserved0 : 27;
	u32 data_size;		/*!< The size for the QP ROI matrix */
	u32 reserved1;
	unsigned long data_offset; /*!< The address offset for the QP ROI. The structure @sa iav_h264_qproi_data
							or @sa iav_h265_qproi_data shows the data format. */
};

struct iav_h26x_enc_param {
	u32 id;
	u16 user1_intra_bias;
	u16 user1_direct_bias;
	u16 user2_intra_bias;
	u16 user2_direct_bias;
};

struct iav_h26x_slice {
	u32 slice_num : 8; 	/*!< Specify slice row number, from 0~255. */
	u32 slices_per_info : 8;/*!< Specify slices per bits information. */
	u32 reserved : 16;
};

struct iav_h26x_pskip {
	u32 repeat_enable : 1;	/*!< Enable repeat P-skip frame pattern */
	u32 repeat_mode : 1;	/*!< Specify P-skip repeat mode.
				0: consider the skip num as the interval between every
					two normal P frames.
				1: consider the skip num as the interval between every
					two Pskip frames.*/
	u32 reserved1 : 14;
	u32 repeat_num : 8;	/*!< Specify the skipped frame number to repeat */
	u32 reserved2 : 8;
};

struct iav_h26x_drop_frame {
	u32 repeat_enable : 1;	/*!< Enable repeat drop frame pattern */
	u32 reserved1 : 15;
	u32 drop_num : 8;	/*!< Specify the dropped frame number to repeat */
	u32 reserved2 : 8;
};

struct iav_mjpeg_drop_frame {
	u32 repeat_enable : 1;	/*!< Enable repeat trigger frame pattern */
	u32 reserved1 : 15;
	u32 drop_num : 8;	/*!< Specify the dropped frame number to repeat */
	u32 reserved2 : 8;
};

struct iav_trigger_frame {
	u32 trigger_frame_enable : 1;	/*!< Enable trigger frame */
	u32 repeat_enable : 1;	/*!< Enable repeat encode frame pattern */
	u32 reserved1 : 14;
	u32 trigger_num : 8;	/*!< Specify the trigger encode frame number to repeat */
	u32 reserved2 : 8;
};

struct iav_h26x_cu_split {
	u32 disable_cu8 : 1;		/*!< Disable CU8 partition, default is 0 */
	u32 disable_cu16 : 1;		/*!< Disable CU16 partition, default is 0 */
	u32 cu8_bias_level : 4;		/*!< Specify the bias level for CU8 partition, from 0~6 */
	u32 cu16_bias_level : 4;	/*!< Specify the bias level for CU16 partition, from 0~6 */
	u32 cu32_bias_level : 4;	/*!< Specify the bias level for CU32 partition, from 0~6 */
	u32 reserved : 18;
};

struct iav_h26x_sar {
	u16 sar_width;	/*!< Specify customized SAR width */
	u16 sar_height;	/*!< Specify customized SAR height */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum {
	IAV_ONE_BITS_INFO_PER_TILE	= 0,   /*!< 0 */
	IAV_ONE_BITS_INFO_PER_FRAME	= 255, /*!< 255 */
};

enum iav_streamcfg_id {
	/* Stream config for H264 & H265 & MJPEG (0x0000 ~ 0x0FFF) */
	IAV_STMCFG_FORMAT				= 0x0000, /*!< 0x0000, Stream config for H264 & H265 & MJPEG (0x0000 ~ 0x0FFF) */
	IAV_STMCFG_FPS					= 0x0001, /*!< 0x0001 */
	IAV_STMCFG_OFFSET 				= 0x0002, /*!< 0x0002 */
	IAV_STMCFG_CHROMA				= 0x0003, /*!< 0x0003 */
	IAV_STMCFG_DUMMY_LATENCY		= 0x0004, /*!< 0x0004 */
	IAV_STMCFG_CUSTOM_SEI 			= 0x0005, /*!< 0x0005 */
	IAV_STMCFG_OVERLAY 				= 0x0006, /*!< 0x0006 */
	IAV_STMCFG_FLIP					= 0x0007, /*!< 0x0007 */
	IAV_STMCFG_BLUR					= 0x0008, /*!< 0x0008 */
	IAV_STMCFG_MANUAL_ARM_PTS		= 0x0009, /*!< 0x0009 */
	IAV_STMCFG_FRAME_TRIGGER		= 0x000A, /*!< 0x000A */
	IAV_STMCFG_NUM					= 0x000B, /*!< 0x000B */
	IAV_STMCFG_FIRST				= IAV_STMCFG_FPS, /*!< IAV_STMCFG_FPS */
	IAV_STMCFG_LAST					= IAV_STMCFG_NUM, /*!< IAV_STMCFG_NUM */

	/* H264 config (0x1000 ~ 0x1FFF) */
	IAV_H264_CFG_GOP			= 0x1000, /*!< 0x1000, H264 config (0x1000 ~ 0x1FFF) */
	IAV_H264_CFG_BITRATE			= 0x1001, /*!< 0x1001 */
	IAV_H264_CFG_FORCE_IDR			= 0x1002, /*!< 0x1002 */
	IAV_H264_CFG_QP_LIMIT			= 0x1003, /*!< 0x1003 */
	IAV_H264_CFG_ENC_PARAM			= 0x1004, /*!< 0x1004 */
	IAV_H264_CFG_QP_ROI			= 0x1005, /*!< 0x1005 */
	IAV_H264_CFG_ZMV_THRESHOLD		= 0x1006, /*!< 0x1006 */
	IAV_H264_CFG_FORCE_FAST_SEEK		= 0x1007, /*!< 0x1007 */
	IAV_H264_CFG_FRAME_DROP			= 0x1008, /*!< 0x1008 */
	IAV_H264_CFG_RC_STRATEGY		= 0x1009, /*!< 0x1009 */
	IAV_H264_CFG_SLICE			= 0x100A, /*!< 0x100A */
	IAV_H264_CFG_STATIS			= 0x100B, /*!< 0x100B */
	IAV_H264_CFG_FORCE_PSKIP		= 0x100C, /*!< 0x100C */
	IAV_H264_CFG_SAR			= 0x100D, /*!< 0x100D */
	IAV_H264_CFG_WEIGHTED_PRED		= 0x100E, /*!< 0x100E */
	IAV_H264_CFG_FAST_SEEK_INTERVAL	= 0x100F, /*!< 0x100F */
	IAV_H264_CFG_SKIP_STRENGTH	= 0x1010, /*!< 0x1010 */
	IAV_H264_CFG_ZMV_THRESHOLD_INFO		= 0x1011, /*!< 0x1011 */
	IAV_H264_CFG_CHROMA_QP_OFFSET	= 0x1012, /*!< 0x1012 */
	IAV_H264_CFG_ONE_FRM_QP_OFFSET	= 0x1013, /*!< 0x1013 */
	IAV_H264_CFG_NUM			= 0x1014, /*!< 0x1014 */
	IAV_H264_CFG_FIRST			= IAV_H264_CFG_GOP, /*!< IAV_H264_CFG_GOP */
	IAV_H264_CFG_LAST			= IAV_H264_CFG_NUM, /*!< IAV_H264_CFG_NUM */

	/* MJPEG config (0x2000 ~ 0x2FFF) */
	IAV_MJPEG_CFG_QUALITY				= 0x2000, /*!< 0x2000, MJPEG config (0x2000 ~ 0x2FFF) */
	IAV_MJPEG_CFG_FRAME_DROP			= 0x2001, /*!< 0x2001 */
	IAV_MJPEG_CFG_NUM				= 0x2002, /*!< 0x2002 */
	IAV_MJPEG_CFG_FIRST				= IAV_MJPEG_CFG_QUALITY, /*!< IAV_MJPEG_CFG_QUALITY */
	IAV_MJPEG_CFG_LAST				= IAV_MJPEG_CFG_NUM, /*!< IAV_MJPEG_CFG_NUM */

	/* H265 config (0x3000 ~ 0x3FFF) */
	IAV_H265_CFG_GOP			= 0x3000, /*!< 0x3000, H265 config (0x3000 ~ 0x3FFF) */
	IAV_H265_CFG_BITRATE			= 0x3001, /*!< 0x3001 */
	IAV_H265_CFG_FORCE_IDR			= 0x3002, /*!< 0x3002 */
	IAV_H265_CFG_QP_LIMIT			= 0x3003, /*!< 0x3003 */
	IAV_H265_CFG_ENC_PARAM			= 0x3004, /*!< 0x3004 */
	IAV_H265_CFG_QP_ROI			= 0x3005, /*!< 0x3005 */
	IAV_H265_CFG_ZMV_THRESHOLD		= 0x3006, /*!< 0x3006 */
	IAV_H265_CFG_FORCE_FAST_SEEK		= 0x3007, /*!< 0x3007 */
	IAV_H265_CFG_FRAME_DROP			= 0x3008, /*!< 0x3008 */
	IAV_H265_CFG_RC_STRATEGY		= 0x3009, /*!< 0x3009 */
	IAV_H265_CFG_SLICE			= 0x300A, /*!< 0x300A */
	IAV_H265_CFG_MD_CAT_LUT			= 0x300B, /*!< 0x300B */
	IAV_H265_CFG_FORCE_PSKIP		= 0x300C, /*!< 0x300C */
	IAV_H265_CFG_SAR			= 0x300D, /*!< 0x300D */
	IAV_H265_CFG_WEIGHTED_PRED		= 0x300E, /*!< 0x300E */
	IAV_H265_CFG_FAST_SEEK_INTERVAL	= 0x300F, /*!< 0x300F */
	IAV_H265_CFG_SKIP_STRENGTH	= 0x3010, /*!< 0x3010 */
	IAV_H265_CFG_CU_SPLIT		= 0x3011, /*!< 0x3011 */
	IAV_H265_CFG_CHROMA_QP_OFFSET	= 0x3012, /*!< 0x3012 */
	IAV_H265_CFG_ONE_FRM_QP_OFFSET	= 0x3013, /*!< 0x3013 */
	IAV_H265_CFG_NUM			= 0x3014, /*!< 0x3014 */
	IAV_H265_CFG_FIRST			= IAV_H265_CFG_GOP, /*!< IAV_H265_CFG_GOP */
	IAV_H265_CFG_LAST			= IAV_H265_CFG_NUM, /*!< IAV_H265_CFG_NUM */
};

enum roi_cat_type {
	ROI_CAT_MIN	= 0, /*!< 0 */
	ROI_CAT_MAX	= 7, /*!< 7 */
};

enum iav_h264_profile {
	H264_PROFILE_MAIN		= 1, /*!< 1 */
	H264_PROFILE_HIGH		= 2, /*!< 2 */
	H264_PROFILE_NUM		= 3, /*!< 3 */
	H264_PROFILE_FIRST		= H264_PROFILE_MAIN, /*!< H264_PROFILE_MAIN */
	H264_PROFILE_LAST		= H264_PROFILE_NUM, /*!< H264_PROFILE_NUM */
};

enum iav_h264_au_type {
	H264_NO_AUD_NO_SEI			= 0, /*!< 0 */
	H264_AUD_BEFORE_SPS_WITH_SEI		= 1, /*!< 1 */
	H264_AUD_AFTER_SPS_WITH_SEI		= 2, /*!< 2 */
	H264_NO_AUD_WITH_SEI			= 3, /*!< 3 */
	H264_NO_AUD_ONLY_SPS_WITH_SEI		= 4, /*!< 4 */
	H264_AU_TYPE_NUM			= 5, /*!< 5 */
};

enum iav_h264_aqp_type {
	H264_AQP_TYPE_DEFAULT	= 0, /*!< 0, Default option in internal RC. */
	H264_AQP_TYPE_FRAME_QP	= 1, /*!< 1, Frame QP for frame size decision. */
	H264_AQP_TYPE_MB_QP		= 2, /*!< 2, MB QP for frame size decision. */
	H264_AQP_TYPE_NUM		= 3, /*!< 3 */
};

enum iav_ltr_num_log2 {
	IAV_LTR_NUM_LOG2_MIN	= 1, /*!< 1 */
	IAV_LTR_NUM_LOG2_MAX	= 8, /*!< 8 */
};

enum iav_ltr_type {
	IAV_LTR_TYPE_SINGLE	= 1, /*!< 1 */
	IAV_LTR_TYPE_TWO	= 2, /*!< 2 */
	IAV_LTR_TYPE_NUM	= IAV_LTR_TYPE_TWO, /*!< IAV_LTR_TYPE_TWO */
};

enum iav_two_ltr_mode {
	IAV_TWO_LTR_FAST_SEEK	= 0, /*!< 0 */
	IAV_TWO_LTR_PREV_PREV	= 1, /*!< 1 */
	IAV_TWO_LTR_MODE_NUM	= 2, /*!< 2 */
};

enum iav_gop_model {
	IAV_GOP_SIMPLE			= 0, /*!< 0, simpe GOP (I & P frames), MPEG2 alike */
	IAV_GOP_ADVANCED		= 1, /*!< 1, advanced GOP (obsolete) */
	IAV_GOP_SVCT_2			= 2, /*!< 2, 2 level SVCT*/
	IAV_GOP_SVCT_3			= 3, /*!< 3, 3 level SVCT */
	IAV_GOP_SVCT_4			= 4, /*!< 4, 4 level SVCT */
	IAV_GOP_FAST_SEEK		= 5, /*!< 5, fast seek GOP */
	IAV_GOP_2_REF			= 6, /*!< 6, 2 ref GOP */
	IAV_GOP_FAST_SEEK_2_REF		= 7, /*!< 7, 2 ref with fast seek GOP */
	IAV_GOP_NON_REF_P		= 8, /*!< 8, all P refers from I. App can drop P anytime from the GOP.
									This GOP enable fast reverse play. */
};

enum iav_bitrate_control_params {
	/* QP limit parameters */
	H264_AQP_MAX					= 4, /*!< 4, QP limit parameters */
	H264_QP_MAX						= 51, /*!< 51 */
	H264_QP_MIN						= 0, /*!< 0 */
	H264_I_QP_REDUCE_MAX			= 10, /*!< 10 */
	H264_I_QP_REDUCE_MIN			= 1, /*!< 1 */
	H264_P_QP_REDUCE_MAX			= 5, /*!< 5 */
	H264_P_QP_REDUCE_MIN			= 0, /*!< 0 */
	H264_B_QP_REDUCE_MAX			= 5, /*!< 5 */
	H264_B_QP_REDUCE_MIN			= 0, /*!< 0 */
	H264_C_QP_REDUCE_MAX			= 5, /*!< 5 */
	H264_C_QP_REDUCE_MIN			= 0, /*!< 0 */
	H264_Q_QP_REDUCE_MAX			= 10, /*!< 10 */
	H264_Q_QP_REDUCE_MIN			= 1, /*!< 1 */
	/* skip frame flag */
	H264_WITHOUT_FRAME_DROP			= 0, /*!< 0, skip frame flag */
	H264_WITH_FRAME_DROP			= 6, /*!< 6 */
	H264_LOG_Q_NUM_MINUS_1_MAX		= 4, /*!< 4 */
	H264_I_SIZE_KB_MAX				= 8192, /*!< 8192 */
	/* svbr control */
	H264_SVBR_NESS_MIN				= 1, /*!< 1, svbr control */
	H264_SVBR_NESS_MAX				= 200, /*!< 200 */
	H264_SVBR_MULTI_MAX				= 5, /*!< 5 */
	/* cbr stable br adjust */
	H264_CBR_STABLE_BR_ADJUST_MIN	= 0, /*!< 0, cbr stable br adjust */
	H264_CBR_STABLE_BR_ADJUST_MAX	= 10, /*!< 10 */
	/* ZMV threshold parameters */
	H264_ZMV_THRESHOLD_QP_OFFSET_MIN	= -51, /*!< -51 */
	H264_ZMV_THRESHOLD_QP_OFFSET_MAX	= 51, /*!< 51 */
	/* chroma qp offset parameters */
	H264_CHROMA_QP_OFFSET_MIN = -12, /*!< -12 */
	H264_CHROMA_QP_OFFSET_MAX = 12, /*!< 12 */
	/* one frame qp offset parameters */
	H264_ONE_FRM_QP_OFFSET_MIN = -51, /*!< -51 */
	H264_ONE_FRM_QP_OFFSET_MAX = 51, /*!< 51 */
};

enum {
	/* bitrate control */
	IAV_BRC_CBR	= 1, /*!< 1. It's OBSOLETE. */
	IAV_BRC_PCBR	= 2, /*!< 2. It's OBSOLETE. */
	IAV_BRC_VBR	= 3, /*!< 3. It's OBSOLETE. */
	IAV_BRC_SCBR	= 4, /*!< 4, smart CBR */
	IAV_BRC_SVBR	= 5, /*!< 5. It's OBSOLETE. */
};

enum {
	WP_FOR_NONE = 0, /*!< 0 */
	WP_FOR_P = 1, /*!< 1 */
	WP_FOR_B = 2, /*!< 2 */
	WP_FOR_PB = 3, /*!< 3 */
	WP_MODE_NUM, /*!< 4 */
	WP_MODE_FIRST = WP_FOR_NONE, /*!< WP_FOR_NONE */
	WP_MODE_LAST = WP_MODE_NUM, /*!< WP_MODE_NUM */
};

#define MAX_NUM_OVERLAY_AREA	(16)
#define MAX_NUM_FAST_OVERLAY_AREA      (2)
#define MAX_NUM_BLUR_AREA		(16)
#define MAX_NUM_BLUR_COLOR		(16)
#define MIN_BLUR_STRENGTH		(0)
#define MAX_BLUR_STRENGTH		(2)
#define OVERLAY_WIN_ALIGN		(4)
#define OVERLAY_WIDTH_ALIGN		(4)
#define OVERLAY_HEIGHT_ALIGN		(2)
#define OVERLAY_OFFSET_ALIGN		(2)
#define MIN_BLUR_WIDTH			(8)
#define BLUR_WIDTH_ALIGN		(4)
#define BLUR_HEIGHT_ALIGN		(2)
#define BLUR_OFFSET_ALIGN		(2)
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_overlay_area {
	u16 enable : 1;	/*!< 0:  Disable; 1:  Enable */
	u16 reserved1 : 15;
	u16 start_x;	/*!< Offset x of the overlay area */
	u16 start_y;	/*!< Offset y of the overlay area */
	u16 width;	/*!< Width of the overlay area */
	u16 pitch;	/*!< Pitch of the overlay area */
	u16 height;	/*!< Height of the overlay area */
	u32 total_size;	/*!< Total byte size of the overlay area */
	unsigned long clut_addr_offset; /*!< CLUT address for the overlay area */
	unsigned long data_addr_offset; /*!< Overlay data buffer (without CLUT) */
};

struct iav_overlay_insert {
	u32 id;		/*!< Stream ID */
	u32 enable: 1;	/*!< Flag to enable / disable overlay insertion */
	u32 osd_insert_always: 1; /*!< Flag to insert overlay all the time no matter the encoding of next frame is started or not. */
	u32 osd_num_regions : 5 ; /*!< osd num region */
	u32 reserved : 25; /*!< reserved */
	struct iav_overlay_area area[MAX_NUM_OVERLAY_AREA]; /*!< Parameters for each overlay area */
};

struct iav_blur_area {
	u32 enable : 1;	/*!< 0:  Disable; 1:  Enable */
	u32 color_idx : 4; /*!< Blur color index of the colors specified through IAV_IOC_SET_BLUR_COLOR */
	u32 strength : 3; /*!< Blur strength, the larger the more heavily blurred */
	u32 use_arb_blur : 1;/*!< Use user customized blur data which is specified through arb_blur_offset */
	u32 reserved1 : 23;
	u16 start_x;	/*!< Offset x of the blur area */
	u16 start_y;	/*!< Offset y of the blur area */
	u16 width;	/*!< Width of the blur area */
	u16 height;	/*!< Height of the blur area */
	u16 arb_blur_pitch;	/*!< Arbitrary blur data pitch. Used only when use_arb_blur is enabled */
	u16 reserved2;
	u32 arb_blur_offset; /*!< Arbitrary blur data offset. Used only when use_arb_blur is enabled */
};

struct iav_blur_insert {
	u32 stream_id : 8;	/*!< Stream ID */
	u32 enable : 1;		/*!< Flag to enable/disable blur insertion */
	u32 insert_always : 1;	/*!< Flag to insert blur all the time no matter the encoding of next frame is started or not. */
	u32 blur_num_regions : 5 ; /*!< blur num regions */
	u32 reserved : 17;
	struct iav_blur_area area[MAX_NUM_BLUR_AREA];	/*!< Parameters for each blur area */
};

struct iav_zmv_threshold_info {
	u8 enable;	/*!< Flag to enable ZMV threshold info */
	s8 qp_offset; /*!< QP offset for zero motion vector MB, valid range is [-51, 51] */
	u8 reserved[2];
};

struct iav_stream_cfg {
	u32 id; /*!< Stream ID */
	enum iav_streamcfg_id cid; /*!< Stream configured ID, @sa iav_streamcfg_id */
	union {
		struct iav_stream_format format;	/*!< Stream format @sa iav_stream_format */
		struct iav_stream_fps fps;			/*!< Stream fps @sa iav_stream_fps */
		struct iav_offset enc_offset;		/*!< Stream offset on canvas */
		enum iav_chroma_format chroma;	/*!< Stream chroma format @sa iav_chroma_format */
		u32 stream_dummy_latency;		/*!< Stream dummy latency. It's used by stream sync mechanism. */
		u32 mv_threshold;				/*!< MV threshold for bitrate control */
		struct iav_custom_sei custom_sei;	/*!< Customer SEI information. It's used by frame sync mechanism for application
										  to synchronize the customized information with the speicfied frame content. */
		struct iav_overlay_insert overlay;	/*!< overlay information. It's used by frame sync mechanism for application
										  to synchronize overlay with the speicfied frame content. */
		struct iav_stream_flip flip;		/*< Stream flip information. */
		struct iav_blur_insert blur;	/*!< blur information. It's used by frame sync mechanism for application
										  to synchronize blur with the speicfied frame content. */
		struct iav_trigger_frame trigger_frame;	/*!< Specify the trigger frame number to encode */

		struct iav_h26x_gop h264_gop;
		struct iav_bitrate h264_rc;
		struct iav_rc_strategy h264_rc_strategy;
		struct iav_qpmatrix h264_roi;
		struct iav_h26x_enc_param h264_enc;
		struct iav_h26x_slice h264_slice;
		struct iav_h26x_pskip h264_pskip;
		struct iav_h26x_drop_frame h264_drop_frame;
		int h264_force_idr;		/*!< Flag for force IDR */
		u32 h264_force_fast_seek;	/*!< Flag for force fast seek frame insertion */
		u32 h264_fast_seek_interval;	/*!< Flag for fast seek interval */
		u32 h264_statis;		/*!< H.264 MV dump flag */
		u32 h264_skip_strength;		/*!< Skip strength only works for HEVC. */
		int h264_chroma_qp_offset;	/*!< Set H.264 chroma qp offset */
		int h264_one_frm_qp_offset;	/*!< Set H.264 one frame qp offset */
		struct iav_h26x_sar h264_sar;	/*!< Customized H.264 stream aspect ratio */
		struct iav_h26x_weighted_pred h264_wp;
		struct iav_zmv_threshold_info h264_zmv_threshold;		/*!< Zero motion vector threshold info */

		u32 mjpeg_quality;		/*!< Quality value for MJPEG stream */
		struct iav_mjpeg_drop_frame mjpeg_drop_frame;	/*!< Frame drop for mjpeg */

		/* H265 shares same structure with H264 */
		struct iav_h26x_gop h265_gop;
		struct iav_bitrate h265_rc;
		struct iav_rc_strategy h265_rc_strategy;
		struct iav_qpmatrix h265_roi;
		struct iav_h26x_enc_param h265_enc;
		struct iav_h26x_slice h265_slice;
		struct iav_h26x_pskip h265_pskip;
		struct iav_h26x_drop_frame h265_drop_frame;
		struct iav_h26x_cu_split h265_cu_split;
		int h265_force_idr;		/*!< Flag for force IDR */
		u32 h265_force_fast_seek;	/*!< Flag for force fast seek frame insertion */
		u32 h265_fast_seek_interval;	/*!< Flag for fast seek interval */
		u32 h265_skip_strength;		/*!< Skip strength to control frame size */
		u8  h265_md_cat_lut[MD_CAT_MAX_NUM]; /*!< H.265 MD category mapping look up table */
		int h265_chroma_qp_offset;	/*!< Set H.265 chroma qp offset */
		int h265_one_frm_qp_offset;	/*!< Set H.265 one frame qp offset */
		struct iav_h26x_sar h265_sar;	/*!< Customized H.265 stream aspect ratio */
		struct iav_h26x_weighted_pred h265_wp;
	} arg; /*!< The stream configuration items */
	u32 dsp_pts; /*!< The DSP PTS for the stream configurations */
	u32 strm_sync_type : 3; /*!< Select frame sync, stream sync or idsp-enc sync */
	u32 manual_arm_pts_enable : 1; /*!< Manual arm_pts enable */
	u32 reserved : 28;
};

struct iav_pic_info {
	u32	rate;
	u32	scale;
	u16	width;
	u16	height;
};

struct iav_h26x_cfg {
	u32 id;			/*!< Stream ID */
	u32 gop_structure : 8;	/*!< @sa iav_gop_model */
	u32 M : 8;		/*!< Number of pictures between reference P pictures */
	u32 N : 16;		/*!< Number of pictures between reference I pictures, should be no larger than 4095 */
	u32 idr_interval : 8;	/*!< Indicate the number of GOP's after which an IDR picture should happen */
	u32 profile : 8;	/*!< This field specifies the profile level. The default is the main profile for stream configuration.
				     1:  Main profile. 2:  High profile. */
	u32 au_type : 8;	/*!< This field specifies the NAL unit structure (@ref iav_h264_au_type).
				     0:  No AUD, no SEI header info
				     1:  Add AUD before SPS, PPS, with SEI in the end
				     2:  Add AUD after SPS, PPS, with SEI in the end
				     3:  IDR: AUD -> SPS -> BPSEI & PTSEI, P: AUD -> SPS & PPS -> PTSEI
				     4:  no AUD, SPS/PPS -> SEI */
	u32 chroma_format : 8;	/*!< Chroma format */
	u32 cpb_buf_idc : 8;	/*!< CPB buffer size indicator. 0 indicates using a buffer size that
						matches the profile and level which are based on the encoding size. */
	u32 is_update_N_to_next_GOP : 1;	/*!< Flag to update GOP length to next GOP */
	u32 scalelist_opt : 2;	/*!< scalelist option, 0: No scaling list,
					1: default scaling list in default_binary, 2: custom scaling list */
	int chroma_qp_offset : 5;	/*!< Chroma qp offset, range from -12 to 12 */
	int one_frm_qp_offset : 8;	/*!< QP offset on specific frames, range from -51 to 51 */
	u32 qp_smooth_enable : 1; /*!< QP smooth enable on specific frames*/
	u32 reserved0 : 7;
	u32 cpb_user_size;	/*!< This field specifies the CPB buffer size */
	u32 en_panic_rc : 2;	/*!< Flag for panic mode of RC */
	u32 cpb_cmp_idc : 2;	/*!< Flag for CPB settings */
	u32 fast_rc_idc : 4;	/*!< Flag for fast RC mode */
	u32 mv_threshold : 1;	 /*!< Motion vector threshold */
	u32 long_start_code : 1;/*!< Flag for long start code */
	u32 dblk_custom_flag : 1; /*!< Flag for dblk */
	u32 two_ltrs_mode : 1;	/*!< 0: two long term + fast seek; 1: two long term + prev prev q */
	u32 ltrs_type: 2;	/*!< Type of long term references. Default is 0.
				     0: No long term ref frame
				     1: 1 long term ref frame
				     2: 2 long term ref frames. */
	u32 zmv_enable_flag : 1;	 /*!< Flag to enable/disable ZMV feature */
	u32 two_str : 1;	/*!< 0: one long term + one short term; 1: two short term. Only valid when GOP is IAV_GOP_2_REF. */
	u32 log2_num_ltrp_per_gop : 8;	/*!< Number of long-term reference picture in a GoP */
	u32 fast_seek_intvl : 8;	/*!< The fast seek interval for long term frames */
	u16 user1_intra_bias;	/*!< The intra bias for user class 1, range from 0 to 9 */
	u16 user1_direct_bias;	/*!< The direct bias for user class 1, range from 0 to 9 */
	u16 user2_intra_bias;	/*!< The intra bias for user class 2, range from 0 to 9 */
	u16 user2_direct_bias;	/*!< The direct bias for user class 2, range from 0 to 9 */
	s32 deblocking_filter_alpha : 4; /*!< The deblocking filter range is -6 to 6 */
	s32 deblocking_filter_beta : 4;	 /*!< The deblocking filter range is -6 to 6 */
	u32 deblocking_filter_enable : 2;/*!< Flag for deblocking filter */
	u32 aqp_type : 2;	/*!< AQP type for frame size decision, @sa iav_h264_aqp_type:
				     0:  Default option
				     1:  Frame QP for frame size decision
				     2:  MB QP for frame size decision	*/
	u32 wp_mode : 2;	/*!< Weighted predict mode :
				     0:  Disable WP,
				     1:  WP for P frame,
				     2:  WP for B frame,
				     3:  WP for P&B frame */
	u32 svc_extension_enable : 1;	/*!< Flag to enable/disable svc extension feature, only for SVCT 2/3/4. */
	u32 reserved1 : 9;
	int zmv_threshold_qp_offset : 8;	/*!< QP offset for ZMV, it's only valid when "zmv_enable_flag" is set */

	struct iav_pic_info pic_info;	/*!< Picture information for decoding (rate / scale) */
};

struct iav_mjpeg_cfg {
	u32 id;			/*!< Stream ID */
	u32 chroma_format : 8;	/*!< Chroma format, @sa iav_chroma_format */
	u32 quality : 8;	/*!< 1 ~ 100, 100 is best quality. The bigger quality value,
					the larger frame size it is (especially for high mega resolution). */
	u32 slice_num : 5;	/*!< Slice number for MJPEG multi-slice encoding. */
	u32 reserved1 : 11;
	u32 restart_interval;	/*!< restart interval MB for mjpeg. 0 : handle in ucode. >0 : user specified. */
};

struct iav_fastosd_string_area {
	u8 enable;	 /*!< Enable flag */
	u8 string_length;/*!< String length */
	u16 string_output_pitch; /*!< Pitch of string output */
	u16 offset_x;	 /*!< X offset */
	u16 offset_y;	 /*!< Y offset */
	/* if each char's width is const,
	 * overall_string_width = num_of_char_in_string * width_of_char_font
	 */
	u32 overall_string_width; /*!< Total width, if each char's width is const,
				       overall_string_width = num_of_char_in_string * width_of_char_font */
	u32 reserved;

	unsigned long string_output_offset; /*!< Memory to store the output overlay string content, which is generated by DSP. */
	unsigned long string_offset; /*!< DSP OVERLAY STRING START */
	unsigned long clut_offset;   /*!< Memory for overlay CLUT content. */
};

struct iav_fastosd_insert {
	u8 stream_id;		/*!< Stream ID */
	u8 enable;		/*!< Enable flag */
	u8 string_num;		/*!< Total FastOSD number */
	u8 logo_num;		/*!< Total logo number */

	u16 font_map_pitch;	/*!< Font map pitch */
	u16 font_map_height;	/*!< Font map height */
	unsigned long font_map_offset;   /*!< Font map offset */
	unsigned long font_index_offset; /*!< Font index offset */

	struct iav_fastosd_string_area string_area[MAX_NUM_OVERLAY_AREA]; /*!< Parameters for each FastOSD string area */
	struct iav_overlay_area logo_area[MAX_NUM_FAST_OVERLAY_AREA]; /*!< Parameters for each FastOSD logo area */
};

struct iav_blur_color {
	u32 color_idx_map; /*!< the idx map of configured blur colors */
	u8 U[MAX_NUM_BLUR_COLOR]; /*!< chroma U value */
	u8 V[MAX_NUM_BLUR_COLOR]; /*!< chroma V value */
	u8 opaque[MAX_NUM_BLUR_COLOR]; /*!< Flag to enable / disable opaque. If enabled, blur area won't blend with background. */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_warp_params {
	MAX_NUM_WARP_AREAS		= 12, /*!< 12, Maximum warp area number from DSP point of view. */
	MAX_NUM_WARP_VIEW		= 12, /*!< 12, Maximum warp view number from user point of view. */

	MAX_GRID_WIDTH			= 128, /*!< 128, Maximum grid width (column) for warp vector table. */
	MAX_GRID_HEIGHT			= 96,  /*!< 96, Maximum grid height (row) for warp vector table. */
	MAX_WARP_TABLE_SIZE		= (MAX_GRID_WIDTH * MAX_GRID_HEIGHT), /*!< MAX_GRID_WIDTH * MAX_GRID_HEIGHT */
	MAX_WARP_VECT_PART_SIZE = (MAX_NUM_WARP_AREAS * \
		MAX_WARP_TABLE_SIZE * sizeof(s16) * 2),   /*!< MAX_NUM_WARP_AREAS * MAX_WARP_TABLE_SIZE * sizeof(s16) * 2 */
	MAX_GRID_WIDTH_LDC		= MAX_GRID_WIDTH, /*!< MAX_GRID_WIDTH */
	MAX_WARP_TABLE_SIZE_LDC	= (MAX_GRID_WIDTH_LDC * MAX_GRID_HEIGHT), /*!< MAX_GRID_WIDTH_LDC * MAX_GRID_HEIGHT */
	MAX_ME1_WARP_TABLE_SIZE_LDC = MAX_WARP_TABLE_SIZE_LDC / 16, /*!< (MAX_GRID_WIDTH_LDC/4) * (MAX_GRID_HEIGHT/4) */
	MAX_MD_WARP_TABLE_SIZE_LDC = MAX_WARP_TABLE_SIZE_LDC / 256, /*!< (MAX_GRID_WIDTH_LDC/16) * (MAX_GRID_HEIGHT/16) */

	GRID_SPACING_PIXEL_8	= 0, /*!< 0 */
	GRID_SPACING_PIXEL_16	= 1, /*!< 1 */
	GRID_SPACING_PIXEL_32	= 2, /*!< 2 */
	GRID_SPACING_PIXEL_64	= 3, /*!< 3 */
	GRID_SPACING_PIXEL_128	= 4, /*!< 4 */
	GRID_SPACING_PIXEL_256	= 5, /*!< 5 */
	GRID_SPACING_PIXEL_512	= 6, /*!< 6 */

	WARP_AREA_H_OFFSET		= 0, /*!< 0 */
	WARP_AREA_V_OFFSET		= 1, /*!< 1 */
	WARP_AREA_VECTOR_NUM		= 2, /*!< 2 */

	WARP_AREA_CHANGE			= 0, /*!< 0, This is to change the selected warp area configuration on the fly. */
	WARP_AREA_UPDATE			= 1, /*!< 1, This is to update all warp areas configuration at the same time. */
	WARP_AREA_CLEAR			= 2, /*!< 2, This is to clear warp for all warp regions. */

	WARP_PIPELINE_VH                = 0, /*!< 0, Pipeline type: V + H. */
	WARP_PIPELINE_HV                = 1, /*!< 1, Pipeline type: H + V. */

#if defined(CONFIG_ARCH_S6LM)
	MAX_WARP_AREA_WIDTH_NON_STITCH = 1504,
#elif defined(CONFIG_ARCH_CV28)
	MAX_WARP_AREA_WIDTH_NON_STITCH = 1088,
#else
	MAX_WARP_AREA_WIDTH_NON_STITCH = 2048,
#endif
	MIN_WARP_AREA_WIDTH = 112,
};

enum lens_warp_reso_type {
	LENS_WARP_RES_TYPE_MAIN = 0,	/*!< 0, Load horizontal warp + vertical warp for main buffer. */
	LENS_WARP_RES_TYPE_MAIN_MONO = LENS_WARP_RES_TYPE_MAIN,	/*!< 0, Load align/ldc horizontal warp + align vertical warp FOR MONO channel. */
	LENS_WARP_RES_TYPE_ME1 = 1,	/*!< 1, Load ME1 vetical warp vector.  Should be disabled in fusion mode*/
	LENS_WARP_RES_TYPE_MAIN_RGB = 2,	/*!< 2, Load RGB horizontal warp + fusion/RGB vertical warp in fusion mode. */
	LENS_WARP_RES_TYPE_MD_BC = 3,	/*!< 3, Load MD_BC vetical warp vector in fusion mode. */
	LENS_WARP_RES_TYPE_NUM = 4,
	LENS_WARP_RES_TYPE_FIRST = LENS_WARP_RES_TYPE_MAIN,	/*!< LENS_WARP_RES_TYPE_MAIN */
	LENS_WARP_RES_TYPE_LAST = LENS_WARP_RES_TYPE_NUM,	/*!< LENS_WARP_RES_TYPE_NUM */
};

enum iav_warp_uncorrected_buf_id {
	IAV_WARP_PRE_MAIN_BUF = 0,	/*!< 0, Premain buffer */
	IAV_WARP_PRE_2ND_BUF,	/*!< 1, Second buffer from uncorrected pass. */
	IAV_WARP_PRE_3RD_BUF,	/*!< 2, Third buffer from uncorrected pass. */
	IAV_WARP_PRE_4TH_BUF,	/*!< 3, Fourth buffer from uncorrected pass. */
	IAV_WARP_PRE_BUF_NUM,
};

/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_warp_map {
	u8 enable;		/*!< Flag to enable / disable warp vector table. */
	u8 output_grid_col;	/*!< Grid columns */
	u8 output_grid_row;	/*!< Grid rows */
	u8 h_spacing : 4;	/*!< H-spacing */
	u8 v_spacing : 4;	/*!< V-spacing */
	u32 reserved;
	unsigned long data_addr_offset; /*!< Warp table DRAM offset */
};

struct iav_warp_area {
	u8 enable;	/*!< Area enable flag */
	u8 rotate_flip;	/*!< rotate and flip flag */
	u8 warp_pipeline_type : 1;	/*!< pipeline type: 1: H + V; 0: V + H*/
	u8 is_out_h_16_aligned : 1; /*!< align warp region height to 16 pixels as encoding requirement*/
	u8 lens_warp_res_type : 2; /*!< Specify lens warp resolution for different kinds of warp control.
		0 (@ref LENS_WARP_RES_TYPE_MAIN_MONO and @ref LENS_WARP_RES_TYPE_MAIN)
		1 (@ref LENS_WARP_RES_TYPE_ME1)
		2 (@ref LENS_WARP_RES_TYPE_MAIN_RGB)
		3 (@ref LENS_WARP_RES_TYPE_MD_BC)*/
	u8 uncorrected_buf_id : 2; /*! Specify the buffer id from uncorrected pass
		0 @ref IAV_WARP_PRE_MAIN_BUF by default
		1 @ref IAV_WARP_PRE_2ND_BUF
		2 @ref IAV_WARP_PRE_3RD_BUF
		3 @ref IAV_WARP_PRE_4TH_BUF*/
	u8 reserved1 : 2;
	u8 reserved2;
	struct iav_rect input;		/*!< Warp area input window */
	struct iav_rect output;		/*!< Warp area output window */
	struct iav_warp_map h_map;	/*!< h-warp map */
	struct iav_warp_map v_map;	/*!< v-warp map */
};

struct iav_warp_main {
	u8 keep_dptz[IAV_SRCBUF_NUM]; /*!< Keep DPTZ attribute for each source buffer output */
	u8 reserved;
	struct iav_warp_area area[MAX_NUM_WARP_AREAS]; /*!< Warp area configuration */
	u8 area_num_per_view[MAX_NUM_WARP_VIEW]; /*!< Specify the number of warp areas for each warp view. */
};

struct iav_warp_dptz {
	u16 buf_id;		/*!< Source buffer ID */
	u16 area_map;	/*!< The bit map of areas to be changed in warp dptz. */
	struct iav_rect input[MAX_NUM_WARP_AREAS];	/*!< Input window of each updated area. */
	struct iav_rect output[MAX_NUM_WARP_AREAS];	/*!< Output window of each updated area. */
};

struct iav_pyramid_roi {
	u32 chan_id : 8;	/*!< Channel ID */
	u32 layers_map : 6;	/*!< Pyramid layer bit map */
	u32 reserved0 : 18;
	struct iav_rect crop_win[IAV_MAX_PYRAMID_LAYERS]; /*!< crop window */
	struct iav_window rescale_size;	/*!< Rescale size for pyramid layer 1. The scale ratio of width or height
			from layer_0 to layer_1 must be in the range of <b>(1/8, 1](Downscale)</b>. The scale ratio from
			layer_N(N = 1 ~ 4) to layer_N+1 is fixed to 2X (Downscale). Only valid when
			<b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>. */
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper */
enum iav_warp_ctrl_id {
	IAV_WARP_CTRL_MAIN		= 0, /*!< 0, This is to configure multi-region warp area parameters for post main. */
	IAV_WARP_CTRL_DPTZ		= 1, /*!< 1, This is to configure multi-region warp DPTZ from post main to sub source buffers. */
	IAV_WARP_CTRL_ENCOFS		= 2, /*!< 2, This is to configure stream encode offset synchronized with warp DPTZ effect. */
	IAV_WARP_CTRL_NUM		= 3, /*!< 3 */
	IAV_WARP_CTRL_FIRST		= IAV_WARP_CTRL_MAIN, /*!< IAV_WARP_CTRL_MAIN */
	IAV_WARP_CTRL_LAST		= IAV_WARP_CTRL_NUM,  /*!< IAV_WARP_CTRL_NUM */
};

/*! @addtogroup iav-ioctl-general-struct */
struct iav_warp_ctrl {
	enum iav_warp_ctrl_id cid;	/*!< Config class ID, @sa iav_warp_ctrl_id */
	u16 channel_id;			/*!< Channel ID */
	u16 warp_area_behavior : 2;	/*!< Specify warp area behavior.
		0 (@ref WARP_AREA_CHANGE), is to change the selected warp area configuration on the fly.
		1 (@ref WARP_AREA_UPDATE). is to update all warp areas configuration at the same time.
		2 (@ref WARP_AREA_CLEAR), is to clear all warp areas configuration at the same time. */

	u16 reserved : 14;
	union {
		struct iav_warp_main main;
		struct iav_warp_dptz dptz;
	} arg;				/*!< Warp configuration */
};

/*! @addtogroup iav-ioctl-general-helper */
enum iav_video_proc_id {
	IAV_VIDEO_PROC_DPTZ			= 0x00, /*!< 0x00, This is to configure DPTZ parameters on the fly. */
	IAV_VIDEO_PROC_MASK			= 0x01, /*!< 0x01, This is to configure single color privacy mask on the fly. */
	IAV_VIDEO_PROC_CANVAS_ORDER	= 0x02, /*!< 0x02, This is to configure channel order in one canvas on the fly. */
	IAV_VIDEO_PROC_MULTI_BLEND	= 0x03, /*!< 0x03, This is to configure multi-channel blend overlap area parameters on the fly. */
	IAV_VIDEO_PROC_BLEND_DPTZ	= 0x04, /*!< 0x04, This is to configure multi-channel blend DPTZ parameters on the fly. */
	IAV_VIDEO_PROC_PYRAMID_ROI	= 0x05, /*!< 0x05, This is to configure pyramid ROI parameters on the fly. */
	IAV_VIDEO_PROC_CANVAS_FPS	= 0x06, /*!< 0x06, This is to configure canvas frame rate on the fly. */
	IAV_VIDEO_PROC_WARP			= 0x07, /*!< 0x07, This is to configure warp cfg on the fly. */
	IAV_VIDEO_PROC_MULTI_COLOR_MASK	= 0x08, /*!< 0x08, This is to configure multi color privacy mask on the fly. */
	IAV_VIDEO_PROC_VSRC_REGION	= 0x09, /*!< 0x09, This is to configure vsrc region idx on the fly. Only for DOL HDR. */
	IAV_VIDEO_PROC_VCAP_FLUSH	= 0x0A, /*!< 0x0A, This is to trigger all frames flushed out from IDSP. */
	IAV_VIDEO_PROC_CANVAS_DPTZ	= 0x0B, /*!< 0x0B, This is to configure canvas DPTZ parameters on the fly.
										It is only for cross-chan stitching without blending on overlapped areas. */
	IAV_VIDEO_PROC_NUM			= 0x0C, /*!< 0x0C */
	IAV_VIDEO_PROC_FIRST			= IAV_VIDEO_PROC_DPTZ, /*!< IAV_VIDEO_PROC_DPTZ */
	IAV_VIDEO_PROC_LAST			= IAV_VIDEO_PROC_NUM   /*!< IAV_VIDEO_PROC_NUM */
};

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_privacy_mask {
	u8 channel_id;	/*!< Channel ID */
	u8 enable;	/*!< 0: disable, 1: enable */
	u8 y;		/*!< y of the mask color, only used for single color mask. */
	u8 u;		/*!< u of the mask color, only used for single color mask. */
	u8 v;		/*!< v of the mask color, only used for single color mask. */
	u8 reserved0;
	u16 buf_pitch;	/*!< Buffer pitch. For single color mask: it is aligned to 32 bytes(in byte unit). The unit depends on the privacy mask type.
						For multi color mask : it is downscaled from VIN's width. */
	u16 buf_height;	/*!< Buffer height. For single color mask: it is in pixel unit and equal to main buffer height.
						For multi color mask : it is downscaled from VIN's height. */
	u16 reserved1[3];
	unsigned long data_addr_offset; /*!< Start address of privacy mask data */
};

struct iav_mask_color {
	u8 V; /*!< chroma V value, used for multi color mask. */
	u8 U; /*!< chroma U value, used for multi color mask. */
	u8 Y; /*!< chroma Y value, used for multi color mask. */
	u8 alpha; /*!< chroma alpha value, used for multi color mask. */
};

struct iav_overlap_area {
	u16 width;	/*!< Width of blend overlap area. */
	u16 height;	/*!< Height of blend overlap area. */
	u16 pitch;	/*!< Pitch of blend overlap area. It must be alighed to 64 bytes. */
	u16 update_alpha_enable : 1; /*!< This is a flag to enable / disable updating alpha table. */
	u16 reserved0 : 15;
	u8 chan_id[IAV_BLEND_NUM]; /*!< Channel ID of overlapped areas */
	u16 reserved1;
	unsigned long alpha_addr_offset[IAV_BLEND_NUM]; /*!< Offset of Alpha table memory */
};

struct iav_blend_overlap {
	u8 active_overlap_num;	/*!< Active blend overlap number. @sa IAV_BLEND_OVERLAP_AREA_MAX */
	u8 reserved[3];
	struct iav_overlap_area mc_overlap[IAV_BLEND_OVERLAP_AREA_MAX]; /*!< Overlap area configuration */
};

struct iav_blend_dptz_info {
	u32 enable : 1;	/*!< Blend DPTZ enable flag */
	u32 reserved : 31;
	struct iav_rect input;	/*!< Blend DPTZ input window */
	struct iav_rect output;	/*!< Blend DPTZ output window */
};

struct iav_blend_dptz {
	struct iav_blend_dptz_info dptz[IAV_SRCBUF_NUM]; /*!< Blend DPTZ configuration */
};

struct iav_vsrc_region {
	u8 channel_id;	/*!< Channel ID */
	u8 map; /*!< The region index map for current channel. Only for DOL HDR. */
	u8 reserved[2];
};

struct iav_vcap_flush     {
	u8 channel_id;	/*!< Channel ID */
	u8 reserved[3];
};

struct iav_canvas_dptz {
	u8 id;	/*!< Output Canvas ID. Must be sub-source buffer canvas. */
	u8 reserved[3];
	struct iav_rect input;	/*!< Canvas DPTZ input window from main buffer canvas. */
	struct iav_rect output;	/*!< Canvas DPTZ output window. */
};

struct iav_video_proc {
	enum iav_video_proc_id cid; /*!< Configuration item ID, @sa iav_video_proc_id */
	union {
		struct iav_dptz dptz;
		struct iav_privacy_mask mask;
		struct iav_canvas_order canvas_order;
		struct iav_blend_overlap blend_overlap;
		struct iav_blend_dptz blend_dptz;
		struct iav_pyramid_roi pyramid_roi;
		struct iav_canvas_fps canvas_fps;
		struct iav_vsrc_region vsrc_region;
		struct iav_vcap_flush vcap_flush;
		struct iav_canvas_dptz canvas_dptz;
	} arg; /*!< Configuration items */
};

struct iav_apply_flag {
	int apply;
	u32 param;
};

struct  iav_apply_frame_sync_flag {
	int apply;	/*!< apply control id. */
	u32 param;	/*!< apply parameters */
	u32 hw_pts[IAV_MAX_CHANNEL_NUM];	/*!< hw_pts for frame sync control with IDSP. */
};

struct iav_efm_get_pool_info {
	u32 stream_id;			/*!< EFM stream id*/
	u32 yuv_buf_num;	/*!< EFM YUV buffer number */
	u32 yuv_pitch;		/*!< YUV pitch */
	u32 me_buf_num;		/*!< EFM ME buffer number */
	u32 me1_pitch;		/*!< ME1 pitch */
	u32 me0_pitch;		/*!< ME0 pitch */
	struct iav_window yuv_size; /*!< YUV size */
	struct iav_window me1_size; /*!< ME1 size */
	struct iav_window me0_size; /*!< ME0 size */
	u32 chroma_format;	/*!< Chroma_format: 0: Mono; 1: YUV420; 2: YUV422; 3: YUV444. */
};

struct iav_efm_release_all_frame {
	u8 stream_id;		/*!< Release frames stream id */
	u8 no_prefetch_flag;	/*!< Flag for enable frame buffer pool no prefetch option */
	u16 reserved;
};

struct iav_efm_request_frame {
	u32 stream_id;	/*!< EFM stream id*/
	u16 frame_idx;	/*!< EFM frame index */
	u16 use_dma_buf_fd : 1; /*!< When set, dma-buf:fd will be used to describe YUV and ME data.
							NOTE: YUV and ME data have their own dma-buf:fd. */
	u16 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u16 reserved : 14;
	unsigned long yuv_luma_offset;	/*!< YUV Luma data offset */
	unsigned long yuv_chroma_offset;/*!< YUV Chromatic data offset */
	unsigned long me1_offset;	/*!< ME1 data offset */
	unsigned long me0_offset;	/*!< ME0 data offset */
	int yuv_dma_buf_fd;	/* dma-buf:fd for YUV data */
	int me_dma_buf_fd;	/* dma-buf:fd for ME data */
};

struct iav_efm_handshake_frame {
	u32 stream_id;	/*!< EFM stream ID */
	u32 frame_idx;	/*!< EFM frame index */
	u32 frame_pts;	/*!< EFM frame PTS in LSB u32. frame_pts_u64 = (frame_pts_msb << 32) | frame_pts */
	u8 is_last_frame; /*!< Flag for last_frame */
	u8 use_hw_pts;	/*!< HW PTS, only apply to real time's case */
	u8 skip_cache_sync : 1;	/*!< The buffer cache will not be synced if this flag is enabled. */
	u8 hold_frame : 1; /*!< The EFM frame will hold current frame after being fed to DSP. */
	u8 use_stream_map : 1; /*!< Enable using stream map for multiple stream. */
	u8 mjpeg_slice_idx : 5;	/*!< Slice index for MJPEG multi-slice encoding. */
	u8 reserved;
	u32 stream_map; /*!< The bits map of mutiple encoding streams. */
	u32 frame_pts_msb;	/*!< EFM frame PTS in MSB u32. frame_pts_u64 = (frame_pts_msb << 32) | frame_pts */
};

struct iav_custom_sei_request_buf {
	u32 frame_idx;	/*!< customized SEI buffer frame index */
	u32 offset;		/*!< customized SEI buffer offset */
	u32 size;		/*!< customized SEI buffer size */
	u32 use_dma_buf_fd : 1; /*!< When set, dma-buf:fd will be used to describe SEI buffer. */
	u32 reserved1 : 31;
	int dma_buf_fd;
	u32 reserved;
};

struct iav_js_frame {
	unsigned long luma_addr;	/*!< YUV luma addr */
	unsigned long chroma_addr;	/*!< YUV chroma addr */
	u32 pitch;		/*!< YUV pitch */
	u32 width;		/*!< YUV width */
	u32 height;		/*!< YUV height */
	u32 start_x;	/*!< encode start_x */
	u32 start_y;	/*!< encode start_y */
	u32 enc_w;		/*!< encode width */
	u32 enc_h;		/*!< encode height */

	u32 yuv_format : 2;	/*!< see @iav_yuv_format */
	u32 hflip : 1;		/*!< enable / disable hflip for JPEG service encoding */
	u32 vflip : 1;		/*!< enable / disable vflip for JPEG service encoding */
	u32 rotate : 1;		/*!< enable / disable rotate for JPEG service encoding */
	u32 reserved0 : 27;

	u32 js_frame_uuid;	/*!< Unique user's JPEG service frame id, read only */
};

struct iav_raw_enc_setup {
	u32 vinc_id;		/*!< VIN Control ID */
	u32 raw_frame_size;	/*!< RAW data size */
	u32 raw_hdec_size;	/*!< HDEC data size */
	u32 preblend_size;	/*!< Preblend data size */
	u32 pitch : 16;		/*!< RAW data pitch */
	u32 raw_hdec_dpitch : 16; /*!< HDEC data pitch */
	u32 preblend_dpitch : 16; /*!< Pre-blend data pitch */
	u32 raw_frame_num : 8;	/*!< RAW frame number */
	u32 use_ext_buf : 1;	/*!< External buf used for raw enc */
	u32 raw_format : 2;	/*!< RGB RAW format */
	u32 hdec_raw_format : 2;	/*!< RGB HDEC RAW (CE) format */
	u32 reserved : 3;
	u32 frame_pts;		/*!< Frame Software PTS in 90KHz */
	u32 frame_hw_pts;	/*!< Frame Hardware PTS in 12.288MHz */
	unsigned long raw_daddr_offset;	/*!< RAW data DRAM offset */
	unsigned long raw_hdec_daddr_offset; /*!< HDEC data DRAM offset */
	unsigned long preblend_daddr_offset; /*!< Pre-blend data DRAM offset */
	unsigned long ext_buf_addr;	 /*!< External buf start address used for raw enc */
	unsigned long uv_daddr_offset;	/*!< UV data DRAM offset. Only for YUV422/YUV420 EFR.
		1. When doing YUV422/YUV420 EFR, it is highly suggested to put Y and UV buffer together(UV right after Y).
		If so, uv_daddr_offset can be set as 0.
		2. To support feeding canvas buffer reported from one channel into DSP as EFR channel again, users need
		to specify the DRAM address of its UV buffer explicitly as there are fixed padding between Y and UV buffer. */
};

struct iav_wait_raw_enc {
	u32 vinc_map;	/*!< VIN bit map for EFR */
	u32 reserved[3];
};

struct iav_apply_frame_sync {
	u32 dsp_pts;			/*!< Specify the PTS of synchronized frame to apply frame sync parameters. */
	u32 stream_updated_map : 16;	/*!< The stream id bit map to update sync parameters. */
	u32 force_update : 1;	/*!< Force to update sync parameters if the frame PTS is not found from the internal queue. */
	u32 strm_sync_type : 3;	/*!< Select frame sync or stream sync */
	u32 reserved : 12;
	u64 stream_frame_num[IAV_STREAM_MAX_NUM_ALL];	/*!< The frame number to apply stream sync parameters. */
};

struct iav_apply_idsp_enc_sync {
	struct iav_apply_flag idsp_apply_flags[IAV_VIDEO_PROC_NUM];
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_vcap_state {
	IAV_VCAP_STATE_NORMAL = 0, /*!< 0 */
	IAV_VCAP_STATE_HALT = 1,   /*!< 1 */
	IAV_VCAP_STATE_VSYNC_LOSS = 2,   /*!< 2 */
	IAV_VCAP_STATE_STATUS_ERROR = 3,   /*!< 3 */
	IAV_VCAP_STATE_STANDBY = 4,   /*!< 4 */
	IAV_VCAP_STATE_NUM = 5,   /*!< 5 */

	IAV_VCAP_STATE_ACTIVE = IAV_VCAP_STATE_NORMAL, /*!< 0 */
	IAV_VCAP_STATE_IDLE = IAV_VCAP_STATE_HALT,     /*!< 1 */
};

enum iav_vcap_cfg_id {
	IAV_VCAP_CFG_STATE = 0x0000, /*!< 0x0000 */
	IAV_VCAP_REPEAT_FRAME = 0x0001, /*!< 0x0001 */
	IAV_VCAP_CFG_NUM,            /*!< 0x0002 */
};
/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_vcap_state_cfg {
	u32 vinc_map; /*!< VIN control ID map */
	enum iav_vcap_state state[VIN_CONTROLLER_NUM]; /*!< vcap states */
};

struct iav_vcap_cfg {
	enum iav_vcap_cfg_id cid; /*!< VCAP configuration ID */
	union {
		struct iav_vcap_state_cfg state_cfg;
		u16 vinc_id;
	} arg;
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper */
enum vin_idsp_apply_map {
	IAV_APPLY_NONE		= 0,		/*!< 0, neither VIN nor IDSP CFG will be applied */
	IAV_APPLY_VIN_CFG	= (1 << 0),	/*!< 1 << 0, apply VIN CFG */
	IAV_APPLY_IDSP_CFG	= (1 << 1),	/*!< 1 << 1, apply IDSP CFG */
	IAV_APPLY_ALL_CFG	= (IAV_APPLY_VIN_CFG | IAV_APPLY_IDSP_CFG), /*!< IAV_APPLY_VIN_CFG | IAV_APPLY_IDSP_CFG */
};

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_vin_idsp_config {
	struct vindev_wdr_gp_info vin_cfg;	/*!< VIN shutter/agc/rhs CFG */
	struct idsp_config_s idsp_cfg;		/*!< IDSP ISO and HDR CFG */
	u32 apply_map : 8;			/*!< apply map @ref vin_idsp_apply_map */
	u32 instant_update : 1;		/*!< apply VIN or IDSP CFG to sensor or ISP instantly without timing logic */
	u32 reserved : 23;
	u8 resend_all_cfg_done[IMG_MAX_VIN_CHANNEL_NUM];
};

struct iav_vin_compand_config {
	u8 vsrc_id;				/*!< Video Source ID */
	u8 comp_en;				/*!< Flag to enable VIN compand option */
	u8 decomp_en;			/*!< Flag to enable VIN de-compand option */
	u8 reserved[1];
	u16 comp_lut[COMP_LUT_ENTRY_NUM];			/*!< VIN compand Look-Up-Table */
	u16 reserved1;
	u32 decomp_lut[DECOMP_LUT_ENTRY_NUM];		/*!< VIN de-compand Look-Up-Table */
};

struct iav_vin_delay_info {
	struct vindev_sht_agc_seq sht_agc[IMG_MAX_VIN_CHANNEL_NUM];
};

struct iav_vin_idsp_delay_info {
	struct iav_vin_delay_info vin;
	struct idsp_delay_info_s idsp;
};
/*! @} */  /* End of iav-ioctl-general-struct */

/*! @addtogroup iav-ioctl-general-helper
 *  @{
 */
enum iav_nalu_type_h264 {
	NT_NON_IDR	= 1, /*!< 1 */
	NT_IDR		= 5, /*!< 5 */
	NT_SEI		= 6, /*!< 6 */
	NT_SPS		= 7, /*!< 7 */
	NT_PPS		= 8, /*!< 8 */
	NT_AUD		= 9, /*!< 9 */
};

enum iav_nalu_type_h265 {
	TRAIL_N		= 0, /*!< 0 */
	TRAIL_R		= 1, /*!< 1 */
	TSA_N		= 2, /*!< 2 */
	TSA_R		= 3, /*!< 3 */
	STSA_N		= 4, /*!< 4 */
	STSA_R		= 5, /*!< 5 */
	IDR_W_RADL	= 19, /*!< 19 */
	IDR_N_LP	= 20, /*!< 20 */
};

enum iav_debugcfg_module {
	IAV_DEBUG_IAV	= (1 << 0), /*!< 1 << 0 */
	IAV_DEBUG_DSP	= (1 << 1), /*!< 1 << 1 */
	IAV_DEBUG_VIN	= (1 << 2), /*!< 1 << 2 */
	IAV_DEBUG_VOUT	= (1 << 3), /*!< 1 << 3 */
	IAV_DEBUG_AAA	= (1 << 4), /*!< 1 << 4 */
};

enum iav_debugcfg_id {
	IAV_DEBUGCFG_CHECK			= 0x0000, /*!< 0x0000 */
	IAV_DEBUGCFG_MODULE			= 0x0001, /*!< 0x0001 */
	IAV_DEBUGCFG_AUDIT_INT		= 0x0002, /*!< 0x0002 */
	IAV_DEBUGCFG_AUDIT_IOCTL	= 0x0003, /*!< 0x0003 */
	IAV_DEBUGCFG_CHECK_SYS_PERF = 0x0004, /*!< 0x0004 */
	IAV_DEBUGCFG_AUDIT_YUV_DELAY	= 0x0005, /*!< 0x0005 */
	IAV_DEBUGCFG_AUDIT_IDSP		= 0x0006, /*!< 0x0006 */
	IAV_DEBUGCFG_AUDIT_ENC		= 0x0007, /*!< 0x0007 */
	IAV_DEBUGCFG_AUDIT_VOUT		= 0x0008, /*!< 0x0008 */
	IAV_DEBUGCFG_AUDIT_ENC_SYNC	= 0x0009, /*!< 0x0009 */
	IAV_DEBUGCFG_AUDIT_EIS_SYNC	= 0x000A, /*!< 0x000A */
	IAV_DEBUGCFG_SKIP_IRQ		= 0x000B, /*!< 0x000B */
	IAV_DEBUGCFG_AUDIT_VV_DELAY	= 0x000C, /*!< 0x000C */
	IAV_DEBUGCFG_NUM			= 0x000D, /*!< 0x000D */
	IAV_DEBUGCFG_FIRST			= IAV_DEBUGCFG_CHECK, /*!< IAV_DEBUGCFG_CHECK */
	IAV_DEBUGCFG_LAST			= IAV_DEBUGCFG_NUM,   /*!< IAV_DEBUGCFG_NUM */

	IAV_DEBUGCFG_CHECK_ALL 		= IAV_DEBUGCFG_CHECK, /*!< IAV_DEBUGCFG_CHECK */
};

enum iav_customcmd_id {
	IAV_CUSTOMCMD_GENERAL_DEBUG,		/*!< 0x0000 */
	IAV_CUSTOMCMD_GET_VIN_LED_CTRL, 	/*!< 0x0001 */
	IAV_CUSTOMCMD_SET_VIN_LED_CTRL,		/*!< 0x0002 */
	IAV_CUSTOMCMD_CFG_IR_LED_RT_CTRL,	/*!< 0x0003 */
	IAV_CUSTOMCMD_CFG_VIN_LED_RT_CTRL,	/*!< 0x0004 */
	IAV_CUSTOMCMD_GET_EXTRA_RAW_CAP_CFG,	/*!< 0x0005 */
	IAV_CUSTOMCMD_SET_EXTRA_RAW_CAP_CFG,	/*!< 0x0006 */

	IAV_CUSTOMCMD_NUM,
	IAV_CUSTOMCMD_FIRST			= IAV_CUSTOMCMD_GENERAL_DEBUG, /*!< IAV_CUSTOMCMD_GENERAL_DEBUG */
	IAV_CUSTOMCMD_LAST			= IAV_CUSTOMCMD_NUM,   /*!< IAV_CUSTOMCMD_NUM */
};

enum iav_custom_ir_led_id {
	IAV_IR_LED_MODE_OFF 			= 0x0000,		/*!< 0x0000 */
	IAV_IR_LED_MODE_ON_ALWAYS 		= 0x0001,		/*!< 0x0001 */
	IAV_IR_LED_MODE_ON_INTERLEAVED 		= 0x0002,		/*!< 0x0002 */
	IAV_IR_LED_MODE_NUM,
	IAV_IR_LED_MODE_FIRST			= IAV_IR_LED_MODE_OFF,	/*!< IAV_IR_LED_MODE_OFF */
	IAV_IR_LED_MODE_LAST			= IAV_IR_LED_MODE_NUM,	/*!< IAV_IR_LED_MODE_NUM */
};

#define IAV_MAX_VIN_LED_TIME_IN_MS	(20)
#define IAV_MIN_VIN_LED_TIME_IN_MS	(1)
#define IAV_MAX_VIN_IR_LED_TIME_IN_MS	(33)
#define IAV_MIN_VIN_IR_LED_TIME_IN_MS	(1)
#define IAV_MIN_CUSTOM_CHAN_FRAME_RATIO	(0)
#define IAV_MAX_CUSTOM_CHAN_FRAME_RATIO	(10)
#define IAV_MIN_CUSTOM_CHAN_NUM	(2)
#define IAV_MAX_CUSTOM_CHAN_NUM	(3)

#define IAV_MAX_TML_ALPHA		(256)

enum iav_custom_vin_led_update_bitmap {
	IAV_CUSTOM_LED_FLASH_TIME_UPDATE_FLAG	= (1 << 0), /*!< 1 << 0 */
	IAV_CUSTOM_LED_FLASH_LATENCY_UPDATE_FLAG	= (1 << 1), /*!< 1 << 1 */
	IAV_CUSTOM_LED_FLASH_MIN_TIME_UPDATE_FLAG	= (1 << 2), /*!< 1 << 2 */
	IAV_CUSTOM_LED_FLASH_TRIGGER_ONCE_UPDATE_FLAG	= (1 << 3), /*!< 1 << 3 */
	IAV_CUSTOM_LED_FLASH_LINE_OFFSET_UPDATE_FLAG	= (1 << 4), /*!< 1 << 4 */
};

enum iav_tml_proc_id {
	IAV_TML_PROC_ALPHA	= 0x00, /*!< 0x00, This is to configure tml alpha on the fly. */
	IAV_TML_PROC_CALIB	= 0x01, /*!< 0x01, This is to configure tml calibration data on the fly. */
	IAV_TML_PROC_TFC	= 0x02, /*!< 0x02, This is to configure tml fusion clut. */
	IAV_TML_PROC_NUM	= 0x03, /*!< 0x03 */
	IAV_TML_PROC_FIRST	= IAV_TML_PROC_ALPHA, /*!< IAV_TML_PROC_ALPHA */
	IAV_TML_PROC_LAST	= IAV_TML_PROC_NUM   /*!< IAV_TML_PROC_NUM */
};

enum dsp_irq_port_type {
	DSP_IRQ_PORT_GEN = 0,	/*!< 0x0000 */
	DSP_IRQ_PORT_VCAP,		/*!< 0x0001 */
	DSP_IRQ_PORT_NUM,
	DSP_IRQ_PORT_FIRST = DSP_IRQ_PORT_GEN,	/*!< DSP_IRQ_PORT_GEN */
	DSP_IRQ_PORT_LAST = DSP_IRQ_PORT_NUM,	/*!< DSP_IRQ_PORT_NUM */
};

/*! @} */  /* End of iav-ioctl-general-helper */

/*! @addtogroup iav-ioctl-general-struct
 *  @{
 */
struct iav_debug_module {
	u8 enable;
	u8 reserved[3];
	u32 flags;
	u32 args[4];
};

struct iav_debug_audit {
	u32	id;
	u32	enable : 1;
	u32	reserved : 31;
	u64	cnt;
	u64	sum;
	u32	max;
	u32	min;
	u32	cur;
};

struct iav_debug_idsp_audit {
	u32 enable : 1; /*!< Enable/Disable idsp frame drop audit. */
	u32 reserved : 31;
	int idsp_frm_drop_cnt[CONFIG_AMBARELLA_MAX_CHANNEL_NUM]; /*!< idsp frame drop count. Each time when this audit is enabled, it will be reset to 0. */
	void (*inc)(struct iav_debug_idsp_audit *idsp_audit, u8 chan_id);
};

struct iav_debug_enc_audit {
	u32 enable : 1; /*!< Enable/Disable encode frame drop audit. it only audits the frame drop count due to BO check. */
	u32 reserved : 31;
	u32 enc_frm_drop_cnt[IAV_STREAM_MAX_NUM_ALL]; /*!< encode frame drop count. Each time when this audit is enabled, it will be reset to 0. */
	void (*inc)(struct iav_debug_enc_audit *enc_audit, u8 stream_id);
};

struct iav_debug_vout_audit {
	u32 enable : 1; /*!< Enable/Disable vout underflow audit. */
	u32 reserved : 31;
	u32 vout_uf_cnt[VOUT_NUM]; /*!< vout underflow count. Each time when this audit is enabled, it will be reset to 0. */
	void (*inc)(struct iav_debug_vout_audit *vout_audit, u8 vout_id);
};

struct iav_debug_skip_dsp_irq {
	u32 skip_cnt;	/*!< Skip DSP ISR count. Used by internal debug purpose. */
	u8 dsp_port;	/*!< DSP IRQ port. */
	u8 reserved[3];
};

struct iav_debug_sync_audit {
	u32 enable : 1; /*!< Enable/Disable sync fail audit. */
	u32 reserved : 31;
	u32 sync_fail_cnt; /*!< sync fail count. Each time when this audit is enabled, it will be reset to 0. */
	void (*inc)(struct iav_debug_sync_audit *sync_audit);
};

struct iav_debug_cfg {
	u32	id; /*!< Not currently supported */
	enum iav_debugcfg_id cid; /*!< Debug configuration item ID */
	union {
		u32	enable; /*!< If IAV, there is no need to check if it is enabled or not */
		struct iav_debug_module module; /*!< Custom debug module configuration */
		struct iav_debug_audit audit;   /*!< IAV Audit debugging configuration */
		struct iav_debug_idsp_audit idsp_audit; /*!< IAV IDSP frame drop audit debugging configuration */
		struct iav_debug_enc_audit enc_audit; /*!< IAV encode frame drop audit debugging configuration */
		struct iav_debug_vout_audit vout_audit; /*!< IAV vout underflow audit debugging configuration */
		struct iav_debug_skip_dsp_irq skip_irq; /*!< DSP ISR skip debugging configuration */
		struct iav_debug_sync_audit enc_sync_audit; /*!< ENC sync fail audit debugging configuration */
		struct iav_debug_sync_audit eis_sync_audit; /*!< EIS sync fail audit debugging configuration */
		struct iav_debug_audit vv_audit[VOUT_NUM]; /*!< VOUT-VIN delay audit debugging configuration */
	} arg; /*!< IAV debug configuration */
};

struct iav_custom_gen_debug_cmd {
	u32	debug_op;
	u32	reserved[7];
};

struct iav_custom_vin_led_ctrl {
	u32 vinc_id : 8;	/*!< vin controller ID */
	u32 flash_enable : 1;	/*!< Whether the sensor enables flash light or not */
	u32 flash_time_in_ms : 7;	/*!< Flash enable times in ms for the sensor */
	u32 structured_light_chan : 2;  /*!< The channel ID of structured light enabled channel */
	u32 ir_led_chan : 2;  /*!< The channel ID of IR LED enabled channel. IR LED flashes on
				every frame of this channel. */
	u32 ir_led_work_mode : 2;	/*!< The IR LED work mode on RGB channel, 0: off,
				1: always on, 2: light on interleaved with structured-light.
				This flag is configurable only when night_mode_enable is set to 1 */
	u32 ir_led_time_in_ms : 7;  /*!< The IR LED enable duration time in ms */
	u32 night_mode_enable : 1;  /*!< The mode flag of day and night. If night mode is enabled,
					IR LED flashes on RGB channel with given behavior defined in
					ir_led_work mode */
	u32 reserved1 : 2;
	u32 frame_ratio;	/*!< The frame ratio between channels. Each byte stands for one
		channel's frame ratio. From the least significant byte, byte[0] is for chan0,
		byte[1] is for chan1, and byte[2] is for chan2.
		The ratio range for each channel is [0-10] */
	u16 led_gpio;	/*!< The LED pin for LED light */
	u16 ir_led_gpio;	/*!< The LED pin num for IR LED */
	u32 flash_led_latency_in_ms_plus_1 : 8;	/*!< Specify the fixed latency after EOF irq. 0: auto, others: (x-1)ms */
	u32 flash_led_min_time_in_ms : 3;	/*!< Specify the min flash time. */
	u32 flash_led_custom_trigger_once : 1;	/*!< Customer trigger flash led */
	u32 flash_led_line_offset : 12;	/*!< Specify the line offset for flash led */
	u32 reserved2 : 8;
	u32 flash_led_update_flag_bitmap; /*!< Specify the realtime update flag */
};

struct iav_custom_extra_raw_cap_cfg {
	u8 enable;		/*!< Enbale/disable extra raw capture. 1:enable; 0:disable */
	u8 top_lines;		/*!< Specify the top lines to capture */
	u8 bottom_lines;	/*!< Specify the bottom lines to capture */
	u8 reserved;
};

struct iav_custom_cfg {
	enum iav_customcmd_id cmd_code;
	union {
		struct iav_custom_gen_debug_cmd debug;
		struct iav_custom_vin_led_ctrl vin_led_ctrl;
		struct iav_custom_extra_raw_cap_cfg extra_raw_cap[VIN_CONTROLLER_NUM];
	} arg;
};

struct iav_tml_alpha {
	u32 alpha : 9;		/*!< [0 ~ 256], output = (alpha * target + (256 - alpha) * ref) / 256 */
	u32 reserved : 23;
};

struct iav_tml_calib {
	u32 invert : 1;		/*!< 0: raw - calib ; 1: calib - raw */
	u32 reserved : 31;

	u32 raw_pid;	/*!< raw data memory partition id */
	u32 hds_pid;	/*!< hds data memory partition id */
	u32 raw_offset;	/*!< raw data offset */
	u32 hds_offset;	/*!< hds data offset */
	u16 raw_pitch;	/*!< raw data pitch */
	u16 hds_pitch;	/*!< hds data pitch */
};

struct iav_tml_tfc {
	unsigned long data_addr_offset; /*!< Start address of TML Fusion CLUT */
};

struct iav_tml_proc_cfg {
	enum iav_tml_proc_id cid; /*!< Configuration item ID, @sa iav_tml_proc_id */
	u32 channel_id : 8;	/*!< Channel ID */
	u32 reserved : 24;
	union {
		struct iav_tml_alpha alpha;
		struct iav_tml_calib calib;
		struct iav_tml_tfc tfc;
	} arg; /*!< Configuration items */
};

/*! @} */ /* End of iav-ioctl-general-struct  */

/*!
 * @addtogroup iav-ioctl-dec-helper
 * @{
 */
#define DIAV_MAX_DECODER_NUMBER 				8
#define DIAV_MAX_DECODE_VOUT_NUMBER 			2

#define DIAV_MAX_INTRA_DECODE_CMD_NUMBER 		4
#define DIAV_MAX_INTRA_FB_NUMBER 				4
#define DIAV_MAX_INTRA_YUV2YUV_DST_FB_NUMBER 	3

enum {
	IAV_DECODER_TYPE_INVALID	= 0x00, /*!< 0x00 */
	IAV_DECODER_TYPE_INTRA		= 0x02, /*!< 0x02 */
	IAV_DECODER_TYPE_H264		= 0x03, /*!< 0x03 */
	IAV_DECODER_TYPE_H265		= 0x04, /*!< 0x04 */

	IAV_DECODER_TYPE_MJPEG		= 0x06, /*!< 0x06 */
};

enum {
	IAV_TRICK_PLAY_PAUSE	= 0, /*!< 0 */
	IAV_TRICK_PLAY_RESUME	= 1, /*!< 1 */
	IAV_TRICK_PLAY_STEP	= 2, /*!< 2 */
};

enum {
	IAV_PB_DIRECTION_FW	= 0, /*!< 0 */
	IAV_PB_DIRECTION_BW	= 1, /*!< 1 */
};

enum {
	IAV_PB_SCAN_MODE_ALL_FRAMES	= 0, /*!< 0 */
	IAV_PB_SCAN_MODE_I_ONLY		= 1, /*!< 1 */
};

enum {
	IAV_DSP_BUFFER_PIX_FMT_420	= 1, /*!< 1 */
	IAV_DSP_BUFFER_PIX_FMT_422	= 2, /*!< 2 */
};

enum iav_dec_type {
	IAV_DEC_NORMAL			= 0, /*!< 0, decoder normal mode. */
	IAV_DEC_LOW_DELAY_DEFAULT	= 1, /*!< 1, decoder low delay mode, VOUT throttle enabled,
						  no frame drop */
	IAV_DEC_LOW_DELAY_FRAME_DROP	= 2, /*!< 2, decoder low delay mode, VOUT throttle disabled,
						  VOUT would drop frame, if needed. */
};
/*! @} */ /* End of iav-ioctl-dec-helper */

/*! @addtogroup iav-ioctl-dec-struct
 * @{
 */
struct iav_decode_vout_config {
	u8 vout_id;	/*!< VOUT ID */
	u8 enable;	/*!< VOUT is enable or not */
	u8 flip;	/*!< VOUT is flip or not */
	u8 rotate;	/*!< VOUT is rotate or not */

	u16 target_win_offset_x; /*!< Display window offset x */
	u16 target_win_offset_y; /*!< Display window offset y */

	u16 target_win_width;  /*!< Display window width */
	u16 target_win_height; /*!< Display window height */

	u32 zoom_factor_x; /*!< Zoom factor x */
	u32 zoom_factor_y; /*!< Zoom factor y */

	u32 vout_mode; /*!< VOUT mode */
	u32 reserved;
};

struct iav_decode_mode_config {
	u8 b_support_ff_fb_bw;			/*!< Playback will support fast FW/BW. Please note that this can need more DRAM usage in DSP if enabled. */
	u8 debug_max_frame_per_interrupt;	/*!< Debug option, please ignore, fill 0. */
	u8 debug_use_dproc;			/*!< Debug option, please ignore, fill 0. */
	u8 num_decoder;				/*!< Number of decoder. */

	u32 max_vout0_width;			/*!< Maximum LCD' width (for DSP's DRAM allocation) */
	u32 max_vout0_height;			/*!< Maximum LCD' height (for DSP's DRAM allocation) */

	u32 max_vout1_width;			/*!< Maximum HDMI' width (for DSP's DRAM allocation) */
	u32 max_vout1_height;			/*!< Maximum HDMI' height (for DSP's DRAM allocation) */

	u16 max_n_to_m_ratio;			/*!< Maximum GOP size (for DSP DRAM allocation), If FW/BW are not enabled, can set it to 0. */
	u8 b_support_all_frame_backward;	/*!< Output: Support all frames backward or not. */
	u8 num_vout;				/*!< Number of VOUT */

	u32 not_reset_vout : 1;			/*!< Not reset VOUT, when vout setting does not change */
	u32 low_delay_mode : 2; 		/*!< Decode low delay mode to optimize decode speed,
						     set 0 by default, @sa iav_dec_type */
	u32 reserved_bits : 29;

	u8 decoder_type[DIAV_MAX_DECODER_NUMBER]; /*!< Decoder type */
	u8 enable_vout[DIAV_MAX_DECODER_NUMBER]; /*!< Enable / Disable VOUT for each decoder */
	u32 max_frm_width[DIAV_MAX_DECODER_NUMBER]; /*!< Maximum Video Width for each decoder */
	u32 max_frm_height[DIAV_MAX_DECODER_NUMBER]; /*!< Maximum Video Height for each decoder */
	struct iav_pyramid_cfg pyramid[DIAV_MAX_DECODER_NUMBER]; /*!< Pyramid buffer configuration for each decoder */
};

struct iav_decoder_info {
	u8 decoder_id;	/*!< Decoder instance ID */
	u8 decoder_type;/*!< Decoder type, see IAV_DECODER_TYPE */
	u8 num_vout;	/*!< Number of VOUT */
	u8 setup_done;	/*!< Ignore it */

	u32 width;	/*!< Video width */
	u32 height;	/*!< Video height */

	u32 bsb_size;	/*!< Size of bitstream-buffer */
	unsigned long bsb_start_offset; /*!< Start offset of bitstream-buffer */

	struct iav_decode_vout_config vout_configs[DIAV_MAX_DECODE_VOUT_NUMBER]; /*!< VOUT configuration */

	u8 full_speed_decode; /*!< Full speed decode flag */
	u8 reserved[3];
};

struct iav_decode_video {
	u8 decoder_id;			/*!< Decoder ID */
	u8 num_frames;			/*!< Number of frames in bitstream */
	u8 reserved[2];

	u32 first_frame_display;	/*!< Specify the PTS of first frame that will be displayed. The former frames will be dropped. */

	unsigned long start_ptr_offset;	/*!< Video data's start offset in bitstream buffer */
	unsigned long end_ptr_offset;	/*!< Video data's end offset in bitstream buffer */
};

struct iav_decode_jpeg {
	u8	decoder_id;		/*!< Decoder ID */
	u8	reserved[3];
	u32	size;			/*!< Size of JPEG data */
	unsigned long start_offset;	/*!< JPEG data start offset in bitstream buffer */
};

struct iav_decode_bsb {
	u8 decoder_id;			/*!< Decoder ID */
	u8 reserved[7];

	unsigned long start_offset;	/*!< Request free zoom's start offset */
	u32 room; 			/*!< Request free zoom's size, minus 256 byte for avoid read_offset == write_offset*/

	//read only
	u32 free_room;			/*!< DSP's free zoom (read only) */
	unsigned long dsp_read_offset;	/*!< DSP's read offset (read only) */
};

struct iav_decode_stop {
	u8 decoder_id;	/*!< Decoder ID */
	u8 stop_flag;	/*!< Stop flag: 0:  End the playback
			     1:  Keep showing last frame, will continue playback when feeding new data */
	u8 reserved[6];
};

struct iav_decode_trick_play {
	u8 decoder_id;	/*!< Decoder ID */
	u8 trick_play;	/*!< Trick play type, see IAV_TRICK_PLAY */
	u8 reserved[6];
};

struct iav_decode_speed {
	u8 decoder_id;	/*!< Decoder ID */
	u8 reserved[3];

	u8 direction;	/*!< See IAV_PB_DIRECTION, 0: forward, 1: backward*/
	u8 scan_mode;	/*!< See IAV_PB_SCAN_MODE */
	u16 speed;	/*!< Playback speed, 8.8 fix point format */
};

struct iav_decode_wait_eos {
	u8	decoder_id;	/*!< Decoder ID */
	u8	timeout_ticks;	/*!< time out ticks, 0: No timeout */
	u8	reserved[6];
};

struct iav_decode_zoom_desc {
       u8 decoder_id;		/*!< Decoder ID */
       u8 vout_id;		/*!< Vout ID */
       u8 reserved[2];
       struct iav_rect zoom_win;/*!< Target zoom window */
};

struct iav_intraplay_frame_buffer {
	u8 buffer_id;			/*!< Buffer ID */
	u8 ch_fmt;			/*!< Channel format */

	u16 buf_pitch;			/*!< Buffer pitch */

	u16 buf_width;			/*!< Buffer width */
	u16 buf_height;			/*!< Buffer height */

	unsigned long lu_buf_offset;	/*!< Luma offset */
	unsigned long ch_buf_offset;	/*!< Chroma offset */

	u16 img_width;			/*!< Image width */
	u16 img_height;			/*!< Image height */
	u16 img_offset_x;		/*!< Image offset x */
	u16 img_offset_y;		/*!< Image offset y */

	u32 buffer_size;		/*!< Buffer size */
	u32 reserved;
};

struct iav_intraplay_decode_bitstream {
	u32 bits_fifo_start;	/*!< Bits fifo start addr */
	u32 bits_fifo_end;	/*!< Bits fifo end addr */
};

struct iav_intraplay_display_desc {
	u8 vout_id;		/*!< Vout ID */
	u8 vid_win_update;	/*!< Video window update flag */
	u8 vid_win_rotate;	/*!< Video window rotate flag */
	u8 vid_flip;		/*!< Video window flip flag */
	u8 reserved[4];

	u16 vid_win_width;	/*!< Video window width */
	u16 vid_win_height;	/*!< Video window height */
	u16 vid_win_offset_x;	/*!< Video window offset x */
	u16 vid_win_offset_y;	/*!< Video window offset y */
};

struct iav_intraplay_reset_buffers {
	u8 decoder_id;		/*!< Decoder ID */
	u8 max_num;		/*!< Max buffer number */
	u8 reserved[6];
};

struct iav_intraplay_decode {
	u8 decoder_id;		/*!< Decoder ID */
	u8 num;			/*!< Decode command number */
	u8 decode_type;		/*!< Decoder type */
	u8 reserved[5];

	struct iav_intraplay_decode_bitstream bitstreams[DIAV_MAX_INTRA_DECODE_CMD_NUMBER];	/*!< Bit stream address */
	struct iav_intraplay_frame_buffer buffers[DIAV_MAX_INTRA_DECODE_CMD_NUMBER];	/*!< Frame buffer info */
};

struct iav_intraplay_yuv2yuv {
	u8 decoder_id;	/*!< Decoder ID */
	u8 num;		/*!< Decode command number */
	u8 rotate;	/*!< Decoder rotate flag */
	u8 flip;	/*!< Decoder flip flag */
	u8 luma_gain;	/*!< Decoder luma gain */
	u8 reserved[3];

	struct iav_intraplay_frame_buffer src_buf;	/*!< Decoder source buffer info */
	struct iav_intraplay_frame_buffer dst_buf[DIAV_MAX_INTRA_YUV2YUV_DST_FB_NUMBER];	/*!< Decoder dest buffer info */
};

struct iav_intraplay_display {
	u8 decoder_id;	/*!< Decoder ID */
	u8 num;		/*!< Decoder command number */
	u8 reserved[6];

	struct iav_intraplay_frame_buffer buffers[DIAV_MAX_INTRA_DECODE_CMD_NUMBER];	/*!< Frame buffers info */
	struct iav_intraplay_display_desc desc[DIAV_MAX_INTRA_DECODE_CMD_NUMBER];	/*!< Display desc info */
};

struct iav_decode_status {
	u8 decoder_id;		/*!< Decoder ID */
	u8 is_started;		/*!< Decoder is started */
	u8 is_send_stop_cmd;	/*!< Decoder has been sent stop command */
	u8 reserved[5];

	u32 last_pts;		/*!< Last showing frame's pts */

	u32 decode_state;	/*!< DSP decode status */
	u32 error_status;	/*!< DSP decode error status */
	u32 total_error_count;	/*!< Total DSP met errors */
	u32 decoded_pic_number;	/*!< Total decoded picture number */

	//bit stream buffer
	u32 room; 			/*!< Free zoom left in bitstream buffer,
					     minus 256 byte for avoid read_offset == write_offset */
	unsigned long write_offset;	/*!< ARM write offset, in bitstream buffer */
	unsigned long dsp_read_offset;	/*!< DSP read offset, in bitstream buffer */
	u32 free_room;			/*!< DSP reported free zoom */

	//debug
	u32 irq_count;			/*!< IRQ count. Debug only. */
	unsigned long yuv422_y_addr;	/*!< Luma address of display frame */
	unsigned long yuv422_uv_addr;	/*!< Chroma address of display frame */
};
/*! @} */  /* End of iav-ioctl-dec-struct */

/*!
 * @addtogroup iav-ioctl-general-helper
 * @{
 */

 /*! @macros IAVENCIOC_MAGIC
  *  @brief IAVENCIOC_MAGIC.
  */
#define IAVENCIOC_MAGIC				'V'

/*! @macros IAVENC_IO(nr)
 *  @brief ioctl none of (nr).
 */
#define IAVENC_IO(nr)				_IO(IAVENCIOC_MAGIC, nr)

/*! @macros IAVENC_IOR(nr)
 *  @brief ioctl read of (nr).
 */
#define IAVENC_IOR(nr, size)		_IOR(IAVENCIOC_MAGIC, nr, size)

/*! @macros IAVENC_IOW(nr)
 *  @brief ioctl write of (nr).
 */
#define IAVENC_IOW(nr, size)		_IOW(IAVENCIOC_MAGIC, nr, size)

/*! @macros IAVENC_IOWR(nr)
 *  @brief ioctl read write of (nr).
 */
#define IAVENC_IOWR(nr, size)		_IOWR(IAVENCIOC_MAGIC, nr, size)

/*! @enum IAV_ENC_IOC
 *  @brief IAV_ENC_IOC Enumerations
 */
enum IAV_ENC_IOC {

	IOC_STATE		= 0x00, /*!< 0x00, For DSP & Driver (0x00 ~ 0x0F) */
	IOC_CHIP_ID		= 0x01, /*!< 0x01 */
	IOC_DSP_LOG		= 0x02, /*!< 0x02 */
	IOC_DSP_INFO		= 0x03, /*!< 0x03 */
	IOC_DSP_HASH		= 0x04, /*!< 0x04 */
	IOC_DSP_VP_CFG		= 0x05, /*!< 0x05 */
	IOC_QUERY_INFO		= 0x06, /*!< 0x06 */
	IOC_QUERY_ENC_MODE_CAP	= 0x07, /*!< 0x07 */
	IOC_QUERY_ENC_BUF_CAP	= 0x08, /*!< 0x08 */
	IOC_DSP_AUTH			= 0x09, /*!< 0x09 */
	IOC_DSP_BOOT_CFG		= 0x0A, /*!< 0x0A */

	IOC_ENTER_IDLE			= 0x10, /*!< 0x10, For system (0x10 ~ 0x2F) */
	IOC_ENABLE_PREVIEW		= 0x11, /*!< 0x11 */
	IOC_START_ENCODE		= 0x12, /*!< 0x12 */
	IOC_STOP_ENCODE			= 0x13, /*!< 0x13 */
	IOC_ABORT_ENCODE		= 0x14, /*!< 0x14 */
	IOC_SYSTEM_RESOURCE		= 0x15, /*!< 0x15 */
	IOC_GDMA_COPY			= 0x16, /*!< 0x16 */
	IOC_QUERY_DESC			= 0x17, /*!< 0x17 */
	IOC_QUERY_MEMBLOCK		= 0x18, /*!< 0x18 */
	IOC_EFM_PROC			= 0x19, /*!< 0x19 */
	IOC_RAW_ENC			= 0x1A, /*!< 0x1A */
	IOC_MEM_PART			= 0x1B, /*!< 0x1B */
	IOC_PYRAMID_BUF			= 0x1C, /*!< 0x1C */
	IOC_CUSTOM_SEI_PROC 	= 0x1D, /*!< 0x1D */
	IOC_PYRAMID_CFG			= 0x1E, /*!< 0x1E */
	IOC_SYNC_CACHE_MEM_PART	= 0x1F, /*!< 0x1F */
	IOC_CANVAS_BUF			= 0x20, /*!< 0x20 */
	IOC_RESET				= 0x21, /*!< 0x21 */
	IOC_MEM_LAYOUT			= 0x22, /*!< 0x22 */
	IOC_ANON_MEM_PART		= 0x23, /*!< 0x23 */
	IOC_POLL_EVENT_CFG		= 0x24, /*!< 0x24 */
	IOC_RAW_BUF				= 0x25, /*!< 0x25 */
	IOC_CUSTOM_PYRAMID_CFG	= 0x26, /*!< 0x26 */
	IOC_CUSTOM_PYRAMID_BUF	= 0x27, /*!< 0x27 */

	IOC_STREAM_CFG			= 0x30, /*!< 0x30, For encode control (0x30 ~ 0x5F) */
	IOC_H264_CFG			= 0x31, /*!< 0x31 */
	IOC_H265_CFG			= 0x32, /*!< 0x32 */
	IOC_MJPEG_CFG			= 0x33, /*!< 0x33 */
	IOC_FRAME_SYNC			= 0x34, /*!< 0x34 */
	IOC_OVERLAY_INSERT		= 0x35, /*!< 0x35 */
	IOC_FASTOSD_INSERT		= 0x36, /*!< 0x36 */
	IOC_FPS_SUGGEST			= 0x37, /*!< 0x37 */
	IOC_BLUR_INSERT			= 0x38, /*!< 0x38 */
	IOC_FRAMEDESC_CTRL		= 0x39, /*!< 0x39 */
	IOC_JPEG_SERVICE		= 0x3a, /*!< 0x3a */

	IOC_VCAP_CFG			= 0x60, /*!< 0x60, For VIN & IDSP & VCAP control (0x60 ~ 0x6F) */
	IOC_WARP_CTRL			= 0x61, /*!< 0x61 */
	IOC_VIDEO_PROC			= 0x62, /*!< 0x62 */
	IOC_VIN_IDSP			= 0x63, /*!< 0x63 */
	IOC_WAIT_IDSP_FRAME		= 0x64, /*!< 0x64 */
	IOC_VIN_COMP			= 0x65, /*!< 0x65 */
	IOC_IMG_SCALE		= 0x66, /*!< 0x66 */
	IOC_TML				= 0x67, /*!< 0x67 */

	IOC_AISP_CFG			= 0x70, /*!< 0x70, For AISP control (0x70 ~ 0x7F) */

	IOC_TEST				= 0xD0, /*!< 0xD0, For Misc setting (0xD0 ~ 0xEF) */
	IOC_DEBUG				= 0xD1, /*!< 0xD1 */
	IOC_DSP_DUMP_CMD		= 0xD2, /*!< 0xD2 */

	IOC_CUSTOM				= 0xF0, /*!< 0xF0, Reserved (0xF0 ~ 0xFF) */
};
/*! @} */  /* End of iav-ioctl-general-helper */


/*!
 * @addtogroup iav-ioc-enc-use-drv
 * @{
 */

/*!
 *  This API can be invoked during any state to return the current device driver state.
 *  @param u32(pointer) : value refers to enum @ref iav_state
 */
#define IAV_IOC_GET_IAV_STATE				IAVENC_IOR(IOC_STATE, u32)

/*!
 *  This API can be invoked during any state to retrieve chip ID information after the DSP is booted.
 *  @param u32(pointer) : value refers to enum @ref iav_chip_id
 */
#define IAV_IOC_GET_CHIP_ID				IAVENC_IOR(IOC_CHIP_ID, u32)

/*!
 *  This API sets the DSP log level for the debug.
 *  @param struct iav_dsplog_setup
 */
#define IAV_IOC_SET_DSP_LOG				IAVENC_IOW(IOC_DSP_LOG, struct iav_dsplog_setup *)

/*!
 *  This API can be used to return the current device driver information such as version, chip id.
 *  @param struct iav_driver_dsp_info
 */
#define IAV_IOC_DRV_DSP_INFO				IAVENC_IOWR(IOC_DSP_INFO, struct iav_driver_dsp_info *)

#define IAV_IOC_GET_DSP_HASH				IAVENC_IOWR(IOC_DSP_HASH, struct iav_dsp_hash *)

/*!
 *  This API can be used to set dsp vp config.
 *  @param struct iav_dsp_vp_cfg
 */
#define IAV_IOC_SET_DSP_VP_CFG				IAVENC_IOW(IOC_DSP_VP_CFG, struct iav_dsp_vp_cfg *)

/*!
 *  This API can be used to get dsp vp config.
 *  @param struct iav_dsp_vp_cfg
 */
#define IAV_IOC_GET_DSP_VP_CFG				IAVENC_IOWR(IOC_DSP_VP_CFG, struct iav_dsp_vp_cfg *)

/*!
 *  This API can be invoked during any state to query IAV information such as
 *  the boot mode, driver version, canvas, stream and privacy mask information.
 *  @param struct iav_queryinfo
 */
#define IAV_IOC_QUERY_INFO					IAVENC_IOWR(IOC_QUERY_INFO, struct iav_queryinfo *)

/*!
 *  This API can be used to do mutual authentication with DSP.
 *  @param struct iav_dsp_auth
 */
#define IAV_IOC_DSP_AUTH						IAVENC_IOWR(IOC_DSP_AUTH, struct iav_dsp_auth *)

/*!
 *  This API can be used to control the operation of dumping DSP commands.
 *  It is mainly used to prepare the combo command sequence for fast boot
 *  use case. For more details, please refer to fast boot document.
 *  @param struct iav_dsp_dump_cmd_ctrl
 */
#define IAV_IOC_CTRL_DSP_DUMP_CMD IAVENC_IOW(IOC_DSP_DUMP_CMD, struct iav_dsp_dump_cmd_ctrl *)

/*!
 *  This API can be used to query the status of dumped DSP commands.
 *  It is mainly used to prepare the combo command sequence for fast boot
 *  use case. For more details, please refer to fast boot document.
 *  @param struct iav_dsp_dump_cmd_query
 */
#define IAV_IOC_QUERY_DSP_DUMP_CMD IAVENC_IOWR(IOC_DSP_DUMP_CMD, struct iav_dsp_dump_cmd_query *)

/*! @} */  /* End of iav-ioc-enc-use-drv */

/*!
 * @addtogroup iav-ioc-enc-use-raw
 * @{
 */
/*!
 *  This API can be used during the preview or encoding states to feed raw
 *  buffers in the channel raw manual-feed mode.
 *  @param struct iav_feed_raw
 */
#define IAV_IOC_FEED_RAW_BUF				IAVENC_IOW(IOC_RAW_BUF, struct iav_feed_raw *)

/*!
 *  This API can be used during any state to release the raw buffer locked
 *  by IAV_IOC_QUERY_DESC (IAV_DESC_RAW) in the channel raw manual-feed mode.
 *  @param struct iav_rawbufdesc
 */
#define IAV_IOC_RELEASE_RAW_BUF			IAVENC_IOWR(IOC_RAW_BUF, struct iav_feed_raw *)
/*! @} */  /* End of iav-ioc-enc-use-raw */

/*!
 * @addtogroup iav-ioc-enc-use-pyra
 * @{
 */
/*!
 *  This API can be used during the preview or encoding states to feed pyramid
 *  buffers in the pyramid manual-feed mode.
 *  @param struct iav_feed_pyramid
 */
#define IAV_IOC_FEED_PYRAMID_BUF			IAVENC_IOW(IOC_PYRAMID_BUF, struct iav_feed_pyramid *)

/*!
 *  This API can be used during the preview or encoding states to feed the custom pyramid buf
 *  in the custom pyramid mode.
 *  @param: iav_feed_custom_pyramid
 */
#define IAV_IOC_FEED_CUSTOM_PYRAMID			IAVENC_IOWR(IOC_CUSTOM_PYRAMID_BUF, struct iav_feed_custom_pyramid *)

/*!
 *  This API can be used during any state to release the pyramid buffer locked
 *  by IAV_IOC_QUERY_DESC (IAV_DESC_PYRAMID) in the pyramid manual-feed mode.
 *  @param struct iav_pyramiddesc
 */
#define IAV_IOC_RELEASE_PYRAMID_BUF			IAVENC_IOWR(IOC_PYRAMID_BUF, struct iav_pyramiddesc *)
/*! @} */  /* End of iav-ioc-enc-use-pyra */

/*!
 * @addtogroup iav-ioc-enc-use-canvas
 * @{
 */
/*!
 *  This API can be used during the preview or encoding states to feed canvas
 *  buffers in the canvas manual-feed mode.
 *  There are some restrictions for canvas manual-feed mode:
 *  1. Either in single channel or multi-channel cases, canvas must be from single
 *  source buffer output. It cannot be composited by multiple source buffers output.
 *  2. For now, the manual feed can only support one canvas, it can be either main
 *  buffer or anyone of the sub source buffers. Future SDK update might support
 *  multiple canvas work in manual feed mode simultaneously.
 *  @param struct iav_feed_canvas
 */
#define IAV_IOC_FEED_CANVAS_BUF				IAVENC_IOW(IOC_CANVAS_BUF, struct iav_feed_canvas *)

/*!
 *  This API can be used during any state to release the canvas buffer locked
 *  by IAV_IOC_QUERY_DESC (IAV_DESC_CANVAS) in the canvas manual-feed mode.
 *  @param struct iav_canvasdesc
 */
#define IAV_IOC_RELEASE_CANVAS_BUF			IAVENC_IOWR(IOC_CANVAS_BUF, struct iav_canvasdesc *)
/*! @} */  /* End of iav-ioc-enc-use-canvas */


/*!
 * @addtogroup iav-ioc-enc-use-sys
 * @{
 */

/*!
 *  This API can be invoked to reset IAV and DSP and if successful, it brings IAV and DSP
 *  to the INIT state.
 *  @param none
 */
#define IAV_IOC_RESET						IAVENC_IOW(IOC_RESET, u8)

/*!
 *  This API can be invoked during init state to configure DSP boot params.
 *  @param struct iav_dsp_boot_params
 */
#define IAV_IOC_SET_DSP_BOOT_CFG			IAVENC_IOW(IOC_DSP_BOOT_CFG, struct iav_dsp_boot_params *)

/*!
 *  This API can be invoked during any state to get DSP boot params.
 *  @param struct iav_dsp_boot_params
 */
#define IAV_IOC_GET_DSP_BOOT_CFG			IAVENC_IOR(IOC_DSP_BOOT_CFG, struct iav_dsp_boot_params *)

/*!
 *  This API can be invoked during idle state to set AISP cfg.
 *  @param struct iav_aisp_cfg
 */
#define IAV_IOC_SET_AISP_CFG				IAVENC_IOW(IOC_AISP_CFG, struct iav_aisp_cfg *)

/*!
 *  This API can be invoked during any state to get AISP cfg.
 *  @param struct iav_aisp_cfg
 */
#define IAV_IOC_GET_AISP_CFG				IAVENC_IOR(IOC_AISP_CFG, struct iav_aisp_cfg *)

/*!
 *  This API can be invoked to disable preview and if successful, it brings the
 *  driver to enter the IDLE state.
 *  @param struct iav_idle_params
 */
#define IAV_IOC_ENTER_IDLE					IAVENC_IOW(IOC_ENTER_IDLE, u8)

/*!
 *  This API can be invoked to enable preview and encoding can be started only
 *  in the preview state.
 *  @param none
 */
#define IAV_IOC_ENABLE_PREVIEW				IAVENC_IOW(IOC_ENABLE_PREVIEW, u8)

/*!
 *  This API can be invoked during the stream-ready state to start stream encoding.
 *  Multiple streams can be encoded together if they are configured and in the
 *  ready state.
 *  @param u32(not pointer) : is streams map
 */
#define IAV_IOC_START_ENCODE				IAVENC_IOW(IOC_START_ENCODE, u32)

/*!
 *  This API can be invoked during the stream-encoding state to stop stream encoding.
 *  Multiple streams can be stopped from encoding at the same time.
 *  @param u32(not pointer) : is streams map
 */
#define IAV_IOC_STOP_ENCODE					IAVENC_IOW(IOC_STOP_ENCODE, u32)

/*!
 *  This API can be invoked during stream state transition from START to STOP or
 *  from STOP to START. It is used to abort such transitions.
 *  It's mainly used for EFM encode cases.
 *  @param u32(not pointer) : is streams map
 */
#define IAV_IOC_ABORT_ENCODE				IAVENC_IOW(IOC_ABORT_ENCODE, u8)

/*!
 *  This API can be invoked during the IDLE state to setup the encoding related
 *  system limit, which will otherwise have a default value.  It must be issued
 *  before any of the APIs are called in the IDLE state.  The configuration of
 *  the limit depends on how much memory has been allocated to DSP, how many
 *  features the DSP needs to support, and which encode mode the application uses.
 *  @param struct iav_system_resource
 */
#define IAV_IOC_SET_SYSTEM_RESOURCE			IAVENC_IOW(IOC_SYSTEM_RESOURCE, u8)

/*!
 *  This API can be invoked during any state to get encoding related system limit.
 *  It is used to retrieve the default system resource limit for each encode mode.
 *  @param struct iav_system_resource
 */
#define IAV_IOC_GET_SYSTEM_RESOURCE			IAVENC_IOWR(IOC_SYSTEM_RESOURCE, u8)

/*!
 *  This API can be invoked during any state to get encoding related system configure separately.
 *  It is used to retrieve the default system resource configures for each encode mode.
 *  NOTE: this API acts similar function with API @ref IAV_IOC_GET_SYSTEM_RESOURCE, but with finer
 *  granularity to retrieve different component separately. If user app just needs partial content
 *  of system resource, it's suggested to call this API instead of API @ref IAV_IOC_GET_SYSTEM_RESOURCE.
 *  @param struct iav_sys_cfg
 */
#define IAV_IOC_GET_SYSTEM_CONFIG			IAVENC_IOWR(IOC_SYSTEM_RESOURCE, u16)

/*!
 *  This API can be invoked during the IDLE state to setup the pyramid related
 *  configuration for a specified channel, which will otherwise have a default
 *  value. It should be issued together with the system resource setup IOCTL.
 *  @param struct iav_pyramid_cfg
 */
#define IAV_IOC_SET_PYRAMID_CFG				IAVENC_IOW(IOC_PYRAMID_CFG, u8)

/*!
 *  This API can be invoked during any state to get pyramid related
 *  configuration for a specified channel.
 *  @param struct iav_pyramid_cfg
 */
#define IAV_IOC_GET_PYRAMID_CFG				IAVENC_IOWR(IOC_PYRAMID_CFG, u8)

/*!
 *  This API can be invoked during the IDLE state to setup the custom pyramid related
 *  configuration. It should be issued together with the system resource setup IOCTL.
 *  @param: iav_custom_pyramid_cfg
 */
#define IAV_IOC_SET_CUSTOM_PYRAMID_CFG			IAVENC_IOW(IOC_CUSTOM_PYRAMID_CFG, struct iav_custom_pyramid_cfg *)

/*!
 *  This API can be invoked during any state to get custom pyramid related
 *  configuration.
 *  @param: iav_custom_pyramid_cfg
 */
#define IAV_IOC_GET_CUSTOM_PYRAMID_CFG			IAVENC_IOWR(IOC_CUSTOM_PYRAMID_CFG, struct iav_custom_pyramid_cfg *)

/*!
 *  This API can be invoked at any state to use the GDMA device to perform memory
 *  copying between large memory partitions. As the GDMA device is a module dedi-
 *  cated for memory copy, it can free up the CPU cycles.
 *
 *  The GDMA device must access contiguous physical memory addresses. It cannot
 *  access any virtual memory space allocated by user applications, meaning that
 *  this API cannot replace the general memory copy function "memcpy". The GDMA
 *  device can support linear memory copy in one and two dimensions. For the two
 *  dimensional copy, the pitch of the source and destination can be different,
 *  but the total memory size needs to be identical.
 *
 *  The IAV driver supports the function of memory mapping from the physical
 *  memory to the user's virtual memory for most IAV/DSP memory partitions and
 *  all anonymous memory partitions, such as privacy mask, overlay, bit stream
 *  buffer, DSP and so on. User applications can call a GDMA copy API to perform
 *  memory copying among these memory partitions.
 *  @param struct iav_gdma_copy
 */
#define IAV_IOC_GDMA_COPY					IAVENC_IOW(IOC_GDMA_COPY, struct iav_gdma_copy *)

/*!
 *  This API can be invoked during any state to query the system capability of each
 *  function for the specified encode mode.
 *  @param struct iav_enc_mode_cap
 */
#define IAV_IOC_QUERY_ENC_MODE_CAP			IAVENC_IOWR(IOC_QUERY_ENC_MODE_CAP, struct iav_enc_mode_cap *)

/*!
 *  This API can be invoked during any state to query the source buffer capability of
 *  the specified buffer.
 *  @param struct iav_enc_buf_cap
 */
#define IAV_IOC_QUERY_ENC_BUF_CAP			IAVENC_IOWR(IOC_QUERY_ENC_BUF_CAP, struct iav_enc_buf_cap *)
/*! @} */  /* End of iav-ioc-enc-use-sys */

/*!
 * @addtogroup iav-ioc-enc-img-scale
 * @{
 */
/*!
 *  This API can be invoked during preview/encoding state to do arbitrary image scale.
 *  For more information about arbitrary image scaler, refer to @ref ut_img_scale.
 *
 *  Application needs to prepare the memory for the input buffer and the output buffer
 *  before calling image scale function.
 *  @param struct iav_img_scale
 */
#define IAV_IOC_SET_IMG_SCALE			IAVENC_IOWR(IOC_IMG_SCALE, struct iav_img_scale *)

/*!
 *  This API can be invoked during preview/encoding state to wait for image scaling task finished.
 *  @note
 *  1. This API is invoked only when member param: non_block_flag in struct iav_img_scale is 1.
 *  2. When ioctl IAV_IOC_SET_IMG_SCALE is invoked multiple times in non-blocking way, DSP will
 *     process these taskes sequentially. So user applicate only needs to wait for the last image
 *     scaling task. Once the last task finished, all other prior tasks are also finished.
 *  @param struct iav_wait_img_scale
 */
#define IAV_IOC_WAIT_IMG_SCALE			IAVENC_IOW(IOC_IMG_SCALE, struct iav_wait_img_scale *)

/*! @} */  /* End of iav-ioc-enc-img-scale */

/*!
 * @addtogroup iav-ioc-enc-use-efm
 * @{
 */
/*!
 *  This API can be invoked during preview/encoding state to get EFM related
 *  parameters.
 *  @param struct iav_efm_get_pool_info
 */
#define IAV_IOC_EFM_GET_POOL_INFO			IAVENC_IOR(IOC_EFM_PROC, struct iav_efm_get_pool_info *)

/*!
 *  This API can be invoked during preview/encoding state to get one EFM frame
 *  for processing.
 *  @param struct iav_efm_request_frame
 */
#define IAV_IOC_EFM_REQUEST_FRAME			IAVENC_IOWR(IOC_EFM_PROC, struct iav_efm_request_frame *)

/*!
 *  This API can be invoked during preview/encoding state to trigger DSP to start
 *  encoding the EFM stream.
 *  @param struct iav_efm_handshake_frame
 */
#define IAV_IOC_EFM_HANDSHAKE_FRAME			IAVENC_IOW(IOC_EFM_PROC, struct iav_efm_handshake_frame *)

/*!
 *  This API can be invoked during preview/encoding state to release all user
 *  requested frame buffers which are requested through IAV_IOC_EFM_REQUEST_FRAME.
 *  @param struct iav_efm_release_all_frame
 */
#define IAV_IOC_EFM_RELEASE_ALL_FRAMES		IAVENC_IOW(IOC_EFM_PROC, u8)
/*! @} */  /* End of iav-ioc-enc-use-efm */

/*!
 * @addtogroup iav-ioc-enc-use-efr
 * @{
 */
/*!
 *  This API can be invoked during IDLE state to set the raw encode config.
 *  @param struct iav_raw_enc_setup
 */
#define IAV_IOC_SET_RAW_ENCODE				IAVENC_IOW(IOC_RAW_ENC, struct iav_raw_enc_setup *)

/*!
 *  This API can be invoked during ANY state to get raw encode config.
 *  @param struct iav_raw_enc_setup
 */
#define IAV_IOC_GET_RAW_ENCODE				IAVENC_IOR(IOC_RAW_ENC, struct iav_raw_enc_setup *)

/*!
 *  This API can be invoked during ANY state to wait for the raw encode ready signal.
 *  @param none
 */
#define IAV_IOC_WAIT_RAW_ENCODE				IAVENC_IOW(IOC_RAW_ENC, u8)

/*! @} */  /* End of iav-ioc-enc-use-efr */

/*!
 * @addtogroup iav-ioc-enc-use-mem
 * @{
 */

/*!
 *  This API can be invoked during preview/encoding state to get one customized SEI buffer.
 *  @param struct iav_custom_sei_request_buf
 */
#define IAV_IOC_CUSTOM_SEI_REQUEST_BUF			IAVENC_IOWR(IOC_CUSTOM_SEI_PROC, struct iav_custom_sei_request_buf *)

/*!
 *  This API queries the frame-based data descriptions. The frame-based data
 *  includes frame bit stream data, frame statistic data, frame raw data, frame
 *  YUV data, frame ME1 data, and bit stream info data for smart rate control library.
 *  @param struct iav_querydesc
 */
#define IAV_IOC_QUERY_DESC					IAVENC_IOWR(IOC_QUERY_DESC, struct iav_querydesc *)

/*!
 *  This API can be used to configure the frame-based data descriptions before poll function.
 *  @param struct iav_poll_event_config
 */
#define IAV_IOC_SET_POLL_EVENT_CFG			IAVENC_IOW(IOC_POLL_EVENT_CFG, struct iav_poll_event_config *)

/*!
 *  This API can be used to clear the frame-based data descriptions after finish the poll job.
 *  @param none
 */
#define IAV_IOC_CLEAR_POLL_EVENT_CFG			IAVENC_IO(IOC_POLL_EVENT_CFG)

/*!
 *  This API queries the physical addresses for all the memory partitions shared
 *  between IAV and user application and the memory blocks of all canvases inside
 *  the DSP buffer. The start addresses, lengths, and data offsets of all memory
 *  partitions and canvases' YUV & ME are returned in information.
 *
 *  The application should further map the physical addresses into user space
 *  virtual addresses, before any operations on these buffers.
 *  @param struct iav_querymem
 */
#define IAV_IOC_QUERY_MEMBLOCK				IAVENC_IOWR(IOC_QUERY_MEMBLOCK, struct iav_querymem *)

/*!
 *  This API can be used during any state to allocate the IAV/DSP sub-partitions.
 *  @param struct iav_alloc_mem_part
 */
#define IAV_IOC_ALLOC_MEM_PART				IAVENC_IOWR(IOC_MEM_PART, u8)

/*!
 *  This API can be used during any state to allocate anonymous memory partitions.
 *  It allows user applications to allocate their own physically continuous memory.
 *  @param struct iav_alloc_mem_part
 */
#define IAV_IOC_ALLOC_ANON_MEM_PART			IAVENC_IOWR(IOC_ANON_MEM_PART, u32)

/*!
 *  This API can be used during any state to register anonymous memory partitions.
 *  For register, if the memory partition has been mapped, this api is no need to call.
 *  @param struct iav_anon_mem_part
 */
#define IAV_IOC_REGISTER_ANON_MEM_PART		IAVENC_IOWR(IOC_ANON_MEM_PART, u16)

/*!
 *  This API can be used during any state to unregister anonymous memory partitions.
 *  For unregister, the memory partition can not be unregistered before unmapping
 *  the mapped memory parition.
 *  @param struct iav_anon_mem_part
 */
#define IAV_IOC_UNREGISTER_ANON_MEM_PART	IAVENC_IOWR(IOC_ANON_MEM_PART, u8)

/*!
 *  This API can be used during any state to free up a specified IAV/DSP sub-
 *  partition or an anonymous memory partition.
 *  @param struct iav_free_mem_part
 */
#define IAV_IOC_FREE_MEM_PART				IAVENC_IOW(IOC_MEM_PART, struct iav_free_mem_part *)

/*!
 *  This API can be used during any state to clean/invalidate memory cache which
 *  is shared between DSP and ARM.
 *  @param struct iav_sync_cache_mem_part
 */
#define IAV_IOC_SYNC_CACHE_MEM_PART			IAVENC_IOW(IOC_SYNC_CACHE_MEM_PART, struct iav_sync_cache_mem_part *)

/*!
 *  This API can be used during any state to allocate anonymous memory partitions.
 *  It allows user applications to allocate their own physically continuous memory.
 *  As return parameter, it reports dma-buf:fd to user space.
 *  If user applications want to free the allocated memory partitions, just close
 *  their dma-buf:fd.
 *  @param struct iav_alloc_mem_part_fd
 */
#define IAV_IOC_ALLOC_ANON_MEM_PART_FD		IAVENC_IOWR(IOC_MEM_PART, u16)

/*!
 *  This API can be used during init state to configure the IAV memory layout. The supported
 *  IAV memory partitions include Multi-Color Mask, Mask, WARP, TML Fusion CLUT and QP matrix.
 *  This API decides the Multi-Color Mask, Mask, WARP, TML Fusion CLUT memory layout for different channels,
 *  and QP matrix memory layout for different streams.
 *  @param struct iav_mem_layout_resource
 */
#define IAV_IOC_SET_MEM_LAYOUT_RESOURCE		IAVENC_IOW(IOC_MEM_LAYOUT, struct iav_mem_layout_resource *)

/*!
 *  This API can be used to get the configuration of IAV memory layout resource. The supported IAV/DSP
 *  memory partitions inlude Multi-Color Mask, Mask, WARP, TML Fusion CLUT and QP matrix.
 *  @param struct iav_mem_layout_resource
 */
#define IAV_IOC_GET_MEM_LAYOUT_RESOURCE		IAVENC_IOR(IOC_MEM_LAYOUT, struct iav_mem_layout_resource *)

/*!
 *  This API can be used to query the IAV memory layout info. The supported IAV memory partitions include
 *  Multi-Color Mask, Mask, WARP, TML Fusion CLUT and QP matrix. When the memory layout info is not configured,
 *  this API also supports to query the memory layout info to achieve backward compatibility.
 *  @param struct iav_mem_layout_info
 */
#define IAV_IOC_QUERY_MEM_LAYOUT_INFO		IAVENC_IOWR(IOC_MEM_LAYOUT, struct iav_mem_layout_info *)

/*! @} */  /* End of iav-ioc-enc-use-mem */

/*!
 * @addtogroup iav-ioc-enc-use-stm
 * @{
 */

/*!
 *  This API can be invoked during the preview/encoding state to set stream configurations.
 *  All run time changeable configurations can be set via this IOCTL.
 *  @param struct iav_stream_cfg
 */
#define IAV_IOC_SET_STREAM_CONFIG			IAVENC_IOW(IOC_STREAM_CFG, struct iav_stream_cfg *)

/*!
 *  This API can be invoked during ANY state to get stream configurations.
 *  @param struct iav_stream_cfg
 */
#define IAV_IOC_GET_STREAM_CONFIG			IAVENC_IOWR(IOC_STREAM_CFG, struct iav_stream_cfg *)

/*!
 *  This API can be invoked during the stream idle state to perform H.264
 *  encoding configuration for a particular stream.
 *  @param struct iav_h26x_cfg
 */
#define IAV_IOC_SET_H264_CONFIG				IAVENC_IOW(IOC_H264_CFG, struct iav_h26x_cfg *)

/*!
 *  This API can be invoked during ANY state to read the H.264 encoding configuration.
 *  @param struct iav_h26x_cfg
 */
#define IAV_IOC_GET_H264_CONFIG				IAVENC_IOWR(IOC_H264_CFG, struct iav_h26x_cfg *)

/*!
 *  This API can be invoked during the stream idle state to perform H.265
 *  encoding configuration for a particular stream.
 *  @param struct iav_h26x_cfg
 */
#define IAV_IOC_SET_H265_CONFIG				IAVENC_IOW(IOC_H265_CFG, struct iav_h26x_cfg *)

/*!
 *  This API can be invoked during ANY state to read the H.265 encoding configuration.
 *  @param struct iav_h26x_cfg
 */
#define IAV_IOC_GET_H265_CONFIG				IAVENC_IOWR(IOC_H265_CFG, struct iav_h26x_cfg *)

/*!
 *  This API can be invoked during the stream idle state to configure MJPEG
 *  encoding quality and chrome format. The quality of the MJPEG can be configured
 *  while the streams are encoding.
 *
 *  In the CV2x & S6Lm implementation, MJPEG only supports YUV420 and mono-chrome format.
 *  @param struct iav_mjpeg_cfg
 */
#define IAV_IOC_SET_MJPEG_CONFIG			IAVENC_IOW(IOC_MJPEG_CFG, struct iav_mjpeg_cfg *)

/*!
 *  This API can be invoked during ANY state to read the MJPEG encoding quality
 *  and chroma format.
 *  @param struct iav_mjpeg_cfg
 */
#define IAV_IOC_GET_MJPEG_CONFIG			IAVENC_IOWR(IOC_MJPEG_CFG, struct iav_mjpeg_cfg *)

/*!
 *  This API can be invoked during the stream encoding state to feed JPEG service frame.
 *  @param struct iav_js_frame
 */
#define IAV_IOC_FEED_JPEG_SERVICE_FRAME		IAVENC_IOW(IOC_JPEG_SERVICE, struct iav_js_frame *)

/*!
 *  This API can be invoked during ANY state to get frame sync related parameters.
 *  @param struct iav_stream_cfg
 */
#define IAV_IOC_GET_FRAME_SYNC_PROC			IAVENC_IOWR(IOC_FRAME_SYNC, struct iav_stream_cfg *)

/*!
 *  This API can be invoked during ANY state to configure frame sync related parameters.
 *  This API is mainly used for application to prepare the encode parameters on the specified
 *  stream in frame accurate level. This API works with @ref IAV_IOC_GET_FRAME_SYNC_PROC
 *  and @ref IAV_IOC_APPLY_FRAME_SYNC_PROC.
 *  @param struct iav_stream_cfg
 */
#define IAV_IOC_CFG_FRAME_SYNC_PROC			IAVENC_IOW(IOC_FRAME_SYNC, struct iav_stream_cfg *)

/*!
 *  This API can be invoked during ENCODING state to configure frame sync related
 *  parameters for VDSP only. This API works with @ref IAV_IOC_GET_FRAME_SYNC_PROC
 *  and @ref IAV_IOC_CFG_FRAME_SYNC_PROC.
 *  @param struct iav_apply_frame_sync
 */
#define IAV_IOC_APPLY_FRAME_SYNC_PROC		IAVENC_IOW(IOC_FRAME_SYNC, u8)

/*!
 *  This API can be invoked during ENCODING state to configure frame sync related
 *  parameters between IDSP (like fisheye dewarp / DPTZ) and VDSP (like stream encode offset, custom_sei).
 *  The IDSP sync parameters (like fisheye dewarp / DPTZ) are configured by @ref IAV_IOC_CFG_WARP_CTRL,
 *  while the VDSP sync parameters are configured by @ref IAV_IOC_CFG_FRAME_SYNC_PROC.
 *  This API works when @ref @b strm_sync_type is set to IAV_IDSP_ENC_SYNC for the VDSP configuration.
 *  @param struct iav_apply_idsp_enc_sync
 */
#define IAV_IOC_APPLY_IDSP_ENC_SYNC_PROC	IAVENC_IOW(IOC_FRAME_SYNC, u16)

/*!
 *  This API can be invoked during preview/encoding state to get the suggested FPS for each stream.
 *  IAV driver will calculate the internal system resource budget and give the proper suggestion for
 *  stream frame rate.
 *  @param struct iav_fps_suggest
 */
#define IAV_IOC_GET_FPS_SUGGEST				IAVENC_IOWR(IOC_FPS_SUGGEST, struct iav_fps_suggest *)

/*!
 *  This API can be invoked during preview/encoding state to release the locked frames of bitstream.
 *  Currently, it's used for release the frame user queried and consumed before, IAV driver will decide
 *  to release the frame or not according to the frame match result, which refer to frame info like @size,
 *  @data_addr_offset, @enc_done_ts, @frame_num, etc.
 *  @param struct iav_framedesc
 */
#define IAV_IOC_RELEASE_FRAMEDESC 				IAVENC_IOWR(IOC_FRAMEDESC_CTRL, struct iav_framedesc *)

/*!
 *  This API can be invoked during preview/encoding state to flush the frame_queue and frame_lock_queue
 *  of bitstream. Ambarella suggests it can be called when user start or restart to query frames, so that
 *  user can always get the latest frames.
 *  @param none
 */
#define IAV_IOC_FLUSH_FRAMEDESC 				IAVENC_IOWR(IOC_FRAMEDESC_CTRL, u16)

/*! @} */  /* End of iav-ioc-enc-use-stm */

/*!
 * @addtogroup iav-ioc-enc-use-ovl
 * @{
 */

/*!
 *  These API can be used to insert a selected picture into the video stream as
 *  an overlay.  It is intended for the OSD overlay library use, and it is
 *  supported by H.264, H. 265 and MJPEG.  Because the picture data is added to
 *  the video data before encoding, it is also referred to as "OSD blending".
 *
 *  It is the responsibility of the application to draw different overlay content
 *  in the memory partition.  The application needs to call the "mmap" system in
 *  order to map the overlay memory partition before drawing the new content.
 *
 *  In CV2x implementation, the overlay is added to the source buffer. This means
 *  that if the two streams share the same source buffer, the OSD overlay will
 *  be affected. Refer to user guide documentation for details.
 *  @param struct iav_overlay_insert
 */
#define IAV_IOC_SET_OVERLAY_INSERT			IAVENC_IOW(IOC_OVERLAY_INSERT, struct iav_overlay_insert *)

/*!
 *  This API can be used to retrieve the overlay information that has already
 *  been inserted into the specified video stream.
 *  @param struct iav_overlay_insert
 */
#define IAV_IOC_GET_OVERLAY_INSERT			IAVENC_IOWR(IOC_OVERLAY_INSERT, struct iav_overlay_insert *)

/*!
 *  This API is similar to IAV_IOC_SET_OVERLAY_INSERT. The only difference is
 *  FastOSD: the API tells DSP the specific region and number of regions that
 *  need to perform FastOSD.
 *  @param struct iav_fastosd_insert
 */
#define IAV_IOC_SET_FASTOSD_INSERT			IAVENC_IOW(IOC_FASTOSD_INSERT, struct iav_fastosd_insert *)

/*!
 *  This API can be used to retrieve the fast osd information that has already
 *  been inserted into the specified video stream.
 *  @param struct iav_fastosd_insert
 */
#define IAV_IOC_GET_FASTOSD_INSERT			IAVENC_IOWR(IOC_FASTOSD_INSERT, struct iav_fastosd_insert *)

/*!
 *  This API can be used to insert blur areas into a video stream where there are privacy areas that
 *  need to be protected. Once blur areas are inserted, the covered stream areas will be blurred heavily.
 *  It can be supported by H.264, H.265 and MJPEG.
 *  @param struct iav_blur_insert
 */
#define IAV_IOC_SET_BLUR_INSERT			IAVENC_IOW(IOC_BLUR_INSERT, struct iav_blur_insert *)

/*!
 *  This API can be used to retrieve the blur information that has already
 *  been inserted into the specified video stream.
 *  @param struct iav_blur_insert
 */
#define IAV_IOC_GET_BLUR_INSERT			IAVENC_IOWR(IOC_BLUR_INSERT, struct iav_blur_insert *)

/*!
 *  This API can be used to configure blur color tables.
 *  @param struct iav_blur_color
 */
#define IAV_IOC_SET_BLUR_COLOR			IAVENC_IOW(IOC_BLUR_INSERT, u8)

/*!
 *  This API can be used to retrieve the blur color tables.
 *  @param struct iav_blur_color
 */
#define IAV_IOC_GET_BLUR_COLOR			IAVENC_IOR(IOC_BLUR_INSERT, u8)
/*! @} */  /* End of iav-ioc-enc-use-ovl */

/*!
 * @addtogroup iav-ioc-enc-use-vcap
 * @{
 */

/*!
 *  This API can be invoked during @b IDLE state to set the VCAP configuration.
 *  @param struct iav_vcap_cfg
 */
#define IAV_IOC_SET_VCAP_CFG				IAVENC_IOW(IOC_VCAP_CFG, struct iav_vcap_cfg *)

/*!
 *  This API can be invoked during @b ANY state to get the VCAP config.
 *  @param struct iav_vcap_cfg
 */
#define IAV_IOC_GET_VCAP_CFG				IAVENC_IOWR(IOC_VCAP_CFG, struct iav_vcap_cfg *)
/*! @} */  /* End of iav-ioc-enc-use-vcap */

/*!
 * @addtogroup iav-ioc-enc-use-warp IAV WARP
 * @{
 */

/*!
 *  This API can be invoked during preview/encode state to configure the LDC (single
 *  region) warp and fisheye (multi-region) warp parameters.
 *  @param struct iav_warp_ctrl
 */
#define IAV_IOC_CFG_WARP_CTRL				IAVENC_IOW(IOC_WARP_CTRL, struct iav_warp_ctrl *)

/*!
 *  This API can be invoked during preview/encode state to get the LDC (single region)
 *  warp and fisheye (multi-region) warp parameters.
 *  @param struct iav_warp_ctrl
 */
#define IAV_IOC_GET_WARP_CTRL				IAVENC_IOWR(IOC_WARP_CTRL, struct iav_warp_ctrl *)

/*!
 *  This API can be invoked during the preview/encode state to APPLY LDC (single
 *  region) warp and fisheye (multi-region) warp parameters.
 *  @param struct iav_apply_flag
 */
#define IAV_IOC_APPLY_WARP_CTRL				IAVENC_IOW(IOC_WARP_CTRL, u8)

/*!
 *  This API can be invoked to APPLY LDC (single region) warp and fisheye (multi-region)
 *  warp parameters with frame sync mechanism at IDSP stage during the preview/encode state .
 *  For those operations without frame sync mechanism, APP can still call IAV_IOC_APPLY_WARP_CTRL
 *  cmd as before.  This API is only used for frame sync mechanism. And it MUST work with
 *  IAV_IOC_CFG/GET_WARP_CTRL APIs.
 *  @param struct iav_apply_frame_sync_flag
 */
#define IAV_IOC_APPLY_WARP_CTRL_IDSP_FRAME_SYNC		IAVENC_IOWR(IOC_WARP_CTRL, u8)
/*! @} */  /* End of iav-ioc-enc-use-warp */

/*!
 * @addtogroup iav-ioc-enc-use-vproc IAV VPROC
 * @{
 */

/*!
 *  This API can be invoked during ANY state to get configurations of Privacy Mask,
 *  DPTZ(digital pan / tile / zoom), Canvas Channel Order, Multi-Channel Blend,
 *  pyramid ROI and so on.
 *  @param struct iav_video_proc
 */
#define IAV_IOC_GET_VIDEO_PROC				IAVENC_IOWR(IOC_VIDEO_PROC, struct iav_video_proc *)

/*!
 *  This API can be invoked during ANY state to configure Privacy Mask,
 *  DPTZ(digital pan / tile / zoom), Canvas Channel Order, Multi-Channel Blend
 *  and so on at run-time.  When all configurations are configured through this
 *  API during PREVIEW/ENCODING state, API IAV_IOC_APPLY_VIDEO_PROC should be
 *  invoked to kick off these configurations to DSP.
 *  @param struct iav_video_proc
 */
#define IAV_IOC_CFG_VIDEO_PROC				IAVENC_IOW(IOC_VIDEO_PROC, struct iav_video_proc *)

/*!
 *  This API can be invoked during PREVIEW/ENCODING state to kick off the
 *  configurations set by API IAV_IOC_CFG_VIDEO_PROC to DSP at run-time.
 *  @param struct iav_apply_flag flags[IAV_VIDEO_PROC_NUM]
 */
#define IAV_IOC_APPLY_VIDEO_PROC			IAVENC_IOW(IOC_VIDEO_PROC, u8)
/*! @} */  /* End of iav-ioc-enc-use-vproc */

/*!
 * @addtogroup iav-ioc-enc-use-vin
 * @{
 */

/*!
 *  This API can be invoked to set vin idsp cfg.
 *  @param struct iav_vin_idsp_config
 */
#define IAV_IOC_SET_VIN_IDSP_CFG			IAVENC_IOW(IOC_VIN_IDSP, struct iav_vin_idsp_config *)

/*!
 *  This API can be invoked get the vin idsp cfg.
 *  @param struct iav_vin_idsp_config
 */
#define IAV_IOC_GET_VIN_IDSP_CFG			IAVENC_IOWR(IOC_VIN_IDSP, struct iav_vin_idsp_config *)

/*!
 *  This API can be invoked to set idsp delay info
 *  warp parameters.
 *  @param struct iav_vin_idsp_delay_info
 */
#define IAV_IOC_SET_VIN_IDSP_DELAY_INFO		IAVENC_IOW(IOC_VIN_IDSP, u8)

/*!
 *  This API can be invoked during the PREVIEW / ENCODING state to wait until the
 *  next valid IDSP frame.  It is useful for applications that need to synchronize
 *  with the IDSP frame rate.
 *
 *  For multi-channel cases, when the IDSP resampling frame rate feature is enabled
 *  and the channels have different IDSP resampling frame rates, ensure the application
 *  specifies the channel ID, because the next frame will need to wait. The application
 *  can also specify a channel map for multi-channel cases. If this is the case,
 *  the IAV driver will wait for the next frame of the channel with the lowest
 *  IDSP frame rate.
 *  @param u16(not pointer) : is channels map
 */
#define IAV_IOC_WAIT_NEXT_IDSP_FRAME		IAVENC_IOW(IOC_WAIT_IDSP_FRAME, u8)

/*!
 *  This API can be invoked during preview/encode state to set the VIN compand
 *  configuration parameters.
 *  @param struct iav_vin_compand_config
 */
#define IAV_IOC_SET_VIN_COMPAND_CFG			IAVENC_IOW(IOC_VIN_COMP, struct iav_vin_compand_config *)

/*!
 *  This API can be invoked during preview/encode state to get the VIN compand
 *  configuration parameters.
 *  @param struct iav_vin_compand_config
 */
#define IAV_IOC_GET_VIN_COMPAND_CFG			IAVENC_IOWR(IOC_VIN_COMP, struct iav_vin_compand_config *)
/*! @} */  /* End of iav-ioc-enc-use-vin */

/*!
 * @addtogroup iav-ioc-enc-use-dbg
 * @{
 */
/*!
 *  This API can be invoked during any state to set the IAV debug configuration.
 *  @param struct iav_debug_cfg
 */
#define IAV_IOC_SET_DEBUG_CONFIG			IAVENC_IOW(IOC_DEBUG, struct iav_debug_cfg *)

/*!
 *  This API can be invoked during any state to fetch the IAV debug configuration.
 *  @param struct iav_debug_cfg
 */
#define IAV_IOC_GET_DEBUG_CONFIG			IAVENC_IOR(IOC_DEBUG, struct iav_debug_cfg *)
/*! @} */  /* End of iav-ioc-enc-use-dbg */

/*!
 * @addtogroup iav-ioc-enc-tml
 * @{
 */
/*!
 *  This API can be invoked during preview/encode state to set tml configuration.
 *  @param struct iav_tml_proc_cfg
 */
#define IAV_IOC_SET_TML_CONFIG			IAVENC_IOW(IOC_TML, struct iav_tml_proc_cfg *)

/*!
 *  This API can be invoked during any state to fetch tml configuration.
 *  @param struct iav_tml_proc_cfg
 */
#define IAV_IOC_GET_TML_CONFIG			IAVENC_IOR(IOC_TML, struct iav_tml_proc_cfg *)
/*! @} */  /* End of iav-ioc-enc-tml */

/*!
 * @addtogroup iav-ioc-enc-use-usr
 * @{
 */

/*!
 *  This API can be invoked for customized commands.
 *  @param struct iav_custom_cfg
 */
#define IAV_IOC_CUSTOM_CMDS					IAVENC_IOWR(IOC_CUSTOM, struct iav_custom_cfg *)
/*! @} */  /* End of iav-ioc-enc-use-usr */



/*!
 * @addtogroup iav-ioctl-dec-helper
 * @{
 */
#define IAVDECIOC_MAGIC				'D'
#define IAVDEC_IO(nr)				_IO(IAVDECIOC_MAGIC, nr)
#define IAVDEC_IOR(nr, size)		_IOR(IAVDECIOC_MAGIC, nr, size)
#define IAVDEC_IOW(nr, size)		_IOW(IAVDECIOC_MAGIC, nr, size)
#define IAVDEC_IOWR(nr, size)		_IOWR(IAVDECIOC_MAGIC, nr, size)

typedef enum {
	/* For decode control (0x00 ~ 0x1F) */
	IOC_ENTER_DECODE_MODE			= 0x00, /*!< 0x00,  For decode control (0x00 ~ 0x1F) */
	IOC_LEAVE_DECODE_MODE			= 0x01, /*!< 0x01 */
	IOC_CREATE_DECODER				= 0x02, /*!< 0x02 */
	IOC_DESTROY_DECODER				= 0x03, /*!< 0x03 */
	IOC_DECODE_START				= 0x04, /*!< 0x04 */
	IOC_DECODE_STOP					= 0x05, /*!< 0x05 */
	IOC_DECODE_VIDEO				= 0x06, /*!< 0x06 */
	IOC_DECODE_JPEG					= 0x07, /*!< 0x07 */
	IOC_WAIT_DECODE_BSB				= 0x08, /*!< 0x08 */
	IOC_INTRAPLAY_RESET_BUFFERS		= 0x09, /*!< 0x09 */
	IOC_INTRAPLAY_REQUEST_BUFFER	= 0x0A, /*!< 0x0A */
	IOC_INTRAPLAY_DECODE			= 0x0B, /*!< 0x0B */
	IOC_INTRAPLAY_YUV2YUV			= 0x0C, /*!< 0x0C */
	IOC_INTRAPLAY_DISPLAY			= 0x0D, /*!< 0x0D */
	IOC_DECODE_TRICK_PLAY			= 0x0E, /*!< 0x0E */
	IOC_DECODE_SPEED				= 0x0F, /*!< 0x0F */
	IOC_WAIT_PLAYBACK_EOS			= 0x10, /*!< 0x10 */
	IOC_DECODE_ZOOM				= 0x11, /*!< 0x11 */

	/* For decode status (0x30 ~ 0x3F) */
	IOC_QUERY_DECODE_STATUS			= 0x30, /*!< 0x30, For decode status (0x30 ~ 0x3F) */
	IOC_QUERY_DECODE_BSB			= 0x31, /*!< 0x31 */
} IAV_DEC_IOC;

/*! @} */ /* iav-ioctl-dec-helper */

/*! @addtogroup iav-ioctl-dec-api
 * @{
 */

/*!
 *  This API can be invoked to allow the video to enter the decode mode.
 *  This transition can only be done when the DSP is in the idle mode or after it boots up.
 *  @param struct iav_decode_mode_config
 */
#define IAV_IOC_ENTER_DECODE_MODE			IAVDEC_IOWR(IOC_ENTER_DECODE_MODE, struct iav_decode_mode_config *)

/*!
 *  This API can be invoked to leave the decode mode. Only when the DSP in the decode mode, this transition can be done.
 *  It will make the DSP go into the idle mode.
 *  @param none
 */
#define IAV_IOC_LEAVE_DECODE_MODE			IAVDEC_IO(IOC_LEAVE_DECODE_MODE)

/*!
 *  This API can be invoked to create a decoder instance.
 *  Only when the DSP is in the decode mode, this API is valid.
 *  @param struct iav_decoder_info
 */
#define IAV_IOC_CREATE_DECODER				IAVDEC_IOWR(IOC_CREATE_DECODER, struct iav_decoder_info *)

/*!
 *  This API can be invoked to destroy a decoder instance and it is valid only when the DSP is in the decode mode.
 *  @param u8(not pointer)
 */
#define IAV_IOC_DESTROY_DECODER				IAVDEC_IOW(IOC_DESTROY_DECODER, u8)

/*!
 *  This API can be invoked to start the decode process and it is valid only when the DSP in the decode mode.
 *  @param u8(not pointer)
 */
#define IAV_IOC_DECODE_START				IAVDEC_IOW(IOC_DECODE_START, u8)

/*!
 *  This API can be invoked to stop the decode process and it is only valid when the DSP is in the decode mode.
 *  @param struct iav_decode_stop
 */
#define IAV_IOC_DECODE_STOP					IAVDEC_IOW(IOC_DECODE_STOP, struct iav_decode_stop *)


/*!
 *  This API can be invoked to decode the video bitstream.
 *  It is only valid when DSP is in the decode mode.
 *  @param struct iav_decode_video
 */
#define IAV_IOC_DECODE_VIDEO				IAVDEC_IOW(IOC_DECODE_VIDEO, struct iav_decode_video *)

/*!
 *  This API can be invoked to decode JPEG bit stream.
 *  This API is valid only when the DSP is in the decode mode.
 *  @param struct iav_decode_jpeg
 */
#define IAV_IOC_DECODE_JPEG					IAVDEC_IOW(IOC_DECODE_JPEG, struct iav_decode_jpeg *)

/*!
 *  This API can be invoked for a wait-free zoom in the bitstream buffer.
 *  This API is valid only when DSP is in the decode mode.
 *  @param struct iav_decode_bsb
 */
#define IAV_IOC_WAIT_DECODE_BSB				IAVDEC_IOWR(IOC_WAIT_DECODE_BSB, struct iav_decode_bsb *)

/*!
 *  This API can be invoked to perform trick play in the playback.
 *  It is only valid when the DSP is in the decode mode.
 *  @param struct iav_decode_trick_play
 */
#define IAV_IOC_DECODE_TRICK_PLAY			IAVDEC_IOW(IOC_DECODE_TRICK_PLAY, struct iav_decode_trick_play *)

/*!
 *  This API can be invoked to update the playback speed and direction.
 *  This API is valid only when the DSP is in the decode mode.
 *  @param struct iav_decode_speed
 */
#define IAV_IOC_DECODE_SPEED				IAVDEC_IOW(IOC_DECODE_SPEED, struct iav_decode_speed *)

/*!
 *  This API can be invoked to query decoding status and it is only valid when the DSP is in the decode mode.
 *  @param struct iav_decode_status
 */
#define IAV_IOC_QUERY_DECODE_STATUS			IAVDEC_IOR(IOC_QUERY_DECODE_STATUS, struct iav_decode_status *)

/*!
 *  This API can be invoked to query the bitstream buffer and it is only valid when the DSP is in the decode mode.
 *  @param struct iav_decode_bsb
 */
#define IAV_IOC_QUERY_DECODE_BSB			IAVDEC_IOR(IOC_QUERY_DECODE_BSB, struct iav_decode_bsb *)

/*!
 *  This API can be invoked to wait until the total stream is decoded by DSP.  It is only valid when the DSP is in the decode mode.
 *  @param struct iav_decode_wait_eos
 */
#define IAV_IOC_WAIT_PLAYBACK_EOS			IAVDEC_IOW(IOC_WAIT_PLAYBACK_EOS, struct iav_decode_wait_eos *)

/*!
 *  This API can be invoked to zoom in/out vout output.  It is only valid when the DSP is in the decode mode.
 *  @param struct iav_decode_zoom_desc
 */
#define IAV_IOC_DECODE_ZOOM                            IAVDEC_IOW(IOC_DECODE_ZOOM, struct iav_decode_zoom_desc *)

#define IAV_IOC_INTRAPLAY_RESET_BUFFERS		IAVDEC_IOW(IOC_INTRAPLAY_RESET_BUFFERS, struct iav_intraplay_reset_buffers *)
#define IAV_IOC_INTRAPLAY_REQUEST_BUFFER	IAVDEC_IOWR(IOC_INTRAPLAY_REQUEST_BUFFER, struct iav_intraplay_frame_buffer *)
#define IAV_IOC_INTRAPLAY_DECODE			IAVDEC_IOW(IOC_INTRAPLAY_DECODE, struct iav_intraplay_decode *)
#define IAV_IOC_INTRAPLAY_YUV2YUV			IAVDEC_IOW(IOC_INTRAPLAY_YUV2YUV, struct iav_intraplay_yuv2yuv *)
#define IAV_IOC_INTRAPLAY_DISPLAY			IAVDEC_IOW(IOC_INTRAPLAY_DISPLAY, struct iav_intraplay_display *)
/*! @} */ /* End of iav-ioctl-dec-api */

#ifdef __cplusplus
}
#endif

#endif
