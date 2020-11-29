
SDController * sd_controller;
SensorDust * sensor_dust;
SensorGas * sensor_gas;
SensorGeigerCounter * sensor_geiger_counter;
SensorGyroscope * sensor_gyroscope;
SensorHumidityTemperature * sensor_humidity_temperature;
SensorTemperature * sensor_temperature;
SensorUV * sensor_uv;
Timer * timer;

void tube_impulse(){       //The method has to stay out of the class for it to work
    counts++;
    }

void setup() {
    Serial.begin(9600);
    Serial.println("\n\n\n*** Entering setup ***\n");
    
  

    setup_rtc();
    
    sd_controller = new SDController();
    sensor_dust = new SensorDust();
    sensor_gas = new SensorGas();
    sensor_geiger_counter = new SensorGeigerCounter();
    sensor_gyroscope = new SensorGyroscope();
    sensor_humidity_temperature = new SensorHumidityTemperature();
    sensor_humidity_temperature -> sensor_setup();
    sensor_temperature = new SensorTemperature();
    sensor_uv = new SensorUV();
    timer = new Timer();

    attachInterrupt(0, tube_impulse, FALLING);//this belongs to the "SensorGeigerCounter" and it needs to be here to work in the backround
  
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
