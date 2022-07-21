/**
 * @file ambarella.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __AMBARELLA_H__
#define __AMBARELLA_H__

#include "target.h"

class ambarella : public deie_target
{
	public:
	 	ambarella();
		~ambarella();
		std::string dev; 
        void set_device(deie_device device);
        void set_video_file_input(deie_file_input *in);
        void set_img_file_input(deie_file_input *in);
        void set_camera_input();
        void set_stream_input();
	    void prepare_model(deie_model_info minfo);
		void run_inference(int *y, deie_io_desc *ptr[]);
};

#endif //__AMBARELLA_H__