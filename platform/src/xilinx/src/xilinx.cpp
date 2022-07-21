/*
 * Copyright 2019 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <dirent.h>
#include <sys/stat.h>
#include <zconf.h>
#include "xilinx.h"
#include "deie_logger.hpp"
#include <glog/logging.h>

#include <algorithm>
//#include <atomic>
#include <chrono>
//#include <fstream>
//#include <iomanip>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <utility>
#include <vector>
/* header file for Vitis AI unified API */
#include <vart/mm/host_flat_tensor_buffer.hpp>
#include <vart/runner.hpp>
#include <xir/graph/graph.hpp>
#include <xir/tensor/tensor.hpp>
#include <xir/util/data_type.hpp>


using namespace std;
using namespace cv;
using namespace std::chrono;

#define NMS_THRESHOLD 0.3f

int idxInputImage = 0;  // frame index of input video
int idxShowImage = 0;   // next frame index to be displayed
bool bReading = true;   // flag of reding input frame
bool bExiting = false;
chrono::system_clock::time_point start_time;
using namespace std::chrono;

#define CONF 0.5
const int classificationCnt = 3;
const int anchorCnt = 5;

struct TensorShape {
	unsigned int height;
	unsigned int width;
	unsigned int channel;
	unsigned int size;
};

struct GraphInfo {
	struct TensorShape* inTensorList;
	struct TensorShape* outTensorList;
	std::vector<int> output_mapping;
}shapes;


xilinx :: xilinx()
{
}

xilinx :: ~xilinx()
{
}
void xilinx :: set_device(deie_device device)
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
void xilinx :: set_video_file_input(deie_file_input *in)
{

}

void xilinx :: set_img_file_input(deie_file_input *in)
{       
	infer_in = in;
}

void xilinx :: set_camera_input()
{

}

void xilinx :: set_stream_input()
{

}

int getTensorShape(vart::Runner* runner, GraphInfo* shapes, int cntin,
		const std::vector<std::string> output_names);
int getTensorShape(vart::Runner* runner, GraphInfo* shapes, int cntin,
		int cnout);

#include <numeric>
int getTensorShape(vart::Runner* runner, GraphInfo* shapes, int cntin,
		int cntout) {
	auto outputTensors = runner->get_output_tensors();
	auto inputTensors = runner->get_input_tensors();
	if (shapes->output_mapping.empty()) {
		shapes->output_mapping.resize((unsigned)cntout);
		std::iota(shapes->output_mapping.begin(), shapes->output_mapping.end(), 0);
	}
	for (int i = 0; i < cntin; i++) {
		auto dim_num = inputTensors[i]->get_shape().size();
		std::cout<<dim_num<<std::endl;
		if (dim_num == 4) {
			shapes->inTensorList[i].channel = inputTensors[i]->get_shape().at(3);
			shapes->inTensorList[i].width = inputTensors[i]->get_shape().at(2);
			shapes->inTensorList[i].height = inputTensors[i]->get_shape().at(1);
			shapes->inTensorList[i].size =
				inputTensors[i]->get_element_num() / inputTensors[0]->get_shape().at(0);
		} else if (dim_num == 2) {
			shapes->inTensorList[i].channel = inputTensors[i]->get_shape().at(1);
			shapes->inTensorList[i].width = 1;
			shapes->inTensorList[i].height = 1;
			shapes->inTensorList[i].size =
				inputTensors[i]->get_element_num() / inputTensors[0]->get_shape().at(0);
		}
	}
	for (int i = 0; i < cntout; i++) {
		auto dim_num = outputTensors[shapes->output_mapping[i]]->get_shape().size();
		if (dim_num == 4) {
			shapes->outTensorList[i].channel =
				outputTensors[shapes->output_mapping[i]]->get_shape().at(3);
			shapes->outTensorList[i].width =
				outputTensors[shapes->output_mapping[i]]->get_shape().at(2);
			shapes->outTensorList[i].height =
				outputTensors[shapes->output_mapping[i]]->get_shape().at(1);
			shapes->outTensorList[i].size =
				outputTensors[shapes->output_mapping[i]]->get_element_num() /
				outputTensors[shapes->output_mapping[0]]->get_shape().at(0);
		} else if (dim_num == 2) {
			shapes->outTensorList[i].channel =
				outputTensors[shapes->output_mapping[i]]->get_shape().at(1);
			shapes->outTensorList[i].width = 1;
			shapes->outTensorList[i].height = 1;
			shapes->outTensorList[i].size =
				outputTensors[shapes->output_mapping[i]]->get_element_num() /
				outputTensors[shapes->output_mapping[0]]->get_shape().at(0);
		}
	}
	return 0;
}

