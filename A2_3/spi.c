/*
 * spi.c
 * Created: 23/08/2025 8:37:20 PM
 * Author: leyla
 */

#include <avr/io.h>
#include "spi.h"

void spi_setup_master(uint8_t clockdivider) {
	DDRB |= (1 << 4) | (1 << 5) | (1 << 7);
	PORTB |= (1 << 4);
	SPCR0 = (1 << SPE0) | (1 << MSTR0);

	switch(clockdivider) {
		case 2:
		case 8:
		case 32:
			SPSR0 = (1 << SPI2X0);
			break;
		default:
			SPSR0 = 0;
			break;
	}
	
       switch(clockdivider) {
	       case 128:
				SPCR0 |= (1 << SPR00);
	       case 32:
	       case 64:
				SPCR0 |= (1 << SPR10);
				break;
	       case 8:
	       case 16:
				SPCR0 |= (1 << SPR00);
	       break;
       }
	   
	PORTB &= ~(1 << 4);
}

uint8_t spi_send_byte(uint8_t byte) {
	SPDR0 = byte;
	while ((SPSR0 & (1 << SPIF0)) == 0) {
		; // Wait
	}
	
	return SPDR0;
}
