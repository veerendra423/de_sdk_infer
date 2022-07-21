/**
 * @file unet.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "deie_logger.hpp"
#include "detector.h"
#include "tiny_yolov3.h"

using namespace std;
using namespace std::chrono;
using deie::L;

// Derived class
tiny_yolov3 :: tiny_yolov3()
{
    L().info()<<"tiny yolov3 Constructor "<< endl;
    custom_postprocess = NULL;
}

tiny_yolov3 :: ~tiny_yolov3()
{
    L().info() << "tiny yolov3 Destructor" << endl;
}

void tiny_yolov3 :: set_target_env(deie_detector *detobj, deie_hw_platform tgt, deie_device device)
{

    switch (tgt)
    {
        case DEIE_HW_AMBA_CV2:
        case DEIE_HW_AMBA_CV28:
        case DEIE_HW_XILINX_ZCU102:
        case DEIE_HW_XILINX_ZCU104:
        case DEIE_HW_XILINX_ZCU106:
        case DEIE_HW_XILINX_KV260:
        case DEIE_HW_NVIDIA_JETSON_TX1:
        case DEIE_HW_NVIDIA_JETSON_TX2:
        case DEIE_HW_NVIDIA_JETSON_NANO:
        case DEIE_HW_NVIDIA_JETSON_XAVIER:
        case DEIE_HW_AMBA_CV22:
            target = deie_target::deie_create_target(tgt);
            target->set_device(device);
            break;
        case DEIE_HW_AMBA_CV25:
            target = deie_target::deie_create_target(tgt);
            target->set_device(device);
            break; 
            
        case DEIE_HW_KINARA:
            target = deie_target::deie_create_target(tgt);
            target->set_device(device);
            break;      
                      
        case DEIE_HW_INTEL_OPENVINO_NUC:
            target = deie_target::deie_create_target(tgt);
            target->set_device(device);
            break;      
        default:
            break;
    }
    hw_type = tgt;

}


void tiny_yolov3 :: set_target_input(deie_detector *detobj, deie_input_src input, deie_file_input *path)
{   
    switch (input)
    {           
        case DEIE_INPUT_SRC_FILE_VIDEO:
           // Vread_video(path->img_path);
            break;
        
        case DEIE_INPUT_SRC_FILE_IMAGE:
            target->set_img_file_input(path);
            break;
        default:
            break;
    }
}
//for camera input
void tiny_yolov3 :: set_target_input(deie_detector *detobj, deie_input_src input, int devicefd) 
{
    switch(input)
    {
        case DEIE_INPUT_SRC_LIVE_CAMERA:
            /* code */
            break;
        
        case DEIE_INPUT_SRC_LIVE_STREAM:
            break;
        
        default:
            break;
    }
}

void tiny_yolov3 :: set_model_info (deie_detector *detobj, deie_detector_model model)
{
    num_inputs = model.info.num_inputs;
    num_outputs = model.info.num_outputs;

    for(int i =0; i<num_inputs; i++){
        strcpy(in_node[i].info.name, model.info.inputs[i].name);
        in_node[i].info.dims.plane = model.info.inputs[i].dims.plane;
        in_node[i].info.dims.depth = model.info.inputs[i].dims.depth;
        in_node[i].info.dims.height = model.info.inputs[i].dims.height;
        in_node[i].info.dims.width = model.info.inputs[i].dims.width;
    }

    for(int i =0; i<num_outputs; i++){
        strcpy(out_node[i].info.name, model.info.outputs[i].name);
        out_node[i].info.dims.plane = model.info.outputs[i].dims.plane;
        out_node[i].info.dims.depth = model.info.outputs[i].dims.depth;
        out_node[i].info.dims.height = model.info.outputs[i].dims.height;
        out_node[i].info.dims.width = model.info.outputs[i].dims.width;
    }

    y_model = model;
    L().info() <<"set model info"<<endl;
    target->prepare_model(y_model.info);
}

void tiny_yolov3 :: set_input_pre_processing(deie_detector *detobj, deie_detector_input_preproc preproc, deie_input_color_format cfmt)
{

}
void tiny_yolov3 :: set_input_pre_processing(deie_detector *detobj, deie_detector_input_preproc preproc, void *value)
{

}

void tiny_yolov3 :: set_output_buffer(deie_detector *detobj, void *ptr, int size)
{

}
void tiny_yolov3 :: set_output_params(deie_detector *detobj, deie_detector_output_params outparams, int value)
{

}

