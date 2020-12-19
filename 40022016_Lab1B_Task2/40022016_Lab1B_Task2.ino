/*Task 2 for Lab 1B, SOEN 422
Pierre-Alexis Barras
*/
#include <avr/io.h>

void setup() {
  DDRB = (1 << 5);  //Set onboard LED as output
  PORTB |= (1 << 5);
  
  MCUCR &= ~(1 << 4); //Allow pull-up functionality
  PORTD |= (1 << 6);  //Pin D6 set as input_pullup
  }

void loop() {
  //check value of PIND6
  if(PIND & (1 << 6)){
    PORTB &= ~(1 << 5); //set LED off
    }
  else{
    PORTB |= (1 << 5);  //set LED on
    }
  }
