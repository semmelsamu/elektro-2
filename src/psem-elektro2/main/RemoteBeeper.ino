/*
 * RemoteBeeper
 * This class lets you control a speaker via a the HC-05 bluetooth module.
 * 
 * See:
 * https://funduino.de/tutorial-hc-05-und-hc-06-bluetooth
 * 
 * Circuit:
 * HC-05 Module connected to Arduino Mega via Pins:
 * - GND
 * - VCC: 3.3V !IMPORTANT
 * - RXD: TX1
 * - TXD: RX1
 * Speaker connected to Arduino Mega via Pins:
 * - GND
 * - PIN 11 (default)
*/

class RemoteBeeper {
    
    private:
    
        int speaker_pin;
        char BTval, lastVal;

    public:

        RemoteBeeper(int speaker_pin=11) {
            speaker_pin = speaker_pin;
        }

        void handle_actions() {
            if (Serial.available()) { // wenn daten empfangen werden
                BTval = Serial.read(); // Daten auslesen
            }
            if (BTval == '1') { // wenn "ein"
                tone(speaker_pin, 800);
                if (lastVal != '1')  // wenn der letzte empfangwert keine 1 war
                    Serial.println(F("Speaker ON"));
                lastVal = BTval;
            }
            else if (BTval == '0') { //wenn "aus"
                noTone(speaker_pin);
                if (lastVal != '0')  // wenn der letzte empfangwert keine 0 war
                    Serial.println(F("Speaker OFF"));
                lastVal = BTval;
            }
        }
};
