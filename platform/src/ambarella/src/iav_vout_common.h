/*
 * iav_vout_common.h
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

#ifndef __IAV_VOUT_COMMON_H__
#define __IAV_VOUT_COMMON_H__

/*! @file iav_vout_common.h
 *  @brief This file defines video output configuration ioctl
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

/*! @addtogroup iav-ioctl-vout-helper
 *  @{
 */
#define VOUT_LCD			0
#define VOUT_TV				1
#if defined(CONFIG_DRIVER_VERSION_V6)
#define VOUT_NUM			3
#else
#define VOUT_NUM			2
#endif

#define VOUT0				0
#define VOUT1				1
#define VOUT2				2

/* VOUT type */
enum {
	VOUT_TYPE_LCD = 0,	/*!< 0 */
	VOUT_TYPE_HDMI = 1,	/*!< 1 */
	VOUT_TYPE_CVBS = 2,	/*!< 2 */
	VOUT_TYPE_MIPI_DSI = 3,	/*!< 3 */
	VOUT_TYPE_MIPI_CSI = 4,	/*!< 4 */
	VOUT_TYPE_FPD_LINK = 5,	/*!< 5 */
	VOUT_TYPE_SLVS = 6,	/*!< 6 */
	VOUT_TYPE_NUM,
};

/* VOUT config status */
enum {
	VOUTC_STATUS_DISABLE = 0,	/*!< 0 */
	VOUTC_STATUS_ON,			/*!< 1 */
	VOUTC_STATUS_OFF,		/*!< 2 */
	VOUTC_STATUS_RESET,		/*!< 3 */
};

/* VOUT flip type, it's related to DSP command, so don't change the order */
enum {
	VOUT_FLIP_NO = 0,		/*!< 0, No flip */
	VOUT_FLIP_HV,			/*!< 1, Horizontal and Vertical */
	VOUT_FLIP_H,			/*!< 2, Horizontal */
	VOUT_FLIP_V,			/*!< 3, Vertical */
};

/* HDMI color space, it's related to AVI InfoFrame, so don't change the order */
enum {
	VOUT_HDMI_CS_RGB = 0,	/*!< 0 */
	VOUT_HDMI_CS_YCBCR_422,	/*!< 1 */
	VOUT_HDMI_CS_YCBCR_444,	/*!< 2 */
	VOUT_HDMI_CS_YCBCR_420,	/*!< 3 */
};

enum {
	VOUT_HDMI_AUTOSCAN = 0,	/*!< 0 */
	VOUT_HDMI_OVERSCAN,	/*!< 1 */
	VOUT_HDMI_UNDERSCAN,	/*!< 2 */
};
/*! @} */  /* End of iav-ioctl-vout-helper */


/*! @addtogroup iav-ioctl-vout-struct
 *  @{
 */
struct voutdev_format {
	unsigned int id;	/*!< VOUT ID */
	unsigned int type;	/*!< sink type: CVBS, HDMI or LCD */
	unsigned int mode;	/*!< VOUT mode (resolution index) */
	unsigned int interlaced;/*!< VOUT interlaced or progressive */
	unsigned int fps;	/*!< VOUT FPS */
	unsigned int vout_append_enable : 1; /*!< VOUT append enable flag */
	unsigned int vout_from_image : 1; /*!< VOUT source from image flag */
	unsigned int default_img_yuv420 : 1; /*!< Specify VOUT default image format. 0(default) : YUV422; 1 : YUV420 */
	unsigned int hdmi_cs : 3;	/*!< VOUT hdmi output color space */
	unsigned int reserved : 26;
};

struct vout_params {
	unsigned int id;		/*!< VOUT ID */
	struct iav_rect vout_win;	/*!< VOUT window size */
	struct iav_rect video_win;	/*!< VOUT video size */
	struct iav_rect osd_win;	/*!< VOUT OSD size */
	struct iav_rect osd_rescaler_win; /*!< VOUT OSD rescale output size */
	unsigned int fps;		/*!< VOUT frame rate */
	unsigned int video_rotate : 1;	/*!< VOUT Video rotate */
	unsigned int video_flip : 2;	/*!< VOUT Video flip */
	unsigned int osd_flip : 2;	/*!< VOUT OSD flip */
	unsigned int osd_rescaler_en : 1; /*!< VOUT OSD rescaler enable flag */
	unsigned int video_enable : 1;	/*!< VOUT Video enable flag */
	unsigned int osd_enable : 1;	/*!< VOUT OSD enable flag */
	unsigned int own_mixer : 1;	/*!< VOUT Own mixer flag */
	unsigned int reserved : 23;
};

