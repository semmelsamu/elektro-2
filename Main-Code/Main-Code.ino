/** 
 *  
 * Main-Code vom Arduino-Team
 *
*/

// INCLUDES

/* DS18B20 */
#include <OneWire.h> 
#include <DallasTemperature.h>

/* SD-Karte */
#include <SPI.h>
#include <SD.h>

/* DHT22 */
#include "DHT.h"

/* RTC */
#include "RTClib.h"

// PINS

/* DS18B20 */
#define PIN_DS18B20 2

/* Dust */
#define PIN_DUST 11

/* UV */
#define PIN_UV A11

/* Gyroskop */
#define PIN_GY_X A8
#define PIN_GY_Y A9
#define PIN_GY_Z A10

/* CJMCU4541 */
#define PIN_CJMCU_PRE 3
#define PIN_CJMCU_NOX A12
#define PIN_CJMCU_RED A13

/* DHT22 */
#define PIN_DHT 4

/* SD */
#define PIN_SD 53

// SETUPS FÜR SENSOREN

/* DS18B20 */
OneWire oneWire(PIN_DS18B20); 
DallasTemperature sensors(&oneWire);

/* DHT22 */

DHT dht(PIN_DHT, DHT22);

// GLOBALE FUNKTIONEN

void wait(){ // Wartet bis man im Serial auf Senden drückt
  while(Serial.available()==0) {} while(Serial.available()>0) { Serial.read(); }
}

// SENSORENKLASSEN

class Sensor_DS18B20 {
  
  public:
  
    Sensor_DS18B20()
    {
      sensors.begin();
    }
  
    float getTemperature()
    {
      sensors.requestTemperatures();
      return sensors.getTempCByIndex(0);
    }
  
};

class Sensor_Dust {

  private:

    unsigned long duration, starttime, sampletime_ms = 2000, lowpulseoccupancy = 0;
    float ratio = 0, concentration = 0;
  
  public:
  
    Sensor_Dust()
    {
      pinMode(PIN_DUST,INPUT);
      starttime = millis();
    }

    float getConcentration()
    {
      duration = pulseIn(PIN_DUST, LOW);//Dustsensor
      lowpulseoccupancy = lowpulseoccupancy+duration;//Dustsensor
      if ((millis()-starttime) >= sampletime_ms) //Dustsensor
      {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  //Dustsensor
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; //Dustsensor
        lowpulseoccupancy = 0;//Dustsensor
        starttime = millis();//Dustsensor
      }
      return concentration;
    }
  
};

class Sensor_Uv {

  public:

    float getUv()
    {
      return analogRead(PIN_UV);
    }
  
};

class Sensor_GY61 {

  public: 

    float getX() { return (analogRead(PIN_GY_X)-363)*1.3; }
    float getY() { return (analogRead(PIN_GY_Y)-359)*1.3; }
    float getZ() { return (analogRead(PIN_GY_Z)-452)*1; }
  
};

class Sensor_CJMCU {

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

class Sensor_DHT22 {

  public:

    Sensor_DHT22() {
      dht.begin();
    }

    float getTemperature() { return dht.readTemperature(); }
    float getHumidity() { return dht.readHumidity(); }
    
};

// RTC KLASSE

class Rtc {

  private:

    RTC_DS3231 rtc;
    int timerTime;
  
  public:

