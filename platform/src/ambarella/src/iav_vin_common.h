/*
 * iav_vin_common.h
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

#ifndef __IAV_VIN_COMMON_H__
#define __IAV_VIN_COMMON_H__

/*! @file iav_vin_common.h
 *  @brief This file defines IAV Video Input Configuration structures.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ==========================================================================*/
#include "config.h"
#include"iav_common.h"

/*! @addtogroup iav-ioctl-vin-helper
 *  @{
 */
/* ==========================================================================*/

#if defined(CONFIG_DRIVER_VERSION_V6)
#define TOTAL_VINC_MAX_NUM			18
#else
#define TOTAL_VINC_MAX_NUM			8
#endif

#define AMBA_VINDEV_MAX_NUM			32
#define AMBA_VINC_MAX_NUM			TOTAL_VINC_MAX_NUM

/* ==========================================================================*/
enum vindev_type {
	VINDEV_TYPE_SENSOR			= 0, /*!< 0 */
	VINDEV_TYPE_DECODER			= 1, /*!< 1 */
};

enum vindev_subtype {
	VINDEV_SUBTYPE_CMOS			= 0x000, /*!< 0x000 */
	VINDEV_SUBTYPE_CCD			= 0x001, /*!< 0x001 */
	VINDEV_SUBTYPE_CVBS			= 0x100, /*!< 0x100 */
	VINDEV_SUBTYPE_SVIDEO		= 0x101, /*!< 0x101 */
	VINDEV_SUBTYPE_YPBPR		= 0x102, /*!< 0x102 */
	VINDEV_SUBTYPE_HDMI			= 0x103, /*!< 0x103 */
	VINDEV_SUBTYPE_VGA			= 0x104, /*!< 0x104 */
	VINDEV_SUBTYPE_SDI			= 0x105, /*!< 0x105 */
};

enum amba_vindev_mirror_pattern_e {
	VINDEV_MIRROR_NONE			= 0, /*!< 0 */
	VINDEV_MIRROR_VERTICALLY		= 1, /*!< 1 */
	VINDEV_MIRROR_HORRIZONTALLY		= 2, /*!< 2 */
	VINDEV_MIRROR_HORRIZONTALLY_VERTICALLY	= 3, /*!< 3 */
	VINDEV_MIRROR_DSP_VFLIP	= 4,	/*!< 4 */
	VINDEV_MIRROR_SENSOR_HFLIP_DSP_VFLIP	= 5, /*!< 5 */
	VINDEV_MIRROR_AUTO			= 255, /*!< 255 */
};

enum amba_vindev_bayer_pattern_e {
	VINDEV_BAYER_PATTERN_RG			= 0,	/*!< 0 */
	VINDEV_BAYER_PATTERN_BG			= 1,	/*!< 1 */
	VINDEV_BAYER_PATTERN_GR			= 2,	/*!< 2 */
	VINDEV_BAYER_PATTERN_GB			= 3,	/*!< 3 */
	/* RGB/IR CFA, IR instead of B */
	VINDEV_BAYER_PATTERN_RG_GI		= 4,	/*!< 4 */
	VINDEV_BAYER_PATTERN_IG_GR		= 5,	/*!< 5 */
	VINDEV_BAYER_PATTERN_GR_IG		= 6,	/*!< 6 */
	VINDEV_BAYER_PATTERN_GI_RG		= 7,	/*!< 7 */
	/* RGB/IR CFA, IR instead of R */
	VINDEV_BAYER_PATTERN_BG_GI		= 8,	/*!< 8 */
	VINDEV_BAYER_PATTERN_IG_GB		= 9,	/*!< 9 */
	VINDEV_BAYER_PATTERN_GB_IG		= 10,	/*!< 10 */
	VINDEV_BAYER_PATTERN_GI_BG		= 11,	/*!< 11 */
	/* RCCB CFA */
	VINDEV_BAYER_PATTERN_RCCB		= 12,	/*!< 12 */
	VINDEV_BAYER_PATTERN_BCCR		= 13,	/*!< 13 */
	VINDEV_BAYER_PATTERN_CRBC		= 14,	/*!< 14 */
	VINDEV_BAYER_PATTERN_CBRC		= 15,	/*!< 15 */
	/* RCCC CFA */
	VINDEV_BAYER_PATTERN_RCCC		= 16,	/*!< 16 */
	VINDEV_BAYER_PATTERN_CCCR		= 17,	/*!< 17 */
	VINDEV_BAYER_PATTERN_CRCC		= 18,	/*!< 18 */
	VINDEV_BAYER_PATTERN_CCRC		= 19,	/*!< 19 */
	/* MONO CFA */
	VINDEV_BAYER_PATTERN_MONO		= 254,	/*!< 254 */

	VINDEV_BAYER_PATTERN_AUTO		= 255, 	/*!< 255 */
};

