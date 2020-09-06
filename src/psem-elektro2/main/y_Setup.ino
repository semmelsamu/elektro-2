
RemoteBeeper * remote_beeper;
SDController * sd_controller;
SensorDust * sensor_dust;
SensorGas * sensor_gas;
SensorGeigerCounter * sensor_geiger_counter;
SensorGyroscope * sensor_gyroscope;
SensorHumidityTemperature * sensor_humidity_temperature;
SensorTemperature * sensor_temperature;
SensorUV * sensor_uv;
SensorVoltage * sensor_voltage;
Timer * timer;

void setup() {
    Serial.begin(9600);
    Serial.println("\n\n\n*** Entering setup ***\n");

    setup_rtc();
    
    remote_beeper = new RemoteBeeper();
    sd_controller = new SDController();
    sensor_dust = new SensorDust();
    sensor_gas = new SensorGas();
    sensor_geiger_counter = new SensorGeigerCounter();
    sensor_gyroscope = new SensorGyroscope();
    sensor_humidity_temperature = new SensorHumidityTemperature();
    sensor_temperature = new SensorTemperature();
    sensor_uv = new SensorUV();
    sensor_voltage = new SensorVoltage();
    timer = new Timer();

    // Lighting the internal LED 3 times so we know everything started
    Serial.println("\n\n\n*** Setup complete, entering the loop ***\n");
    pinMode(LED_BUILTIN, OUTPUT);
    for(int i=0; i<3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}