static int find_tensor(std::vector<const xir::Tensor*> tensors,
		const std::string& name) {
	int ret = -1;
	for (auto i = 0u; i < tensors.size(); ++i) {
		if (tensors[i]->get_name().find(name) != std::string::npos) {
			ret = (int)i;
			break;
		}
	}
	assert(ret != -1);
	return ret;
}
int getTensorShape(vart::Runner* runner, GraphInfo* shapes, int cntin,
		std::vector<std::string> output_names) {
	for (auto i = 0u; i < output_names.size(); ++i) {
		auto idx = find_tensor(runner->get_output_tensors(), output_names[i]);
		shapes->output_mapping.push_back(idx);
	}
	getTensorShape(runner, shapes, cntin, (int)output_names.size());
	return 0;
}

typedef struct {
	int w;
	int h;
	int c;
	float* data;
} image;

image load_image_cv(const cv::Mat& img);
image letterbox_image(image im, int w, int h);
void free_image(image m);

inline float sigmoid(float p) { return 1.0 / (1 + exp(-p * 1.0)); }

inline float overlap(float x1, float w1, float x2, float w2) {
	float left = max(x1 - w1 / 2.0, x2 - w2 / 2.0);
	float right = min(x1 + w1 / 2.0, x2 + w2 / 2.0);
	return right - left;
}

inline float cal_iou(vector<float> box, vector<float> truth) {
	float w = overlap(box[0], box[2], truth[0], truth[2]);
	float h = overlap(box[1], box[3], truth[1], truth[3]);
	if (w < 0 || h < 0) return 0;

	float inter_area = w * h;
	float union_area = box[2] * box[3] + truth[2] * truth[3] - inter_area;
	return inter_area * 1.0 / union_area;
}

void correct_region_boxes(vector<vector<float>>& boxes, int n, int w, int h,
		int netw, int neth, int relative = 0) {
	int new_w = 0;
	int new_h = 0;

	if (((float)netw / w) < ((float)neth / h)) {
		new_w = netw;
		new_h = (h * netw) / w;
	} else {
		new_h = neth;
		new_w = (w * neth) / h;
	}
	for (int i = 0; i < n; ++i) {
		boxes[i][0] = (boxes[i][0] - (netw - new_w) / 2. / netw) /
			((float)new_w / (float)netw);
		boxes[i][1] = (boxes[i][1] - (neth - new_h) / 2. / neth) /
			((float)new_h / (float)neth);
		boxes[i][2] *= (float)netw / new_w;
		boxes[i][3] *= (float)neth / new_h;
	}
}

void detect(vector<vector<float>>& boxes, vector<float> result, int channel,
		int height, int weight, int num, int sh, int sw);

void detect(vector<vector<float>>& boxes, vector<float> result, int channel,
		int height, int width, int num, int sHeight, int sWidth) {
	vector<float> biases{123, 100, 167, 83, 98, 174, 165, 158, 347, 98,
		76,  37,  40,  97, 74, 64,  105, 63,  66,  131,
		18,  46,  33,  29, 47, 23,  28,  68,  52,  42,
		5.5, 7,   8,   17, 14, 11,  13,  29,  24,  17};
	int conf_box = 5 + classificationCnt;
	float swap[height * width][anchorCnt][conf_box];

	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			for (int c = 0; c < channel; ++c) {
				int temp = c * height * width + h * width + w;
				swap[h * width + w][c / conf_box][c % conf_box] = result[temp];
			}
		}
	}
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			for (int c = 0; c < anchorCnt; ++c) {
				float obj_score = sigmoid(swap[h * width + w][c][4]);
				if (obj_score < CONF) continue;
				vector<float> box;

				box.push_back((w + sigmoid(swap[h * width + w][c][0])) / width);
				box.push_back((h + sigmoid(swap[h * width + w][c][1])) / height);
				box.push_back(exp(swap[h * width + w][c][2]) *
						biases[2 * c + 10 * num] / float(sWidth));
				box.push_back(exp(swap[h * width + w][c][3]) *
						biases[2 * c + 10 * num + 1] / float(sHeight));
				box.push_back(-1);
				box.push_back(obj_score);
				for (int p = 0; p < classificationCnt; p++) {
					box.push_back(obj_score * sigmoid(swap[h * width + w][c][5 + p]));
				}
				boxes.push_back(box);
			}
		}
	}
}

