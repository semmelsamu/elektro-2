char BTval; //Werte per BT gesendet
char lastVal; //Speichert den letztenstatus des Lautsprechers
int speakerPin = 11; //einer der Frei ist

void setup() {

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { // wenn daten empfangen werden
    BTval = Serial.read(); // Daten auslesen
  }
  if (BTval == '1') { // wenn "ein"
    tone(speakerPin, 800);
    if (lastVal != '1')  // wenn der letzte empfangwert keine 1 war
      Serial.println(F("Speaker ON"));
    lastVal = BTval;
  }
  else if (BTval == '0') { //wenn "aus"
    noTone(speakerPin);
    if (lastVal != '0')  // wenn der letzte empfangwert keine 0 war
      Serial.println(F("Speaker OFF"));
    lastVal = BTval;
  }
}
