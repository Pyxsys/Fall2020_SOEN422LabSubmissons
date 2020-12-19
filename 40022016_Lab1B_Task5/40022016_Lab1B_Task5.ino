/*Task 5 for Lab 1B, SOEN 422
Pierre-Alexis Barras
*/
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
  MCUCR &= ~(1 << 4);     //Allow pull-up functionality
    
  DDRB |= (1 << PB5);     //Set onboard led as output
  PORTB &= ~(1 << 5);     //Pull down onboard led

  DDRD |= (1 << PD2);     //set PIND2 as input
  PORTD |= (1 << PD2);    //Specify PIND2 (INT0) set as input_pullup
  
  EIMSK |= (1 << 0);      //Enable INT0 to gen external interrupts
  EICRA |= (1 << ISC00);  //Logical change in INT0 causes interrupt
  
  OCR1A = 0x9895;         //Set value to check compare at 39061
  TCCR1B |= (1 << WGM12); //Clear on Compare (CTC) on OCR1A
  TIMSK1 |= (1 << OCIE1A);//Set interrupt on compare match
  TCCR1B |= (1 << CS12) | (1 << CS10);  // set prescaler to 1024 and start the timer

  sei();  // enable interrupts

  while (1){} //loop empty as described by task.
  }

//Interrupt occurs on INT0 logic change
ISR (INT0_vect) {
  cli();              //disable interrupts  

  //check state of PIND2
  if(PIND & (1 << PIND2) ){}
                      //do nothing if pulled high
  else {
    PORTB |= (1 << 5);//turn on onboard LED
  
    TCNT1H = 0;       //clear 16-bit timer value
    TCNT1L = 0;
    }

  sei();              //enable interrupts
  }

//Interrupt occurs in a little under 2.5s periods
ISR (TIMER1_COMPA_vect) {
  cli();              //disable interrupts
  
  PORTB &= ~(1 << 5); //set LED off
  
  sei();              //enable interrupts
  }
