add_library(yolov5Lib src/yolov5.cpp)
target_include_directories(yolov5Lib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(yolov5Lib PUBLIC targetLib)