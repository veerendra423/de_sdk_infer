add_library(GatedSCNNLib src/gated-scnn.cpp)

target_include_directories(GatedSCNNLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/ /usr/local/include/)

target_link_libraries(GatedSCNNLib PUBLIC targetLib)
