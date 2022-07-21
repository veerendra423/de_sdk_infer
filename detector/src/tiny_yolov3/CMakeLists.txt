add_library(tiny_yolov3Lib src/tiny_yolov3.cpp)
target_include_directories(tiny_yolov3Lib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(tiny_yolov3Lib PUBLIC targetLib)