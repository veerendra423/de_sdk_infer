add_library(unetLib src/unet.cpp)

target_include_directories(unetLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/segmentation/inc ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(unetLib PUBLIC targetLib)