    Rtc()
    {
      if (! rtc.begin()) {
        Serial.println("[RTC] Couldn't find RTC");
      }
      if (rtc.lostPower()) {
        Serial.println("[RTC] RTC lost power, lets set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      }
    }

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

// GPS

class Gps {

  public:

    float getLatitude()
    {
      // DUMMY CODE
      return 0.0f;
    }

    float getLongitude()
    {
      // DUMMY CODE
      return 0.0f;
    }
  
};


// SIM KLASSE

class Sim {

  public:

    boolean writeData(String content)
    {
      // DUMMY CODE
      Serial.println("[SIM] Writing Data...");
      return true;
    }
  
};

// SD KLASSE

class Sd {

  private:

    File file;
    String folderId;
    int bufferCounter;
    Rtc * rtc;

  public:

    Sd() {
      SD.begin(PIN_SD);
      rtc = new Rtc();
      folderId = rtc->getUnixTime();
      bufferCounter = 0;
    }

    void writeSensorData(String sensor, String data) {

      String currentTime = rtc->getUnixTime();

      file = SD.open(folderId+"\\"+sensor+".sns", FILE_WRITE);
      if(file) {  
        file.println(currentTime+"+"+data);
        file.close();
      }
      else{
        Serial.println("[SD] Fatal Error: Couldn't open sensor file on SD card");
      }
      
      file = SD.open(folderId+"\\buffer.bf", FILE_WRITE);
      if(file) {  
        file.println(currentTime+"+"+sensor+"+"+data);
        file.close();
      }
      else{
        Serial.println("[SD] Fatal Error: Couldn't open buffer file on SD card");
      }
    }

    String readBuffer() { 
      file = SD.open(folderId+"\\buffer.bf");
      String buffer;
      int i = 0;
      while (file.available() && bufferCounter != i) {
        i++;
        buffer = file.readStringUntil('\n');
      }
      return buffer;
    }

    void nextBuffer() {
      bufferCounter++;
    }

    boolean bufferAvailable() {
      if(readBuffer().length()==0) return false; return true;
    }
  
};

// MAIN

class Main {
  
  private:
    
    Sensor_DS18B20 * DS18B20;
    Sensor_Dust * Dust;
    Sensor_Uv * Uv;
    Sensor_GY61 * GY61;
    Sensor_CJMCU * CJMCU;
    Sensor_DHT22 * S_DHT;

    Gps * GPS;
    Sim * sim;
    Sd * sd;
    Rtc * rtc;
    
  public:
  
    Main()
    {
      Serial.println("[Main] Init...");
      
      DS18B20 = new Sensor_DS18B20();
      Dust = new Sensor_Dust();
      Uv = new Sensor_Uv();
      GY61 = new Sensor_GY61();
      CJMCU = new Sensor_CJMCU(0);
      S_DHT = new Sensor_DHT22();

      GPS = new Gps();
      sim = new Sim();
      sd = new Sd();
      rtc = new Rtc();

      Serial.println("[Main] Init complete."); 
    }

    void loop()
    {
      boolean exitLoop = false;
      while(!exitLoop)
      {
        /*
        Serial.println("[Main] Reading sensor data...");
        Serial.println("Temperature: "+String(DS18B20->getTemperature()));
        Serial.println("Dust: "+String(Dust->getConcentration()));
        Serial.println("Uv: "+String(Uv->getUv()));
        Serial.println("X: "+String(GY61->getX())+", Y: "+String(GY61->getY())+", Z: "+String(GY61->getZ()));
        Serial.println("Nox: "+String(CJMCU->getNox())+", Red: "+String(CJMCU->getRed()));
        Serial.println("Temperature: "+String(S_DHT->getTemperature())+", Humidity: "+String(S_DHT->getHumidity()));
        */

        Serial.println("[Main] Reading and writing sensor data to sd and buffer...");
        sd->writeSensorData("DS18B20_TEMP", String(DS18B20->getTemperature()));
        sd->writeSensorData("DUST", String(Dust->getConcentration()));
        sd->writeSensorData("UV", String(Uv->getUv()));
        sd->writeSensorData("GY_X", String(GY61->getX()));
        sd->writeSensorData("GY_Y", String(GY61->getY()));
        sd->writeSensorData("GY_Z", String(GY61->getZ()));
        sd->writeSensorData("CJMCU_NOX", String(CJMCU->getNox()));
        sd->writeSensorData("CJMCU_RED", String(CJMCU->getNox()));
        sd->writeSensorData("DHT_TEMP", String(S_DHT->getTemperature()));
        sd->writeSensorData("DHT_HUM", String(S_DHT->getHumidity()));
        sd->writeSensorData("GPS_LONG", String(GPS->getLongitude()));
        sd->writeSensorData("GPS_LAT", String(GPS->getLatitude()));
        
        Serial.println("[Main] Sending buffer data...");
        int i = 0;
        rtc->resetTimer();
        while(rtc->secondsPassed()<10 && sd->bufferAvailable())
        {
          if(sim->writeData(sd->readBuffer())) 
            sd->nextBuffer(); 
          }
        }
      }

};

void setup() {
  Serial.begin(9600);
}

void loop() {
  Main * main = new Main();
  main->loop();
}
