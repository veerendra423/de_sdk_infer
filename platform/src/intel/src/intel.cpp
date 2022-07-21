/**
 * @file intel.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#include <iostream>
#include "intel.h"
#include "deie_logger.hpp"
using deie::L;
#ifdef _SEGMENTATION
     #define SEGMENT _SEGMENTATION
#endif

intel :: intel()
{
    return;
}

intel :: ~intel()
{
   return;
}
void intel :: set_device(deie_device device)
{
    if(device = DEIE_DEVICE_CPU)
    {
        dev = "CPU";
    }
    else if(device = DEIE_DEVICE_GPU)
    {
        dev = "GPU";
    }
    else
    {
        dev = "unknown";
        return;
    }
}
void intel :: set_video_file_input(deie_file_input *in)
{

}

void intel :: set_img_file_input(deie_file_input *in)
{       
    infer_in = in;
}

void intel :: set_camera_input()
{

}

void intel :: set_stream_input()
{

}

void intel :: prepare_model(deie_model_info minfo)
{
    std::string model_path = minfo.path;
   
    model.net = ie.ReadNetwork(model_path);
    std::cout.flush();
    std::cout << "Network Read \n" << std::flush;

    std::string imInfoInputName;
    InputInfo::Ptr inputInfo = nullptr;

    DataPtr outputInfo;
    InputsDataMap inputsInfo(model.net.getInputsInfo());

    if (inputsInfo.size() != 1 && inputsInfo.size() != 2)
        throw std::logic_error("Sample supports topologies only with 1 or 2 inputs");

    SizeVector inputImageDims;

    for (auto& item : inputsInfo) {
        /** Working with first input tensor that stores image **/
        if (item.second->getInputData()->getTensorDesc().getDims().size() == 4) {
            model.imageInputName = item.first;

            inputInfo = item.second;

            Precision inputPrecision = Precision::FP32;
            item.second->setPrecision(inputPrecision);
        }
        else if (item.second->getInputData()->getTensorDesc().getDims().size() == 2) {
            imInfoInputName = item.first;

            Precision inputPrecision = Precision::FP32;
            item.second->setPrecision(inputPrecision);
            if ((item.second->getTensorDesc().getDims()[1] != 3 &&
                item.second->getTensorDesc().getDims()[1] != 6)) {
                throw std::logic_error("Invalid input info. Should be 3 or 6 values length");
            }
        }
    }

    if (inputInfo == nullptr) {
        inputInfo = inputsInfo.begin()->second;
    }
    OutputsDataMap outputsInfo(model.net.getOutputsInfo());

    outputInfo = outputsInfo.begin()->second;
    model.outputInfo = outputsInfo;

    if (outputInfo == nullptr) {
        throw std::logic_error("Can't find a DetectionOutput layer in the topology");
    }

    const SizeVector outputDims = outputInfo->getTensorDesc().getDims();

    const int maxProposalCount = outputDims[2];
    const int objectSize = outputDims[3];
   
    int i = 0;
    for (auto& item : outputsInfo) {
        const char* output_name = item.first.c_str();
        DataPtr dim = item.second; 
        printf("%s",output_name);
        model.outs[i] = output_name;
        model.dims[i] = dim;
        i++;
    }

    outputInfo->setPrecision(Precision::FP32);

    std::cout << "Input Output Sanity check done" << std::flush;

    model.exec_net = ie.LoadNetwork(model.net,dev); 
    std::cout << "Network Preperation Done" << std::flush;

}

