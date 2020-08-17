#include "DHT.h"

DHT dht(PIN_DHT, DHT22);

class SensorTemperatureDHT {

  public:

    SensorTemperatureDHT() {
      dht.begin();
    }

    float getTemperature() { return dht.readTemperature(); }
    float getHumidity() { return dht.readHumidity(); }
    
};
