/*
 * basetypes.h
 *
 * Histroy:
 *  2012-12-12 [Louis] Created file
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

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

/*! @file basetypes.h
 *  @brief This file defines basic types used in all IAV driver and header files
 */
#ifdef __cplusplus
extern "C" {
#endif

/*! @addtogroup iav-basetype
 *  @{
 */

/*!
 * @defgroup iav-typedef IAV Typedef
 * @{
 */
typedef unsigned char       u8; /*!< UNSIGNED  8-bit data type */
typedef unsigned short     u16; /*!< UNSIGNED 16-bit data type */
typedef unsigned int       u32; /*!< UNSIGNED 32-bit data type */
typedef unsigned long long u64; /*!< UNSIGNED 64-bit data type */
typedef signed char         s8; /*!<   SIGNED  8-bit data type */
typedef signed short       s16; /*!<   SIGNED 16-bit data type */
typedef signed int         s32; /*!<   SIGNED 32-bit data type */
typedef signed long long   s64; /*!<   SIGNED 64-bit data type */
/*! @} */

/*!
 * @defgroup iav-define IAV Macros
 * @breif All IAV Macros Definition
 * @{
 */
/*!
 * @defgroup iav-define-common IAV Common Macros
 * @brief Common IAV Macros
 * @{
 */
/*! @macros AMBA_API
 *  @brief API function attribute */
#define AMBA_API __attribute__((visibility("default")))

/*! @macros ARRAY_SIZE
 *  @breif Helper macro to calculate array size */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)		(sizeof(x) / sizeof((x)[0]))
#endif
/*! @} */ /* End of iav-define-common */

/*! @} */ /* End of iav-define */

/* ==========================================================================*/

/*!
 * @defgroup iav-structure IAV Data Structures
 * @ingroup iav-structure-common
 * @brief Common IAV Data Structure
 * @{
 */
/*! @struct iav_window
 *  @brief IAV Window Size
 */
struct iav_window {
	u32 width;  //!< Window width
	u32 height; //!< Window height
};

/*! @struct iav_offset
 *  @brief IAV Window Starting Point
 */
struct iav_offset {
	u32 x; //!< Offset X
	u32 y; //!< Offset Y
};

/*! @struct iav_rect
 *  @brief IAV rectangle
 */
struct iav_rect {
	u32 x;      //!< Offset X
	u32 y;      //!< Offset Y
	u32 width;  //!< Width
	u32 height; //!< Height
};
/* @} */

/*! @struct iav_circle
 *  @brief IAV circle
 */
struct iav_circle {
	u16 center_x;      //!< Circle Center Offset X
	u16 center_y;      //!< Circle Center Offset Y
	u16 radius;  //!< Circle Radius
	u16 reserved;
};
/* @} */

/*! @struct iav_point
 *  @brief IAV point
 */
struct iav_point{
	int x;
	int y;
};
/* @} */

/*!
 * @ingroup iav-define-common
 * @{
 */

/*! @macros rect_init(_x, _y, _w, _h)
 *  @brief struct @sa iav_rect init macro
 */
#define rect_init(_x, _y, _w, _h)(	\
{				\
	struct iav_rect _r;		\
	_r.x = (_x); _r.y = (_y); _r.width = (_w); _r.height = (_h);	\
	_r;			\
})

/*! @macros win_init(w, h)
 *  @brief @sa rect_init(_x, _y, _w, _h)
 */
#define win_init(w, h)		rect_init(0, 0, w, h)

/*! @macros win_invalid(w)
 *  @sa iav_window
 */
#define win_invalid(w)		((w).width == 0 || (w).height == 0)

/*! @macros win_diff(w1, w2)
 *  @sa iav_window
 */
#define win_diff(w1, w2)	(((w1).width != (w2).width) || ((w1).height != (w2).height))

/*! @macros rect_invalid(w)
 *  @sa iav_rect
 */
#define rect_invalid(w)		(win_invalid(w) || (w).x > 0xffff || (w).y > 0xffff)

/*! return 1 if r1 contains r2 */
#define rect_contain(r1, r2) ({			\
	u32 _x1 = (r1).x, _y1 = (r1).y, _w1 = (r1).width, _h1 = (r1).height; \
	u32 _x2 = (r2).x, _y2 = (r2).y, _w2 = (r2).width, _h2 = (r2).height; \
	_x1 <= _x2 && (_x1 + _w1) >= (_x2 + _w2) &&		\
	_y1 <= _y2 && (_y1 + _h1) >= (_y2 + _h2) ? 1 : 0;	\
	 })
/*! @} */

/* ==========================================================================*/

/*!
 * @defgroup IAV Helper Function
 * @brief IAV Helper Functions
 * @{
 */
/*! Helper function to set a perticular bit
 *  @param bit_map Pointer to an actual bitmap to be set
 *  @param nr The bit number, which will be set
 */
static inline void iav_set_bit(u32 *bit_map, int nr)
{
	*bit_map |= (1 << nr);
}

/*! Helper function to test if a perticular bit is set
 *  @param bit_map Pointer to an actual bitmap to be tested
 *  @param nr The bit number, which will be tested
 */
static inline int iav_test_bit(u32 *bit_map, int nr)
{
	return !!((*bit_map) & (1 << nr));
}
/* @} */

/* ==========================================================================*/
/* @} */ /* IAV API */

#ifdef __cplusplus
}
#endif

#endif
