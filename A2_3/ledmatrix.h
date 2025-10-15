/*
 * ledmatrix.h
 * Created: 23/08/2025 8:39:34 PM
 * Author: leyla
 */

#ifndef LEDMATRIX_H_

#include <stdint.h>

#define LEDMATRIX_H_
#define MATRIX_NUM_COLUMNS 16
#define MATRIX_NUM_ROWS 8

// Each PixelType is an 8 bit number:
// 4 bits of green in the high bits
// 4 bits of red in the low bits
typedef uint8_t PixelColour;

// Colour Definitions
#define COLOUR_BLACK 0x00
#define COLOUR_RED 0x0F
#define COLOUR_GREEN 0xF0
#define COLOUR_YELLOW 0xDF
#define COLOUR_ORANGE 0x3C
#define COLOUR_LIGHT_ORANGE 0x13
#define COLOUR_LIGHT_YELLOW 0x35
#define COLOUR_LIGHT_GREEN 0x11
#define COLOUR_LIGHT_RED 0x01

typedef PixelColour MatrixData[MATRIX_NUM_COLUMNS][MATRIX_NUM_ROWS];
typedef PixelColour MatrixRow[MATRIX_NUM_COLUMNS];
typedef PixelColour MatrixColumn[MATRIX_NUM_ROWS];

void ledmatrix_setup(void);

void ledmatrix_update_all(MatrixData data);

void ledmatrix_update_pixel(uint8_t x, uint8_t y, PixelColour pixel);

void ledmatrix_update_row(uint8_t y, MatrixRow row);

void ledmatrix_update_column(uint8_t x, MatrixColumn col);

void ledmatrix_shift_display_left(void);

void ledmatrix_shift_display_right(void);

void ledmatrix_shift_display_up(void);

void ledmatrix_shift_display_down(void);

void ledmatrix_clear(void);

void copy_matrix_column(MatrixColumn from, MatrixColumn to);

void copy_matrix_row(MatrixRow from, MatrixRow to);

void set_matrix_column_to_colour(MatrixColumn matrix_column, PixelColour colour);

void set_matrix_row_to_colour(MatrixRow matrix_row, PixelColour colour);

#endif
