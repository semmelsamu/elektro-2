class SensorGyroscope {

  public: 

    float getX() { return (analogRead(PIN_GY_X)-363)*1.3; }
    float getY() { return (analogRead(PIN_GY_Y)-359)*1.3; }
    float getZ() { return (analogRead(PIN_GY_Z)-452)*1; }
  
};
