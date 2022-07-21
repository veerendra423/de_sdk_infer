/**
 * @file detector.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-29
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
//#include <opencv2/dnn.hpp>

#include "detector.h"

#ifdef _YOLOV3_MODEL
	#define YOLOV3 _YOLOV3_MODEL
#endif

#ifdef _YOLOV4_MODEL
	#define YOLOV4 _YOLOV4_MODEL
#endif

#ifdef _YOLOV5_MODEL
	#define YOLOV5 _YOLOV5_MODEL
#endif

#ifdef _TINYYOLOV3_MODEL
	#define TINYYOLOV3 _TINYYOLOV3_MODEL
#endif

#ifdef _EFFICIENTDET_MODEL
	#define EFFICIENTDET _EFFICIENTDET_MODEL
#endif


#ifdef YOLOV3
	#include "yolov3.h"
#endif

#ifdef YOLOV4
	#include "yolov4.h"
#endif

#ifdef YOLOV5
	#include "yolov5.h"
#endif

#ifdef TINYYOLOV3
	#include "tiny_yolov3.h"
#endif

#ifdef EFFICIENTDET
    #include "efficientdet.h"
#endif

using namespace std;
using namespace cv;
//using namespace dnn;

//factory method to create object for the model architecture type
deie_detector* deie_detector::deie_create_detector(deie_detector_class type) 
{
	if (type == DEIE_DETECTOR_TYPE_YOLO_V3)
    {
        #ifdef YOLOV3
            return new Yolov3();
        #endif
    }
	else if (type == DEIE_DETECTOR_TYPE_YOLO_V4)
    {
        #ifdef YOLOV4
            return new Yolov4();
        #endif
    }
	else if (type == DEIE_DETECTOR_TYPE_YOLO_V5)
    {
        #ifdef YOLOV5
            return new Yolov5();
        #endif
    }
		
    else if (type == DEIE_DETECTOR_TYPE_TINYYOLO_V3)
    {
        #ifdef TINYYOLOV3
            return new tiny_yolov3();
        #endif
    }

    else if (type == DEIE_DETECTOR_TYPE_ED_0)
    {
        #ifdef EFFICIENTDET
            return new efficientdet();
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
