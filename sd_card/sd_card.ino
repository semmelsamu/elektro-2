#include <SPI.h>
#include <SD.h>

//#include <ArduinoJson.h>

#define PIN_SD 53

class SD_Card {
  
  private:
  
    File file;

  public:

    SD_Card() {
      SD.begin(PIN_SD);
    }
  
    void writeData(String sensor, String data) {

      file = SD.open(sensor+".sns", FILE_WRITE);
      if(file){  
        file.println(data);
        file.close();
      }
      else{
        Serial.print("[SD] Fatal Error: Couldn't open file on SD card");
      }
    }

    void readData(String sensor)
    {
      file = SD.open(sensor+".sns");
      if (file) {
        
        while (file.available()) {
          Serial.write(file.read());
        }
     
        file.close();
      } 
      else 
      {
        Serial.println("[SD] Fatal Error: Couldn't open file on SD card");
      }
    }
    
};

SD_Card * sdcard;

void setup(){
  Serial.begin(9600);
  sdcard = new SD_Card();
}

void loop() {
  sdcard->writeData("testsensor","testvalue");
  delay(1000);
}