vector<vector<float>> applyNMS(vector<vector<float>>& boxes, int classes,
		const float thres) {
	vector<pair<int, float>> order(boxes.size());
	vector<vector<float>> result;

	for (int k = 0; k < classes; k++) {
		for (size_t i = 0; i < boxes.size(); ++i) {
			order[i].first = i;
			boxes[i][4] = k;
			order[i].second = boxes[i][6 + k];
		}
		sort(order.begin(), order.end(),
				[](const pair<int, float>& ls, const pair<int, float>& rs) {
				return ls.second > rs.second;
				});

		vector<bool> exist_box(boxes.size(), true);

		for (size_t _i = 0; _i < boxes.size(); ++_i) {
			size_t i = order[_i].first;
			if (!exist_box[i]) continue;
			if (boxes[i][6 + k] < CONF) {
				exist_box[i] = false;
				continue;
			}
			/* add a box as result */
			result.push_back(boxes[i]);

			for (size_t _j = _i + 1; _j < boxes.size(); ++_j) {
				size_t j = order[_j].first;
				if (!exist_box[j]) continue;
				float ovr = cal_iou(boxes[j], boxes[i]);
				if (ovr >= thres) exist_box[j] = false;
			}
		}
	}

	return result;
}

void get_output(int8_t* dpuOut, int sizeOut, int oc, int oh, int ow,
		float output_scale, vector<float>& result) {
	// vector<int8_t> nums(sizeOut);
	// memcpy(nums.data(), dpuOut, sizeOut);
	for (int a = 0; a < oc; ++a) {
		for (int b = 0; b < oh; ++b) {
			for (int c = 0; c < ow; ++c) {
				int offset = b * oc * ow + c * oc + a;
				result[a * oh * ow + b * ow + c] = dpuOut[offset] * output_scale;
			}
		}
	}
}

static float get_pixel(image m, int x, int y, int c) {
	assert(x < m.w && y < m.h && c < m.c);
	return m.data[c * m.h * m.w + y * m.w + x];
}

static void set_pixel(image m, int x, int y, int c, float val) {
	if (x < 0 || y < 0 || c < 0 || x >= m.w || y >= m.h || c >= m.c) return;
	assert(x < m.w && y < m.h && c < m.c);
	m.data[c * m.h * m.w + y * m.w + x] = val;
}

static void add_pixel(image m, int x, int y, int c, float val) {
	assert(x < m.w && y < m.h && c < m.c);
	m.data[c * m.h * m.w + y * m.w + x] += val;
}

image make_empty_image(int w, int h, int c) {
	image out;
	out.data = 0;
	out.h = h;
	out.w = w;
	out.c = c;
	return out;
}

void free_image(image m) {
	if (m.data) {
		free(m.data);
	}
}

image make_image(int w, int h, int c) {
	image out = make_empty_image(w, h, c);
	out.data = (float*)calloc(h * w * c, sizeof(float));
	return out;
}

void fill_image(image m, float s) {
	int i;
	for (i = 0; i < m.h * m.w * m.c; ++i) m.data[i] = s;
}

void embed_image(image source, image dest, int dx, int dy) {
	int x, y, k;
	for (k = 0; k < source.c; ++k) {
		for (y = 0; y < source.h; ++y) {
			for (x = 0; x < source.w; ++x) {
				float val = get_pixel(source, x, y, k);
				set_pixel(dest, dx + x, dy + y, k, val);
			}
		}
	}
}

void rgbgr_image(image im) {
	int i;
	for (i = 0; i < im.w * im.h; ++i) {
		float swap = im.data[i];
		im.data[i] = im.data[i + im.w * im.h * 2];
		im.data[i + im.w * im.h * 2] = swap;
	}
}

