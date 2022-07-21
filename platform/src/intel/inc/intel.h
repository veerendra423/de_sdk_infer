/**
 * @file intel.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef __INTEL_H__
#define __INTEL_H__

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <inference_engine.hpp>
#include <map>
#include <array>
#include <memory>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <ngraph/ngraph.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "target.h"

using namespace std;
using namespace std::chrono;
using namespace cv;
using namespace InferenceEngine;

/**
 * @brief 
 * 
 * @tparam T 
 * @param orig_image 
 * @param blob 
 * @param batchIndex 
 */
template <typename T>
void matU8ToBlob(const cv::Mat& orig_image, const InferenceEngine::Blob::Ptr& blob, int batchIndex = 0) {
    InferenceEngine::SizeVector blobSize = blob->getTensorDesc().getDims();
    const size_t width = blobSize[3];
    const size_t height = blobSize[2];
    const size_t channels = blobSize[1];
    if (static_cast<size_t>(orig_image.channels()) != channels) {
        throw std::runtime_error("The number of channels for net input and image must match");
    }
    //InferenceEngine::LockedMemory<void> blobMapped = InferenceEngine::as<InferenceEngine::MemoryBlob>(blob)->wmap();
    InferenceEngine::MemoryBlob::Ptr mblob = InferenceEngine::as<InferenceEngine::MemoryBlob>(blob);
    auto blobMapped = mblob->wmap();
    T* blob_data = blobMapped.as<T*>();

    cv::Mat resized_image(orig_image);
    if (static_cast<int>(width) != orig_image.size().width ||
        static_cast<int>(height) != orig_image.size().height) {
        cv::resize(orig_image, resized_image, cv::Size(width, height));
    }

    int batchOffset = batchIndex * width * height * channels;

    if (channels == 1) {
        for (size_t h = 0; h < height; h++) {
            for (size_t w = 0; w < width; w++) {
                blob_data[batchOffset + h * width + w] = static_cast<float>(resized_image.at<uchar>(h, w));
            }
        }
    }
    else if (channels == 3) {
        for (size_t c = 0; c < channels; c++) {
            for (size_t h = 0; h < height; h++) {
                for (size_t w = 0; w < width; w++) {
                    blob_data[batchOffset + c * width * height + h * width + w] =
                        resized_image.at<cv::Vec3f>(h, w)[c];
                }
            }
        }
    }
    else {
        throw std::runtime_error("Unsupported number of channels");
    }
}

/**
 * @brief 
 * intel target class
 * 
 */
class intel : public deie_target
{
	public:
		intel();
		~intel();
        Core ie;
        struct net_info {
            CNNNetwork net;
            ExecutableNetwork exec_net;
            std::string imageInputName;
            OutputsDataMap outputInfo;
            InferRequest infer_req;
            std::string outs[5];
            DataPtr dims[5]; 
        };
        net_info model;
        std::string dev; 
        void set_device(deie_device device);
        void set_video_file_input(deie_file_input *in);
        void set_img_file_input(deie_file_input *in);
        void set_camera_input();
        void set_stream_input();
	    void prepare_model(deie_model_info minfo);
		void run_inference(int *y, deie_io_desc *ptr[]);
};

#endif //__INTEL_H__