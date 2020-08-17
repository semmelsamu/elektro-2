class SensorDust {

  private:

    unsigned long duration, starttime, sampletime_ms = 2000, lowpulseoccupancy = 0;
    float ratio = 0, concentration = 0;
  
  public:
  
    SensorDust()
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