void tiny_yolov3 :: allocate_io_buffer(deie_detector *detobj, deie_io_desc *ioptr)
{
    // allocate 5 int memory blocks
    //int *ptrs = *(int *)ioptr->data;
    int* ptr = (int*) malloc(5 * sizeof(int));

    // check if memory has been allocated successfully
    if (!ptr) {
        L().info() << "Memory Allocation Failed";
        exit(1);
    }
    free(ptr);
}
void tiny_yolov3 :: free_io_buffer(deie_detector *detobj, deie_io_desc *ioptr)
{
    //free(ioptr);
}

void tiny_yolov3 :: set_model_input_buffers(deie_detector *detobj, int num, void** ptr)
{

}

void tiny_yolov3 :: set_model_output_buffers(deie_detector *detobj, int num, void** ptr)
{

}

void tiny_yolov3 :: register_custom_pre_processor(deie_detector *detobj, deie_detector_preprocessor preprocessor)
{

}

void tiny_yolov3 :: register_custom_post_processor(deie_detector *detobj, deie_detector_postprocessor postprocessor)
{
    if (detobj == this)
        custom_postprocess = postprocessor;
}

void tiny_yolov3 :: intel_nuc_post_process(void *, int num_outputs, deie_detector_model* out)
{   
    auto start = high_resolution_clock::now();
    L().info()<<"intel post processing at tiny yolov3"<<endl;
    // for(int i=0; i<num_outputs; i++)
    // {
    //     cout<<"intel func at yolov3 layer name: "<<out->info.outputs[i].name<<endl;
    //     cout<<"intel func at yolov3 plane: "<<out->info.outputs[i].dims.plane<<endl;
    //     cout<<"intel func at yolov3 depth: "<<out->info.outputs[i].dims.depth<<endl;
    //     cout<<"intel func at yolov3 height: "<<out->info.outputs[i].dims.height<<endl;
    //     cout<<"intel func at yolov3 width: "<<out->info.outputs[i].dims.width<<endl;
    // }  

    float *scores = (float *)out_node[2].data;
              
    cout<<"scores from ptr void: "<<*scores<<endl;
  
    float *boxes = (float *)out_node[1].data;

    int num_class = out->info.outputs[2].dims.height;
    int loop_length = out->info.outputs[2].dims.depth;
    
    cout<<"num class: "<<num_class<<endl;
    cout<<"loop lengeth: "<<loop_length<<endl;
    
    // nlohmann::json payload;
    process_out.payload["detections"] = {};

    for (size_t i = 0; i < loop_length; i++)
    {   
        int start = num_class * i;
        int end = start + num_class - 1;
        float max_score = *max_element(&scores[start], &scores[end]);
        float detections[6]; 
        if ( max_score > 0.50){
            //std::cout <<"|"<<start<<"|"<<end<<"|"<< max_score << endl;
            detections[0] = static_cast<float>(boxes[i * 4 + 0]);
            detections[1] = static_cast<float>(boxes[i * 4 + 1]);
            detections[2] = static_cast<float>(boxes[i * 4 + 2]);
            detections[3] = static_cast<float>(boxes[i * 4 + 3]);
            detections[4] = static_cast<float>(max_score);
            int label_pos = distance(scores, max_element(&scores[start], &scores[end]));
            int label = num_class - (loop_length / label_pos);
            detections[5] = static_cast<float>(label);
            process_out.payload["detections"].push_back(detections); 
        }                             
    }
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    process_out.payload["image_id"] = "results.json";
    process_out.payload["time_taken"] = to_string(duration.count());
    //cout<<"detected output:"<<process_out.payload<<endl;
}
        
void tiny_yolov3 :: run_inference(deie_detector *detobj, deie_detector_process_results inference_out)
{
    L().info() << "run inference at tiny yolov3 info";
    int x = num_outputs;
    deie_io_desc *out_node_addresses[MAX_OUTPUTS]= {NULL};
    for(int addr=0; addr<MAX_OUTPUTS; addr++)
    {
        out_node_addresses[addr]=&out_node[addr];
    }

    target->run_inference(&x, out_node_addresses);
    
    for(int i=0; i<num_outputs; i++)
    {
        y_model.info.outputs[i] = out_node[i].info;
    }
    
    if (custom_postprocess != NULL)
        custom_postprocess((void *)this, num_outputs, &y_model);//num_outputs,,out_nodes
    else {
        // handle target specific post processing intel_nuc_post_process       
        if ( hw_type == DEIE_HW_INTEL_OPENVINO_NUC )
            intel_nuc_post_process((void *)this, num_outputs, &y_model);
    
        process_out.num_objects=num_outputs;
        inference_out(this, &process_out);
    }
}

void tiny_yolov3 :: stop_inference(deie_detector *detobj)
{
    delete detobj;
}