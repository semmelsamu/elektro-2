
void loop() {
    Serial.println(sensor_humidity_temperature->get_temperature());
    delay(3000);
}
