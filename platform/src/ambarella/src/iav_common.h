/*
 * iav_common.h
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

#ifndef __IAV_COMMON_H__
#define __IAV_COMMON_H__
/*! @file iav_common.h
 *  @brief This file defines common enumerations used in all IAV driver and header files
 */

#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup iav-common-helper
 * @{
 */

/** @enum amba_chip_arch
 *  @brief AMBA CHIP ARCH definition
 */
enum amba_chip_arch {
	AMBA_CHIP_ARCH_UNKNOWN	= 0xFFFF, /*!< 0xFFFF */
	AMBA_CHIP_ARCH_S5 		= 11000, /*!< 11000 */
	AMBA_CHIP_ARCH_S2L		= 12000, /*!< 12000 */
	AMBA_CHIP_ARCH_S3L		= 13000, /*!< 13000 */
	AMBA_CHIP_ARCH_S5L		= 16000, /*!< 16000 */
	AMBA_CHIP_ARCH_S6LM		= 17000, /*!< 17000 */
	AMBA_CHIP_ARCH_CV1		= 20000, /*!< 20000 */
	AMBA_CHIP_ARCH_CV2		= 21000, /*!< 21000 */
	AMBA_CHIP_ARCH_CV22		= 22000, /*!< 22000 */
	AMBA_CHIP_ARCH_CV25		= 25000, /*!< 25000 */
	AMBA_CHIP_ARCH_CV2FS	= 26000, /*!< 26000 */
	AMBA_CHIP_ARCH_CV28		= 27000, /*!< 27000 */
	AMBA_CHIP_ARCH_CV5		= 30000, /*!< 30000 */
};

/*! @enum amba_video_format
 *  @brief AMBA Video Format Enumerations
 */
enum amba_video_format {
	AMBA_VIDEO_FORMAT_AUTO			= 0, /*!< 0 */
	AMBA_VIDEO_FORMAT_INTERLACE		= 1, /*!< 1 */
	AMBA_VIDEO_FORMAT_PROGRESSIVE		= 2, /*!< 2 */
};

/*! @enum amba_video_type
 *  @brief AMBA Video Type Enumerations
 */
enum amba_video_type {
	AMBA_VIDEO_TYPE_AUTO		= 0, /*!< 0 */
	AMBA_VIDEO_TYPE_YUV_601		= 1, /*!< 1 */
	AMBA_VIDEO_TYPE_YUV_656		= 2, /*!< 2 */
	AMBA_VIDEO_TYPE_RGB_601		= 3, /*!< 3 */
	AMBA_VIDEO_TYPE_RGB_656		= 4, /*!< 4 */
	AMBA_VIDEO_TYPE_RGB_RAW		= 5, /*!< 5 */
	AMBA_VIDEO_TYPE_YUV_BT1120	= 6, /*!< 6 */
	AMBA_VIDEO_TYPE_RGB_BT1120	= 7, /*!< 7 */
};

/*! @macros AMBA_VIDEO_FPS(fps)
 *  @brief Formula of video fps.Input fps would be in enum amba_video_fps
 */
#define AMBA_VIDEO_FPS(fps)			(DIV_ROUND(512000000, fps))

/*! @enum amba_video_fps
 *  @brief AMBA Video FPS Enumerations
 */
enum amba_video_fps {
	AMBA_VIDEO_FPS_AUTO		= 0, /*!< 0 */
	AMBA_VIDEO_FPS_1		= 512000000, /*!< 512000000 */
	AMBA_VIDEO_FPS_2		= 256000000, /*!< 256000000 */
	AMBA_VIDEO_FPS_3		= 170666667, /*!< 170666667 */
	AMBA_VIDEO_FPS_4		= 128000000, /*!< 128000000 */
	AMBA_VIDEO_FPS_5		= 102400000, /*!< 102400000 */
	AMBA_VIDEO_FPS_6		= 85333334, /*!< 85333334 */
	AMBA_VIDEO_FPS_7		= 73142858, /*!< 73142858 */
	AMBA_VIDEO_FPS_8		= 64000000, /*!< 64000000 */
	AMBA_VIDEO_FPS_9		= 56888889, /*!< 56888889 */
	AMBA_VIDEO_FPS_10		= 51200000, /*!< 51200000 */
	AMBA_VIDEO_FPS_11		= 46545455, /*!< 46545455 */
	AMBA_VIDEO_FPS_12		= 42666667, /*!< 42666667 */
	AMBA_VIDEO_FPS_13		= 39384616, /*!< 39384616 */
	AMBA_VIDEO_FPS_14		= 36571429, /*!< 36571429 */
	AMBA_VIDEO_FPS_15		= 34133334, /*!< 34133334 */
	AMBA_VIDEO_FPS_16		= 32000000, /*!< 32000000 */
	AMBA_VIDEO_FPS_17		= 30117648, /*!< 30117648 */
	AMBA_VIDEO_FPS_18		= 28444445, /*!< 28444445 */
	AMBA_VIDEO_FPS_19		= 26947369, /*!< 26947369 */
	AMBA_VIDEO_FPS_20		= 25600000, /*!< 25600000 */
	AMBA_VIDEO_FPS_21		= 24380953, /*!< 24380953 */
	AMBA_VIDEO_FPS_22		= 23272728, /*!< 23272728 */
	AMBA_VIDEO_FPS_23		= 22260870, /*!< 22260870 */
	AMBA_VIDEO_FPS_24		= 21333334, /*!< 21333334 */
	AMBA_VIDEO_FPS_25		= 20480000, /*!< 20480000 */
	AMBA_VIDEO_FPS_26		= 19692308, /*!< 19692308 */
	AMBA_VIDEO_FPS_27		= 18962963, /*!< 18962963 */
	AMBA_VIDEO_FPS_28		= 18285715, /*!< 18285715 */
	AMBA_VIDEO_FPS_29		= 17655173, /*!< 17655173 */
	AMBA_VIDEO_FPS_30		= 17066667, /*!< 17066667 */
	AMBA_VIDEO_FPS_40		= 12800000, /*!< 12800000 */
	AMBA_VIDEO_FPS_45		= 11377778, /*!< 11377778 */
	AMBA_VIDEO_FPS_50		= 10240000, /*!< 10240000 */
	AMBA_VIDEO_FPS_54		= 9481482, /*!< 9481482 */
	AMBA_VIDEO_FPS_55		= 9309091, /*!< 9309091 */
	AMBA_VIDEO_FPS_60		= 8533334, /*!< 8533334 */
	AMBA_VIDEO_FPS_90		= 5688889, /*!< 5688889 */
	AMBA_VIDEO_FPS_100		= 5120000, /*!< 5120000 */
	AMBA_VIDEO_FPS_120		= 4266667, /*!< 4266667 */
	AMBA_VIDEO_FPS_180		= 2844445, /*!< 2844445 */
	AMBA_VIDEO_FPS_239		= 2142260, /*!< 2142260 */
	AMBA_VIDEO_FPS_240		= 2133334, /*!< 2133334 */
	AMBA_VIDEO_FPS_480		= 1066667, /*!< 1066667 */
	AMBA_VIDEO_FPS_29_97		= 17083750, /*!< 17083750 */
	AMBA_VIDEO_FPS_59_94		= 8541875, /*!< 8541875 */
	AMBA_VIDEO_FPS_23_976		= 21354688, /*!< 21354688 */
	AMBA_VIDEO_FPS_12_5		= 40960000, /*!< 40960000 */
	AMBA_VIDEO_FPS_6_25		= 81920000, /*!< 81920000 */
	AMBA_VIDEO_FPS_3_125		= 163840000, /*!< 163840000 */
	AMBA_VIDEO_FPS_7_5		= 68266667, /*!< 68266667 */
	AMBA_VIDEO_FPS_3_75		= 136533333, /*!< 136533333 */
	AMBA_VIDEO_FPS_1_5625		= 327680000, /*!< 327680000 */
};

/*! @enum amba_video_mode
 *  @brief AMBA Video Mode Enumerations
 */
enum amba_video_mode {
	AMBA_VIDEO_MODE_AUTO		= 0,		/*!< 0, default mode*/

	AMBA_VIDEO_MODE_240_400,
	AMBA_VIDEO_MODE_320_240,
	AMBA_VIDEO_MODE_320_288,
	AMBA_VIDEO_MODE_320_480,
	AMBA_VIDEO_MODE_360_240,
	AMBA_VIDEO_MODE_360_288,
	AMBA_VIDEO_MODE_480_240,
	AMBA_VIDEO_MODE_480_640,
	AMBA_VIDEO_MODE_480_800,
	AMBA_VIDEO_MODE_640_480,
	AMBA_VIDEO_MODE_640_512,
	AMBA_VIDEO_MODE_720_240,
	AMBA_VIDEO_MODE_720_480,
	AMBA_VIDEO_MODE_720_576,
	AMBA_VIDEO_MODE_720_1280,
	AMBA_VIDEO_MODE_800_480,
	AMBA_VIDEO_MODE_800_1280,
	AMBA_VIDEO_MODE_848_480,
	AMBA_VIDEO_MODE_800_600,
	AMBA_VIDEO_MODE_960_240,
	AMBA_VIDEO_MODE_960_540,
	AMBA_VIDEO_MODE_1024_600,
	AMBA_VIDEO_MODE_1024_768,
	AMBA_VIDEO_MODE_1152_576,
	AMBA_VIDEO_MODE_1152_648,
	AMBA_VIDEO_MODE_1280_320,
	AMBA_VIDEO_MODE_1280_720,
	AMBA_VIDEO_MODE_1280_800,
	AMBA_VIDEO_MODE_1280_960,
	AMBA_VIDEO_MODE_1280_1024,
	AMBA_VIDEO_MODE_1296_1032,
	AMBA_VIDEO_MODE_1400_1050,
	AMBA_VIDEO_MODE_1440_900,
	AMBA_VIDEO_MODE_1600_1200,
	AMBA_VIDEO_MODE_1600_1600,
	AMBA_VIDEO_MODE_1632_1632,
	AMBA_VIDEO_MODE_1640_1232,
	AMBA_VIDEO_MODE_1680_1050,
	AMBA_VIDEO_MODE_1728_486,
	AMBA_VIDEO_MODE_1920_1080,
	AMBA_VIDEO_MODE_1920_1200,
	AMBA_VIDEO_MODE_1920_1440,
	AMBA_VIDEO_MODE_1920_1920,
	AMBA_VIDEO_MODE_2048_1080,
	AMBA_VIDEO_MODE_2048_1152,
	AMBA_VIDEO_MODE_2048_1536,
	AMBA_VIDEO_MODE_2048_2048,
	AMBA_VIDEO_MODE_2208_1242,
	AMBA_VIDEO_MODE_2304_1296,
	AMBA_VIDEO_MODE_2304_1536,
	AMBA_VIDEO_MODE_2304_1728,
	AMBA_VIDEO_MODE_2432_2048,
	AMBA_VIDEO_MODE_2520_1424,
	AMBA_VIDEO_MODE_2560_800,
	AMBA_VIDEO_MODE_2560_1440,
	AMBA_VIDEO_MODE_2560_2048,
	AMBA_VIDEO_MODE_2592_1944,
	AMBA_VIDEO_MODE_2688_1512,
	AMBA_VIDEO_MODE_2688_1520,
	AMBA_VIDEO_MODE_2688_1944,
	AMBA_VIDEO_MODE_3072_1728,
	AMBA_VIDEO_MODE_3072_2048,
	AMBA_VIDEO_MODE_3280_1852,
	AMBA_VIDEO_MODE_3280_2464,
	AMBA_VIDEO_MODE_3840_2160,
	AMBA_VIDEO_MODE_4000_3000,
	AMBA_VIDEO_MODE_4016_3016,
	AMBA_VIDEO_MODE_4096_2160,
	AMBA_VIDEO_MODE_5472_3648,
	AMBA_VIDEO_MODE_7680_4320,
	AMBA_VIDEO_MODE_1920_2160,
	AMBA_VIDEO_MODE_3008_3000,
	AMBA_VIDEO_MODE_1792_1792,
	AMBA_VIDEO_MODE_2000_1118,
	AMBA_VIDEO_MODE_1312_996,
	AMBA_VIDEO_MODE_1920_480,
	AMBA_VIDEO_MODE_1920_640,
	AMBA_VIDEO_MODE_1920_720,
	AMBA_VIDEO_MODE_3264_2448,
	AMBA_VIDEO_MODE_1856_1856,
	AMBA_VIDEO_MODE_3008_3008,
	AMBA_VIDEO_MODE_1536_1536,
	AMBA_VIDEO_MODE_2176_2160,
	AMBA_VIDEO_MODE_2880_1856,
	AMBA_VIDEO_MODE_2432_2064,
	AMBA_VIDEO_MODE_1952_1112,
	AMBA_VIDEO_MODE_1200_1920,
	AMBA_VIDEO_MODE_1824_944,
	AMBA_VIDEO_MODE_1280_1080,
	AMBA_VIDEO_MODE_6016_4008,
	AMBA_VIDEO_MODE_4768_3184,
	AMBA_VIDEO_MODE_1280_1000,
	AMBA_VIDEO_MODE_2592_1440,
	AMBA_VIDEO_MODE_2880_1080,
	AMBA_VIDEO_MODE_2592_1456,
	AMBA_VIDEO_MODE_1920_1216,
	AMBA_VIDEO_MODE_2880_1128,
	AMBA_VIDEO_MODE_1920_1096,
	AMBA_VIDEO_MODE_2880_1872,
	AMBA_VIDEO_MODE_1280_3840,
	AMBA_VIDEO_MODE_9568_6376,
	AMBA_VIDEO_MODE_9568_5384,
	AMBA_VIDEO_MODE_3072_3064,
	AMBA_VIDEO_MODE_2048_1552,
	AMBA_VIDEO_MODE_4096_3072,
	AMBA_VIDEO_MODE_3840_1920,
	AMBA_VIDEO_MODE_3072_3040,
	AMBA_VIDEO_MODE_2048_1944,
	AMBA_VIDEO_MODE_2112_2112,
	AMBA_VIDEO_MODE_1920_1088,
	AMBA_VIDEO_MODE_1280_768,
	AMBA_VIDEO_MODE_2560_768,
	AMBA_VIDEO_MODE_1728_2336,
	AMBA_VIDEO_MODE_3264_1832,
	AMBA_VIDEO_MODE_2560_720,
	AMBA_VIDEO_MODE_3840_1080,
	AMBA_VIDEO_MODE_1920_1536,
	AMBA_VIDEO_MODE_2880_1616,

	AMBA_VIDEO_MODE_NUM,

	/* alias name */
	AMBA_VIDEO_MODE_HVGA		= AMBA_VIDEO_MODE_320_480, /*!< AMBA_VIDEO_MODE_320_480 */
	AMBA_VIDEO_MODE_VGA			= AMBA_VIDEO_MODE_640_480, /*!< AMBA_VIDEO_MODE_640_480 */
	AMBA_VIDEO_MODE_WVGA		= AMBA_VIDEO_MODE_800_480, /*!< AMBA_VIDEO_MODE_800_480 */
	AMBA_VIDEO_MODE_SVGA		= AMBA_VIDEO_MODE_800_600, /*!< AMBA_VIDEO_MODE_800_600 */
	AMBA_VIDEO_MODE_WSVGA		= AMBA_VIDEO_MODE_1024_600, /*!< AMBA_VIDEO_MODE_1024_600 */
	AMBA_VIDEO_MODE_XGA			= AMBA_VIDEO_MODE_1024_768, /*!< AMBA_VIDEO_MODE_1024_768 */
	AMBA_VIDEO_MODE_WXGA		= AMBA_VIDEO_MODE_1280_800, /*!< AMBA_VIDEO_MODE_1280_800 */
	AMBA_VIDEO_MODE_SXGA		= AMBA_VIDEO_MODE_1280_1024, /*!< AMBA_VIDEO_MODE_1280_1024 */
	AMBA_VIDEO_MODE_SXGAP		= AMBA_VIDEO_MODE_1400_1050, /*!< AMBA_VIDEO_MODE_1400_1050 */
	AMBA_VIDEO_MODE_WSXGA		= AMBA_VIDEO_MODE_1440_900, /*!< AMBA_VIDEO_MODE_1440_900 */
	AMBA_VIDEO_MODE_UXGA		= AMBA_VIDEO_MODE_1600_1200, /*!< AMBA_VIDEO_MODE_1600_1200 */
	AMBA_VIDEO_MODE_WSXGAP		= AMBA_VIDEO_MODE_1680_1050, /*!< AMBA_VIDEO_MODE_1680_1050 */
	AMBA_VIDEO_MODE_WUXGA		= AMBA_VIDEO_MODE_1920_1200, /*!< AMBA_VIDEO_MODE_1920_1200 */
	AMBA_VIDEO_MODE_QXGA		= AMBA_VIDEO_MODE_2048_1536, /*!< AMBA_VIDEO_MODE_2048_1536 */
	AMBA_VIDEO_MODE_QSXGA		= AMBA_VIDEO_MODE_2592_1944, /*!< AMBA_VIDEO_MODE_2592_1944 */
	AMBA_VIDEO_MODE_1080P		= AMBA_VIDEO_MODE_1920_1080, /*!< AMBA_VIDEO_MODE_1920_1080 */
	AMBA_VIDEO_MODE_1080I		= AMBA_VIDEO_MODE_1920_1080, /*!< AMBA_VIDEO_MODE_1920_1080 */
	AMBA_VIDEO_MODE_720P		= AMBA_VIDEO_MODE_1280_720, /*!< AMBA_VIDEO_MODE_1280_720 */
	AMBA_VIDEO_MODE_576P		= AMBA_VIDEO_MODE_720_576, /*!< AMBA_VIDEO_MODE_720_576 */
	AMBA_VIDEO_MODE_480P		= AMBA_VIDEO_MODE_720_480, /*!< AMBA_VIDEO_MODE_720_480 */
	AMBA_VIDEO_MODE_576I		= AMBA_VIDEO_MODE_720_576, /*!< AMBA_VIDEO_MODE_720_576 */
	AMBA_VIDEO_MODE_480I		= AMBA_VIDEO_MODE_720_480, /*!< AMBA_VIDEO_MODE_720_480 */
	AMBA_VIDEO_MODE_D1_PAL		= AMBA_VIDEO_MODE_720_576, /*!< AMBA_VIDEO_MODE_720_576 */
	AMBA_VIDEO_MODE_D1_NTSC		= AMBA_VIDEO_MODE_720_480, /*!< AMBA_VIDEO_MODE_720_480 */

	/* misc */
	AMBA_VIDEO_MODE_OFF				= 0xF000, /*!< 0xF000 */
	AMBA_VIDEO_MODE_NOT_SUPPORT		= -1, /*!< -1 */
	AMBA_VIDEO_MODE_CURRENT			= -2, /*!< -2 */
	AMBA_VIDEO_MODE_INVALID			= AMBA_VIDEO_MODE_NUM + 1, /*!< AMBA_VIDEO_MODE_NUM + 1 */
};

/*! @enum amba_video_bits
 *  @brief AMBA Video Bits Enumerations
 */
enum amba_video_bits {
	AMBA_VIDEO_BITS_AUTO		= 0, /*!< 0 */
	AMBA_VIDEO_BITS_8		= 8, /*!< 8 */
	AMBA_VIDEO_BITS_10		= 10, /*!< 10 */
	AMBA_VIDEO_BITS_12		= 12, /*!< 12 */
	AMBA_VIDEO_BITS_14		= 14, /*!< 14 */
	AMBA_VIDEO_BITS_16		= 16, /*!< 16 */
};

/*! @enum amba_video_ratio
 *  @brief AMBA Video Ration Enumerations
 */
enum amba_video_ratio {
	AMBA_VIDEO_RATIO_AUTO		= 0x0, /*!< 0x0 */
	AMBA_VIDEO_RATIO_4_3		= 0x1, /*!< 0x1 */
	AMBA_VIDEO_RATIO_16_9		= 0x2, /*!< 0x2 */
	AMBA_VIDEO_RATIO_1_1		= 0x4, /*!< 0x4 */
};

/*! @enum amba_video_system
 *  @brief AMBA Video Ration Enumerations
 */
enum amba_video_system {
	AMBA_VIDEO_SYSTEM_AUTO		= 0x0, /*!< 0x0 */
	AMBA_VIDEO_SYSTEM_NTSC		= 0x1, /*!< 0x1 */
	AMBA_VIDEO_SYSTEM_PAL		= 0x2, /*!< 0x2 */
	AMBA_VIDEO_SYSTEM_SECAM		= 0x4, /*!< 0x4 */
	AMBA_VIDEO_SYSTEM_ALL		= 0xf, /*!< 0xf */
};

enum amba_video_hdr_mode {
	AMBA_VIDEO_LINEAR_MODE		= 0, /*!< 0 */
	AMBA_VIDEO_2X_HDR_MODE,
	AMBA_VIDEO_3X_HDR_MODE,
	AMBA_VIDEO_4X_HDR_MODE,

	AMBA_VIDEO_INT_HDR_MODE		= 15, /*!< 15 */

	AMBA_VIDEO_MODE_TOTAL_NUM,

	AMBA_VIDEO_HDR_MODE_INVALID	= 0xFF, /*!< 0xFF */

	AMBA_VIDEO_MODE_FIRST		= 0,/*!< 0 */
	AMBA_VIDEO_MODE_LAST		= AMBA_VIDEO_MODE_TOTAL_NUM, /*!< AMBA_VIDEO_MODE_TOTAL_NUM */
};

enum amba_video_rhs_mode {
	AMBA_VIDEO_RHS_FIXED	= 0x0, /*!< 0x0 */
	AMBA_VIDEO_RHS_DYNAMIC	= 0x1, /*!< 0x1 */
	AMBA_VIDEO_RHS_AUTO	= 0x2, /*!< 0x2 */
};

enum amba_vsrc_status {
	AMBA_VSRC_STATUS_ACTIVE	= 0, /*!< 0x0 */
	AMBA_VSRC_STATUS_BROKEN	= 1, /*!< 0x1 */
};

enum amba_vsrc_op {
	AMBA_VSRC_OP_ENABLE		= 0, /*!< 0x0 */
	AMBA_VSRC_OP_DISABLE	= 1, /*!< 0x1 */
};

/*! @} */ /* iav-common-helper */


/*! @addtogroup iav-common-struct
 *  @{
 */

/*! @struct amba_video_info
 *  @brief Amba video info
 */
struct amba_video_info {
	u32	mode;		/*!< Video mode, @sa amba_video_mode */
	u32	width;		/*!< Window width */
	u32	height;		/*!< Window height */
	u32	max_fps;	/*!< Video max fps */
	u32	fps;		/*!< Video fps */
	u8 	format;		/*!< Video format */
	u8 	type;		/*!< Video type */
	u8 	bits;		/*!< Video encode bit width */
	u8 	ratio;		/*!< Width-height ratio */
	u8 	system;		/*!< Video system type */
	u8 	flip;		/*!< Video flip */
	u8 	rotate;		/*!< Video rotate */
	u8 	hdr_mode;	/*!< Video rotate */
	u32	rev;		/*!< Struct definition revision */
};
/*! @} */ /* iav-common-struct */

/*!
 * @addtogroup iav-common-helper
 * @{
 */
/*! @macros DIV_ROUND(x,d)
 *  @brief div_round in 32-bit.
 */
#ifndef DIV_ROUND
#define DIV_ROUND(x, d)	(((x) + ((d) - 1)) / (d))
#endif

/*! @macros DIV_CLOSEST(x,d)
 *  @brief div_closest in 32-bit.
 */
#ifndef DIV_CLOSEST
#define DIV_CLOSEST(x, d)	(((x) + ((d) / 2)) / (d))
#endif

/*!
 * @macros DIV64_ROUND(x,d)
 * @brief div_round in 64-bit.
 */
#ifndef DIV64_ROUND
#define DIV64_ROUND(x, d)	({u64 _tmp = (x)+((d) - 1); do_div(_tmp, d); _tmp;})
#endif

/*!
 * @macros DIV64_CLOSEST(x,d)
 * @brief div_closet in 64-bit.
 */
#ifndef DIV64_CLOSEST
#define DIV64_CLOSEST(x, d)	({u64 _tmp = (x)+((d)/2); do_div(_tmp, d); _tmp;})
#endif

/*!
 * @macros ROUND_UP(x,d)
 * @brief round up func.
 */
#ifndef ROUND_UP
#define ROUND_UP(x, n)  ( ((x)+(n)-1u) & ~((n)-1u) )
#endif

/*!
 * @macros ROUND_DOWN(x,d)
 * @brief round down func.
 */
#ifndef ROUND_DOWN
#define ROUND_DOWN(x, n)	((x) & ~((n) - 1))
#endif

/*!
 * @macros MIN(a, b)
 * @brief return minimum value of a and b.
 */
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/*!
 * @macros MAX(a, b)
 * @brief return maximum value of a and b.
 */
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/*!
 * @macros ABS(x)
 * @brief return absolute value of x.
 */
#ifndef ABS
#define ABS(x) ({                               \
                int __x = (x);                  \
                (__x < 0) ? -__x : __x;         \
            })
#endif

/*!
 * @macros ARRAY_SIZE(array)
 * @brief return array_size of input array.
 */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array)   (sizeof(array) / sizeof(array[0]))
#endif

/*!
 * @macros BIT(n)
 * @brief bit n.
 */
#ifndef BIT
#define BIT(n) (1U << (n))
#endif

/*!
 * @macros TEST_BIT(x, n)
 * @brief test if the (n) th bit of (x) is 1.
 */
#ifndef TEST_BIT
#define TEST_BIT(x, n) ((x) & (1U << (n)))
#endif

/*!
 * @macros SET_BIT(x, n)
 * @brief set the (n)th bit of (x) to 1.
 */
#ifndef SET_BIT
#define SET_BIT(x, n) do {x = (x | (1U << (n)));} while(0);
#endif

/*!
 * @macros CLEAR_BIT(x, n)
 * @brief set the (n)th bit of (x) to 0.
 */
#ifndef CLEAR_BIT
#define CLEAR_BIT(x, n) do {x = (x & (~(1U << (n))));} while(0);
#endif
/*! @} */ /* End of iav-common-helper */


#ifdef __cplusplus
}
#endif

#endif

