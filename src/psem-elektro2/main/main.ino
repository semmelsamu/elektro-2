
////////// PINS //////////

#define PIN_ABORT_LOOP 30

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

/* Strommesser */
#define PIN_STROM A14

/* SD */
#define PIN_SD 53

/* Strom */
#define STROM_WIEDERSTAND 0.1


////////// INCLUDES //////////

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


////////// SETUPS FÜR SENSOREN //////////

/* DS18B20 */
OneWire oneWire(PIN_DS18B20); 
DallasTemperature sensors(&oneWire);

/* DHT22 */

DHT dht(PIN_DHT, DHT22);

////////// GLOBALE FUNKTIONEN //////////

void wait(){ // Wartet bis man im Serial auf Senden drückt
  while(Serial.available()==0) {} while(Serial.available()>0) { Serial.read(); }
}

////////// SENSORENKLASSEN //////////

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

class Sensor_Strom {

  public: 

    float getStromstaerke() { return ((analogRead(PIN_STROM)/1024*5)/50*STROM_WIEDERSTAND); }
    float getSpannung() { return 0.0f; }
  
};

// RTC KLASSE

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

// SD

class Sd {
  private:
    File file;
    int bufferLine;
    String currentBuffer;

  public: 
    Sd()
    {
      SD.begin(PIN_SD);
      bufferNext();
    }

    void writeData(String sensor, String data)
    {
      Serial.println("[SD] Writing: {\""+sensor+"\" -> \""+data+"\"}");
      file = SD.open(sensor+".SNS", FILE_WRITE);
      if(file){  
        file.println(getUnixTime()+"_"+data);
        file.close();
      }
      else{
        Serial.println("[SD] Fatal Error: Couldn't open file on SD card");
      }
      
      file = SD.open("BUFFER00.BUF", FILE_WRITE);
      if(file){  
        file.println(getUnixTime()+"_"+sensor+"_"+data);
        file.close();
      }
      else{
        Serial.println("[SD] Fatal Error: Couldn't open file on SD card");
      }
    }

    String getCurrentBuffer()
    {
      return currentBuffer;
    }

    void bufferNext()
    {
      file = SD.open("BUFFER00.BUF");
  
      if(file)
      {
        String bufferString = file.readString();
        file.close();

        currentBuffer = bufferString.substring(0, bufferString.indexOf('\n'));
        currentBuffer.trim();
        bufferString = bufferString.substring(bufferString.indexOf('\n'));
        bufferString.trim();
      
        SD.remove("BUFFER00.BUF");
        
        File file = SD.open("BUFFER00.BUF", FILE_WRITE);
        
        if(file)
        {
          file.println(bufferString);
          file.close();
        } else Serial.println("[SD] Fatal Error: Could not open file on SD");
      } else Serial.println("[SD] Fatal Error: Could not open file on SD");
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

    boolean sendData(String content)
    {
      Serial.println("[SIM] Sending: \""+content+"\"");
      return true;
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
    Sensor_Strom * strom;

    Gps * GPS;
    Sim * sim;
    Sd * sd;
    
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
      strom = new Sensor_Strom();

      GPS = new Gps();
      sim = new Sim();
      sd = new Sd();

      pinMode(PIN_ABORT_LOOP, INPUT);

      Serial.println("[Main] Init complete."); 
    }

    void loop()
    {
      while(digitalRead(PIN_ABORT_LOOP) == LOW)
      {

        Serial.println("[Main] Reading sensor data...");
        String sensorvalues[] = {
          String(DS18B20->getTemperature()),
          String(Dust->getConcentration()),
          String(Uv->getUv()),
          String(GY61->getX()),
          String(GY61->getY()),
          String(GY61->getZ()),
          String(CJMCU->getNox()),
          String(CJMCU->getRed()),
          String(S_DHT->getTemperature()),
          String(S_DHT->getHumidity()),
          String(GPS->getLatitude()),
          String(GPS->getLongitude()),
          String(strom->getSpannung()),
          String(strom->getStromstaerke())
        };
        
        Serial.println("[Main] Writing sensor data to sd and buffer...");
        for(int i=0; i<13; i++)
        {
          String filename = "SENSOR";
          if(i<10) filename+="0";
          filename+=String(i);
          sd->writeData(filename, sensorvalues[i]);
        }
        
        Serial.println("[Main] Sending buffered data...");
        resetTimer();
        if(sd->getCurrentBuffer().length() == 0) sd->bufferNext();
        while(sd->getCurrentBuffer().length() != 0 && secondsPassed() < 30)
        {
          if(sim->sendData(sd->getCurrentBuffer()))
          {
            sd->bufferNext();
          }
        }
        
        delay(1000);
      }
   }
};

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
