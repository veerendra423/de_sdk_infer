add_library(efficientdetLib src/efficientdet.cpp)
target_include_directories(efficientdetLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(efficientdetLib PUBLIC targetLib)