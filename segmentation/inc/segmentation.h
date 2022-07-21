/**
 * @file segmentation.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include "model.h"
#include "platform.h"  //HW platforms supported by the DE SDK
#include <vector>
#include <nlohmann/json.hpp>

#define MAX_ANCHORS 0

//Lists all supported segment model architectures
/**
 * @brief 
 * model architecture types
 * 
 */
typedef enum {
    DEIE_SEGMENT_TYPE_U_NET=1, 
    DEIE_SEGMENT_TYPE_FCN=2,
    DEIE_SEGMENT_TYPE_FAST_FCN=3,
    DEIE_SEGMENT_TYPE_GATED_SCNN=4,
    DEIE_SEGMENT_TYPE_DEEPLAB=5,
    DEIE_SEGMENT_TYPE_MASK_R_CNN=6, 
    DEIE_SEGMENT_TYPE_END=99
}deie_segment_class;

/**
 * @brief 
 * bounding box dimensions
 * 
 */
typedef struct
{
    int left;
    int right;
    int low;
    int high;
}deie_box;

/**
 * @brief 
 * object details
 * 
 */
typedef struct
{
    int id;
    float score;
    deie_box box;
}deie_object;

/**
 * @brief 
 * @payload     : output detections
 * @num_objects : number of objects
 * 
 */
typedef struct {
    nlohmann::json payload;
    int num_objects;
    //vector<deie_object> object_info;
}deie_segment_output; 

/**
 * @brief 
 * @x   :anchors X
 * @y   :anchors Y
 */
typedef struct {
    unsigned int x;   
    unsigned int y;   
}deie_model_anchors;

/**
 * @brief 
 * @type    :deie_detector_class structure variable
 * @info    :deie_model_info structure variable
 * @num_classes :number of classes
 * @num_anchers :number of anchors
 * @anchors[MAX_ANCHORS]    :deie_model_anchors stucture 
 *  variable with array
 * 
 */
typedef struct {
    deie_segment_class type;
    deie_model_info    info;
    unsigned int num_classes; 
    unsigned int num_anchors; 
    deie_model_anchors anchors[MAX_ANCHORS];   
}deie_segment_model;


// Input data management for inference 
//Lists all supported object detection model architectures
/**
 * @brief 
 * input preprocssing parameters
 */
typedef enum {
    DEIE_SEGMENT_INPUT_MEAN=1,
    DEIE_SEGMENT_INPUT_SCALING=2,
    DEIE_SEGMENT_INPUT_COLOR_FORMAT=3, 
    DEIE_SEGMENT_INPUT_PREPROC_NONE=98,
    DEIE_SEGMENT_INPUT_PREPROC_END=99
}deie_segment_input_preproc;

/**
 * @brief 
 * output parameters
 * 
 */
typedef enum {
    DEIE_SEGMENT_OUTPUT_PARAM_NMS_THRESHOLD=1,
    DEIE_SEGMENT_OUTPUT_PARAM_END=99
}deie_segment_output_params;

/**
 * @brief 
 * custom defined functions
 * 
 */
typedef void (*deie_segment_process_results)(void*, deie_segment_output*);
typedef void (*deie_segment_preprocessor)(void*, void*, int, void*, int);
typedef void (*deie_segment_postprocessor)(void *, int, deie_segment_model*);


class deie_segment
{
    public:
        /**
         * @brief 
         * it will create the object of type based on model architecture
         * which is sent by the application
         * 
         * @param 
         * type it indicates the model architecture
         * @return deie_segment* 
         * returns the object
         */
        static deie_segment* deie_create_segment(deie_segment_class type);

        // setup the edge hw on which object detection application would be running
        /**
         * @brief creates the target env object 
         * and target specific initializations
         * 
         * @param segment segment object
         * it is the detector object(model architecture)
         * @param target 
         * it is type of the target
         * ex: intel, ambarella, xilinx etc..
         * @param device 
         * it is type of device
         * ex: CPU, GPU, VP etc..
         */
        virtual void set_target_env(deie_segment *segment, deie_hw_platform target, deie_device device)=0;

