add_library(MaskRCNNLib src/mask_rcnn.cpp)

target_include_directories(MaskRCNNLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(MaskRCNNLib PUBLIC targetLib)
