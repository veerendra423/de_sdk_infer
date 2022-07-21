add_library(xilinxLib src/xilinx.cpp)
include_directories(/usr/include/opencv4/)
link_directories(/usr/lib/)
target_include_directories(xilinxLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/)

target_link_libraries(xilinxLib -lvart-runner -lxir -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_core -lglog -lunilog -lpthread)