struct vout_onoff {
	unsigned int id; /*!< VOUT ID */
	unsigned int on; /*!< 0: off, 1: on */
};
/*! @} */  /* End of iav-ioctl-vout-struct */
/* ==========================================================================*/

/*! @addtogroup iav-ioctl-vout-helper
 *  @{
 */

#define AMBA_VOUT_NAME_LENGTH		(32)

#define AMBA_VOUT_SOURCE_TYPE_DVE	(1 << 0)
#define AMBA_VOUT_SOURCE_TYPE_DIGITAL	(1 << 1)
#define AMBA_VOUT_SOURCE_TYPE_HDMI	(1 << 2)
#define AMBA_VOUT_SOURCE_TYPE_MIPI	(1 << 3)

#define AMBA_VOUT_SOURCE_STARTING_ID	(0)
#define AMBA_VOUT_SINK_STARTING_ID	(0)

enum amba_vout_display_device_type {
	AMBA_VOUT_DISPLAY_DEVICE_LCD		= 0,
	AMBA_VOUT_DISPLAY_DEVICE_HDMI,
};

enum amba_vout_output_port_id {
        AMBA_VOUT_OUTPUT_DVE = AMBA_VOUT_SOURCE_TYPE_DVE,
        AMBA_VOUT_OUTPUT_DIGITAL = AMBA_VOUT_SOURCE_TYPE_DIGITAL,
        AMBA_VOUT_OUTPUT_HDMI = AMBA_VOUT_SOURCE_TYPE_HDMI,
        AMBA_VOUT_OUTPUT_MIPI = AMBA_VOUT_SOURCE_TYPE_MIPI,
};

enum amba_vout_sink_type {
	AMBA_VOUT_SINK_TYPE_AUTO = 0,
	AMBA_VOUT_SINK_TYPE_CVBS = ((0 << 16) | AMBA_VOUT_SOURCE_TYPE_DVE),
	AMBA_VOUT_SINK_TYPE_SVIDEO = ((1 << 16) | AMBA_VOUT_SOURCE_TYPE_DVE),
	AMBA_VOUT_SINK_TYPE_YPBPR = ((2 << 16) | AMBA_VOUT_SOURCE_TYPE_DVE),
	AMBA_VOUT_SINK_TYPE_HDMI = ((0 << 16) | AMBA_VOUT_SOURCE_TYPE_HDMI),
	AMBA_VOUT_SINK_TYPE_DIGITAL = ((0 << 16) | AMBA_VOUT_SOURCE_TYPE_DIGITAL),
	AMBA_VOUT_SINK_TYPE_MIPI = ((0 << 16) | AMBA_VOUT_SOURCE_TYPE_MIPI),
};

enum amba_vout_display_input {
	AMBA_VOUT_INPUT_FROM_MIXER = 0,
	AMBA_VOUT_INPUT_FROM_SMEM,
};

enum amba_vout_flip_info {
	AMBA_VOUT_FLIP_NORMAL = 0,
	AMBA_VOUT_FLIP_HV,
	AMBA_VOUT_FLIP_HORIZONTAL,
	AMBA_VOUT_FLIP_VERTICAL,
};

enum amba_vout_rotate_info {
	AMBA_VOUT_ROTATE_NORMAL,
	AMBA_VOUT_ROTATE_90,
};

enum amba_vout_tailored_info {
	AMBA_VOUT_OSD_NO_CSC	= 0x01,			/*!< No Software CSC */
	AMBA_VOUT_OSD_AUTO_COPY	= 0x02,			/*!< Auto copy to other fb */
};

enum amba_vout_mixer_csc {
       AMBA_VOUT_MIXER_DISABLE            = 0x00, /*!< No Mixer CSC */
       AMBA_VOUT_MIXER_ENABLE_FOR_VIDEO	= 0x01, /*!< Mixer CSC for video */
       AMBA_VOUT_MIXER_ENABLE_FOR_OSD     = 0x02, /*!< Mixer CSC for OSD */
};

