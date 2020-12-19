/*Task 2 for Lab 1C, SOEN 422
Pierre-Alexis Barras
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

static const uint8_t MAXDATASLOTS = 40;   //size maximum outlined in assignment
static const uint8_t DATASEGMENTSIZE = 8; //allocate in blocks of 8


volatile char * dataString; //char array that will store name
volatile uint8_t slotCount; //number of total slots
volatile uint8_t index;     //number of used slots

void UartSetup();           //init UART values
void UartSend(char * data); //send data over UART
void ExpandSlots(void);     //Increases dataString memory size


int main(void){
  
  slotCount = DATASEGMENTSIZE;                   //8 slots
  dataString = malloc(sizeof(char) * slotCount); //start with 8 slots
  index = 0;                                     //place at start
  
  UartSetup();
  
  sei();  //enable interrupts
  
  while(1){ //LOOP

    if(index){            //if string has been received
      while ((UCSR0A & (1<<RXC0)));  //wait for receiving to be done
      UartSend("Hello ");   //send greeting
      UartSend(dataString); //display name
      
                            //reset data
      free(dataString);       //clear data from memory
      dataString = malloc(sizeof(char) * slotCount);  //allocate new memory
      index = 0;              //reset index 
                              //(ensures only single message is sent)

      //send new line for readability
      while( !(UCSR0A & (1 << UDRE0)) );  //wait for send to be done
      UDR0 = '\n';                        //send newline char
      }

    }//ENDOF LOOP
  }//ENDOF MAIN

ISR(USART_RX_vect){
  dataString[index] = UDR0; //append data onto dataString
  index = index + 1;      //shift index to next pos
  
  if(index >= slotCount){  //check if index is past allocated memory.
    ExpandSlots();        //increase available memory
    }
  }

void UartSetup(){
  UBRR0L = (uint8_t)(BAUD_PRESCALLER & 0xFF);        //write lower baud byte
  UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);          //write higher baud byte
  
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);     //set frame character size to 8 data bits + 1 stop bit
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      //enable transmitter and reciever
  UCSR0B |= (1<<RXCIE0); //enable RXC interrupt
  }

void UartSend(char * data){
  uint8_t i = 0;
  while(data[i] > 31){                  //charcter is not whitespace (except SPACE = 32)
    while( !(UCSR0A & (1 << UDRE0)) );  //wait for transmit buffer to be empty
    UDR0 = data[i];                     //iterate over string
    i++;                                //increment counter
    }
  }

void ExpandSlots(void){
  if(slotCount < MAXDATASLOTS){                     //Limit the number of expansions
    slotCount += DATASEGMENTSIZE;                   //increase the number of slots                     
    realloc(dataString, sizeof(char) * slotCount);  //reallocate memory for the dataString
    }
  else{
    index = MAXDATASLOTS - 1; //hold index at end of string
    }
  }
