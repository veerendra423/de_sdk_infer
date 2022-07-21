/**
 * @file target.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-29
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */

#ifdef _INTEL_TARGET
	#define INTEL _INTEL_TARGET
#endif

#ifdef _XILINX_TARGET
	#define XILINX _XILINX_TARGET
#endif

#ifdef _AMBARELLA_TARGET
	#define AMBARELLA _AMBARELLA_TARGET
#endif
#ifdef _AMBARELLA_TARGET
	#define AMBARELLA _AMBARELLA_TARGET
	#undef INTEL
#endif


#ifdef INTEL
	#include "intel.h"
#endif

#ifdef XILINX
	#include "xilinx.h"
#endif

#ifdef AMBARELLA
	#include "ambarella.h"
#endif

#include "target.h"

using namespace std;

// Factory method to create objects of different hardware types.
deie_target* deie_target :: deie_create_target(deie_hw_platform hw_type)
{
	if (hw_type == DEIE_HW_INTEL_OPENVINO_NUC)
	{
		#ifdef INTEL
			return new intel();
		#endif
	}
	else if (hw_type == DEIE_HW_XILINX_KV260)
	{
		#ifdef XILINX
			return new xilinx();
		#endif
	}
        else if (hw_type == DEIE_HW_AMBA_CV22)
	{
		#ifdef AMBARELLA
			return new ambarella();
		#endif
	}	
	else return NULL;
}