enum amba_vout_hdmi_color_space {
	AMBA_VOUT_HDMI_CS_AUTO = 0,
	AMBA_VOUT_HDMI_CS_RGB,
	AMBA_VOUT_HDMI_CS_YCBCR_444,
	AMBA_VOUT_HDMI_CS_YCBCR_422,
};

enum amba_vout_hdmi_overscan {
	AMBA_VOUT_HDMI_OVERSCAN_AUTO = 0,
	AMBA_VOUT_HDMI_NON_FORCE_OVERSCAN,
	AMBA_VOUT_HDMI_FORCE_OVERSCAN,
};

enum amba_vout_sink_state {
	AMBA_VOUT_SINK_STATE_IDLE = 0,
	AMBA_VOUT_SINK_STATE_RUNNING,
	AMBA_VOUT_SINK_STATE_SUSPENDED,
};

enum amba_vout_lcd_mode_info {
	AMBA_VOUT_LCD_MODE_DISABLE = 0,
	AMBA_VOUT_LCD_MODE_1COLOR_PER_DOT,
	AMBA_VOUT_LCD_MODE_3COLORS_PER_DOT,
	AMBA_VOUT_LCD_MODE_RGB565,
	AMBA_VOUT_LCD_MODE_3COLORS_DUMMY_PER_DOT,
	AMBA_VOUT_LCD_MODE_RGB888,
};

enum amba_vout_lcd_seq_info {
	AMBA_VOUT_LCD_SEQ_R0_G1_B2 = 0,
	AMBA_VOUT_LCD_SEQ_R0_B1_G2,
	AMBA_VOUT_LCD_SEQ_G0_R1_B2,
	AMBA_VOUT_LCD_SEQ_G0_B1_R2,
	AMBA_VOUT_LCD_SEQ_B0_R1_G2,
	AMBA_VOUT_LCD_SEQ_B0_G1_R2,
};

enum amba_vout_lcd_clk_edge_info {
	AMBA_VOUT_LCD_CLK_RISING_EDGE	= 0,
	AMBA_VOUT_LCD_CLK_FALLING_EDGE,
};

enum amba_vout_lcd_hvld_pol_info {
	AMBA_VOUT_LCD_HVLD_POL_LOW	= 0,
	AMBA_VOUT_LCD_HVLD_POL_HIGH,
};

enum amba_vout_lcd_model {
	AMBA_VOUT_LCD_MODEL_DIGITAL	= 0,
	AMBA_VOUT_LCD_MODEL_AUO27,
	AMBA_VOUT_LCD_MODEL_P28K,
	AMBA_VOUT_LCD_MODEL_TPO489,
	AMBA_VOUT_LCD_MODEL_TPO648,
	AMBA_VOUT_LCD_MODEL_TD043,
	AMBA_VOUT_LCD_MODEL_WDF2440,
	AMBA_VOUT_LCD_MODEL_1P3831,
	AMBA_VOUT_LCD_MODEL_1P3828,
	AMBA_VOUT_LCD_MODEL_EJ080NA,
	AMBA_VOUT_LCD_MODEL_AT070TNA2,
	AMBA_VOUT_LCD_MODEL_E330QHD,
	AMBA_VOUT_LCD_MODEL_PPGA3,
};

enum amba_vout_sink_plug {
	AMBA_VOUT_SINK_PLUGGED = 0,
	AMBA_VOUT_SINK_REMOVED,
};

enum ddd_structure {
	DDD_FRAME_PACKING		= 0,
	DDD_FIELD_ALTERNATIVE		= 1,
	DDD_LINE_ALTERNATIVE		= 2,
	DDD_SIDE_BY_SIDE_FULL		= 3,
	DDD_L_DEPTH			= 4,
	DDD_L_DEPTH_GRAPHICS_DEPTH	= 5,
	DDD_TOP_AND_BOTTOM		= 6,
	DDD_RESERVED			= 7,

	DDD_SIDE_BY_SIDE_HALF		= 8,

	DDD_UNSUPPORTED			= 16,
};
/*! @} */   /* End of iav-ioctl-vout-helper */

/*! @addtogroup iav-ioctl-vout-struct
 *  @{
 */
struct amba_vout_bg_color_info {
	u8 y;
	u8 cb;
	u8 cr;
};

struct amba_vout_video_size {
	u32 specified;
	u16 vout_width;		/*!< Vout width */
	u16 vout_height;	/*!< Vout height */
	u16 video_width;	/*!< Video width */
	u16 video_height;	/*!< Video height */
};