enum vindev_reg_context {
	VINDEV_REG_CONTEXT_A			= 0, /*!< 0 */
	VINDEV_REG_CONTEXT_B			= 1, /*!< 1 */
	VINDEV_REG_CONTEXT_C			= 2, /*!< 2 */
	VINDEV_REG_CONTEXT_D			= 3, /*!< 3 */
	VINDEV_REG_CONTEXT_NUM			= 4, /*!< 4 */
};

enum sensor_list {
	/* Onsemi Sensor */
	SENSOR_MT9J001				= 0x00000000,	/*!< 0x00000000 */
	SENSOR_MT9M033				= 0x00000001,	/*!< 0x00000001 */
	SENSOR_MT9P001				= 0x00000002,	/*!< 0x00000002 */
	SENSOR_MT9V136				= 0x00000003,	/*!< 0x00000003 */
	SENSOR_MT9T002				= 0x00000004,	/*!< 0x00000004 */
	SENSOR_AR0331				= 0x00000005,	/*!< 0x00000005 */
	SENSOR_AR0130				= 0x00000006,	/*!< 0x00000006 */
	SENSOR_AR0141				= 0x00000007,	/*!< 0x00000007 */
	SENSOR_AR0230				= 0x00000008,	/*!< 0x00000008 */
	SENSOR_AR0237				= 0x00000009,	/*!< 0x00000009 */
	SENSOR_AR0239				= 0x0000000A,	/*!< 0x0000000A */
	SENSOR_AR0521				= 0x0000000B,	/*!< 0x0000000B */
	SENSOR_AR0144				= 0x0000000C,	/*!< 0x0000000C */
	SENSOR_AR0144_RGB			= 0x0000000D,	/*!< 0x0000000D */
	SENSOR_AR0143				= 0x0000000E,	/*!< 0x0000000E */
	SENSOR_AR0221				= 0x0000000F,	/*!< 0x0000000F */
	SENSOR_AR0233				= 0x00000010,	/*!< 0x00000010 */
	SENSOR_AR0231				= 0x00000011,	/*!< 0x00000011 */
	SENSOR_AR0132				= 0x00000012,	/*!< 0x00000012 */
	SENSOR_AR0237_RGBIR			= 0x00000013,	/*!< 0x00000013 */
	SENSOR_AR0138				= 0x00000014,	/*!< 0x00000014 */
	SENSOR_AR0431				= 0x00000015,	/*!< 0x00000015 */
	SENSOR_AR0135				= 0x00000016,	/*!< 0x00000016 */
	SENSOR_AR0323				= 0x00000017,	/*!< 0x00000017 */
	SENSOR_AR0220				= 0x00000018,	/*!< 0x00000018 */
	SENSOR_AR0432				= 0x00000019,	/*!< 0x00000019 */
	SENSOR_AR0147				= 0x0000001A,   /*!< 0x0000001A */
	SENSOR_AR0820				= 0x0000001B,   /*!< 0x0000001B */
	SENSOR_AR0234				= 0x0000001C,   /*!< 0x0000001C */
	SENSOR_AR0830				= 0x0000001D,   /*!< 0x0000001D */
	SENSOR_AR0822				= 0x0000001E,   /*!< 0x0000001E */

	/* Onsemi-XGS series */
	SENSOR_XGS12000				= 0x00000200,   /*!< 0x00000200 */

