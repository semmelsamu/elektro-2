
#include "RTClib.h"

RTC_DS3231 rtc;
int timerTime;

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

if (! rtc.begin()) {
    Serial.println("[RTC] Couldn't find RTC");
  }
  if (rtc.lostPower()) {
    Serial.println("[RTC] RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
