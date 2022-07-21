if(UNET_MODEL)
    add_subdirectory(u-net)
endif(UNET_MODEL)

if(FCN_MODEL)
    add_subdirectory(FCN)
endif(FCN_MODEL)

if(FASTFCN_MODEL)
    add_subdirectory(FastFCN)
endif(FASTFCN_MODEL)

if(GATEDSCNN_MODEL)
    add_subdirectory(Gated-SCNN)
endif(GATEDSCNN_MODEL)

if(MASK_RCNN_MODEL)
    add_subdirectory(Mask_R-CNN)
endif(MASK_RCNN_MODEL)

if(DEEPLAB_MODEL)
    add_subdirectory(DeepLab)
endif(DEEPLAB_MODEL)