	/* OV Sensor */
	SENSOR_OV10620				= 0x00001000,	/*!< 0x00001000 */
	SENSOR_OV14810				= 0x00001001,	/*!< 0x00001001 */
	SENSOR_OV2710				= 0x00001002,	/*!< 0x00001002 */
	SENSOR_OV5653				= 0x00001003,	/*!< 0x00001003 */
	SENSOR_OV7720				= 0x00001004,	/*!< 0x00001004 */
	SENSOR_OV7725				= 0x00001005,	/*!< 0x00001005 */
	SENSOR_OV7740				= 0x00001006,	/*!< 0x00001006 */
	SENSOR_OV9710				= 0x00001007,	/*!< 0x00001007 */
	SENSOR_OV10630				= 0x00001008,	/*!< 0x00001008 */
	SENSOR_OV9726				= 0x00001009,	/*!< 0x00001009 */
	SENSOR_OV4689				= 0x0000100A,	/*!< 0x0000100A */
	SENSOR_OV9718				= 0x0000100B,	/*!< 0x0000100B */
	SENSOR_OV5658				= 0x0000100C,	/*!< 0x0000100C */
	SENSOR_OV9750				= 0x0000100D,	/*!< 0x0000100D */
	SENSOR_OV9732				= 0x0000100E,	/*!< 0x0000100E */
	SENSOR_OV2718				= 0x0000100F,	/*!< 0x0000100F */
	SENSOR_OV7251				= 0x00001010,	/*!< 0x00001010 */
	SENSOR_OV10823				= 0x00001011,	/*!< 0x00001011 */
	SENSOR_OV9281				= 0x00001012,	/*!< 0x00001012 */
	SENSOR_OS08A10				= 0x00001013,	/*!< 0x00001013 */
	SENSOR_OV2732				= 0x00001014,	/*!< 0x00001014 */
	SENSOR_OV2735				= 0x00001015,	/*!< 0x00001015 */
	SENSOR_OV2770				= 0x00001016,	/*!< 0x00001016*/
	SENSOR_OS05A10				= 0x00001017,	/*!< 0x00001017 */
	SENSOR_OS02A1Q				= 0x00001018,	/*!< 0x00001018 */
	SENSOR_OV8856				= 0x00001019,	/*!< 0x00001019 */
	SENSOR_OV10640				= 0x0000101A,	/*!< 0x0000101A */
	SENSOR_OX01A10				= 0x0000101B,	/*!< 0x0000101B */
	SENSOR_OV9284				= 0x0000101C,	/*!< 0x0000101C */
	SENSOR_OVM7690				= 0x0000101D,	/*!< 0x0000101D */
	SENSOR_OV2775				= 0x0000101E,	/*!< 0x0000101E */
	SENSOR_OV9755				= 0x0000101F,	/*!< 0x0000101F */
	SENSOR_OS02C10				= 0x00001020,	/*!< 0x00001020 */
	SENSOR_OS04A10				= 0x00001021,	/*!< 0x00001021 */
	SENSOR_OV2778				= 0x00001022,	/*!< 0x00001022 */
	SENSOR_OV9706				= 0x00001023,	/*!< 0x00001023 */
	SENSOR_OV2311				= 0x00001024,	/*!< 0x00001024 */
	SENSOR_OV2736				= 0x00001025,	/*!< 0x00001025 */
	SENSOR_OV2312				= 0x00001026,	/*!< 0x00001026 */
	SENSOR_OS08B10				= 0x00001027,	/*!< 0x00001027 */
	SENSOR_OS04C10				= 0x00001028,	/*!< 0x00001028 */
	SENSOR_OS02K10				= 0x00001029,	/*!< 0x00001029 */
	SENSOR_OS02F10				= 0x0000102A,	/*!< 0x0000102A */
	SENSOR_OV02K10				= 0x0000102B,	/*!< 0x0000102B */
	SENSOR_OS02H10				= 0x0000102C,	/*!< 0x0000102C */
	SENSOR_OG01A1B				= 0x0000102D,	/*!< 0x0000102D */
	SENSOR_OX03C10				= 0x0000102E,	/*!< 0x0000102E */

	/* Samsung Sensor */
	SENSOR_S5K3E2FX				= 0x00002000,	/*!< 0x00002000 */
	SENSOR_S5K4AWFX				= 0x00002001,	/*!< 0x00002001 */
	SENSOR_S5K5B3GX				= 0x00002002,	/*!< 0x00002002 */

