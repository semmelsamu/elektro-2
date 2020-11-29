/*
 * SDController
 * This is a controller class for the sd module. It saves various log values in 
 * dedicated files and in a buffer, which can be red as well.
 * 
 * See:
 * https://www.arduino.cc/en/reference/SD
 * 
 * Circuit:
 * SD Card Module connected to a Arduino Mega via Pins:
 * - GND
 * - VCC: 5V
 * - MOSI: 50
 * - MISO: 51
 * - CLK: 52
 * - CS (default: 53)
*/

// If SPI is already included, we skip the include. Otherwise, a compiling error would occur
#ifndef __SPI
#define __SPI
#include <SPI.h>
#endif

#include <SD.h>

class SDController
{
    private:
            
        int sd_buffer_size = 0;
        int sd_buffer_position = 0;

    public:
        
        SDController(int pin_cs=53)
        {
            Serial.print("Initializing SD card... ");
        
            if (!SD.begin(pin_cs)) {
                Serial.println("Card failed, or not present. Exiting Program.");
                // don't do anything more:
                while (1);
            }
            
            Serial.println("card initialized.");
        }
        
        int add_to_file(String filename, String value)
        {
            File file = SD.open(filename, FILE_WRITE);
            if (file)
            {
                file.println(value);
                file.close();
                return 0;
            }
            Serial.println("Could not open "+filename);
            return 1;
        }
};
