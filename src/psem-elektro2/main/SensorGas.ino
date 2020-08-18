/*
 * SensorGas
 * This class reads out carbon monoxide, nitrogen and oxygen values with the CJMCU-4541 sensor.
 * 
 * See:
 * https://www.sgxsensortech.com/content/uploads/2014/08/0278_Datasheet-MiCS-4514-rev-16.pdf
 * 
 * Circuit:
 * CJMCU-4541 sensor connected to Arduino Mega via pins:
 * - GND: GND
 * - VCC: 5V
 * - PRE: default 3
 * - NOx: default A12
 * - RED: default A13
*/

class SensorGas {

    private:

        int pin_nox, pin_red;

    public:

        SensorGas(int pin_preheat, int pin_nox, int pin_red, int heat_time = 10000) 
        {
            pinMode(pin_preheat, OUTPUT);
    
            Serial.println("[CJMCU] Vorheizen...");
            digitalWrite(pin_preheat, 1);
            delay(heat_time);
            digitalWrite(pin_preheat, 0);
            Serial.println("[CJMCU] Vorheizen beendet");
        }

        float get_nox() { return analogRead(pin_nox); }
        float get_red() { return analogRead(pin_red); }
    
};
