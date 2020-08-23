
SensorHumidityTemperature * sensor_humidity_temperature;

void setup() {
    Serial.begin(9600);
    setup_rtc();
    setup_geiger_counter();
    
    sensor_humidity_temperature = new SensorHumidityTemperature(7);
}
