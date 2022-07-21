/**
 * @file unet.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __UNET_H__
#define __UNET_H__

#include "target.h"
#include "segmentation.h"

class unet : public deie_segment
{
    private:
		deie_target *target;
        deie_segment_output process_out;
        deie_segment_model y_model;
        deie_io_desc in_node[MAX_INPUTS];
        deie_io_desc out_node[MAX_OUTPUTS];
        int num_inputs;
        int num_outputs;

	public:
		unet();
		~unet();
		// setup the edge hw on which segmentation application would be running
        void set_target_env(deie_segment *segment, deie_hw_platform tgt, deie_device device);
		void set_target_input(deie_segment *segment, deie_input_src input, deie_file_input *path);  // for file and stream inputs
        void set_target_input(deie_segment *segment, deie_input_src input, int devicefd); //for camera input
                
        // Inference related functions
		void set_model_info(deie_segment *segment, deie_segment_model model);
	    
		// input preprocessing functions
        void set_input_pre_processing(deie_segment *segment, deie_segment_input_preproc preproc, deie_input_color_format cfmt);
        void set_input_pre_processing(deie_segment *segment, deie_segment_input_preproc preproc, void *value);

        // Model output postprocessing functions       
        void set_output_buffer(deie_segment *segment, void *ptr, int size);
        void set_output_params(deie_segment *segment, deie_segment_output_params outparams, int value);
        void allocate_io_buffer(deie_segment *segment, deie_io_desc *ioptr);
        void free_io_buffer(deie_segment *segment, deie_io_desc *ioptr);

        void set_model_input_buffers(deie_segment *segment, int num, void** ptr);
        void set_model_output_buffers(deie_segment *segment, int num, void** ptr);

        void register_custom_pre_processor(deie_segment *segment, deie_segment_preprocessor preprocessor);
        void register_custom_post_processor(deie_segment *segment, deie_segment_postprocessor postprocessor);
        
        void run_inference(deie_segment *segment, deie_segment_process_results inference_out);  
		void stop_inference(deie_segment *segment); 

		//Target Specific Post Processing functions
		void intel_nuc_post_process(void *, int num_outputs, deie_segment_model* out);
};

#endif //__UNET_H__