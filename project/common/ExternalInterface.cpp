#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif

#include <hx/CFFI.h>
#include "SensorVL53L1X.h"

using namespace sensorvl53l1x;

static value sensorvl53xl1_initialize()
{	
	bool result = initialize();
	return alloc_bool(result);	
}
DEFINE_PRIM (sensorvl53xl1_initialize, 0);


static value sensorvl53xl1_getDistance () {
	int returnValue = getDistance();
	return alloc_int(returnValue);
}
DEFINE_PRIM (sensorvl53xl1_getDistance, 0);


extern "C" void sensorvl53xl1_main () {
	val_int(0);
}
DEFINE_ENTRY_POINT (sensorvl53xl1_main);


//extern "C" int sensorvl53xl1_register_prims () { return 0; }