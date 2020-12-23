/* 
 * SensorGeierCounter
 * It reads out the action of the Geiger-Müller-Counter 
 *  
 * See: 
 * https://create.arduino.cc/projecthub/EDUcentrum/geiger-counter-with-arduino-uno-2cf621
 * 
 * Circuit:
 * GeigerCounter connected to Arduino Mega via pins:
 * -GND: GND
 * -VCC: 5V
 * -VIN: DIGITAL 2
*/

#include <SPI.h>
#define countingTime 60000

unsigned long counts=0;            
unsigned long previousMillis;  

void tube_impulse(){
    counts++;
}
