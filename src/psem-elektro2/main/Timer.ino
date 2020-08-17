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
    
        String getUnixTime() {
            DateTime now = rtc.now();
            return String(now.unixtime());
        }
        
        void resetTimer() {
            DateTime now = rtc.now();
            timerTime = now.unixtime();
        }
        
        int secondsPassed()
        {
            DateTime now = rtc.now();
            return now.unixtime()-timerTime;
        }
        
        void waitUntilTimerHits(int seconds) {
            while(secondsPassed()<seconds) {
                delay(1000);
            }
        }

};

// Those functions are for setup purposes. As Arduino doesn't let us 
// initialize the RTC in the class itself, we just put it here and 
// call it later in the setup function.

void setup_rtc()
{
    // Initialize the RTC
    if (! rtc.begin()) {
        Serial.println("[RTC] Couldn't find RTC");
    }

    if (rtc.lostPower()) {
        Serial.println("[RTC] RTC lost power, lets set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}