	/* Sony Sensor */
	SENSOR_IMX035				= 0x00003000,	/*!< 0x00003000 */
	SENSOR_IMX036				= 0x00003001,	/*!< 0x00003001 */
	SENSOR_IMX072				= 0x00003002,	/*!< 0x00003002 */
	SENSOR_IMX122				= 0x00003003,	/*!< 0x00003003 */
	SENSOR_IMX121				= 0x00003004,	/*!< 0x00003004 */
	SENSOR_IMX104				= 0x00003005,	/*!< 0x00003005 */
	SENSOR_IMX136				= 0x00003006,	/*!< 0x00003006 */
	SENSOR_IMX105				= 0x00003007,	/*!< 0x00003007 */
	SENSOR_IMX172				= 0x00003008,	/*!< 0x00003008 */
	SENSOR_IMX178				= 0x00003009,	/*!< 0x00003009 */
	SENSOR_IMX123				= 0x0000300A,	/*!< 0x0000300A */
	SENSOR_IMX123_DCG			= 0x0000300B,	/*!< 0x0000300B */
	SENSOR_IMX322				= 0x0000300C,	/*!< 0x0000300C */
	SENSOR_IMX124				= 0x0000300D,	/*!< 0x0000300D */
	SENSOR_IMX224				= 0x0000300E,	/*!< 0x0000300E */
	SENSOR_IMX174				= 0x0000300F,	/*!< 0x0000300F */
	SENSOR_IMX291				= 0x00003010,	/*!< 0x00003010 */
	SENSOR_IMX185				= 0x00003011,	/*!< 0x00003011 */
	SENSOR_IMX226				= 0x00003012,	/*!< 0x00003012 */
	SENSOR_IMX290				= 0x00003013,	/*!< 0x00003013 */
	SENSOR_IMX274				= 0x00003014,	/*!< 0x00003014 */
	SENSOR_IMX377				= 0x00003015,	/*!< 0x00003015 */
	SENSOR_IMX183				= 0x00003016,	/*!< 0x00003016 */
	SENSOR_IMX277				= 0x00003017,	/*!< 0x00003017 */
	SENSOR_IMX408				= 0x00003018,	/*!< 0x00003018 */
	SENSOR_IMX117				= 0x00003019,	/*!< 0x00003019 */
	SENSOR_IMX335				= 0x0000301A,	/*!< 0x0000301A */
	SENSOR_IMX577				= 0x0000301B,	/*!< 0x0000301B */
	SENSOR_IMX390				= 0x0000301C,	/*!< 0x0000301C */
	SENSOR_IMX415				= 0x0000301D,	/*!< 0x0000301D */
	SENSOR_IMX412				= 0x0000301E,	/*!< 0x0000301E */
	SENSOR_IMX265				= 0x0000301F,	/*!< 0x0000301F */
	SENSOR_IMX250				= 0x00003020,	/*!< 0x00003020 */
	SENSOR_IMX299				= 0x00003021,	/*!< 0x00003021 */
	SENSOR_IMX326				= 0x00003022,	/*!< 0x00003022 */
	SENSOR_IMX307				= 0x00003023,	/*!< 0x00003023 */
	SENSOR_IMX385				= 0x00003024,	/*!< 0x00003024 */
	SENSOR_IMX334				= 0x00003025,	/*!< 0x00003025 */
	SENSOR_IMX327				= 0x00003026,	/*!< 0x00003026 */
	SENSOR_IMX264				= 0x00003027,	/*!< 0x00003027 */
	SENSOR_IMX490				= 0x00003028,	/*!< 0x00003028 */
	SENSOR_IMX455				= 0x00003029,   /*!< 0x00003029 */
	SENSOR_IMX347				= 0x0000302A,	/*!< 0x0000302A */
	SENSOR_IMX462				= 0x0000302B,	/*!< 0x0000302B */
	SENSOR_IMX571				= 0x0000302C,	/*!< 0x0000302C */
	SENSOR_IMX305				= 0x0000302D,	/*!< 0x0000302D */
	SENSOR_IMX485				= 0x0000302E,	/*!< 0x0000302E */
	SENSOR_IMX464				= 0x0000302F,	/*!< 0x0000302F */
	SENSOR_IMX515				= 0x00003030,	/*!< 0x00003030 */
	SENSOR_IMX586				= 0x00003031,	/*!< 0x00003031 */
	SENSOR_IMX585				= 0x00003032,	/*!< 0x00003032 */
	SENSOR_IMX678				= 0x00003033,	/*!< 0x00003033 */
	SENSOR_IMX422				= 0x00003034,	/*!< 0x00003034 */
	SENSOR_IMX424				= 0x00003035,	/*!< 0x00003035 */
	SENSOR_IMX715				= 0x00003036,	/*!< 0x00003036 */
	SENSOR_IMX492				= 0x00003037,	/*!< 0x00003037 */
	SENSOR_IMX568				= 0x00003038,	/*!< 0x00003038 */
	SENSOR_IMX623				= 0x00003039,	/*!< 0x00003039 */

	/* Panasonic Sensor */
	SENSOR_MN34041PL			= 0x00004000,	/*!< 0x00004000 */
	SENSOR_MN34031PL			= 0x00004001,	/*!< 0x00004001 */
	SENSOR_MN34220PL			= 0x00004002,	/*!< 0x00004002 */
	SENSOR_MN34210PL			= 0x00004003,	/*!< 0x00004003 */
	SENSOR_MN34227PL			= 0x00004004,	/*!< 0x00004004 */
	SENSOR_MN34420PL			= 0x00004005,	/*!< 0x00004005 */
	SENSOR_MN34422PL			= 0x00004006,	/*!< 0x00004006 */
	SENSOR_MN34424PL			= 0x00004007,	/*!< 0x00004007 */

	/* Dummy Sensor */
	SENSOR_AMBDS				= 0x00005000,	/*!< 0x00005000 */
	SENSOR_ALTERA_FPGA			= 0x00005001,   /*!< 0x00005001 */

	/* Cista Sensor */
	SENSOR_C2390				= 0x00005040,	/*!< 0x00005040 */

	/* Brillnics Sensor */
	SENSOR_BRV0500				= 0x00005080,	/*!< 0x00005080 */
	SENSOR_BRV0200				= 0x00005081,	/*!< 0x00005081 */

	/* SOI Sensor */
	SENSOR_JX_F22				= 0x000050C0,	/*!< 0x000050C0 */
	SENSOR_JX_K02				= 0x000050C1,	/*!< 0x000050C1 */
	SENSOR_JX_F23				= 0x000050C2,	/*!< 0x000050C2 */
	SENSOR_JX_F32				= 0x000050C3,	/*!< 0x000050C3 */

