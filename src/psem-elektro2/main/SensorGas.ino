/*
 * SensorGas
 * This class reads out carbon monoxide, nitrogen and oxygen values with the CJMCU-4541 sensor.
 * 
 * Circuit:
 * CJMCU-4541 sensor connected to Arduino Mega via pins:
 * - GND: GND
 * - VCC: 5V
 * - PRE: default 3
 * - NOx: default A12
 * - RED: default A13
*/

class SensorGas {

  public:

    SensorGas(int heat = 10000) {
      pinMode(PIN_CJMCU_PRE, OUTPUT);

      Serial.println("[CJMCU] Vorheizen...");
      digitalWrite(PIN_CJMCU_PRE, 1);
      delay(heat);
      digitalWrite(PIN_CJMCU_PRE, 0);
      Serial.println("[CJMCU] Vorheizen beendet");
    }

    float get_nox() { return analogRead(PIN_CJMCU_NOX); }
    float get_red() { return analogRead(PIN_CJMCU_NOX); }
    
};
