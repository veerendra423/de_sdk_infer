/**
 * @file target.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __TARGET_H__
#define __TARGET_H__

#include "model.h"
#include "platform.h"

/**
 * @brief 
 * 
 */
class deie_target
{
    public:
        /**
         * @brief 
         * 
         * @param hw_type 
         * @return deie_target* 
         */
        static deie_target *deie_create_target(deie_hw_platform hw_type);

        /**
         * @brief Set the device object
         * 
         * @param device 
         */
        virtual void set_device(deie_device device)=0;

        /**
         * @brief Set the video file input object
         * 
         * @param in 
         */
        virtual void set_video_file_input(deie_file_input *in)=0;

        /**
         * @brief Set the img file input object
         * 
         * @param in 
         */
        virtual void set_img_file_input(deie_file_input *in)=0;

        /**
         * @brief Set the camera input object
         * 
         */
        virtual void set_camera_input()=0;

        /**
         * @brief Set the stream input object
         * 
         */
        virtual void set_stream_input()=0;

        /**
         * @brief 
         * 
         * @param minfo 
         */
        virtual void prepare_model(deie_model_info minfo)=0;

        /**
         * @brief 
         * 
         * @param y 
         * @param ptr 
         */
        virtual void run_inference(int *y, deie_io_desc *ptr[])=0;

        deie_file_input *infer_in;
};

#endif //__TARGET_H__