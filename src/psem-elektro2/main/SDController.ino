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

#include <SPI.h>
#include <SD.h>

class SDController
{
    private:
            
        int sd_buffer_size = 0;
        int sd_buffer_position = 0;

    public:
        
        SDController(int pin_cs=53)
        {
            Serial.print("Initializing SD card...");
        
            if (!SD.begin(pin_cs)) {
                Serial.println("Card failed, or not present");
                // don't do anything more:
                while (1);
            }
            
            Serial.println("card initialized.");
        
            SD.remove("buffer.log");
        }
        
        int sd_add_to_file(String filename, String value)
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
        
        void sd_add_log(String key, String value)
        {
            sd_add_to_file(key+".log", value);
            sd_add_to_file("buffer.log", key+": "+value);
            sd_buffer_size++;
        }
        
        String sd_get_current_buffer()
        {
            File file = SD.open("buffer.log");
            if (file)
            {
                int i = 0;
                for(i=0; i<sd_buffer_position; i++) {
                    file.read();
                }
                String result = "";
                while(file.available()) {
                    char current_character = char(file.read());
                    result += current_character;
                    Serial.println(current_character);
                    if(current_character == '\n') {
                        break;
                    }
                }
                return result;
            }
            return "";
        }
        
        int sd_buffer_next()
        {
            if(sd_buffer_position < sd_buffer_size)
            {
                sd_buffer_position++;
                return 0;
            }
            return 1;
        }
};
