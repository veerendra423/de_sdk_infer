/**
 * @file efficientdet.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __EFFICIENTDET_H__
#define __EFFICIENTDET_H__

#include "target.h"

class efficientdet : public deie_detector
{
    private:
        deie_target *target;
        deie_detector_output process_out;
        deie_detector_model y_model;
        deie_io_desc in_node[MAX_INPUTS];
        deie_io_desc out_node[MAX_OUTPUTS];
        int num_inputs;
        int num_outputs;
    public:
		efficientdet();
		~efficientdet();
		// setup the edge hw on which object detection application would be running
        void set_target_env(deie_detector *detobj, deie_hw_platform tgt, deie_device device);
		void set_target_input(deie_detector *detobj, deie_input_src input, deie_file_input *path);  // for file and stream inputs
        void set_target_input(deie_detector *detobj, deie_input_src input, int devicefd); //for camera input
                
        // Inference related functions
		void set_model_info(deie_detector *detobj, deie_detector_model model);
	    
		// input preprocessing functions
        void set_input_pre_processing(deie_detector *detobj, deie_detector_input_preproc preproc, deie_input_color_format cfmt);
        void set_input_pre_processing(deie_detector *detobj, deie_detector_input_preproc preproc, void *value);

        // Model output postprocessing functions       
        void set_output_buffer(deie_detector *detobj, void *ptr, int size);
        void set_output_params(deie_detector *detobj, deie_detector_output_params outparams, int value);
        void allocate_io_buffer(deie_detector *detobj, deie_io_desc *ioptr);
        void free_io_buffer(deie_detector *detobj, deie_io_desc *ioptr);

        void set_model_input_buffers(deie_detector *detobj, int num, void** ptr);
        void set_model_output_buffers(deie_detector *detobj, int num, void** ptr);

        void register_custom_pre_processor(deie_detector *detobj, deie_detector_preprocessor preprocessor);
        void register_custom_post_processor(deie_detector *detobj, deie_detector_postprocessor postprocessor);
        
        void run_inference(deie_detector *detobj, deie_detector_process_results inference_out);  
		void stop_inference(deie_detector *detobj); 

		//Target Specific Post Processing functions
		void intel_nuc_post_process(void *, int num_outputs, deie_detector_model* out);
};
#endif //__EFFICIENTDET_H__