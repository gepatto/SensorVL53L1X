#include <hx/CFFI.h>
#include <stdio.h>
#include <stdarg.h>
#include "VL53L1X.h"
#include "SensorVL53L1X.h"

namespace sensorvl53l1x {

	VL53L1X Distance_Sensor;

    bool initialize()
	{
		bool status;  
   		status = Distance_Sensor.begin(); 
		return status;
    }

	int getDistance(){
		Distance_Sensor.startMeasurement();
    	while(Distance_Sensor.newDataReady() == false){
      		usleep(5);
    	}   
	    return Distance_Sensor.getDistance();
	}
}