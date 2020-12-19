/*Task 3 for Lab 1B, SOEN 422
Pierre-Alexis Barras
*/
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

static const float VREF = 5.0;            //Reference voltage
static const float VOLTTHRESHOLD = 2.0;   //Distance voltage minima for aprox. between 4cm & 14cm

float readAdc(uint8_t adcPin) {
  ADMUX = (ADMUX & 0xF0) | (adcPin & 0x0F); //Select ADC channel with safety mask
                                            //MUXn bits modified to select correct channel to read
  ADCSRA |= (1 << ADSC);                    //Start conversion 
  while( ADCSRA & (1 << ADSC) );            //Wait until conversion is complete
  
  return ADC;
  }

void setup() {
  DDRB |= (1 << 5);   //Set onboard LED as output
  DDRC &= ~(1 << 2);  //Set A2(PINC2) pin as input

  ADMUX = (1 << 0x40);  //REFSn bits set to '01' so that Vref = AVcc at AREF pin

  ADCSRA |= (1 << ADEN);                                //Enable the ADC
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //ADC control register A prescaler bits set to 
                                                        //128 that ADC will operate between 50 and 200kHz

  readAdc(2);   //garbage read of ADC2 (Pin A2) to clear out ADC
  
  Serial.begin(9600);   //Set serial to Baud Rate 9600 (IDE default)
  Serial.println("[Startof Task 3]");
  }

void loop() {
  float sensorData = readAdc(2);  //read ADC of ADC2 (Pin A2)
  float sensorVolt = VREF / 1024 * sensorData;  //get sensorData as voltage
  
  Serial.print("Data: ");
  Serial.print(sensorData, 2);
  Serial.print("  Volt: ");
  Serial.print(sensorVolt , 2);
  Serial.println();
  
  if(sensorVolt > VOLTTHRESHOLD) {  //If sensor voltage lies within distance threshold
    PORTB |= (1 << 5);  //Turn on LED
    }
  else {
    PORTB &= ~(1 << 5); //Turn off LED
    }
  _delay_ms(5000);      //5 second delay
  }
