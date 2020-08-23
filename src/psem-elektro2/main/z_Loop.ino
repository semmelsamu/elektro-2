
void loop() {
    Serial.println(sensor_humidity_temperature->get_humidity());
    delay(3000);
}
