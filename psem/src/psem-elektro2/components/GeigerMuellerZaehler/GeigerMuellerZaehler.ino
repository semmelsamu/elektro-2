/* 
  Anschlüsse: 
      GND = GND
      5V  = 5V
      VIN = DIGITAL 2

*/
              
#include <SPI.h>  
#define countingTime 60000

unsigned long counts;            
unsigned long previousMillis;  



void tube_impulse(){       
  counts++;
}

void setup(){  
  Serial.begin(9600); 
  counts = 0;
  attachInterrupt(0, tube_impulse, FALLING);
  
}

void loop(){                                
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > countingTime){
    previousMillis = currentMillis;

    Serial.print("CPM: ");
    Serial.println(counts);
    counts = 0;
  }
  
}
