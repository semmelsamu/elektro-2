#include "DHT.h" //Feuchtigkeit und temp

#define DHTPIN 2 //Feuchtigkeit und temp
#define DHTTYPE DHT11//Feuchtigkeit und temp
DHT FSen(DHTPIN, DHTTYPE);//Feuchtigkeit und temp

#define PRE_Pin 3

int nox_wert = 0;
int red_wert = 0;
int Dust = 11; //Dustsensor
int Hall = 12;//Magnetfeld
int x;//Accelerometer
int y;//Accelerometer
int z;//Accelerometer
int uv; //uv-Sensor
unsigned long duration; //Dustsensor
unsigned long starttime;//Dustsensor
unsigned long sampletime_ms = 2000; //Dustsensor
unsigned long lowpulseoccupancy = 0;//Dustsensor
float ratio = 0;//Dustsensor
float concentration = 0;//Dustsensor
float temp = 0;//Feuchtigkeit und temp
float feucht = 0;//Feuchtigkeit und temp

void setup() {
  Serial.begin(9600);
  pinMode(Dust,INPUT);//Dustsensor
  starttime = millis(); //Dustsensor
  
  pinMode(Hall,INPUT);  //Magnetfeld

  FSen.begin();//Feuchtigkeit und temp

  pinMode(PRE_Pin, OUTPUT);
  Serial.println("Aufwärmen(10sec)...");
  digitalWrite(PRE_Pin, 1);
  delay(10000);
  digitalWrite(PRE_Pin,1);
  Serial.println("Fertig");
}

void loop() {
  duration = pulseIn(Dust, LOW);//Dustsensor
  lowpulseoccupancy = lowpulseoccupancy+duration;//Dustsensor
  if ((millis()-starttime) >= sampletime_ms) //Dustsensor
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  //Dustsensor
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; //Dustsensor
    Serial.println("\n");//Dustsensor
    Serial.print("Konzentation = ");//Dustsensor
    Serial.print(concentration);//Dustsensor
    Serial.println(" pcs/0.01cf");//Dustsensor
    lowpulseoccupancy = 0;//Dustsensor
    starttime = millis();//Dustsensor
 }
   x=analogRead(A8);//Accelerometer
   y=analogRead(A9);//Accelerometer
   z=analogRead(A10);//Accelerometer

   uv=analogRead(A11);//UV-Sensor

   nox_wert = analogRead(A12);
   red_wert = analogRead(A13);
   
   feucht = FSen.readHumidity();
   temp = FSen.readTemperature();
   
   
   Serial.print("Magnetfeld: ");//Magnetfeld
   Serial.print(digitalRead(Hall));//Magnetfeld

   Serial.println("\n");//Accelerometer
   Serial.print("xBeschleunigung= ");//Accelerometer
   Serial.println(x);//Accelerometer
   Serial.print("yBeschleunigung= ");//Accelerometer
   Serial.println(y);//Accelerometer
   Serial.print("zBeschleunigung= ");//Accelerometer
   Serial.println(z);//Accelerometer
   Serial.println("\n");
   

   Serial.print("UV-Sensor: ");//UV-Sensor
   Serial.println(uv); //UV-Sensor
   
   Serial.print("Luftfeuchtigkeit: "); //Feuchtigkeit und temp
   Serial.print(feucht);//Feuchtigkeit und temp
   Serial.print(" %\t");//Feuchtigkeit und temp
   Serial.print("Temperatur: ");//Feuchtigkeit und temp
   Serial.print(temp);//Feuchtigkeit und temp
   Serial.println("°C");//Feuchtigkeit und temp

   Serial.print("noxWert: ");
   Serial.println(nox_wert);
   Serial.print("redWert: ");
   Serial.println(red_wert);
   
   
   Serial.print("-----------------------------------------------------");//ABSCHLUSS
   delay(2000);

   
}
