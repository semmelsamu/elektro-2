/*
 * SensorTemperature
 * This class reads out temperature values with the DS18B20 sensor.
 * 
 * See:
 * https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 * https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/
 * 
 * Circuit:
 * DS18B20 connected to Arduino Mega via pins:
 * - VCC: 5V
 * - Data: default 30 + also connected via 4.7kOhm resistor to VCC
 * - GND: GND
*/

#include <OneWire.h> 
#include <DallasTemperature.h>

OneWire oneWire(30); 
DallasTemperature sensors(&oneWire);

class SensorTemperature {
    
    public:
  
        SensorTemperature() {
            sensors.begin();
        }
      
        float get_temperature() {
          sensors.requestTemperatures();
          return sensors.getTempCByIndex(0);
        }
};
