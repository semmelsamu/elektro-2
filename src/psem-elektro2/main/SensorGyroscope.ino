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

        SensorGyroscope(int pin_x2=A8, int pin_y2=A9, int pin_z2=A10) {
            pin_x = pin_x2;
            pin_y = pin_y2;
            pin_z = pin_z2;
        }

        int get_x() { return (analogRead(pin_x)); }
        int get_y() { return (analogRead(pin_y)); }
        int get_z() { return (analogRead(pin_z)); }
  
};
