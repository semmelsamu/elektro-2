/*
 * SensorHumidityTemperature
 * This class reads out temperature and humidity values with the DHT22 sensor by adafruit.
 * 
 * See:
 * https://learn.adafruit.com/dht
 * 
 * Circuit:
 * DHT22 connected to Arduino Mega via pins:
 * - VCC: Transistor:
 *   - Collector: 5V of Arduino
 *   - Base: pin_power_reset - default 7
 *   - Emitter: VCC of DHT
 * - Data: default 4
 * - GND: GND
 * - (GND: GND)
*/

#include "DHT.h"

DHT dht(PIN_DHT, DHT22);

class SensorHumidityTemperature {

    int pin_power_reset;
    int nan_counter;

    public:

        SensorHumidityTemperature(int pin_power_reset=7)
        {
            pin_power_reset = pin_power_reset;
            nan_counter = 0;
            pinMode(pin_power_reset, OUTPUT);
            digitalWrite(pin_power_reset, HIGH);
        }
    
        float get_temperature() { 
            fix_if_defect();
            return dht.readTemperature(); 
        }
        
        float get_humidity() { 
            fix_if_defect();
            return dht.readHumidity(); 
        }

        void reset_sensor() {
            Serial.println("Resetting DHT...");
            digitalWrite(pin_power_reset, LOW);
            delay(3000);
            digitalWrite(pin_power_reset, HIGH);
        }

        void fix_if_defect() {
            if(isnan(dht.readTemperature()) || isnan(dht.readHumidity())) {
                nan_counter++;
                if(nan_counter > 5) {
                    Serial.println("DHT returned nan 6 times, trying to reset it...");
                    reset_sensor();
                    nan_counter = 0;
                }
                else {
                    Serial.println("DHT returned nan "+String(nan_counter)+" times, maybe the sensor crashed?");
                }
            }
            else {
                nan_counter = 0;
            }
        }
    
};

