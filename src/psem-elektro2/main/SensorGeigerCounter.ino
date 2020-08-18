/* 
  Circuit: 
      GND = GND
      5V  = 5V
      VIN = DIGITAL 2

*/

// If SPI is already included, we skip the include. Otherwise, a compiling error would occur
#ifndef __SPI
#define __SPI
#include <SPI.h>
#endif

unsigned long SensorGeigerCounter__counts = 0;

void tube_impulse(){       
    SensorGeigerCounter__counts++;
}

void setup_geiger_counter() {
    attachInterrupt(0, tube_impulse, FALLING);
}

class SensorGeigerCounter {
    
    public: 

        int get_counts() {
            return SensorGeigerCounter__counts;
        }
};
