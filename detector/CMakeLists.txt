add_subdirectory(src)
find_package(OpenCV REQUIRED)
add_library(detectorLib src/detector.cpp)

if(YOLOV3_MODEL)
    ADD_DEFINITIONS(-D_YOLOV3_MODEL=1)
    target_link_libraries(detectorLib PRIVATE yolov3Lib  PUBLIC ${OpenCV_LIBS})
endif(YOLOV3_MODEL)

if(YOLOV4_MODEL)
    ADD_DEFINITIONS(-D_YOLOV4_MODEL=1)
    target_link_libraries(detectorLib PRIVATE yolov4Lib  PUBLIC ${OpenCV_LIBS})
endif(YOLOV4_MODEL)

if(YOLOV5_MODEL)
    ADD_DEFINITIONS(-D_YOLOV5_MODEL=1)
    target_link_libraries(detectorLib PRIVATE yolov5Lib  PUBLIC ${OpenCV_LIBS})
endif(YOLOV5_MODEL)

if(TINYYOLOV3_MODEL)
    ADD_DEFINITIONS(-D_TINYYOLOV3_MODEL=1)
    target_link_libraries(detectorLib PRIVATE tiny_yolov3Lib  PUBLIC ${OpenCV_LIBS})
endif(TINYYOLOV3_MODEL)

if(EFFICIENTDET_MODEL)
    ADD_DEFINITIONS(-D_EFFICIENTDET_MODEL=1)
    target_link_libraries(detectorLib PRIVATE efficientdetLib  PUBLIC ${OpenCV_LIBS})
endif(EFFICIENTDET_MODEL)
