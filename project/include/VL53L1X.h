/*
The VL53L1X is the latest Time Of Flight (ToF) sensor to be released. It uses
  a VCSEL (vertical cavity surface emitting laser) to emit a class 1 IR laser
  and time the reflection to the target. What does all this mean? You can measure
  the distance to an object up to 4 meters away with millimeter resolution!

  We’ve found the precision of the sensor to be 1mm but the accuracy is around +/-5mm.

  This library handles the initialization of the VL53L1X and is able to query the sensor
  for different readings.

  Because ST has chosen not to release a complete datasheet we are forced to reverse
  engineer the interface from their example code and I2C data stream captures.
  For ST's reference code see STSW-IMG007

  The device operates as a normal I2C device. There are *many* registers. Reading and 
  writing happens with a 16-bit address. The VL53L1X auto-increments the memory
  pointer with each read or write.

  Development environment specifics:
  Arduino IDE 1.8.5

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VL53L1X_H
#define VL53L1X_H

#include "vl53l1_register_map.h"
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <iostream>
#include <unistd.h>
#include <stdint.h>


#define byte uint8_t
const byte defaultAddress_VL53L1X = 0x29; //The default I2C address for the VL53L1X on the SparkFun breakout is 0x29.
//#define defaultAddress_VL53L1X 0x29 //The default I2C address for the VL53L1X on the SparkFun breakout is 0x29.
//int i2c_port; //raspberry pi I2C handle

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

using namespace std;

class VL53L1X {
  public:

    bool begin(uint8_t deviceAddress = defaultAddress_VL53L1X); //By default use the default I2C address, and use Wire port

    void softReset(); //Reset the sensor via software
    void startMeasurement(uint8_t offset = 0); //Write a block of bytes to the sensor to configure it to take a measurement
    bool newDataReady(); //Polls the measurement completion bit
    uint16_t getDistance(); //Returns the results from the last measurement, distance in mm
    uint16_t getSignalRate(); //Returns the results from the last measurement, signal rate
    uint8_t getRangeStatus(); //Returns the results from the last measurement, 0 = valid

    uint8_t readRegister(uint16_t addr); //Read a byte from a 16-bit address
    uint16_t readRegister16(uint16_t addr); //Read two bytes from a 16-bit address
    bool writeRegister(uint16_t addr, uint8_t val); //Write a byte to a spot
    bool writeRegister16(uint16_t addr, uint16_t val); //Write two bytes to a spot
   // int i2cInit(void);
  private:

    //Variables
    uint8_t _deviceAddress; //Keeps track of I2C address. setI2CAddress changes this.
};


#endif


