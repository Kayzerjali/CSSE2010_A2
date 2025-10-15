/*
 * microwaveAssessment.c
 * Author : <Your Name + Student ID>
 */ 

#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

/* Internal Library Includes */
#include "serialio.h"
#include "terminalio.h"
#include "ledmatrix.h"

#define F_CPU 8000000UL 

// ENUMs / 'enumerations' basically give names to integer constants; by default values start at 0 and auto-increment.
// This lets you use readable labels (like MODE_QUICK, MODE_POPCORN) instead of magic numbers (0,1,2,...), though under the hood they are still integers
// Cooking mode enumeration.
typedef enum {
	MODE_QUICK,
	MODE_POPCORN,
	MODE_BEVERAGE,
	MODE_DEFROST
} Mode;

// Power level enumeration.
typedef enum {
	POWER_10,
	POWER_50,
	POWER_100
} PowerLevel;

// GLOBAL FLAGS - these can be accessed from anywhere in the file, making them useful for storing global state information: 
// These global variables are here to help you track the state of your microwave, feel free to add more as you see fit.
Mode mode;   // Quick, Popcorn, Beverage or Defrost mode.
uint8_t time_remaining; // Integer value between 0 and 9.
PowerLevel power_level; // 10% / 50% / 100%.
bool is_running; // Tracks whether the microwave is counting down.
bool is_paused;


void initialise_hardware(void) {
	// This is where you should set up your hardware ports; define inputs and outputs; initalise and clear your displays, etc.
	// Depending on what part you're up to, implement hardware setup based on what you've learnt in labs.
}

// Main microwave control logic.
// Handles state transitions, user input processing, and display updates.
void run_microwave() {
	// Feel free to edit this as much as you see fit.
	
	if (!is_running && !is_paused) {
		// IDLE STATE - microwave ready for mode selection and configuration.
		
	} else if (is_running) {
		// RUNNING STATE - timer actively counting down.
		
	} else if (is_paused) {
		// PAUSED STATE - timer stopped, awaiting resume or reset.
		
	} 
}


int main(void)
{
	// Method call to where you can ready all your one-time hardware related settings.
	initialise_hardware();
	
	// Initialises Microwave State to Quick Cook Mode, 5 seconds remaining, 10% Power, not running nor paused.
	mode = MODE_QUICK;
	time_remaining = 7;
	power_level = POWER_10;
	is_running = false;
	is_paused = false;
		
	// Main execution loop - runs continuously.
	// Handles all microwave operations through state machine.
	while (true) {
		run_microwave();
	}
}

