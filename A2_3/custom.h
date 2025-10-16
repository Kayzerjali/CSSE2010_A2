
#ifndef 

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



#endif