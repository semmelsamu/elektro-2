
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


/* SD-Karte */
#include <SPI.h>
#include <SD.h>

/* DHT22 */
#include "DHT.h"

/* RTC */
#include "RTClib.h"


////////// SETUPS FÜR SENSOREN //////////

/* DS18B20 */


/* DHT22 */

DHT dht(PIN_DHT, DHT22);

////////// GLOBALE FUNKTIONEN //////////

void wait(){ // Wartet bis man im Serial auf Senden drückt
  while(Serial.available()==0) {} while(Serial.available()>0) { Serial.read(); }
}

////////// SENSORENKLASSEN //////////





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