        /**
         * @brief it sets the target input for file and stream inputs
         * 
         * @param segment 
         * @param input 
         * input source type file input or stream input
         * ex: image, mp4 etc..
         * @param path path to the input source file
         */
        virtual void set_target_input(deie_segment *segment, deie_input_src input, deie_file_input *path)=0;

        /**
         * @brief it sets the target input for camera input
         * 
         * @param segment 
         * @param input 
         * input source type camera
         * @param devicefd 
         * camera id: 0 or 1 and for ambarella /dev/iav etc,..
         */
        virtual void set_target_input(deie_segment *segment, deie_input_src input, int devicefd)=0;
                
        /**
         * @brief Set the model info 
         * 
         * @param segment 
         * @param model 
         * structure variable which containes the all model details.
         */
	    virtual void set_model_info(deie_segment *segment, deie_segment_model model)=0;

        // input preprocessing functions
        /**
         * @brief Sets input pre_processing for images or frames
         * 
         * @param segment 
         * @param preproc 
         * custom preprocessor function
         * @param cfmt 
         * image colour format enum
         */
        virtual void set_input_pre_processing(deie_segment *segment, deie_segment_input_preproc preproc, deie_input_color_format cfmt)=0;

        /**
         * @brief Set the input pre processing object
         * 
         * @param segment 
         * @param preproc
         * custom preprocessor function
         * @param value 
         * preprocessing value
         */
        virtual void set_input_pre_processing(deie_segment *segment, deie_segment_input_preproc preproc, void *value)=0;

        // Model output postprocessing functions 
        /**
         * @brief Set the output buffer 
         * 
         * @param segment 
         * @param ptr 
         * buffer pointer
         * @param size 
         * size of buffer required
         */
        virtual void set_output_buffer(deie_segment *segment, void *ptr, int size)=0;  

        /**
         * @brief Set the output params 
         * 
         * @param segment 
         * @param outparams 
         * enumaration variables with output threshold and nms etc..
         * @param value 
         * value to the above enum variable
         */
        virtual void set_output_params(deie_segment *segment, deie_segment_output_params outparams, int value)=0;

        /**
         * @brief it allocates the io buffer
         * 
         * @param segment 
         * @param ioptr pointer to the io descripter strucutre
         */
        virtual void allocate_io_buffer(deie_segment *segment, deie_io_desc *ioptr)=0;

        /**
         * @brief it deallocatets the memory 
         * 
         * @param segment 
         * @param ioptr pointer to the io descripter strucutre
         */
        virtual void free_io_buffer(deie_segment *segment, deie_io_desc *ioptr)=0;

        /**
         * @brief Set the model input buffers 
         * 
         * @param segment 
         * @param num 
         * @param ptr 
         */
        virtual void set_model_input_buffers(deie_segment *segment, int num, void** ptr)=0;

        /**
         * @brief Set the model output buffers 
         * 
         * @param segment
         * @param num 
         * @param ptr 
         */
        virtual void set_model_output_buffers(deie_segment *segment, int num, void** ptr)=0;

        /**
         * @brief register custom preprocessor
         * 
         * @param segment 
         * @param preprocessor 
         * custom preprocessor function
         */
        virtual void register_custom_pre_processor(deie_segment *segment, deie_segment_preprocessor preprocessor)=0;

        /**
         * @brief register custom postprocessor
         * 
         * @param segment 
         * @param postprocessor 
         * custom postprocessor function
         */
        virtual void register_custom_post_processor(deie_segment *segment, deie_segment_postprocessor postprocessor)=0;

        /**
         * @brief run the inference
         * 
         * @param segment 
         * @param inference_out 
         * process the result to user application function
         */
        virtual void run_inference(deie_segment *segment, deie_segment_process_results inference_out)=0;

        /**
         * @brief stops the running inference
         * 
         * @param segment 
         */
        virtual void stop_inference(deie_segment *segment)=0;

        /**
         * @brief member variables
         * 
         */
        deie_segment_postprocessor custom_postprocess;
        deie_hw_platform hw_type;
};

#endif //__SEGMENT_H__