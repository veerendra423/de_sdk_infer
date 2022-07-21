add_library(yolov3Lib src/yolov3.cpp)

target_include_directories(yolov3Lib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(yolov3Lib PUBLIC targetLib)
