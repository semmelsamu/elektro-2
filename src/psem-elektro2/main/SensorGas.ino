class SensorCJMCU {

  public:

    Sensor_CJMCU(int heat = 10000) {
      pinMode(PIN_CJMCU_PRE, OUTPUT);

      Serial.println("[CJMCU] Vorheizen...");
      digitalWrite(PIN_CJMCU_PRE, 1);
      delay(heat);
      digitalWrite(PIN_CJMCU_PRE, 0);
      Serial.println("[CJMCU] Vorheizen beendet");
    }

    float getNox() { return analogRead(PIN_CJMCU_NOX); }
    float getRed() { return analogRead(PIN_CJMCU_NOX); }
    
};
