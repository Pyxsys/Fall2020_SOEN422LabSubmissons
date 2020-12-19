/*Task 1 for Lab 1B, SOEN 422
Pierre-Alexis Barras
*/
#include <avr/io.h>
const uint8_t ledPin = 13;
const uint8_t inputPin = 6;

void setup() {
    pinMode(inputPin, INPUT_PULLUP);  //set PD6 as input
    pinMode(ledPin, OUTPUT);          //Set onboard LED as output
}

void loop() {
  //Assign led output based on input in value
  digitalWrite(ledPin, (digitalRead(inputPin) == HIGH) ? LOW : HIGH);
}