image resize_image(image im, int w, int h) {
	image resized = make_image(w, h, im.c);
	image part = make_image(w, im.h, im.c);
	int r, c, k;
	float w_scale = (float)(im.w - 1) / (w - 1);
	float h_scale = (float)(im.h - 1) / (h - 1);
	for (k = 0; k < im.c; ++k) {
		for (r = 0; r < im.h; ++r) {
			for (c = 0; c < w; ++c) {
				float val = 0;
				if (c == w - 1 || im.w == 1) {
					val = get_pixel(im, im.w - 1, r, k);
				} else {
					float sx = c * w_scale;
					int ix = (int)sx;
					float dx = sx - ix;
					val = (1 - dx) * get_pixel(im, ix, r, k) +
						dx * get_pixel(im, ix + 1, r, k);
				}
				set_pixel(part, c, r, k, val);
			}
		}
	}
	for (k = 0; k < im.c; ++k) {
		for (r = 0; r < h; ++r) {
			float sy = r * h_scale;
			int iy = (int)sy;
			float dy = sy - iy;
			for (c = 0; c < w; ++c) {
				float val = (1 - dy) * get_pixel(part, c, iy, k);
				set_pixel(resized, c, r, k, val);
			}
			if (r == h - 1 || im.h == 1) continue;
			for (c = 0; c < w; ++c) {
				float val = dy * get_pixel(part, c, iy + 1, k);
				add_pixel(resized, c, r, k, val);
			}
		}
	}

	free_image(part);
	return resized;
}

image load_image_cv(const cv::Mat& img) {
	int h = img.rows;
	int w = img.cols;
	int c = img.channels();
	image im = make_image(w, h, c);

	unsigned char* data = img.data;

	for (int i = 0; i < h; ++i) {
		for (int k = 0; k < c; ++k) {
			for (int j = 0; j < w; ++j) {
				im.data[k * w * h + i * w + j] = data[i * w * c + j * c + k] / 256.;
			}
		}
	}

	for (int i = 0; i < im.w * im.h; ++i) {
		float swap = im.data[i];
		im.data[i] = im.data[i + im.w * im.h * 2];
		im.data[i + im.w * im.h * 2] = swap;
	}

	return im;
}

image letterbox_image(image im, int w, int h) {
	int new_w = im.w;
	int new_h = im.h;
	if (((float)w / im.w) < ((float)h / im.h)) {
		new_w = w;
		new_h = (im.h * w) / im.w;
	} else {
		new_h = h;
		new_w = (im.w * h) / im.h;
	}
	image resized = resize_image(im, new_w, new_h);
	image boxed = make_image(w, h, im.c);
	fill_image(boxed, .5);

	embed_image(resized, boxed, (w - new_w) / 2, (h - new_h) / 2);
	free_image(resized);

	return boxed;
}


// fix_point to scale for input tensor
inline float get_input_scale(const xir::Tensor* tensor) {
	int fixpos = tensor->template get_attr<int>("fix_point");
	return std::exp2f(1.0f * (float)fixpos);
}
// fix_point to scale for output tensor
inline float get_output_scale(const xir::Tensor* tensor) {
	int fixpos = tensor->template get_attr<int>("fix_point");
	return std::exp2f(-1.0f * (float)fixpos);
}

inline std::vector<std::unique_ptr<xir::Tensor>> cloneTensorBuffer(
		const std::vector<const xir::Tensor*>& tensors) {
	auto ret = std::vector<std::unique_ptr<xir::Tensor>>{};
	auto type = xir::DataType::XINT;
	ret.reserve(tensors.size());
	for (const auto& tensor : tensors) {
		ret.push_back(std::unique_ptr<xir::Tensor>(xir::Tensor::create(
						tensor->get_name(), tensor->get_shape(), xir::DataType{type, 8u})));
	}
	return ret;
}

inline std::vector<const xir::Subgraph*> get_dpu_subgraph(
		const xir::Graph* graph) {
	auto root = graph->get_root_subgraph();
	auto children = root->children_topological_sort();
	auto ret = std::vector<const xir::Subgraph*>();
	for (auto c : children) {
		CHECK(c->has_attr("device"));
		auto device = c->get_attr<std::string>("device");
		if (device == "DPU") {
			ret.emplace_back(c);
		}
	}
	return ret;
}

