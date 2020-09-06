/*
 * Timer
 * This class reads time via a RTC Module and can also be used as a Timer.
 * 
 * Circuit:
 * RTC Module DS3231 connected to an Arduino Mega via pins:
 * - GND
 * - VCC: 5V
 * - SCL: 21
 * - SDA: 20
*/

#include "RTClib.h"

RTC_DS3231 rtc;
int timerTime;

class Timer {

    public:
    
        unsigned long get_unix_time() {
            DateTime now = rtc.now();
            return now.unixtime();
        }

        float get_temperature() {
            return rtc.getTemperature();
        }
        

};

// Those functions are for setup purposes. As Arduino doesn't let us 
// initialize the RTC in the class itself, we just put it here and 
// call it later in the setup function.

void setup_rtc()
{
    Serial.println("Setting up RTC...");
    // Initialize the RTC
    if (! rtc.begin()) {
        Serial.println("    CRITICAL: Couldn't find RTC");
    }

    if (rtc.lostPower()) {
        Serial.print("    RTC lost power, setting time... ");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        Serial.println("Done.");
    }
}
