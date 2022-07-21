if(YOLOV3_MODEL)
    add_subdirectory(yolov3)
endif(YOLOV3_MODEL)

if(YOLOV4_MODEL)
    add_subdirectory(yolov4)
endif(YOLOV4_MODEL)

if(YOLOV5_MODEL)
    add_subdirectory(yolov5)
endif(YOLOV5_MODEL)

if(TINYYOLOV3_MODEL)
    add_subdirectory(tiny_yolov3)
endif(TINYYOLOV3_MODEL)

if(EFFICIENTDET_MODEL)
    add_subdirectory(EfficientDet)
endif(EFFICIENTDET_MODEL)
