/*Task 3 for Lab 1C, SOEN 422
Pierre-Alexis Barras
-Slave Device Code-
*/
#include "spi.h"

int main(void){
  //SETUP
  SPI_DDR = (1 << MISO);          //set MISO to output
  SPCR = (1 << SPE) | (1<<SPIE);  //enable SPI, and SPI-interrupts
  SPDR = 0;
  
  DD_LED |= (1 << LEDPIN);        //set LED pin as output.

  //LOOP
  while(1){
    
    //receive from master via interrupt
    switch(command){  //obtain character from data register
      
      case LEDONCHAR:       //value is equal to 'on' char
        PT_LED |= (1 << LEDPIN);  //toggle led on
        command = '1';            //led on
        break;
        
      case LEDOFFCHAR:      //value is equal to 'off' char
        PT_LED &= ~(1 << LEDPIN); //toggle led off
        command = '0';            //led off
        break;

      case 0:               //Null case
        command = 0;
        break;
      default:
        command = 'x';      //fail
      }

    //send confirmation
    if(command){  //if value
      SPDR = command;
      command = 0;  //set command to do nothing
      }
      
    }//ENDOF LOOP  
  }//ENDOF SLAVE

ISR (SPI_STC_vect){
  command = SPDR;
  }
