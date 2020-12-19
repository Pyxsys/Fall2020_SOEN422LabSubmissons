/*Task 4 for Lab 1B, SOEN 422
Pierre-Alexis Barras
*/
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

void setup(){
  DDRD |= (1 << 5);  //Set PD5 as an output
  
  OCR0B = 255;  //Set PWM for 100% duty cycle

  TCCR0A |= (1 << COM0B1);  //Set none-inverting mode (HIGH at bottom, LOW on Match)
                            //and allow output on OC0B.
  TCCR0A |= (1 << WGM01);   //Set to fast PWM Mode (Mode 3)
  TCCR0B |= (1 << CS01);    //Set prescaler to 8 and start PWM
  }

void loop(){
  _delay_ms(5000);  //Wait 5 seconds
  OCR0B = 0;        //Set PWM for 0% duty cycle
  _delay_ms(5000);
  OCR0B = 64;       //Set PWM for 25% duty cycle
  _delay_ms(5000);
  OCR0B = 128;      //Set PWM for 50% duty cycle
  _delay_ms(5000);
  OCR0B = 192;      //Set PWM for 75% duty cycle
  _delay_ms(5000);
  OCR0B = 255;      //Set PWM for 100% duty cycle*/
  }
