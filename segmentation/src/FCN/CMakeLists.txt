add_library(fcnLib src/fcn.cpp)

target_include_directories(fcnLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(fcnLib PUBLIC targetLib)