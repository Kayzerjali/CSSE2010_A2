/*
 * serialio.h
 * Created: 23/08/2025 6:01:18 PM
 * Author: leyla
 */

#ifndef SERIALIO_H_
#define SERIALIO_H_
#include <stdint.h>

// Initialise serial IO using the UART
void init_serial_stdio(long baudrate, int8_t echo);

// Test if input is available from the serial port
// Return 0 if not, non-zero otherwise 
// If there is input available then it can be read with fgetc()
int8_t serial_input_available(void);

// Discard any input waiting to be read from the serial port
void clear_serial_input_buffer(void);

#endif
