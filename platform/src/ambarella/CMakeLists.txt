add_library(ambarellaLib src/ambarella.cpp)

target_include_directories(ambarellaLib PUBLIC inc/ ${PROJECT_SOURCE_DIR}/platform/inc ${PROJECT_SOURCE_DIR}/common/inc/ ${PROJECT_SOURCE_DIR}/utils/)

#target_link_libraries(ambarellaLib PRIVATE "-L/home/deltdl08/sdk_cv22/TEMP_PRO_42290/TEMP_PRO_8053/cv22_linux_sdk_3.0_20200929/cv22_linux_sdk_3.0/ambarella/out/cv22_walnut/packages/nnctrl -lnnctrl")


#link_directories(/home/deltdl08/sdk_cv25_2.5/cv25_linux_sdk_2.5/ambarella/packages/cavalry_mem/inc)
#link_directories(/home/deltdl08/sdk_cv25_2.5/cv25_linux_sdk_2.5/ambarella/packages/vproc/inc)

#add_library(nnctrl SHARED IMPORTED)
#set_property(TARGET nnctrl PROPERTY IMPORTED_LOCATION "/home/deltdl08/sdk_cv22/TEMP_PRO_42290/TEMP_PRO_8053/cv22_linux_sdk_3.0_20200929/cv22_linux_sdk_3.0/ambarella/out/cv22_walnut/packages/nnctrl/libnnctrl.so")

#target_link_libraries(ambarellaLib nnctrl cavalry_mem vproc)
link_directories(/home/deltdl08/sdk_cv22/TEMP_PRO_42290/TEMP_PRO_8053/cv22_linux_sdk_3.0_20200929/cv22_linux_sdk_3.0/ambarella/packages/nnctrl)
link_directories(/home/deltdl08/sdk_cv22/TEMP_PRO_42290/TEMP_PRO_8053/cv22_linux_sdk_3.0_20200929/cv22_linux_sdk_3.0/ambarella/out/cv22_walnut/packages/nnctrl/)
target_link_libraries(ambarellaLib nnctrl)
