/*
 * SensorHumidityTemperature
 * This class reads out temperature and humidity values with the DHT22 sensor by adafruit.
 * 
 * See:
 * https://learn.adafruit.com/dht
 * 
 * Circuit:
 * DHT22 connected to Arduino Mega via pins:
 * - VCC: 5V
 * - Data: default 4
 * - GND: GND
 * - (GND: GND)
*/

#include "DHT.h"

DHT dht(PIN_DHT, DHT22);

class SensorHumidityTemperature {

    public:
    
        float getTemperature() { return dht.readTemperature(); }
        float getHumidity() { return dht.readHumidity(); }
    
};
