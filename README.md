**DeepEdge Inference Engine SDK **

git clone the de_sdk repository

cd de_sdk/

cd build/

FOR OBJECT DETECTION APPLICATION

For YOLOV3 model and INTEL platform example

cmake -DBUILD_DETECTOR=ON -DBUILD_YOLOV3=ON -DBUILD_INTEL=ON ../

make

For YOLOV3 model and XILINX platform example

cmake -DBUILD_DETECTOR=ON -DBUILD_YOLOV3=ON -DBUILD_XILINX=ON ../

make

For YOLOV3 model and AMBARELLA platform example

cmake -DBUILD_DETECTOR=ON -DBUILD_YOLOV3=ON -DBUILD_AMBARELLA=ON ../

make

FOR SEGMENTATION APPLICATION

For UNET model and INTEL platform example

cmake -DBUILD_SEGMENT=ON -DBUILD_UNET=ON -DBUILD_INTEL=ON ../

make

For UNET model and XILINX platform example

cmake -DBUILD_SEGMENT=ON -DBUILD_UNET=ON -DBUILD_XILINX=ON ../

make

For UNET model and AMBARELLA platform example

cmake -DBUILD_SEGMENT=ON -DBUILD_UNET=ON -DBUILD_AMBARELLA=ON ../

make

copy the app file from build directory to top directory

Update the config.in.detector file with model path and image folder path  for object detection application

Update the config.in.segment file with model path and image folder path  for segmentation application

Update the target_platfom

Run the app(application) with ./app