	/* Smartsens Sensor */
	SENSOR_SC130GS				= 0x00005100,	/*!< 0x00005100 */
	SENSOR_SC2135				= 0x00005101,	/*!< 0x00005101 */
	SENSOR_SC2235				= 0x00005102,	/*!< 0x00005102 */
	SENSOR_SC5238				= 0x00005103,	/*!< 0x00005103 */
	SENSOR_SC5300				= 0x00005104,	/*!< 0x00005104 */
	SENSOR_SC2310				= 0x00005105,	/*!< 0x00005105 */
	SENSOR_SC2315				= 0x00005106,	/*!< 0x00005106 */
	SENSOR_SC2332				= 0x00005107,	/*!< 0x00005107 */
	SENSOR_SC4210				= 0x00005108,	/*!< 0x00005108 */
	SENSOR_SC200AI				= 0x00005109,	/*!< 0x00005109 */
	SENSOR_SC500AI				= 0x0000510A,	/*!< 0x0000510A */
	SENSOR_SC8235				= 0x0000510B,	/*!< 0x0000510B */
	SENSOR_SC2339				= 0x0000510C,	/*!< 0x0000510C */
	SENSOR_SC410GS				= 0x0000510D,	/*!< 0x0000510D */
	SENSOR_SC301IOT				= 0x0000510E,	/*!< 0x0000510E */
	SENSOR_SC230AI				= 0x0000510F,	/*!< 0x0000510F */
	SENSOR_SC530AI				= 0x00005110,	/*!< 0x00005110 */

	/* Himax sensor */
	SENSOR_HM2140				= 0x00005140,	/*!< 0x00005140 */
	SENSOR_HM5532				= 0x00005141,	/*!< 0x00005141 */

	/* Prime sensor */
	SENSOR_PS5270				= 0x00005180,	/*!< 0x00005180 */
	SENSOR_PS5250				= 0x00005181,	/*!< 0x00005181 */
	SENSOR_PS5260				= 0x00005182,	/*!< 0x00005182 */

	/* Galaxycore sensor */
	SENSOR_GC2093				= 0x000051C0,   /*!< 0x000051C0 */
	SENSOR_GC2145				= 0x000051C1,   /*!< 0x000051C1 */

	/* SuperPix sensor */
	SENSOR_SP2309				= 0x00005200,   /*!< 0x00005200 */

	/* ST sensor */
	SENSOR_VG5761				= 0x00005280,   /*!< 0x00005280 */
	SENSOR_VG1762				= 0x00005281,   /*!< 0x00005281 */

	/* TML sensor */
	SENSOR_TML_260_192			= 0x00005800,   /*!< 0x00005800 */
	SENSOR_TML_120_90			= 0x00005801,   /*!< 0x00005801 */

	/* TOF sensor */
	SENSOR_TOF_GP9043			= 0x00006000,   /*!< 0x00006000 */
	SENSOR_TOF_MN34906			= 0x00006001,   /*!< 0x00006001 */
	SENSOR_TOF_IMX316			= 0x00006002,   /*!< 0x00006002 */
	SENSOR_TOF_IMX456			= 0x00006003,   /*!< 0x00006003 */
	SENSOR_TOF_IMX528			= 0x00006004,   /*!< 0x00006004 */
	SENSOR_TOF_IRS2877C			= 0x00006005,	/*!< 0x00006005 */

	/* Customized Sensor */
	SENSOR_CUSTOM_FIRST			= 0x00010000,	/*!< 0x00010000 */

	/* ADI Decoder */
	DECODER_ADV7403				= 0x80000000,	/*!< 0x80000000 */
	DECODER_ADV7441A			= 0x80000001,	/*!< 0x80000001 */
	DECODER_ADV7443				= 0x80000002,	/*!< 0x80000002 */

	/* RICHNEX Decoder */
	DECODER_RN6240				= 0x80001000,	/*!< 0x80001000 */

	/* TI Decoder */
	DECODER_TVP5150				= 0x80002000,	/*!< 0x80002000 */

	/* Techwell Decoder */
	DECODER_TW2864				= 0x80003000,	/*!< 0x80003000 */
	DECODER_TW9910				= 0x80003001,	/*!< 0x80003001 */

	DECODER_GS2970				= 0x80004000,	/*!< 0x80004000 */

	/* Toshiba Decoder */
	DECODER_TC358840			= 0x80005000,	/*!< 0x80005000 */

	/* Lontium Decoder */
	DECODER_LT6911				= 0x80006000,	/*!< 0x80006000 */

	/* Dummy Decoder */
	DECODER_AMBDD				= 0x8FFFFFFF,	/*!< 0x8FFFFFFF */
};

enum vindev_set_type {
	VINDEV_SET_AGC_ONLY		= 0, /*!< 0 */
	VINDEV_SET_SHT_ONLY		= 1, /*!< 1 */
	VINDEV_SET_AGC_SHT		= 2, /*!< 2 */
};

enum vindev_status {
	VINDEV_STATUS_SENSOR_ERR	= (1 << 0), /*!< (1 << 0) */
	VINDEV_STATUS_DES_ERR		= (1 << 1), /*!< (1 << 1) */
	VINDEV_STATUS_SER_ERR		= (1 << 2), /*!< (1 << 2) */
};
/*! @} */  /* End of iav-ioctl-vin-helper */


