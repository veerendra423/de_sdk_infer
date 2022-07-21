cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_C_COMPILER /usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-gcc)
# set(CMAKE_CXX_COMPILER /usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(app LANGUAGES CXX)

option(BUILD_DETECTOR "Build detector application" OFF)
option(BUILD_SEGMENT "Build segmentation application" OFF)


option(BUILD_INTEL "Build intel platform" OFF)
option(BUILD_XILINX "Build xilinx platform" OFF)
option(BUILD_AMBARELLA "Build ambarella platform" OFF)

option(BUILD_YOLOV3 "Build yolov3 model" OFF)
option(BUILD_YOLOV4 "Build yolov4 model" OFF)
option(BUILD_YOLOV5 "Build yolov5 model" OFF)
option(BUILD_TINYYOLOV3 "Build tinyyolov3 model" OFF)
option(BUILD_EFFICIENTDET "Build EfficientDet model" OFF)

set(LIBRARY_NAME "deieLogger")
set(DETECTOR_LIBRARY_NAME "detectorLib")
set(SEGMENT_LIBRARY_NAME "segmentLib")
set(PLATFORM_LIBRARY_NAME "targetLib")
add_subdirectory(config_parser)

if(BUILD_INTEL)
    option(INTEL_TARGET "source cmake at platform intel" ON) 
    add_subdirectory(platform)
endif(BUILD_INTEL)

if(BUILD_XILINX)
    option(XILINX_TARGET "source cmake at platform xilinx" ON)
    add_subdirectory(platform)
endif(BUILD_XILINX)

if(BUILD_AMBARELLA)
    option(AMBARELLA_TARGET "source cmake at platform ambarella" ON)
    add_subdirectory(platform)
endif(BUILD_AMBARELLA)

if(BUILD_DETECTOR)
    if(BUILD_YOLOV3)
        option(YOLOV3_MODEL "yolov3 model architecture" ON)
        add_subdirectory(detector)
    endif(BUILD_YOLOV3)

    if(BUILD_YOLOV4)
        option(YOLOV4_MODEL "yolov4 model architecture" ON)
        add_subdirectory(detector)
    endif(BUILD_YOLOV4)

    if(BUILD_YOLOV5)
        option(YOLOV5_MODEL "yolov5 model architecture" ON)
        add_subdirectory(detector)
    endif(BUILD_YOLOV5)

    if(BUILD_TINYYOLOV3)
        option(TINYYOLOV3_MODEL "tiny_yolov3 model architecture" ON)
        add_subdirectory(detector)
    endif(BUILD_TINYYOLOV3)

    if(BUILD_EFFICIENTDET)
        option(EFFICIENTDET_MODEL "yolov5 model architecture" ON)
        add_subdirectory(detector)
    endif(BUILD_EFFICIENTDET)

    set(main_cpp "${PROJECT_SOURCE_DIR}/test_apps/object_detection_test_main.cpp")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

    add_executable(${PROJECT_NAME} ${platform} ${detector} ${main_cpp}) 

    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    add_subdirectory(utils)

    target_link_libraries(${PROJECT_NAME} PUBLIC config_parser ${DETECTOR_LIBRARY_NAME} ${PLATFORM_LIBRARY_NAME} ${LIBRARY_NAME})

    target_include_directories(app PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/config_parser/common" 
                            "${PROJECT_SOURCE_DIR}/config_parser/config"
                            "${PROJECT_SOURCE_DIR}/utils/"
                            "/usr/local/include/"
                            )
endif(BUILD_DETECTOR)

if(BUILD_SEGMENT)
    if(BUILD_UNET)
    option(UNET_MODEL "unet model architecture" ON)
    add_subdirectory(segmentation)
    endif(BUILD_UNET)

    if(BUILD_FCN)
    option(FCN_MODEL "fcn model architecture" ON)
    add_subdirectory(segmentation)
    endif(BUILD_FCN)

    if(BUILD_FASTFCN)
    option(FASTFCN_MODEL "fsatfcn model architecture" ON)
    add_subdirectory(segmentation)
    endif(BUILD_FASTFCN)

    if(BUILD_GATEDSCNN)
    option(GATEDSCNN_MODEL "gated scnn model architecture" ON)
    add_subdirectory(segmentation)
    endif(BUILD_GATEDSCNN)

    if(BUILD_MASK_RCNN)
    option(MASK_RCNN_MODEL "mask rcnn model architecture" ON)
    add_subdirectory(segmentation)
    endif(BUILD_MASK_RCNN)

    if(BUILD_DEEPLAB)
    option(DEEPLAB_MODEL "deeplab model architecture" ON)
    add_subdirectory(segmentation)
    endif(BUILD_DEEPLAB)

    set(main_cpp "${PROJECT_SOURCE_DIR}/test_apps/segmentation_test_main.cpp")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

    add_executable(${PROJECT_NAME} ${platform} ${segmentation} ${main_cpp}) 

    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    add_subdirectory(utils)

    target_link_libraries(${PROJECT_NAME} PUBLIC config_parser ${SEGMENT_LIBRARY_NAME} ${PLATFORM_LIBRARY_NAME} ${LIBRARY_NAME})

    target_include_directories(app PUBLIC
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_SOURCE_DIR}/segmentation/inc/"
                        "${PROJECT_SOURCE_DIR}/config_parser/common" 
                        "${PROJECT_SOURCE_DIR}/config_parser/config"
                        "${PROJECT_SOURCE_DIR}/utils/"
                        "/usr/local/include/"
                        )

endif(BUILD_SEGMENT)