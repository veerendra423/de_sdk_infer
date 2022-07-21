/**
 * @file platform.h
 * @author your name (you@domain.com)
 * @brief target discription
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Deepedge.ai, Inc. and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Deepedge.ai, Inc. or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Deepedge.ai, Inc.
 * 
 */

// Lists supported HW platforms and chipsets
#ifndef __DEIE_PLATFORM_H__
#define __DEIE_PLATFORM_H__
#include<iostream>
#include<vector>

using namespace std;

/**
 * @brief 
 * device type ex: CPU or GPU etc..
 * 
 */
typedef enum{
    DEIE_DEVICE_CPU=1,
    DEIE_DEVICE_GPU=2,
    DEIE_DEVICE_DSP=3,
    DEIE_DEVICE_VP=4,
    DEIE_DEVICE_MAX=99
}deie_device;

/**
 * @brief 
 * supported platforms
 * 
 */
typedef enum {
    // Ambarella
    DEIE_HW_AMBA_CV2=1, 
    DEIE_HW_AMBA_CV22=2,
    DEIE_HW_AMBA_CV25=3,
    DEIE_HW_AMBA_CV28=4,

    // Xilinx
    DEIE_HW_XILINX_ZCU102=11, 
    DEIE_HW_XILINX_ZCU104=12,
    DEIE_HW_XILINX_ZCU106=13,
    DEIE_HW_XILINX_KV260=14,

    // Intel
    DEIE_HW_INTEL_OPENVINO_NUC=21,

    // Nvidia
    DEIE_HW_NVIDIA_JETSON_TX1=31,
    DEIE_HW_NVIDIA_JETSON_TX2=32,
    DEIE_HW_NVIDIA_JETSON_NANO=33,
    DEIE_HW_NVIDIA_JETSON_XAVIER=34,

    DEIE_HW_KINARA=51, // DeepVision
    DEIE_HW_END=99
}deie_hw_platform;

/**
 * @brief 
 * supported input data types
 * 
 */
typedef enum {
    DEIE_INPUT_SRC_LIVE_CAMERA=1, 
    DEIE_INPUT_SRC_LIVE_STREAM=2,
    DEIE_INPUT_SRC_FILE_VIDEO=3,
    DEIE_INPUT_SRC_FILE_IMAGE=4,
    DEIE_INPUT_SRC_END=99
}deie_input_src;

/**
 * @brief 
 * supported color formats
 * 
 */
typedef enum {
    DEIE_INPUT_COLOR_FORMAT_RGB=1,
    DEIE_INPUT_COLOR_FORMAT_BGR=2,
    DEIE_INPUT_COLOR_FORMAT_YUV=3,
    DEIE_INPUT_COLOR_FORMAT_MONO=4,
    DEIE_INPUT_COLOR_FORMAT_END=99
}deie_input_color_format;

/**
 * @brief 
 * input image path
 * 
 */
typedef struct {
    std::string path;
    std::string task;
    std::vector<std::string> files;
    std::string img_file;
}deie_file_input;

#endif  //__DEIE_PLATFORM_H__