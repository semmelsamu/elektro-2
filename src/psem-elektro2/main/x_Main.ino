
// MAIN

class Main {
  
  private:
    
    Sensor_DS18B20 * DS18B20;
    SensorDust * Dust;
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
      Dust = new SensorDust();
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


