
SensorDust * sensor_dust;
SensorGas * sensor_gas;
SensorUV * sensor_uv;

void setup() {
    Serial.begin(9600);
    Serial.println("*** Entering setup ***");

    setup_rtc();
    setup_geiger_counter();
    
    sensor_dust = new SensorDust();
    sensor_gas = new SensorGas();
    sensor_uv = new SensorUV();

    // Lighting the internal LED 3 times so we know everything started
    Serial.println("*** Setup complete, entering the loop ***");
    pinMode(LED_BUILTIN, OUTPUT);
    for(int i=0; i<3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}
