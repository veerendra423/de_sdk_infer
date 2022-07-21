/**
 * @file xilinx.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __XILINX_H__
#define __XILINX_H__

#include "target.h"
/* header file for Vitis AI unified API */
#include <vart/mm/host_flat_tensor_buffer.hpp>
#include <vart/runner.hpp>
#include <xir/graph/graph.hpp>
#include <xir/tensor/tensor.hpp>
#include <xir/util/data_type.hpp>


class xilinx : public deie_target
{
	public:
		xilinx();
		~xilinx();
		std::string dev;
		deie_model_info xmodel;
		std::unique_ptr<vart::Runner> runner;	
        void set_device(deie_device device);
        void set_video_file_input(deie_file_input *in);
        void set_img_file_input(deie_file_input *in);
        void set_camera_input();
        void set_stream_input();
	    void prepare_model(deie_model_info minfo);
		void run_inference(int *y, deie_io_desc *ptr[]);
};

#endif //__XILINX_H__