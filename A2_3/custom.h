
#ifndef CUSTOM_H_

/* ===== PIN MAP ==== 

A[0:7] SSD

B0 -> S0
B1 -> S1
B2 -> B2
B3 -> *
B[4:7] -> SPI

C[0:7] -> IO LED's

D[0:1] -> USART
D2 -> B0
D3 -> B1


*/

/* ===== PORTS AND PINS ===== */

// Switches
#define SWITCH_DDR DDRB
#define SWITCH_PIN PINB
#define S0 0
#define S1 1

// IO BOARD LED 
#define IO_LED_DDR DDRC
#define IO_LED_PORT PORTC

// SSD
#define SSD_DDR DDRA
#define SSD_PORT PORTA


/* ===== ENUMS ===== */

// Mode enumeration
typedef enum {
	MODE_QUICK,
	MODE_POPCORN,
	MODE_BEVERAGE,
	MODE_DEFROST
} Mode;

// Power level enumeration
typedef enum {
	POWER_10,
	POWER_50,
	POWER_100
} PowerLevel;

// SSD encodings
typedef enum {
	
	SSD_ZERO = 0x3F,
	SSD_ONE = 0x06,
	SSD_TWO = 0x5B,
	SSD_THREE = 0x4F,
	SSD_FOUR = 0x66,
	SSD_FIVE = 0x6D,
	SSD_SIX = 0x7D,
	SSD_SEVEN = 0x07,
	SSD_EIGHT = 0x7F,
	SSD_NINE = 0x6F,
	SSD_Q = 0x67,
	SSD_P = 0x73,
	SSD_B = 0x7C,
	SSD_D = 0x5E
	
} SSD_SYMBOL;

typedef struct {
	
	uint8_t DIGIT;
	SSD_SYMBOL DIGIT0;
	SSD_SYMBOL DIGIT1;
	
} SSD_STATE;



#endif