class CpuFlatTensorBuffer : public vart::TensorBuffer {
	public:
		explicit CpuFlatTensorBuffer(void* data, const xir::Tensor* tensor)
			: TensorBuffer{tensor}, data_{data} {}
		virtual ~CpuFlatTensorBuffer() = default;

	public:
		virtual std::pair<uint64_t, size_t> data(
				const std::vector<int> idx = {}) override {
			uint32_t size = std::ceil(tensor_->get_data_type().bit_width / 8.f);
			if (idx.size() == 0) {
				return {reinterpret_cast<uint64_t>(data_),
					tensor_->get_element_num() * size};
			}
			auto dims = tensor_->get_shape();
			auto offset = 0;
			for (auto k = 0; k < tensor_->get_shape().size(); k++) {
				auto stride = 1;
				for (auto m = k + 1; m < tensor_->get_shape().size(); m++) {
					stride *= dims[m];
				}
				offset += idx[k] * stride;
			}
			auto elem_num = tensor_->get_element_num();
			return {reinterpret_cast<uint64_t>(data_) + offset * size,
				(elem_num - offset) * size};
		}

	private:
		void* data_;
};

/**
 * @brief Feed input frame into DPU for process
 *
 * @param task - pointer to DPU Task for YOLO-v3 network
 * @param frame - pointer to input frame
 * @param mean - mean value for YOLO-v3 network
 * @param input_scale - input scale , used to convert float to fixed
 *
 * @return none
 */
void setInputImageForYOLO(vart::Runner* runner, int8_t* data, const Mat& frame,
		float* mean, float input_scale) {
	Mat img_copy;
	int width = shapes.inTensorList[0].width;
	int height = shapes.inTensorList[0].height;
	int size = shapes.inTensorList[0].size;
	image img_new = load_image_cv(frame);
	image img_yolo = letterbox_image(img_new, width, height);

	vector<float> bb(size);
	for (int b = 0; b < height; ++b) {
		for (int c = 0; c < width; ++c) {
			for (int a = 0; a < 3; ++a) {
				bb[b * width * 3 + c * 3 + a] =
					img_yolo.data[a * height * width + b * width + c];
			}
		}
	}

	float scale = pow(2, 7);
	for (int i = 0; i < size; ++i) {
		data[i] = (int8_t)(bb.data()[i] * input_scale);
		if (data[i] < 0) data[i] = (int8_t)((float)(127 / scale) * input_scale);
	}
	free_image(img_new);
	free_image(img_yolo);
}


/**
 * @brief Post process after the running of DPU for YOLO-v3 network
 *
 * @param task - pointer to DPU task for running YOLO-v3
 * @param frame
 * @param sWidth
 * @param sHeight
 *
 * @return none
 */
void postProcess(vart::Runner* runner, Mat& frame, vector<int8_t*> results,
		int sWidth, int sHeight, const float* output_scale) {
	const string classes[3] = {"car", "person", "cycle"};

	/* four output nodes of YOLO-v3 */
	// const string outputs_node[4] = {"layer81_conv", "layer93_conv",
	//                                    "layer105_conv", "layer117_conv"};

	vector<vector<float>> boxes;
	// auto  outputTensors = runner->get_output_tensors();
	for (int ii = 0; ii < 4; ii++) {
		int width = shapes.outTensorList[ii].width;
		int height = shapes.outTensorList[ii].height;
		int channel = shapes.outTensorList[ii].channel;
		int sizeOut = channel * width * height;
		vector<float> result(sizeOut);
		boxes.reserve(sizeOut);

		/* Store every output node results */
		get_output(results[ii], sizeOut, channel, height, width, output_scale[ii],
				result);

		/* Store the object detection frames as coordinate information  */
		detect(boxes, result, channel, height, width, ii, sHeight, sWidth);
	}

	/* Restore the correct coordinate frame of the original image */
	correct_region_boxes(boxes, boxes.size(), frame.cols, frame.rows, sWidth,
			sHeight);

	/* Apply the computation for NMS */
	vector<vector<float>> res = applyNMS(boxes, classificationCnt, NMS_THRESHOLD);

	float h = frame.rows;
	float w = frame.cols;
	for (size_t i = 0; i < res.size(); ++i) {
		float xmin = (res[i][0] - res[i][2] / 2.0) * w + 1.0;
		float ymin = (res[i][1] - res[i][3] / 2.0) * h + 1.0;
		float xmax = (res[i][0] + res[i][2] / 2.0) * w + 1.0;
		float ymax = (res[i][1] + res[i][3] / 2.0) * h + 1.0;

		if (res[i][res[i][4] + 6] > CONF) {
			int type = res[i][4];
			string classname = classes[type];

			if (type == 0) {
				rectangle(frame, Point(xmin, ymin), Point(xmax, ymax),
						Scalar(0, 0, 255), 1, 1, 0);
			} else if (type == 1) {
				rectangle(frame, Point(xmin, ymin), Point(xmax, ymax),
						Scalar(255, 0, 0), 1, 1, 0);
			} else {
				rectangle(frame, Point(xmin, ymin), Point(xmax, ymax),
						Scalar(0, 255, 255), 1, 1, 0);
			}
		}
	}
}

