/**
 * @file object_detection_test_main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-28
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#include <iostream>
#include <iterator>
#include <bits/stdc++.h>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

#include "deie_logger.hpp"

// Don't compile asserts away
#ifdef NDEBUG
    #undef NDEBUG
#endif

#include <cassert>
#include <cstdlib>

#include <opencv2/highgui/highgui.hpp>
#include "handler.h"
#include "detector.h"

using namespace std;
using namespace cv;

// Map to associate the strings with the enum values
static std::map<std::string, deie_detector_class> s_mapStringValues;
static std::map<std::string, deie_hw_platform> s_maphwStringValues;
static void init_config_stringtoenum_detectorclass();
static void init_config_stringtoenum_deie_hw_platform();

//void deie_process_results (deie_detector *detector, deie_detector_output *results)
void process_results (void *ptr, deie_detector_output *results)
{
	cout<<"at main process results: "<<results->num_objects<<endl;
	//cout<<"detected output at main: "<<results->payload<<endl;
} 
/**
 * @brief 
 * 
 * @param ptr 
 * @param io_num 
 * @param app_model 
 */
void custom_application_post_process(void *ptr, int io_num, deie_detector_model* app_model)
{
	cout<<"custom post process at main application "<<endl;	
}

/**
 * @brief 
 * 
 * @return int 
 */

