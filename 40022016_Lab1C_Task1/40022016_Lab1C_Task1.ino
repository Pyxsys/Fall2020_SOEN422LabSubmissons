/* Task 1 for Lab 1C, SOEN 422
 * Pierre-Alexis Barras
 */
#include <avr/io.h>
#include <stdint.h>;
#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

static const char LEDONCHAR = 'a';    //LED on control char value
static const char LEDOFFCHAR = '2';   //LED off control char value

void UartSetup(void);             //init UART values
unsigned char UartReceive(void);  //listen for uart data

int main(void) {
  //Setup
  DDRB |= (1 << PB5);                   //set onboard LED as output.
  PORTB &= ~(1 << PB5);                 //default LED state as 'off'

  UartSetup();  //set baud rate to 9600 and enable reciever
  
  //Loop
  while(1){
    switch(UartReceive()){  //obtain character from UDR0
      
      case LEDONCHAR:       //value is equal to 'on' char
        PORTB |= (1 << PB5);  //toggle led on
        break;
        
      case LEDOFFCHAR:      //value is equal to 'off' char
        PORTB &= ~(1 << PB5); //toggle led off
        break;
      } 
    }
  }

void UartSetup(void){
  UBRR0L = (uint8_t)(BAUD_PRESCALLER & 0xFF); //write lower baud byte
  UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);   //write higher baud byte
  
  UCSR0B |= (1 << RXEN0);  //enable reciever
  }

unsigned char UartReceive(void) {
  while (!(UCSR0A & (1<<RXC0)));        //Wait for data to be received
  return UDR0;                          //get and return data from buffer
  }