/**
 * @brief Thread entry for running YOLO-v3 network on DPU for acceleration
 *
 * @param task - pointer to DPU task for running YOLO-v3
 *
 * @return none
 */


void runYOLO(vart::Runner* runner, Mat& frame) {
	cout<<"in runYOLO"<<endl;
	/* mean values for YOLO-v3 */
	float mean[3] = {0.0f, 0.0f, 0.0f};
	auto inputTensors = cloneTensorBuffer(runner->get_input_tensors());
	/*int width = shapes.inTensorList[0].width;
	int height = shapes.inTensorList[0].height;
*/
	int width = 512;
	int height = 256;

	cout<<"width:"<<width<<endl;
	cout<<"height:"<<height<<endl;

	auto outputTensors = cloneTensorBuffer(runner->get_output_tensors());

	auto input_scale = get_input_scale(runner->get_input_tensors()[0]);
	cout<<"input_scale:"<<input_scale<<endl;
	auto output_scale = vector<float>();
	cout<<get_output_scale(
			runner->get_output_tensors()[shapes.output_mapping[0]])<<endl;
	cout<<get_output_scale(
			runner->get_output_tensors()[shapes.output_mapping[1]])<<endl;
	for (int i; i < 4; i++) {
		output_scale.push_back(get_output_scale(
					runner->get_output_tensors()[shapes.output_mapping[i]]));
	}
	cout<<"output_scale:"<<endl;
	for (int i = 0; i < output_scale.size(); i++) {
		// Printing the element at
		// index 'i' of vector
		cout << output_scale[i] << " ";
	}
	// input/output data define
	int8_t* data = new int8_t[shapes.inTensorList[0].size *
		inputTensors[0]->get_shape().at(0)];
	cout<<"data:  "<<shapes.inTensorList[0].size *
		inputTensors[0]->get_shape().at(0)<<endl;

	cout<<shapes.inTensorList[0].size<<endl;
	cout<<inputTensors[0]->get_shape().at(0)<<endl;

	int8_t* result0 =
		new int8_t[shapes.outTensorList[0].size *
		outputTensors[shapes.output_mapping[0]]->get_shape().at(0)];
	cout<<"res0:  "<<shapes.outTensorList[0].size *
		outputTensors[shapes.output_mapping[0]]->get_shape().at(0)<<endl;
	int8_t* result1 =
		new int8_t[shapes.outTensorList[1].size *
		outputTensors[shapes.output_mapping[1]]->get_shape().at(0)];
	cout<<"res1:  "<<shapes.outTensorList[1].size *
		outputTensors[shapes.output_mapping[1]]->get_shape().at(0)<<endl;
	int8_t* result2 =
		new int8_t[shapes.outTensorList[2].size *
		outputTensors[shapes.output_mapping[2]]->get_shape().at(0)];
	cout<<"res2:  "<<shapes.outTensorList[2].size *
		outputTensors[shapes.output_mapping[2]]->get_shape().at(0)<<endl;
	int8_t* result3 =
		new int8_t[shapes.outTensorList[3].size *
		outputTensors[shapes.output_mapping[3]]->get_shape().at(0)];
	cout<<"res3:  "<<shapes.outTensorList[3].size *
		outputTensors[shapes.output_mapping[3]]->get_shape().at(0)<<endl;
	vector<int8_t*> result;
	result.push_back(result0);
	result.push_back(result1);
	result.push_back(result2);
	result.push_back(result3);

	/*for (int i = 0; i < result.size(); i++) {
	  cout << **result << " ";
	  }*/
	cout<<"############################"<<endl;
	std::vector<std::unique_ptr<vart::TensorBuffer>> inputs, outputs;
	std::vector<vart::TensorBuffer*> inputsPtr, outputsPtr;
	/* feed input frame into DPU Task with mean value */


	setInputImageForYOLO(runner, data, frame, mean,
			input_scale);
	// input/output tensorbuffer prepare
	inputs.push_back(
			std::make_unique<CpuFlatTensorBuffer>(data, inputTensors[0].get()));

	cout<<outputTensors[shapes.output_mapping[0]].get()<<endl;
	cout<<outputTensors[shapes.output_mapping[1]].get()<<endl;
	cout<<outputTensors[shapes.output_mapping[2]].get()<<endl;
	cout<<outputTensors[shapes.output_mapping[3]].get()<<endl;


	outputs.push_back(std::make_unique<CpuFlatTensorBuffer>(	
				result0, outputTensors[shapes.output_mapping[0]].get()));
	outputs.push_back(std::make_unique<CpuFlatTensorBuffer>(
				result1, outputTensors[shapes.output_mapping[1]].get()));
	outputs.push_back(std::make_unique<CpuFlatTensorBuffer>(
				result2, outputTensors[shapes.output_mapping[2]].get()));
	outputs.push_back(std::make_unique<CpuFlatTensorBuffer>(
				result3, outputTensors[shapes.output_mapping[3]].get()));
	inputsPtr.push_back(inputs[0].get());
	outputsPtr.resize(4);
	outputsPtr[shapes.output_mapping[0]] = outputs[0].get();
	outputsPtr[shapes.output_mapping[1]] = outputs[1].get();
	outputsPtr[shapes.output_mapping[2]] = outputs[2].get();
	outputsPtr[shapes.output_mapping[3]] = outputs[3].get();
	/* invoke the running of DPU for YOLO-v3 */
	auto job_id = runner->execute_async(inputsPtr, outputsPtr);
	runner->wait(job_id.first, -1);

	postProcess(runner, frame, result, width, height,
			output_scale.data());
	imwrite("out.jpg",frame);
	inputs.clear();
	outputs.clear();
	inputsPtr.clear();
	outputsPtr.clear();
	//}
	delete[] data;
	delete[] result0;
	delete[] result1;
	delete[] result2;
	delete[] result3;
	}


