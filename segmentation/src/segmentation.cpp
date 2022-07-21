/**
 * @file segmetation.cpp
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
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "segmentation.h"

#ifdef _UNET_MODEL
	#define UNET _UNET_MODEL
#endif

#ifdef _FCN_MODEL
	#define FCN _FCN_MODEL
#endif

#ifdef _FASTFCN_MODEL
	#define FASTFCN _FASTFCN_MODEL
#endif

#ifdef _GATEDSCNN_MODEL
	#define GATEDSCNN _GATEDSCNN_MODEL
#endif

#ifdef _MASK_RCNN_MODEL
	#define MASK_RCNN _MASK_RCNN_MODEL
#endif

#ifdef _DEEPLAB_MODEL
	#define DEEPLAB _DEEPLAB_MODEL
#endif


#ifdef UNET
	#include "unet.h"
#endif

#ifdef FCN
	#include "fcn.h"
#endif

#ifdef FASTFCN
	#include "fastfcn.h"
#endif

#ifdef GATEDSCNN
	#include "gated-scnn.h"
#endif

#ifdef MASK_RCNN
    #include "mask_rcnn.h"
#endif

#ifdef DEEPLAB
    #include "deeplab.h"
#endif

using namespace std;
using namespace cv;

deie_segment* deie_segment::deie_create_segment(deie_segment_class type) 
{
	if (type == DEIE_SEGMENT_TYPE_U_NET)
    {
        #ifdef UNET
            return new unet();
        #endif
    }
	else if (type == DEIE_SEGMENT_TYPE_FCN)
    {
        #ifdef FCN
            return new fcn();
        #endif
    }
	else if (type == DEIE_SEGMENT_TYPE_FAST_FCN)
    {
        #ifdef FASTFCN
            return new fastfcn();
        #endif
    }
		
    else if (type == DEIE_SEGMENT_TYPE_GATED_SCNN)
    {
        #ifdef GATEDSCNN
            return new gatedscnn();
        #endif
    }

    else if (type == DEIE_SEGMENT_TYPE_MASK_R_CNN)
    {
        #ifdef MASK_RCNN
            return new maskrcnn();
        #endif 
    }

    else if (type == DEIE_SEGMENT_TYPE_DEEPLAB)
    {
        #ifdef DEEPLAB
            return new deeplab();
        #endif
    }
   	else return NULL;
}

// check the file exists 
bool file_exists(std::string filename)
{
    try
    {
        if (FILE *file = fopen(filename.c_str(), "r"))
        {
            fclose(file);
            return true;
        }
    }
    catch (std::exception &ex)
    {
        std::cout << "Exception in file_exists to:" << ex.what() << "\n";
    }
    return false;
}

// Api to convert video to frames
void Vread_video(std::string video_path)
{
    try
    {
        bool is_exists = file_exists(video_path);
        std::cout << "File exist status: " << is_exists << "video_path:" << video_path << "\n";
        cv::VideoCapture cap(video_path);
        // Check if camera opened successfully
        std::cout << "video is opened: " << cap.isOpened() << "\n";
        if (!cap.isOpened())
        {
            std::cout << "Error opening video stream or file" << "\n";
        }
        cv::Mat frame;
        int count = 0;
        while (cap.isOpened())
        {
            cap >> frame;
            cv::imwrite("/home/veerendra/sdk/video_frame/" + std::to_string(count) + ".jpg", frame);
            count++;
        }
        std::cout << "Video Reader ended.." << '\n';
    }
    catch (const cv::Exception &ex)
    {
        std::cout << "Exception in read_video due to:" << ex.what() << "\n";
    }
}


void read_image(std::string image_path)
{
	cv::Mat input_img = cv::imread(image_path,IMREAD_COLOR);

    // pre process for image resize and apply mean , scale 
	/*int padding_value[4]={0,0,0,0};
    Mat image=add_padding(input_img,padding_value);
    Size szf=input_img.size();
    float xrf=(float)szf.width/padding_value[1];
    float yrf=(float)szf.height/padding_value[0];*/
    cv::Size imsz=input_img.size();
    int h=imsz.height;
    int w=imsz.width;
    float xr=(float)w/800;
    float yr=(float)h/600;
    cv::resize(input_img,input_img,Size(800,600));
    cv::Size sz=input_img.size();
    cv::imwrite("input_image.jpg",input_img);
}
