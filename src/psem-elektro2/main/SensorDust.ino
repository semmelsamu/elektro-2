/*
 * SensorDust
 * This class reads out dust values out of the Grove dust sensor.
 * 
 * See: 
 * https://wiki.seeedstudio.com/Grove-Dust_Sensor/
 * https://files.seeedstudio.com/wiki/Grove_Dust_Sensor/resource/Grove_-_Dust_sensor.pdf
 * 
 * Circuit:
 * Grove Dust sensor connected to Arduino Mega via pins:
 * - GND: GND
 * - VCC: 5V
 * - OUTPUT(P1): default 42
*/

class SensorDust {

    private:

        unsigned long duration, starttime, sampletime_ms = 2000, lowpulseoccupancy = 0;
        float ratio = 0, concentration = 0;
    
        int pin_output_1;
  
    public:
  
        SensorDust(int pin_output_1=42)
        {
            Serial.print("Setting up Dust Sensor... ");
            pin_output_1 = pin_output_1;
            pinMode(pin_output_1,INPUT);
            starttime = millis();
            Serial.println("Done.");
        }
    
        float get_concentration()
        {
            duration = pulseIn(pin_output_1, LOW);
            lowpulseoccupancy = lowpulseoccupancy+duration;
            if ((millis()-starttime) >= sampletime_ms)
            {
                ratio = lowpulseoccupancy/(sampletime_ms*10.0);
                concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
                lowpulseoccupancy = 0;
                starttime = millis();
            }
            return concentration;
        }
};
