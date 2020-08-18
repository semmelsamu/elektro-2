/*
 * SensorGyroscope
 * This class reads out X, Y and Z tilt values with the GY-61 module.
 * 
 * See:
 * https://forum.arduino.cc/index.php?topic=343426.0
 * 
 * Circuit:
 * GY-61 module connected to Arduino Mega via pins:
 * - VCC: 5V
 * - X_OUT: default A8
 * - Y_OUT: default A9
 * - Z_OUT: default A10
 * - GND: GND
*/

class SensorGyroscope {

    private:

        int pin_x, pin_y, pin_z;

    public: 

        SensorGyroscope(int pin_x, int pin_y, int pin_z) {
            pin_x = pin_x;
            pin_y = pin_y;
            pin_z = pin_z;
        }

        float getX() { return (analogRead(pin_x)-363)*1.3; }
        float getY() { return (analogRead(pin_y)-359)*1.3; }
        float getZ() { return (analogRead(pin_z)-452)*1; }
  
};
