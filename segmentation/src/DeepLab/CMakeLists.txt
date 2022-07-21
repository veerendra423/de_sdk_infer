add_library(deeplabLib src/deeplab.cpp)

target_include_directories(deeplabLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(deeplabLib PUBLIC targetLib)