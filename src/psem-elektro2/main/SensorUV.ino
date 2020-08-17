class SensorUv {

  public:

    float getUv()
    {
      return analogRead(PIN_UV);
    }
  
};
