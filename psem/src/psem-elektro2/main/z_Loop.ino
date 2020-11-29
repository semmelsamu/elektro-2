
void loop() {


    // Reading the values and printing them to the Serial:
    delay(2000);

    unsigned long current_time = timer->get_unix_time();
    Serial.println("current_time="+String(current_time));

    float dust_concentration = sensor_dust->get_concentration();
    Serial.println("dust_concentration="+String(dust_concentration));

    int gas_nox = sensor_gas->get_nox();
    Serial.println("gas_nox="+String(gas_nox));
    int gas_red = sensor_gas->get_red();
    Serial.println("gas_red="+String(gas_red));

    int gyroscope_x = sensor_gyroscope->get_x();
    Serial.println("gyroscope_x="+String(gyroscope_x));
    int gyroscope_y = sensor_gyroscope->get_y();
    Serial.println("gyroscope_y="+String(gyroscope_y));
    int gyroscope_z = sensor_gyroscope->get_z();
    Serial.println("gyroscope_z="+String(gyroscope_z));

    float temperature = sensor_temperature->get_temperature();
    Serial.println("sensor_temperature="+String(temperature)+"°C");

    int uv = sensor_uv->get_uv();
    Serial.println("UV="+String(uv));

    float timer_temperature = timer->get_temperature();
    Serial.println("timer_temperature="+String(timer_temperature)+"°C");
    
    int DHT_humidity = sensor_humidity_temperature->get_humidity();
    Serial.println("DHT_humidity="+String(DHT_humidity)+"%");

    int DHT_temperature = sensor_humidity_temperature->get_temperature();
    Serial.println("DHT_temperature="+String(DHT_temperature)+"°C");
  
      
    
   

    // Writing Sensor Values to SD:
    Serial.println("\nLogging to SD Card...");
    sd_controller->add_to_file("dustconc.log", String(current_time)+":"+String(dust_concentration)); //dust concentration
    sd_controller->add_to_file("sngasnox.log", String(current_time)+":"+String(gas_nox)); 
    sd_controller->add_to_file("sngasred.log", String(current_time)+":"+String(gas_red));
    sd_controller->add_to_file("gyroscox.log", String(current_time)+":"+String(gyroscope_x));
    sd_controller->add_to_file("gyroscoy.log", String(current_time)+":"+String(gyroscope_y));
    sd_controller->add_to_file("gyroscoz.log", String(current_time)+":"+String(gyroscope_z));
    sd_controller->add_to_file("dstemper.log", String(current_time)+":"+String(temperature)); //temperature outside
    sd_controller->add_to_file("uvintens.log", String(current_time)+":"+String(uv)); //uv intensity outside
    sd_controller->add_to_file("timetemp.log", String(current_time)+":"+String(timer_temperature)); //temperature inside (timer)
    sd_controller->add_to_file("humidity.log", String(current_time)+":"+String(DHT_humidity)); //humidity inside
    sd_controller->add_to_file("DHT_temp.log", String(current_time)+":"+String(DHT_temperature)); //temperature inside (DHT)
   

    // Waiting at least 10 seconds
    Serial.print("Waiting at least 10 seconds");
    while(timer->get_unix_time() < current_time+10) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" Done.");


    // Blinking so we see the loop passed 1 time
    Serial.println("\n\n\n*** Loop passed ***\n");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);

     unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > countingTime){
    previousMillis = currentMillis;
    sd_controller->add_to_file("GMZ.log", String(current_time)+":"+String(counts));
    Serial.print("CPM: ");
    Serial.println(counts);
    counts = 0;
}
}
