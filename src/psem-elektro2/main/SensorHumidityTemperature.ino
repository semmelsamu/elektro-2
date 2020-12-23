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
 * - Data: default 3
 * - GND: GND
*/

#include <DHT.h>;


#define DHTPIN 3    // what pin we're connected to
#define DHTTYPE DHT22 // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


class SensorHumidityTemperature {

    

    public:

        void sensor_setup(){
            dht.begin();
          }
      
        float get_temperature() { 

            return dht.readTemperature(); 
        }
        
        float get_humidity() { 

            return dht.readHumidity(); 
        }

      

  

};
