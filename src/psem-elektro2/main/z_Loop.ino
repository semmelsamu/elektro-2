
void loop() {
    Serial.println("Gas:");
    Serial.println(sensor_gas->get_nox(), DEC);
    Serial.println(sensor_gas->get_nox(), DEC);

    Serial.println("UV:");
    Serial.println(sensor_uv->get_uv());

    delay(3000);

    

    // Blinking -> Loop passed 1 time
    Serial.println("*** Loop passed ***");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
}