struct amba_vout_video_offset {
	u32 specified;
	s16 offset_x;
	s16 offset_y;
};

struct amba_vout_osd_size {
	u16 width;
	u16 height;
};

struct amba_vout_osd_rescale {
	u32 enable;
	u16 width;
	u16 height;
};

struct amba_vout_osd_offset {
	u32 specified;
	s16 offset_x;
	s16 offset_y;
};

struct amba_vout_lcd_info {
	enum amba_vout_lcd_mode_info		mode;
	enum amba_vout_lcd_seq_info		seqt;
	enum amba_vout_lcd_seq_info		seqb;
	enum amba_vout_lcd_clk_edge_info	dclk_edge;
	enum amba_vout_lcd_hvld_pol_info	hvld_pol;
	u32					dclk_freq_hz;	/*!< PLL_CLK_XXX */
	enum amba_vout_lcd_model		model;
};
/*! @} */   /* End of iav-ioctl-vout-struct */

/*! @addtogroup iav-ioctl-vout-helper */
typedef enum {
	COLORIMETRY_NO_DATA	= 0,
	COLORIMETRY_ITU601	= 1,
	COLORIMETRY_ITU709	= 2,
	COLORIMETRY_EXTENDED	= 3,
} colorimetry_t;

/*! @addtogroup iav-ioctl-vout-struct
 *  @{
 */
typedef struct {
	enum amba_video_mode			vmode;
	char					name[32];

	u32					pixel_clock;		/*!< kHz */

	u16					hsync_offset;		/*!< pixels */
	u16					hsync_width;		/*!< pixels */
	u16					h_blanking;		/*!< pixels */
	u16					h_active;		/*!< pixels */

	u16					vsync_offset;		/*!< lines */
	u16					vsync_width;		/*!< lines */
	u16					v_blanking;		/*!< lines */
	u16					v_active;		/*!< lines */

	u8					interlace;		/*!< 1: Interlace; 0: Progressive */
	u8					hsync_polarity;		/*!< 1: Positive; 0: Negative */
	u8					vsync_polarity;		/*!< 1: Positive; 0: Negative */

	u8					pixel_repetition;	/*!< repetition times */
	u32					aspect_ratio;		/*!< 16:9, 4:3, ... */
	colorimetry_t				colorimetry;		/*!< ITU601, ITU709 */
} amba_hdmi_video_timing_t;


struct amba_video_sink_mode {
	/* Sink */
	int				id;		/*!< Sink ID */
	u32				mode;		/*!< enum amba_video_mode */
	u32				ratio;		/*!< AMBA_VIDEO_RATIO */
	u32				bits;		/*!< AMBA_VIDEO_BITS */
	u32				type;		/*!< AMBA_VIDEO_TYPE */
	u32				format;		/*!< AMBA_VIDEO_FORMAT */
	u32				frame_rate;	/*!< AMBA_VIDEO_FPS */
	int				csc_en;		/*!< enable csc or not */
	struct amba_vout_bg_color_info	bg_color;
	enum amba_vout_display_input	display_input;	/*!< input from SMEM or Mixer */
	enum amba_vout_sink_type	sink_type;
	enum amba_vout_mixer_csc	mixer_csc;

	/* Video */
	int				video_en;	/*!< enable video or not */
	struct amba_vout_video_size	video_size;	/*!< video size */
	struct amba_vout_video_offset	video_offset;	/*!< video offset */
	enum amba_vout_flip_info	video_flip;	/*!< flip */
	enum amba_vout_rotate_info	video_rotate;	/*!< rotate */

	/* OSD */
	int				fb_id;		/*!< frame buffer id */
	struct amba_vout_osd_size	osd_size;	/*!< OSD size */
	struct amba_vout_osd_rescale	osd_rescale;	/*!< OSD rescale */
	struct amba_vout_osd_offset	osd_offset;	/*!< OSD offset */
	enum amba_vout_flip_info	osd_flip;	/*!< flip */
	enum amba_vout_rotate_info	osd_rotate;	/*!< rotate */
	enum amba_vout_tailored_info	osd_tailor;	/*!< no csc, auto copy */

