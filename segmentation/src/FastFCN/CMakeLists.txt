add_library(FastFcnLib src/fastfcn.cpp)

target_include_directories(FastFcnLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(FastFcnLib PUBLIC targetLib)
