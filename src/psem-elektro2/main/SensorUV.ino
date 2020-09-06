/*
 * SensorUV
 * This class reads out UV values with the Waveshare UV Sensor.
 * 
 * See:
 * https://www.waveshare.com/uv-sensor.htm
 * 
 * Circuit:
 * UV Sensor connected to Arduino Mega via pins:
 * - AOUT: Analog, default: A15
 * - GND: GND
 * - VCC: 5V
*/

class SensorUV {

    private:

        int pin_uv;

    public:

        SensorUV(int pin_uv=A15) {
            Serial.print("Setting up UV Sensor... ");
            pin_uv = pin_uv;
            Serial.println("Done.");
        }

        int get_uv() {
            return analogRead(pin_uv);
        }
  
};
