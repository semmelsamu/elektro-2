/** 
 *  
 * Main-Code vom Arduino-Team
 *
*/

// INCLUDES

#include <OneWire.h> 
#include <DallasTemperature.h>

// PINS

const int pin_DS18B20 = 2;

// SETUPS FÜR SENSOREN

/* DS18B20 */
OneWire oneWire(pin_DS18B20); 
DallasTemperature sensors(&oneWire);

// KLASSEN

class Sensor_DS18B20 {
  
  public:
  
    Sensor_DS18B20()
    {
      Serial.println("[DS18B20] Initialisieren...");
      sensors.begin();
      Serial.println("[DS18B20] Initialisiert...");
    }
  
    float getTemperature()
    {
      Serial.println("[DS18B20] getTemperature...");
      sensors.requestTemperatures();
      return sensors.getTempCByIndex(0);
    }
  
};

class Main {
  
  private:

    Sensor_DS18B20 * DS18B20;
    
  public:
  
    Main()
    {
      Serial.println("[Main] Initialisieren...");
      DS18B20 = new Sensor_DS18B20();
    }

    void loop()
    {
      Serial.println("[Main] Starte...");
      boolean exitLoop = false;
      while(!exitLoop)
      {
        Serial.println(DS18B20->getTemperature());
        delay(2000);
      }
      Serial.println("[Main] Gestoppt.");
    }
    
};

void setup() {
  
  Serial.begin(9600); 
  
}

void loop() {
  Main * main = new Main();
  main->loop();

}
