/*Task 3 for Lab 1C, SOEN 422
Pierre-Alexis Barras
-Master Device Code-
*/
#include "spi.h"

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

int main(void){
  //SETUP
                                              //setup UART
  UBRR0L = (uint8_t)(BAUD_PRESCALLER & 0xFF); //write lower baud byte
  UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);   //write higher baud byte
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      //enable reciever/transmitter
                                                                //setup SPI
  SPI_DDR |= (1 << SS) | (1 << MOSI) | (1 << SCK);              //set SS, MOSI and SCK to output
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);  //enable SPI, set as master, and clock to fosc/128

  //LOOP
  while(1){

    //receive from uart
    while (!(UCSR0A & (1 << RXC0)));  //wait for usart data to be received
    switch(UDR0){                   //obtain character from UDR0
      
      case LEDONCHAR:       //value is equal to 'on' char
        command = LEDONCHAR;
        break;
        
      case LEDOFFCHAR:      //value is equal to 'off' char
        command = LEDOFFCHAR;
        break;

      case '\n':            //newline case
        command = 0;        //send null
        break;
      default:
        command = '-';      //bad char case
      
      }
      
    //send to slave
    SPI_DDR &= ~(1 << SS);        //pull slave select low
    SPDR = command;               //send command over spi
    while(!(SPSR & (1 << SPIF))); //wait for spi transmission to complete
    SPI_DDR |= (1 << SS);         //return slave select high

    //get confirmation
    SPDR = 0xFF;                  //send dummy byte
    while(!(SPSR & (1 << SPIF))); // Wait for reception complete
    command = SPDR;

    //display confrimation
    UDR0 = command;
    
    }//ENDOF LOOP
  }//ENDOF MASTER
