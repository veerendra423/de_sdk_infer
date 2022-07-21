/**
 * @file unet.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-23
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
#include "segmentation.h"
#include "unet.h"

using namespace std;
using namespace std::chrono;
using deie::L;

// Derived class
unet :: unet()
{
    L().info()<<"unet Constructor "<< endl;
    custom_postprocess = NULL;
}

unet :: ~unet()
{
    L().info() << "unet Destructor" << endl;
}

void unet :: set_target_env(deie_segment *segment, deie_hw_platform tgt, deie_device device)
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

void unet :: set_target_input(deie_segment *segment, deie_input_src input, deie_file_input *path)
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
void unet :: set_target_input(deie_segment *segment, deie_input_src input, int devicefd) 
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

void unet :: set_model_info (deie_segment *segment, deie_segment_model model)
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

void unet :: set_input_pre_processing(deie_segment *segment, deie_segment_input_preproc preproc, deie_input_color_format cfmt)
{

}

void unet :: set_input_pre_processing(deie_segment *segment, deie_segment_input_preproc preproc, void *value)
{

}

void unet :: set_output_buffer(deie_segment *segment, void *ptr, int size)
{

}

void unet :: set_output_params(deie_segment *segment, deie_segment_output_params outparams, int value)
{

}

void unet :: allocate_io_buffer(deie_segment *segment, deie_io_desc *ioptr)
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

void unet :: free_io_buffer(deie_segment *segment, deie_io_desc *ioptr)
{
    //free(ioptr);
}

void unet :: set_model_input_buffers(deie_segment *segment, int num, void** ptr)
{

}

void unet :: set_model_output_buffers(deie_segment *segment, int num, void** ptr)
{

}

void unet :: register_custom_pre_processor(deie_segment *segment, deie_segment_preprocessor preprocessor)
{

}

void unet :: register_custom_post_processor(deie_segment *segment, deie_segment_postprocessor postprocessor)
{
    if (segment == this)
        custom_postprocess = postprocessor;
}

void unet :: intel_nuc_post_process(void *, int num_outputs, deie_segment_model* out)
{   
    auto start = high_resolution_clock::now();
    L().info()<<"intel post processing at yolov3"<<endl;
    float *prob_mat = (float *)out_node[1].data;
    int height = out->info.outputs[1].dims.height;
    int width = out->info.outputs[3].dims.width;
    
    std::vector<std::vector<float>> trans_matrix;

        for (size_t i=0 ; i < height ; i++){
            
            int row_start = width*(i);
            int row_end = width*(i+1)-1;
            std::vector<float> row;
            
            for(size_t k=row_start ; k<row_end ; k++){
                row.push_back(prob_mat[k]);
            }

            trans_matrix.push_back(row);
        }

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);

        process_out.payload["masks"]={};
        process_out.payload["masks"].push_back(trans_matrix);
        process_out.payload["image_id"] = "segment.json";
        process_out.payload["time_taken"] = to_string(duration.count());


    // for(int i=0; i<num_outputs; i++)
    // {
    //     cout<<"intel func at unet layer name: "<<out->info.outputs[i].name<<endl;
    //     cout<<"intel func at unet plane: "<<out->info.outputs[i].dims.plane<<endl;
    //     cout<<"intel func at unet depth: "<<out->info.outputs[i].dims.depth<<endl;
    //     cout<<"intel func at unet height: "<<out->info.outputs[i].dims.height<<endl;
    //     cout<<"intel func at unet width: "<<out->info.outputs[i].dims.width<<endl;
    // }  
     
    cout<<"segmentoutput:"<<process_out.payload<<endl;
}
        
void unet :: run_inference(deie_segment *segment, deie_segment_process_results inference_out)
{
    L().info() << "run inference at yolov3 info";
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

void unet :: stop_inference(deie_segment *segment)
{
    delete segment;
}