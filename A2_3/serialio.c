/*
 * serialio.c
 * Created: 23/08/2025 6:01:18 PM
 * Author: leyla
 */

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define SYSCLK 8000000L
#define OUTPUT_BUFFER_SIZE 255
#define INPUT_BUFFER_SIZE 16

volatile char out_buffer[OUTPUT_BUFFER_SIZE];
volatile uint8_t out_insert_pos;
volatile uint8_t bytes_in_out_buffer;
volatile char input_buffer[INPUT_BUFFER_SIZE];
volatile uint8_t input_insert_pos;
volatile uint8_t bytes_in_input_buffer;
volatile uint8_t input_overrun;

static int8_t do_echo; // Keep track of whether incoming characters are to be echoed back or not
static int uart_put_char(char, FILE*);
static int uart_get_char(FILE*);
static FILE myStream = FDEV_SETUP_STREAM(uart_put_char, uart_get_char, _FDEV_SETUP_RW);

void init_serial_stdio(long baudrate, int8_t echo);

void init_serial_stdio(long baudrate, int8_t echo) {
	uint16_t ubrr;
	out_insert_pos = 0;
	bytes_in_out_buffer = 0;
	input_insert_pos = 0;
	bytes_in_input_buffer = 0;
	input_overrun = 0;
	do_echo = echo;
	
	// Configure serial port baud rate
	ubrr = ((SYSCLK / (8 * baudrate)) + 1)/2 - 1;
	UBRR0 = ubrr;
	
	// Enable transmission and receiving via UART
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	// Enable receive complete interrupt
	UCSR0B  |= (1 <<RXCIE0);
	stdout = &myStream;
	stdin = &myStream;
}

int8_t serial_input_available(void) {
	return (bytes_in_input_buffer != 0);
}

void clear_serial_input_buffer(void) {
	input_insert_pos = 0;
	bytes_in_input_buffer = 0;
}

static int uart_put_char(char c, FILE* stream) {
	uint8_t interrupts_enabled;
	
	if(c == '\n') {
		uart_put_char('\r', stream);
	}
	
	interrupts_enabled = bit_is_set(SREG, SREG_I);
	while(bytes_in_out_buffer >= OUTPUT_BUFFER_SIZE) {
		if(!interrupts_enabled) {
			return 1;
		}		
		// Else do nothing
	}
	
	cli();
	out_buffer[out_insert_pos++] = c;
	bytes_in_out_buffer++;
	if (out_insert_pos == OUTPUT_BUFFER_SIZE) {
		out_insert_pos = 0;
	}

	UCSR0B |= (1 << UDRIE0);
	if (interrupts_enabled) {
		sei();
	}
	
	return 0;
}

int uart_get_char(FILE* stream) {
	// Wait until we've received a character
	while(bytes_in_input_buffer == 0) {
		// Do nothing
	}
	
	uint8_t interrupts_enabled = bit_is_set(SREG, SREG_I);
	cli();
	char c;
	if (input_insert_pos - bytes_in_input_buffer < 0) {
		// Need to wrap around
		c = input_buffer[input_insert_pos - bytes_in_input_buffer + INPUT_BUFFER_SIZE];
	} else {
		c = input_buffer[input_insert_pos - bytes_in_input_buffer];
	}
	
	// Decrement our count of bytes in the input buffer
	bytes_in_input_buffer--;
	if (interrupts_enabled) {
		sei();
	}	
	
	return c;
}

// Define the interrupt handler for UART Data Register Empty
ISR(USART0_UDRE_vect) 
{
	if (bytes_in_out_buffer > 0) {
		char c;
		if (out_insert_pos - bytes_in_out_buffer < 0) {
			c = out_buffer[out_insert_pos - bytes_in_out_buffer + OUTPUT_BUFFER_SIZE];
		} else {
			c = out_buffer[out_insert_pos - bytes_in_out_buffer];
		}
		
		bytes_in_out_buffer--;
		UDR0 = c;
		
	} else {
		UCSR0B &= ~(1 << UDRIE0);
	}
}

ISR(USART0_RX_vect) 
{
	// Read the character - we ignore the possibility of overrun
	char c;
	c = UDR0;
		
	if (do_echo && bytes_in_out_buffer < OUTPUT_BUFFER_SIZE) {
		uart_put_char(c, 0);
	}
	
	
	if (bytes_in_input_buffer >= INPUT_BUFFER_SIZE) {
		input_overrun = 1;
	} else {
		if (c == '\r') {
			c = '\n';
		}
		
		input_buffer[input_insert_pos++] = c;
		bytes_in_input_buffer++;
		if (input_insert_pos == INPUT_BUFFER_SIZE) {
			input_insert_pos = 0; // Wrap around buffer pointer if necessary
		}
	}
}