/*
 * spi.h
 * Created: 23/08/2025 8:40:20 PM
 * Author: leyla
 */

 #ifndef SPI_H_
 #define SPI_H_
 
 uint8_t spi_send_byte(uint8_t byte);

 void spi_setup_master(uint8_t clockdivider);

 #endif
