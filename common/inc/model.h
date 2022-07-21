/**
 * @file model.h
 * @author your name (you@domain.com)
 * @brief model description
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

#ifndef __DEIE_MODEL_H__
#define __DEIE_MODEL_H__

#include <vector>
#define MAX_LENGTH 100
#define MAX_INPUTS 2
#define MAX_OUTPUTS 10

// Model specific data
/**
 * @brief 
 * model io dimensions
 * 
 */
typedef struct {
    unsigned int plane;  // No. of planes
    unsigned int depth;  // No. of Channels
    unsigned int height; // height of the vector (matrix rows)
    unsigned int width;  // width of the vector (matrx columns)
}deie_model_io_dims;

/**
 * @brief 
 * model output data formats and size
 * 
 */
typedef struct {
    unsigned int type;    // 0: Floating point;  1: Fixed point;
    unsigned int size;    // 0: 8-bit;  1: 16-bit;  2: 32-bit;  3: 64-bit 
}deie_model_io_format;

/**
 * @brief 
 * model info
 * 
 */
typedef struct {
    char name[MAX_LENGTH];            // Name of the io node
    deie_model_io_dims dims;          // io vector size
    deie_model_io_format fmt;  // 0: Floating point;  1: Fixed point;
}deie_model_io_info;

/**
 * @brief 
 * model output info
 * 
 */
typedef struct{
    void *data;
    deie_model_io_info info;
}deie_io_desc;

/**
 * @brief 
 * total top level model info
 * 
 */
typedef struct {
    char path[MAX_LENGTH];
    char name[MAX_LENGTH];
    unsigned int num_inputs;
    deie_model_io_info inputs[MAX_INPUTS];
    unsigned int num_outputs;
    deie_model_io_info outputs[MAX_OUTPUTS];
}deie_model_info;

#endif //__DEIE_MODEL_H__