void xilinx :: prepare_model(deie_model_info minfo)
{
	xmodel = minfo;
	auto graph = xir::Graph::deserialize(xmodel.path);
	cout<<xmodel.path<<endl;
	auto subgraph = get_dpu_subgraph(graph.get());
	CHECK_EQ(subgraph.size(), 1u)
		<< "yolov3 should have one and only one dpu subgraph.";
	LOG(INFO) << "create running for subgraph: " << subgraph[0]->get_name();

	runner = vart::Runner::create_runner(subgraph[0], "run");
	// get in/out tenosrs
	auto inputTensors = runner->get_input_tensors();
	auto outputTensors = runner->get_output_tensors();

	int inputCnt = inputTensors.size();
	int outputCnt = outputTensors.size();
	// init the shape info
	TensorShape inshapes[inputCnt];
	TensorShape outshapes[outputCnt];
	shapes.inTensorList = inshapes;
	shapes.outTensorList = outshapes;
	getTensorShape(runner.get(), &shapes,1,4);

	cout<<"Model Preparation Done"<<endl;
}


void xilinx :: run_inference(int *y, deie_io_desc *ptr[])
{
	
	cout<<"Reading Image in run_inference func"<<endl;
	Mat frame = imread(infer_in->img_file);
	cout<<"Run YOLO v3 model"<<endl;
	runYOLO(runner.get(),frame);

}