void intel :: run_inference(int *y, deie_io_desc *ptr[])
{  

    string file_name = "result.json";
     L().info()<<"intel inference function" <<endl;
   
    std::cout << model.imageInputName << std::flush;
    OutputsDataMap outputInf = model.outputInfo;

    model.infer_req = model.exec_net.CreateInferRequest();
        
    Blob::Ptr  frameBlob = model.infer_req.GetBlob(model.imageInputName);

    cv::Mat frame = imread(infer_in->img_file,cv::COLOR_BGR2RGB);
    cout<<"input files:" <<infer_in->img_file<<endl;
    frame.convertTo(frame,CV_32F);
    frame.convertTo(frame,CV_32F,1.0/255,0);

    // int reshape_dims[] = {frame.size[2], frame.size[0], frame.size[1]} ;
    // cv::Mat infer_frame(3, reshape_dims, frame.type(), frame.data);
    
    matU8ToBlob<float_t>(frame, frameBlob);

    auto start = high_resolution_clock::now();
        
    model.infer_req.Infer();
    nlohmann::json payload;

    if(infer_in->task == "object_detection")
    {
        printf("%s\n","Object_Detection triggered....");
        L().info() << "inference done" <<endl;
        std::cout<<"output size: "<<sizeof(model.outs)/sizeof(model.outs[0])<<endl;

        //int n=0; //no.of outputs
        // Send the network output back to the caller
        // for (int i=0; i < sizeof(model.outs)/sizeof(model.outs[0]); i++)
        // {
        //     strcpy(ptr[i]->info.name, model.outs[i].c_str());
        //     ptr[i]->info.dims.plane =  model.dims[i]->getTensorDesc().getDims()[0];
        //     ptr[i]->info.dims.depth =  model.dims[i]->getTensorDesc().getDims()[1];
        //     ptr[i]->info.dims.height = model.dims[i]->getTensorDesc().getDims()[2];
        //     ptr[i]->info.dims.width = model.dims[i]->getTensorDesc().getDims()[3];
                
        //     n++;
        // }  
        // *y = n; 
        *y = sizeof(model.outs)/sizeof(model.outs[0]);
        cout<<"test print here"<<endl;
        float* scores = model.infer_req.GetBlob(model.outs[2])->buffer().as<PrecisionTrait<Precision::FP32>::value_type*>();
         ptr[2]->data = (void *)scores;            

        cout<<"test scores: "<<*(float *)ptr[2]->data<<endl;
        cout<<"scores: "<<*scores<<endl; 
        ptr[2]->info.dims.height = model.dims[2]->getTensorDesc().getDims()[2];
        ptr[2]->info.dims.depth = model.dims[2]->getTensorDesc().getDims()[1];;
        
        int num_class = model.dims[2]->getTensorDesc().getDims()[2];
        int loop_length = model.dims[2]->getTensorDesc().getDims()[1];;
        std::cout << num_class <<"|"<< loop_length << endl;
        printf("num_class: %d loop | lentgh: %d", num_class, loop_length);

        float* boxes = model.infer_req.GetBlob(model.outs[3])->buffer().as<PrecisionTrait<Precision::FP32>::value_type*>();
        ptr[3]->data = (void *)boxes;
        cout<<"test boxes: "<<*(float *)ptr[3]->data<<endl;
        cout<<"boxes: "<<*boxes<<endl; 
    }

    if(infer_in->task == "segmentation")
    {

        float* prob_mat = model.infer_req.GetBlob(model.outs[1])->buffer().as<PrecisionTrait<Precision::FP32>::value_type*>();
        ptr[1]->data = (void *)prob_mat;
        cout<<"test boxes: "<<*(float *)ptr[1]->data<<endl;
        cout<<"boxes: "<<*prob_mat<<endl; 

        ptr[1]->info.dims.height = model.dims[0]->getTensorDesc().getDims()[1];
        ptr[3]->info.dims.width = model.dims[0]->getTensorDesc().getDims()[3];
        int height = model.dims[0]->getTensorDesc().getDims()[1];
        int width = model.dims[0]->getTensorDesc().getDims()[3];

        printf("%d\n",height);
        printf("%d\n", width);
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

        payload["masks"]={};
        payload["masks"].push_back(trans_matrix);
        payload["image_id"] = file_name;
        payload["time_taken"] = to_string(duration.count());
    }
}