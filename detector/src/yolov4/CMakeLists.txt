add_library(yolov4Lib src/yolov4.cpp)
target_include_directories(yolov4Lib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(yolov4Lib PUBLIC targetLib)