/*
 * SensorGas
 * This class reads out carbon monoxide, nitrogen and oxygen values with the CJMCU-4541 sensor.
 * 
 * See:
 * https://www.sgxsensortech.com/content/uploads/2014/08/0278_Datasheet-MiCS-4514-rev-16.pdf
 * https://github.com/jo-seph/Mobisens/blob/master/mobisens7.6.ino
 * 
 * Circuit:
 * CJMCU-4541 sensor connected to Arduino Mega via pins:
 * - GND: GND
 * - VCC: 5V
 * - PRE: default 38
 * - NOx: default A12
 * - RED: default A13
*/

class SensorGas {

    private:

        int pin_nox, pin_red;

    public:

        SensorGas(int pin_preheat=38, int pin_nox=A6, int pin_red=A7, int heat_time = 10) 
        {
            Serial.println("Setting up CJMCU... ");
            
            pinMode(pin_preheat, OUTPUT);

            Serial.print("    Preheating");
            digitalWrite(pin_preheat, 1);
            for(int i=0; i<heat_time; i++) {
                Serial.print(".");
                delay(1000);
            }
            digitalWrite(pin_preheat, 0);
            
            Serial.println(" Done.");
        }

        int get_nox() { return analogRead(pin_nox); }
        int get_red() { return analogRead(pin_red); }
    
};
