add_subdirectory(src)
find_package(OpenCV REQUIRED)
add_library(segmentLib src/segmentation.cpp)
ADD_DEFINITIONS(-D_SEGMENTATION=1)

if(UNET_MODEL)
    ADD_DEFINITIONS(-D_UNET_MODEL=1)
    target_link_libraries(segmentLib PRIVATE unetLib  PUBLIC ${OpenCV_LIBS})
endif(UNET_MODEL)

if(FCN_MODEL)
    ADD_DEFINITIONS(-D_FCN_MODEL=1)
    target_link_libraries(segmentLib PRIVATE fcnLib  PUBLIC ${OpenCV_LIBS})
endif(FCN_MODEL)

if(FASTFCN_MODEL)
    ADD_DEFINITIONS(-D_FASTFCN_MODEL=1)
    target_link_libraries(segmentLib PRIVATE FastFcnLib  PUBLIC ${OpenCV_LIBS})
endif(FASTFCN_MODEL)

if(GATEDSCNN_MODEL)
    ADD_DEFINITIONS(-D_GATEDSCNN_MODEL=1)
    target_link_libraries(segmentLib PRIVATE GatedSCNNLib  PUBLIC ${OpenCV_LIBS})
endif(GATEDSCNN_MODEL)

if(MASK_RCNN_MODEL)
    ADD_DEFINITIONS(-D_MASK_RCNN_MODEL=1)
    target_link_libraries(segmentLib PRIVATE MaskRCNNLib  PUBLIC ${OpenCV_LIBS})
endif(MASK_RCNN_MODEL)

if(DEEPLAB_MODEL)
    ADD_DEFINITIONS(-D_DEEPLAB_MODEL=1)
    target_link_libraries(segmentLib PRIVATE deeplabLib  PUBLIC ${OpenCV_LIBS})
endif(DEEPLAB_MODEL)
