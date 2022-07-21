if(INTEL_TARGET)
    add_subdirectory(intel)
endif(INTEL_TARGET)

if(XILINX_TARGET)
    add_subdirectory(xilinx)
endif(XILINX_TARGET)

if(AMBARELLA_TARGET)
    add_subdirectory(ambarella)
endif(AMBARELLA_TARGET)