	/* Misc */
	u32				direct_to_dsp;	/*!< bypass iav */
	struct amba_vout_lcd_info	lcd_cfg;	/*!< LCD only */
	enum amba_vout_hdmi_color_space hdmi_color_space;/*!< HDMI only */
	enum ddd_structure		hdmi_3d_structure;/*!< HDMI only */
	enum amba_vout_hdmi_overscan	hdmi_overscan;	/*!< HDMI only */
	const amba_hdmi_video_timing_t  *hdmi_displayer_timing; /*!< HDMI only */
};

struct amba_vout_sink_info {
	int					id;		/*!< Sink ID */
	int					source_id;
	char					name[AMBA_VOUT_NAME_LENGTH];
	enum amba_vout_sink_type		sink_type;
	struct amba_video_sink_mode		sink_mode;
	enum amba_vout_sink_state		state;
	enum amba_vout_sink_plug		hdmi_plug;
	enum amba_video_mode			hdmi_modes[32];
	enum amba_video_mode			hdmi_native_mode;
	u16					hdmi_native_width;
	u16					hdmi_native_height;
	enum amba_vout_hdmi_overscan		hdmi_overscan;

};

typedef struct iav_vout_fb_sel_s {
	int		vout_id;
	int		fb_id;
} iav_vout_fb_sel_t;

typedef struct iav_vout_enable_video_s {
	int		vout_id;
	int		video_en;
} iav_vout_enable_video_t;

typedef struct iav_vout_flip_video_s {
	int		vout_id;
	int		flip;
} iav_vout_flip_video_t;

typedef struct iav_vout_rotate_video_s {
	int		vout_id;
	int		rotate;
} iav_vout_rotate_video_t;

typedef struct iav_vout_enable_csc_s {
	int		vout_id;
	int		csc_en;
} iav_vout_enable_csc_t;

typedef struct iav_vout_change_video_size_s {
	int		vout_id;
	int		width;
	int		height;
} iav_vout_change_video_size_t;

typedef struct iav_vout_change_video_offset_s {
	int		vout_id;
	int		specified;
	int		offset_x;
	int		offset_y;
} iav_vout_change_video_offset_t;

typedef struct iav_vout_flip_osd_s {
	int		vout_id;
	int		flip;
} iav_vout_flip_osd_t;

typedef struct iav_vout_enable_osd_rescaler_s {
	int		vout_id;
	int		enable;
	int		width;
	int		height;
} iav_vout_enable_osd_rescaler_t;

typedef struct iav_vout_change_osd_offset_s {
	int		vout_id;
	int		specified;
	int		offset_x;
	int		offset_y;
} iav_vout_change_osd_offset_t;

typedef struct iav_vout_sync_img_osd_s {
	int		vout_id;

	u32		img_luma_addr;
	u32		img_chroma_addr;
	int		img_pitch;

	u32		osd_buf_addr;
	int		osd_pitch;
} iav_vout_sync_img_osd_t;

/*! @} */   /* End of iav-ioctl-vout-struct */


/****************************************************/
/* version for HDMI phy value version              */
/****************************************************/
#define	HDMI_PHYVAL_VERSION_0		0
#define	HDMI_PHYVAL_VERSION_1		1

struct mipi_vout_info {
	u32 vout_id;
	u32 type;
	u32 output_mode;

	u32 tx_bias_en : 1;
	u32 tx_ibctrl : 3;
	u32 tx_vcmset : 3;
	u32 tx_pib : 4;
	u32 tx_lvds_res_en : 1;
	u32 tx_lvds_rsel : 4;
	u32 reserved : 16;
};

typedef struct setval_s {
	u32 vout_id;
	u32 val;
} setval_t;

struct cvbs_info {
	u32 vout_id;
	u32 interlace;
	u32 active_width;
	u32 active_height;
	u32 frequency;
	u32 blacklevel;
	u32 blanklevel;
	u32 synclevel;
	u32 ygain;
	u32 cgain;
};

struct hdmi_info {
	u32 vout_id;
	int connect;
	u32 output_color_format;

	u32 phy_version;
	u32 pib : 4;
	u32 pib_ib : 4;
	u32 pre_emp_tap0_cur : 4;
	u32 pre_emp_tap1_cur : 3;
	u32 pre_emp_tap2_cur : 3;
	u32 pos_emp_tap1_cur : 4;
	u32 bias_control : 4;
	u32 reserved : 6;
	u32 termination;
};

#ifdef __cplusplus
}
#endif

#endif // __IAV_VOUT_COMMON_H__


