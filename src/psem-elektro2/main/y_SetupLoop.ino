void setup() {
  Serial.begin(9600);

  // RTC
  
  if (! rtc.begin()) {
    Serial.println("[RTC] Couldn't find RTC");
  }
  if (rtc.lostPower()) {
    Serial.println("[RTC] RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {
  Main * main = new Main();
  main->loop();
  Serial.println("Programm beendet. Neustart in 60s.");
  delay(60000);
}
