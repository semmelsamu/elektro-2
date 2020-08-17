

#include <OneWire.h> 
#include <DallasTemperature.h>

OneWire oneWire(PIN_DS18B20); 
DallasTemperature sensors(&oneWire);


class SensorTemperatureDS
    {
    public:
  
    Sensor_DS18B20()
    {
      sensors.begin();
    }
  
    float getTemperature()
    {
      sensors.requestTemperatures();
      return sensors.getTempCByIndex(0);
    }
  
};
