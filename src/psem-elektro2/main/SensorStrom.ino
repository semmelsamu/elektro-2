class SensorStrom {

  public: 

    float getStromstaerke() { return ((analogRead(PIN_STROM)/1024*5)/50*STROM_WIEDERSTAND); }
    float getSpannung() { return 0.0f; }
  
};