/* ==========================================================================*/
/*! @addtogroup iav-ioctl-vin-struct
 *  @{
 */
struct vindev_devinfo {
	unsigned int vsrc_id;	/*!< Source ID */
	unsigned int vinc_id;	/*!< VIN controller ID */
	char name[32];		/*!< The name of the VIN source */
	unsigned int dev_type;	/*!< The type of the VIN source, @sa vindev_type */
	unsigned int sub_type;	/*!< VIN source sub type, @sa vindev_subtype */
	unsigned int sensor_id;	/*!< Sensor ID */
	unsigned int vsrc_num;	/*!< Total VIN Source number registered */
	unsigned int vsrc_ctx_switch_cap : 1;	/*!< Possibility to support sensor context switch */
	unsigned int vsrc_status : 1;	/*!< VIN source operation, 0: enabled; 1: disabled, @sa amba_vsrc_op */
	unsigned int reserved0 : 30;
};

struct vindev_mode {
	unsigned int vsrc_id;		/*!< Source ID of the current VIN */
	unsigned int video_mode;	/*!< Video mode, @sa amba_video_mode */
	unsigned int hdr_mode;		/*!< HDR mode, @sa amba_video_hdr_mode */
	unsigned int bits;		/*!< Bits depth */
	unsigned int vsrc_ctx_auto_switch;	/*!< Enable sensor context auto switch */
	unsigned int vsrc_status : 1;	/* This is a flag used to mark sensor operation to support entering preivew
			with broken sensor.0(Default): marked as enabled, 1: marked as disabled, @sa amba_vsrc_op */
	unsigned int reserved0 : 31;
	unsigned int fps;		/*!< Video frame rate in Q9 format, @sa amba_video_fps */
	unsigned int max_fps;	/*!< Max frame rate in Q9 format, it's used for driver to
								retrieve the proper VIN MODE with the same resolution*/
};

struct vindev_mode_group {
	u32 vsrc_map;
	struct vindev_mode mode[AMBA_VINDEV_MAX_NUM];
};

struct vindev_fps {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int fps;	/*!< Video fps in Q9 format, @sa amba_video_fps */
	unsigned int max_fps;	/*!< Max fps in Q9 format, it's used for driver to
								retrieve the proper VIN MODE with the same resolution*/
};

struct vindev_video_info {
	unsigned int vsrc_id;		/*!< Source ID of the current VIN */
	struct amba_video_info info;	/*!< Video infomation of the current VIN source */
	unsigned int vsrc_status : 1;	/*!< VIN source operation, 0: enabled; 1: disabled, @sa amba_vsrc_op */
	unsigned int reserved : 31;
};

struct vindev_shutter {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int vsrc_ctx;	/*!< Context ID of current Sensor */
	unsigned int shutter;	/*!< The parameter shutter_time is expressed in Q9 format, which is 512000000*time_in_sec.
				     For example, 1/30 sec can be expressed as 512000000/30 = 17066667 = 0x1046aab */
};

struct vindev_shutter_row {
	unsigned int vsrc_id;	  /*!< Source ID of the current VIN */
	unsigned int shutter_row; /*!< Shutter Row */
};

struct vindev_agc_shutter {
	unsigned int vsrc_id;	  /*!< Source ID of the current VIN */
	unsigned int vsrc_ctx;	  /*!< Context ID of current Sensor */
	unsigned int shutter_row; /*!< Shutter Row */
	unsigned int agc_idx;	  /*!< AGC index of the current VIN source */
	unsigned int mode;	  /*!< @sa vindev_set_type */
};

struct vindev_agc {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int vsrc_ctx;	/*!< Context ID of current Sensor */
	unsigned int agc;	/*!< AGC value of the current VIN source */
	unsigned int agc_max;	/*!< AGC max value of the current VIN source */
	unsigned int agc_min;	/*!< AGC min value of the current VIN source */
	unsigned int agc_step;	/*!< AGC step of the current VIN source */
	unsigned int wdr_again_idx_min; /*!< Minimum index of analog gain for sensor WDR mode */
	unsigned int wdr_again_idx_max;	/*!< Maximum index of analog gain for sensor WDR mode */
	unsigned int wdr_dgain_idx_min;	/*!< Minimum index of digital gain for sensor WDR mode */
	unsigned int wdr_dgain_idx_max; /*!< Maximum index of digital gain for sensor WDR mode */
};

struct vindev_mirror {
	unsigned int vsrc_id;		/*!< Source ID of the current VIN */
	unsigned int pattern;		/*!< Mirror pattern for the sensor, @sa amba_vindev_mirror_pattern_e */
	unsigned int bayer_pattern; 	/*!< Bayer pattern for the sensor, @sa amba_vindev_bayer_pattern_e */
};

