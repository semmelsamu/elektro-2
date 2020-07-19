/*
 * sd
 * This is a class for the sd module.
 * 
 * Circuit:
 * SD Card Module attached to a Arduino Mega via Pins:
 * MOSI - pin 50
 * MISO - pin 51
 * CLK - pin 52
 * CS - pin 53
 */

#include <SPI.h>
#include <SD.h>

#define PIN_SD_CHIPSELECT 53

/*class SD_Card {
    
    private:
    
        File file;
        
    public:

        SD_Card() 
        {
            SD.begin(PIN_SD_CS);
        }
      
        void writeData(String sensor, String data) {
            file = SD.open(sensor+".sns", FILE_WRITE);
            
            if(file)
            {  
                file.println(data);
                file.close();
            }
            else
            {
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
};*/

void setup(){
    Serial.begin(9600);
    
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.print("Initializing SD card...");

    if (!SD.begin(PIN_SD_CHIPSELECT)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        while (1);
    }
    Serial.println("card initialized.");
}

void loop() {
    // make a string for assembling the data to log:
    String dataString = "val1,val2,val3";

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

     // if the file is available, write to it:
    if (dataFile) 
    {
        dataFile.println(dataString);
        dataFile.close();
        // print to the serial port too:
        Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else 
    {
        Serial.println("error opening datalog.txt");
    }

    // wait for a sec:
    delay(1000);
}
