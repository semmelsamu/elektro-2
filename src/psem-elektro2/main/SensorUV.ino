/*
 * SensorUV
 * This class reads out UV values with the Waveshare UV Sensor.
 * 
 * See:
 * https://www.waveshare.com/uv-sensor.htm
 * 
 * Circuit:
 * UV Sensor connected to Arduino Mega via pins:
 * - AOUT: Analog, default: A11
 * - GND: GND
 * - VCC: 5V
*/

class SensorUV {

    private:

        int pin_uv;

    public:

        SensorUv(int pin_uv=A11) {
            pin_uv = pin_uv;
        }

        float getUv() {
            return analogRead(pin_uv);
        }
  
};