struct vindev_reg {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int addr;	/*!< Register DRAM address */
	unsigned int data;	/*!< Register Value */
};

struct vindev_eisinfo {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int vb_time;	/*!< Vb time, ns */
	unsigned short sensor_cell_width;  /*!< Sensor cell width, um * 100 */
	unsigned short sensor_cell_height; /*!< Sensor cell height, um * 100*/
	unsigned char column_bin;	/*!< Column of binning pixels */
	unsigned char row_bin;		/*!< Row of binning pixels */
};

struct vindev_wdr_gain_info {
	unsigned int vsrc_id;	/*!< Source ID of the current Sensor */
	unsigned int vsrc_ctx;	/*!< Context ID of current Sensor */
	unsigned int gain_idx;	/*!< Gain index */
};

enum sensor_subframe_topology {
	SENSOR_SUBFRAME_SINGLE_FRAME		= 0,
	SENSOR_SUBFRAME_LINE_INTERLACE		= 1,
	SENSOR_SUBFRAME_FRAME_INTERLACE		= 2,
};

enum sensor_subframe_idx {
	SENSOR_SUBFRAME_L					= 0,
	SENSOR_SUBFRAME_M1					= 1,
	SENSOR_SUBFRAME_M2					= 2,
	SENSOR_SUBFRAME_S					= 3,
	SENSOR_SUBFRAME_NUM					= 4,
};

enum sensor_subframe_comb {
	SENSOR_SUBFRAME_NCB					= 0, /*!< single frame */
	SENSOR_SUBFRAME_CB2					= 1,
	SENSOR_SUBFRAME_CB3					= 2,
	SENSOR_SUBFRAME_CB4					= 3,
};

enum sensor_subframe_comp {
	SENSOR_SUBFRAME_NCP					= 0,  /*!< Not compressed */
	SENSOR_SUBFRAME_CPF14				= 1,
	SENSOR_SUBFRAME_CPF16				= 2,
	SENSOR_SUBFRAME_CPF20				= 3,
	SENSOR_SUBFRAME_CPF24				= 4,
};

enum sensor_ratio_type {
	SENSOR_RATIO_TYPE_SHUTTER			= (1 << 0),
	SENSOR_RATIO_TYPE_GAIN				= (1 << 1),
	SENSOR_RATIO_TYPE_PIXEL				= (1 << 2),
};

struct vindev_frame_info {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned char frame_num;	/*!< total frame number in each line-interleaved VIN raw  */
	unsigned char frame_topology; /*!< structure between frames */
	unsigned char reserved[2];

	unsigned char index[SENSOR_SUBFRAME_NUM];	/*!< indicate long or short frame */
	unsigned char combine[SENSOR_SUBFRAME_NUM];	/*!< how many frames before combine */
	unsigned char compress[SENSOR_SUBFRAME_NUM];	/*!< bit width before compress */

	unsigned char expo_ratio[SENSOR_SUBFRAME_NUM];	/*!< exposure ratio  */
	unsigned char ratio_type[SENSOR_SUBFRAME_NUM];	/*!< ways to control ratio  */

	unsigned char bayer_pattern[SENSOR_SUBFRAME_NUM];	/*!< normal RGB or special IR */
};

struct vindev_aaa_info {
	unsigned int vsrc_id;		/*!< Source ID of the current VIN */
	unsigned int sensor_id;		/*!< Sensor ID of the current VIN */
	unsigned int bayer_pattern;	/*!< Bayer pattern of current VIN */
	unsigned int agc_max;		/*!< AGC max value of the current VIN source */
	unsigned int agc_min;		/*!< AGC min value of the current VIN source */
	unsigned int agc_step;		/*!< The minimum AGC step unit */
	unsigned int wdr_again_idx_min;	/*!< Minimum index of analog gain for sensor WDR mode */
	unsigned int wdr_again_idx_max;	/*!< Maximum index of analog gain for sensor WDR mode */
	unsigned int wdr_dgain_idx_min;	/*!< Minimum index of digital gain for sensor WDR mode */
	unsigned int wdr_dgain_idx_max;	/*!< Maximum index of digital gain for sensor WDR mode */
	unsigned int hdr_mode;		/*!< HDR mode of current VIN */
	unsigned int hdr_rhs_mode;	/*!< RHS mode of current VIN */
	unsigned int hdr_long_offset;	/*!< Line offset of the longest exposure frame */
	unsigned int hdr_short1_offset;	/*!< Line offset of the medium exposure frame */
	unsigned int hdr_short2_offset;	/*!< Line offset of the above medium exposure frame */
	unsigned int hdr_short3_offset;	/*!< Line offset of the shortest exposure frame */
	unsigned int pixel_size;	/*!< Pixel size in micro meter of the current sensor */
	unsigned int dual_gain_mode;	/*!< Flag to indicate if the current VIN supports the dual gain mode */
	unsigned int line_time;		/*!< The time duration of each capture line */
	unsigned int vb_time;		/*!< The time duration of video blank */
	unsigned int sht0_max;		/*!< The maximum shutter value */
	unsigned int sht1_max;		/*!< The maximum shutter value */
	unsigned int sht2_max;		/*!< The maximum shutter value */
	unsigned int sht0_min;		/*!< The minimum shutter value */
	unsigned int sht1_min;		/*!< The minimum shutter value */
	unsigned int sht2_min;		/*!< The minimum shutter value */
	unsigned int wdr0_ratio;	/*!< long:short1 ratio */
	unsigned int wdr1_ratio;	/*!< short1:short2 ratio */
	unsigned int wdr2_ratio;	/*!< short2:short3 ratio */
	unsigned int ll_mode : 1;		/*!< ll mode */
	unsigned int is_negative_response : 1; /*!< Flag to indicate if sensor is negative response */
	unsigned int reserved : 30;
	unsigned int expo_bias_10x;		/*!< Deviation between real exposure lines and set value, 10*bias */
	struct vindev_frame_info frame_info;	/*!< frame info */
};