int main() 
{
	deie_detector_model model;
	deie_file_input img;
	std::string model_arch;
	std::string target_dev;
	deie_detector *detector;

	using deie::L;

    const auto logFile = "deie_log_report.log";

   	// init the string map
  	init_config_stringtoenum_detectorclass();
	init_config_stringtoenum_deie_hw_platform();

	try {
		// Get a config handler
		config::Handler handler;

		// Load a config file
		handler.Load("config.ini.detector", {});

		// Output some settings to standard output
		config::Item* configItem;
		//model detailes filled in structures
		configItem = handler.Get("Debug_level.level");
		int level = configItem->GetInteger();
		switch(level)
		{
			case 0:
				L::setLoggingLevel(L::Level::Trace);
				break;
			case 1:
				L::setLoggingLevel(L::Level::Debug);
				break;
			case 2:
				L::setLoggingLevel(L::Level::Info);
				break;
			case 3:
				L::setLoggingLevel(L::Level::Warning);
				break;
			case 4:
				L::setLoggingLevel(L::Level::Error);
				break;
			case 5:
				L::setLoggingLevel(L::Level::Fatal);
				break;
			default:
				L::setLoggingLevel(L::Level::Trace);
				break;
		}
		L::init(logFile);
		L::enableEchoMode(true);
		L::setLoggingLevel(L::Level::Trace);

		const std::string message = "deie_object detection inference application!";
		const std::string timestampSeparator = " ## ";
		L::setTimestampMode(L::TimestampMode::DateTime, timestampSeparator);

		L().trace() << message;
		L().debug() << message;
		L().info() << message;
		L().warning() << "warning message!";
		L().error() << message;
		L().fatal() << message;	


		configItem = handler.Get("target_details.target_platform");
		target_dev = configItem->GetString();

		configItem = handler.Get("model_details.model_architecture");
		model_arch = configItem->GetString();

		configItem = handler.Get("model_details.model_path");
		strcpy(model.info.path, configItem->GetString().c_str());
		std::cout << "model path: " << model.info.path <<"\n";
		
		configItem = handler.Get("model_details.model_file");
		strcpy(model.info.name, configItem->GetString().c_str());
		std::cout << "model file name: " << model.info.name <<"\n";

		configItem = handler.Get("model_details.no_of_inputs");
		model.info.num_inputs = configItem->GetInteger();
		std::cout << "number of inputs: " << model.info.num_inputs <<"\n";

		configItem = handler.Get("model_details.input_dims");
		std::vector<std::string> list = configItem->GetList();
			unsigned int i = 0;
			for (; i < model.info.num_inputs; i++) {
				model.info.inputs[i].dims.plane = stoi(list[0]);
				model.info.inputs[i].dims.depth = stoi(list[1]);
				model.info.inputs[i].dims.height = stoi(list[2]);
				model.info.inputs[i].dims.width = stoi(list[3]);
			}

		configItem = handler.Get("model_details.input_tensors");
		vector<string> input_tensors;
		stringstream ss_in(configItem->GetString());
		while (ss_in.good()) 
		{
			string substr;
			getline(ss_in, substr, ',');
			input_tensors.push_back(substr);
		}
		for (int i = 0; i < input_tensors.size(); i++)
		{
			strcpy(model.info.inputs[i].name, input_tensors[i].c_str());
			std::cout << "input tensor name:"<< model.info.inputs[i].name <<"\n\n";
		}

		configItem = handler.Get("model_details.no_of_outputs");
		model.info.num_outputs = configItem->GetInteger();
		std::cout << "number of outputs: " << model.info.num_outputs <<"\n";

		configItem = handler.Get("model_details.output_tensors");
		vector<string> output_tensors;
		stringstream ss_out(configItem->GetString());
		while (ss_out.good()) 
		{
			string substr;
			getline(ss_out, substr, ',');
			output_tensors.push_back(substr);
		}
		for (int i = 0; i < output_tensors.size(); i++)
		{
			strcpy(model.info.outputs[i].name, output_tensors[i].c_str());
			std::cout << "output tensors name: " << model.info.outputs[i].name <<"\n";
		}

		configItem = handler.Get("cv_task.cv_task_type");
		img.task = configItem->GetString();
		std::cout << "cv_task_type: " << img.task <<"\n";
		
		configItem = handler.Get("test_input_data.test_data_path");
		img.path = configItem->GetString();
		std::cout << "input image: " << img.path <<"\n";
		glob(img.path, img.files);
		
		configItem = handler.Get("model_postprocessing.nms_threshold");
		float threshold = configItem->GetDouble();
		std::cout << "intel threshold: " << threshold <<"\n\n";

		configItem = handler.Get("target_details.target_device_type");
		string device_type = configItem->GetString();
		std::cout << "input device type: " << device_type <<"\n";

		//model architecture object creation	
		switch(s_mapStringValues[model_arch])
		{
			case DEIE_DETECTOR_TYPE_YOLO_V3:
				detector = deie_detector::deie_create_detector(DEIE_DETECTOR_TYPE_YOLO_V3);
				break;
			case DEIE_DETECTOR_TYPE_YOLO_V4:
				detector = deie_detector::deie_create_detector(DEIE_DETECTOR_TYPE_YOLO_V4);
				break;
			case DEIE_DETECTOR_TYPE_YOLO_V5:
				detector = deie_detector::deie_create_detector(DEIE_DETECTOR_TYPE_YOLO_V5);
				break;
			case DEIE_DETECTOR_TYPE_TINYYOLO_V3:
				detector = deie_detector::deie_create_detector(DEIE_DETECTOR_TYPE_TINYYOLO_V3);
				break;
			case DEIE_DETECTOR_TYPE_SSD:
				detector = deie_detector::deie_create_detector(DEIE_DETECTOR_TYPE_SSD);
				break;
			case DEIE_DETECTOR_TYPE_ED_0:
				detector = deie_detector::deie_create_detector(DEIE_DETECTOR_TYPE_ED_0);
				break;
			default:
				cout << "Invalid model architecture"<< endl;
				return 0;
			break;
		}
		//set the target environment based on config.ini
		switch(s_maphwStringValues[target_dev])
		{
			case DEIE_HW_AMBA_CV2:
				detector->set_target_env(detector, DEIE_HW_AMBA_CV2, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_AMBA_CV22:
				detector->set_target_env(detector, DEIE_HW_AMBA_CV22, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_AMBA_CV25:
				detector->set_target_env(detector, DEIE_HW_AMBA_CV25, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_AMBA_CV28:
				detector->set_target_env(detector, DEIE_HW_AMBA_CV28, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_INTEL_OPENVINO_NUC:
				detector->set_target_env(detector, DEIE_HW_INTEL_OPENVINO_NUC, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_XILINX_ZCU102:
				detector->set_target_env(detector, DEIE_HW_XILINX_ZCU102, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_XILINX_ZCU104:
				detector->set_target_env(detector, DEIE_HW_XILINX_ZCU104, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_XILINX_ZCU106:
				detector->set_target_env(detector, DEIE_HW_XILINX_ZCU106, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_XILINX_KV260:
				detector->set_target_env(detector, DEIE_HW_XILINX_KV260, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_NVIDIA_JETSON_TX1:
				detector->set_target_env(detector, DEIE_HW_NVIDIA_JETSON_TX1, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_NVIDIA_JETSON_TX2:
				detector->set_target_env(detector, DEIE_HW_NVIDIA_JETSON_TX2, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_NVIDIA_JETSON_NANO:
				detector->set_target_env(detector, DEIE_HW_NVIDIA_JETSON_NANO, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_NVIDIA_JETSON_XAVIER:
				detector->set_target_env(detector, DEIE_HW_NVIDIA_JETSON_XAVIER, DEIE_DEVICE_CPU);
				break;
			case DEIE_HW_KINARA:
				detector->set_target_env(detector, DEIE_HW_KINARA, DEIE_DEVICE_CPU);
				break;
			default:
				cout << "Invalid target device"<< endl;
				return 0;
			break;
		}
		detector->set_model_info(detector, model);
		detector-> register_custom_post_processor(detector, NULL);
		
		for (size_t j = 0; j < img.files.size(); ++j)
    	{
			cout<<"file at main app inputs: "<<img.files[j]<<endl;
			img.img_file = img.files[j];
			detector->set_target_input(detector, DEIE_INPUT_SRC_FILE_IMAGE, &img);
			detector->run_inference(detector, process_results);
		}
		
		
	} catch (std::exception e) {
		std::cout << "Encountered error: " << e.what() << "\n";
	}

	return 0;
}

void init_config_stringtoenum_detectorclass()
{
	s_mapStringValues["yolov3"] = DEIE_DETECTOR_TYPE_YOLO_V3;
	s_mapStringValues["yolov4"] = DEIE_DETECTOR_TYPE_YOLO_V4;
	s_mapStringValues["yolov5"] = DEIE_DETECTOR_TYPE_YOLO_V5;
	s_mapStringValues["tiny_yolov3"] = DEIE_DETECTOR_TYPE_TINYYOLO_V3;
	s_mapStringValues["ssd"] = DEIE_DETECTOR_TYPE_SSD;
	s_mapStringValues["ed"] = DEIE_DETECTOR_TYPE_ED_0;
}

void init_config_stringtoenum_deie_hw_platform()
{
	s_maphwStringValues["ambarella_cv2"] = DEIE_HW_AMBA_CV2;
	s_maphwStringValues["ambarella_cv22"] = DEIE_HW_AMBA_CV22;
	s_maphwStringValues["ambarella_cv25"] = DEIE_HW_AMBA_CV25;
	s_maphwStringValues["ambarella_cv28"] = DEIE_HW_AMBA_CV28;

	s_maphwStringValues["intel"] = DEIE_HW_INTEL_OPENVINO_NUC;

	s_maphwStringValues["xilinx_zcu102"] = DEIE_HW_XILINX_ZCU102;
	s_maphwStringValues["xilinx_zcu104"] = DEIE_HW_XILINX_ZCU104;
	s_maphwStringValues["xilinx_zcu106"] = DEIE_HW_XILINX_ZCU106;
	s_maphwStringValues["xilinx_kv260"] = DEIE_HW_XILINX_KV260;

	s_maphwStringValues["jetson_tx1"] = DEIE_HW_NVIDIA_JETSON_TX1;
	s_maphwStringValues["jetson_tx2"] = DEIE_HW_NVIDIA_JETSON_TX2;
	s_maphwStringValues["jetson_nano"] = DEIE_HW_NVIDIA_JETSON_NANO;
	s_maphwStringValues["jetson_xavier"] = DEIE_HW_NVIDIA_JETSON_XAVIER;
	
	s_maphwStringValues["kinara"] = DEIE_HW_KINARA;
}

/*
DEIE_INPUT_SRC_LIVE_CAMERA=1, 
DEIE_INPUT_SRC_LIVE_STREAM=2,
DEIE_INPUT_SRC_FILE_VIDEO=3,
DEIE_INPUT_SRC_FILE_IMAGE=4,
*/
