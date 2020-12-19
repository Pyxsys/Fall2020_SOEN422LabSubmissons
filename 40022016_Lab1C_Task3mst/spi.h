#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define DD_LED DDRB
#define PT_LED PORTB
#define LEDPIN PB1

#define SPI_DDR DDRB
#define SS    PINB2
#define MOSI  PINB3
#define MISO  PINB4
#define SCK   PINB5

static const char LEDONCHAR = 'a';
static const char LEDOFFCHAR = '2';
volatile uint8_t command;
