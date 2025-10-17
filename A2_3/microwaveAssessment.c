/*
 * microwaveAssessment.c
 * Author : Kayzer Ali 49621169 
 */ 

#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

/* Internal Library Includes */
#include "serialio.h"
#include "terminalio.h"
#include "ledmatrix.h"
#include "custom.h"

#define F_CPU 8000000UL 


/* ===== GLOBAL FLAGS ===== */
Mode mode;   
uint8_t time_remaining; 
volatile PowerLevel power_level; 
bool is_running; 
bool is_paused;
volatile SSD_STATE ssd_state;


void initialise_hardware(void) {
	
	// Test ssd cc pin
	DDRD = 0xFF;
	
	
	// IO Board LED's
	IO_LED_DDR = 0xFF;
	
	// SSD Display. Interrupt every 1ms using TC1
	SSD_DDR = 0xFF;
	
	// WGM = CTC
	TCCR1A = 0;
	// CS11 = 1 sets prescalar to 8
	
	TCCR1B = (1 << CS11) | (1 << WGM12);
	OCR1A = 999; // Match every 1000 ticks (1ms)
	
	// Enable interrupt on OCR1A (pg. 142)
	TIMSK1 = (1 << OCIE1A);
	
	// Clear interrupt flag in Timer Interrupt Flag Register 1 (TIFR1)
	TIFR1 = (1 << OCF1A);
	
	
	// Task 1.1 mode selection with switches
	SWITCH_DDR &= ~((1 << S0) | (1 << S1));
	
	// Task 1.2 power selection with button. Setting up interrupt on rising edge INT2
	
	EICRA = (1 << ISC20) | (1 << ISC21); // rising edge
	EIMSK = (1 << INT2);
	EIFR = (1 << INTF2);
	
	
	
	
	sei();	
	
}
/* Task 1.1. Switches IO:S0 (AVR:B0) and IO:S1 (AVR:B1) are used to change the mode of the machine.

The subroutine queries the state of the switches and updates the global mode variable.
LED displayed are handled by a separate subroutine.
*/
void select_mode(void) {
	
	if (SWITCH_PIN & (1 << S0) && SWITCH_PIN & (1<< S1)) {
		
		// S0:1, S1:1 -> defrost
		mode = MODE_DEFROST;
		
	}
	else if (!(SWITCH_PIN & (1 << S0)) && (SWITCH_PIN & (1 << S1))) {
		
		// S0:0, S1:1 -> beverage
		mode = MODE_BEVERAGE;
	}
	else if ((SWITCH_PIN & (1 << S0)) && !(SWITCH_PIN & (1 << S1))) {
		
		// S0:1, S1:0 -> popcorn
		mode = MODE_POPCORN;
		
		} else {
			
		// S0:0, S1: 0 -> quick
		mode = MODE_QUICK;
	}
	
}


/* Task 1.2. ISR for when IO:B2 (AVR: B2/INT2). ISR updates state of power global*/
ISR(INT2_vect) {
	
	
	if (power_level == POWER_10) {power_level = POWER_50; return;}
	if (power_level == POWER_50) {power_level = POWER_100; return;}
	if (power_level == POWER_100) {power_level = POWER_10; return;}
	
}


/* Displays the IO Board LED's based on the current state of the mode global.

===== Notes:

17/10 - 
ISSUE: LEDS are not full brightness. Using if statements didn't fix issue. Adding returns to if statements didn't fix and neither did else ifs.
SOL: Fixed by setting DDR in initialise hardware.


*/
void display_io_led(void) {
	
	// Displaying LED's for mode
	if (mode == MODE_DEFROST) {IO_LED_PORT = (1 << 3);}
	if (mode == MODE_BEVERAGE) {IO_LED_PORT = (1 << 2);}
	if (mode == MODE_POPCORN) {IO_LED_PORT = (1 << 1);}
	if (mode == MODE_QUICK) {IO_LED_PORT = (1 << 0);}
	
	// Displaying LED's for power
	if (power_level == POWER_10) {IO_LED_PORT |= (1 << 5);}
	if (power_level == POWER_50) {IO_LED_PORT |= (1 << 5) | (1 << 6);}
	if (power_level == POWER_100) {IO_LED_PORT |= (1 << 5) | (1 << 6) | (1 << 7);}
		
}

/* Displays the current state of the SSD as specified by the global SSD_STATE variable
Subroutine to be called in ISR.

==== Notes:
17/10
ISSUE: Currently not multiplexing

 */
void display_ssd() {
	
	// ssd_state.DIGIT ^= 1; // toggle Digit to switch which digit is being displayed
	
	if (ssd_state.DISPLAY_DIGIT == 0) {
		SSD_PORT = ssd_state.DIGIT0;
		PORTD = 0;
		ssd_state.DISPLAY_DIGIT = 1;
		return;

	}
	if (ssd_state.DISPLAY_DIGIT == 1) {
		SSD_PORT = ssd_state.DIGIT1;
		PORTD = 1;
		ssd_state.DISPLAY_DIGIT = 0;
		return;
		
	}
	
}

/* ISR for SSD on OCR1A */
ISR(TIMER1_COMPA_vect) {
	display_ssd();
}










void run_microwave() {
	
	if (!is_running && !is_paused) {
		// IDLE STATE - microwave ready for mode selection and configuration.
		
		select_mode();
		display_io_led();
		
		
	} else if (is_running) {
		// RUNNING STATE - timer actively counting down.
		
	} else if (is_paused) {
		// PAUSED STATE - timer stopped, awaiting resume or reset.
		
	} 
}


int main(void)
{
	
	initialise_hardware();
	
	// Initialises Microwave State to Quick Cook Mode, 5 seconds remaining, 10% Power, not running nor paused.
	mode = MODE_QUICK;
	time_remaining = 7;
	power_level = POWER_10;
	is_running = false;
	is_paused = false;
	ssd_state = (SSD_STATE) {0, SSD_ONE, SSD_ONE};
	
	
	
	
	while (true) {
		run_microwave();
	}
}