struct vindev_dgain_ratio {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int vsrc_ctx;	/*!< Context ID of current Sensor */
	unsigned int r_ratio;	/*!< Value of r_ratio */
	unsigned int gr_ratio;	/*!< Value of gr_ratio */
	unsigned int gb_ratio;	/*!< Value of gb_ratio */
	unsigned int b_ratio;	/*!< Value of b_ratio */
};

struct vindev_chip_status {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	int temperature;	/*!< Chip temperature */
	int access_status;	/*!< Access status */
};
/*! @} */  /* End of iav-ioctl-vin-struct */


/*! @addtogroup iav-ioctl-vin-helper */
#define VINDEV_WDR_CFG_DELAY_MAX	8

/*! @addtogroup iav-ioctl-vin-struct
 *  @{
 */
struct vindev_wdr_gp_s {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int vsrc_ctx;	/*!< Context ID of current Sensor */
	unsigned int l;
	unsigned int s1;
	unsigned int s2;
	unsigned int s3;
	unsigned int s1_offset;
	unsigned int s2_offset;
};

struct vindev_wdr_gp_info {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int vsrc_ctx;	/*!< Context ID of current Sensor */
	struct vindev_wdr_gp_s shutter_gp;	/*!< Shutter */
	struct vindev_wdr_gp_s again_gp;	/*!< Again */
	struct vindev_wdr_gp_s dgain_gp;	/*!< Dgain */
	struct vindev_wdr_gp_s rhs_gp;		/*!< RHS */
};
/*! @} */  /* End of iav-ioctl-vin-struct */


/*! @addtogroup iav-ioctl-vin-helper
 *  @{
 */
#define VINDEV_SHT_AGC_DELAY_MAX		8
#define VINDEV_SHT_AGC_DELAY_INVALID	VINDEV_SHT_AGC_DELAY_MAX
#define VINDEV_SHT_AGC_PARAM_NUM		4
/*! @} */  /* End of iav-ioctl-vin-helper */

/*! @addtogroup iav-ioctl-vin-struct
 *  @{
 */
struct vindev_sht_agc_seq {
	unsigned short vsrc_id;	/*!< Source ID of the current VIN */
	unsigned short max_exposure_num;	/*!< max exposure number */
	unsigned int shutter_delays[VINDEV_SHT_AGC_PARAM_NUM];	/*!< the delay frame counter of shutter */
	unsigned int again_delays[VINDEV_SHT_AGC_PARAM_NUM];	/*!< the delay frame counter of analog gain */
	unsigned int dgain_delays[VINDEV_SHT_AGC_PARAM_NUM];	/*!< the delay frame counter of digital gain */
};

struct vindev_ae_check {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	char ae_check_flag;	/*!< AE check flag */
};

struct vindev_stream_mode {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	char stream_mode;	/*!< steam mode */
};

struct vindev_low_light_info {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int ll_mode;	/*!< Low light mode */
};

struct vindev_tp_mode {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
	unsigned int tp_mode;	/*!< Test pattern mode */
};

struct vindev_switch_vsrc_ctx {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
};

struct vindev_lock_vsrc_ctx_frame_cnt {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
};

struct vindev_unlock_vsrc_ctx_frame_cnt {
	unsigned int vsrc_id;	/*!< Source ID of the current VIN */
};

struct vin_global_info {
	unsigned char total_vsrc_num;	/*!< Total video source number of all VIN controllers */
	unsigned char reserved[3];
	unsigned int vsrc_map[AMBA_VINC_MAX_NUM];	/*!< Video source bit map of each VIN controller */
	unsigned int active_vsrc_map;	/*!< Active video source bit map */
};

/*! @} */  /* End of iav-ioctl-vin-struct */

#ifdef __cplusplus
}
#endif

#endif	//__IAV_VIN_COMMON_H__

