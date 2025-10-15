/*
 * terminalio.h
 * Created: 23/08/2025 6:03:28 PM
 * Author: leyla
 */ 
#ifndef TERMINAL_IO_H_
#define TERMINAL_IO_H_

#include <stdint.h>

// x (column number) and y (row number) are measured relative to the top left of the screen
// First column is 1; first row is 1
// The display parameter is a number between 0 and 47
typedef enum {
TERM_RESET = 0,
TERM_BRIGHT = 1,
TERM_DIM = 2,
TERM_UNDERSCORE = 4,
TERM_BLINK = 5,
TERM_REVERSE = 7,
TERM_HIDDEN = 8,
FG_BLACK = 30,
FG_RED = 31,
FG_GREEN = 32,
FG_YELLOW= 33,
FG_BLUE = 34,
FG_MAGENTA = 35,
FG_CYAN = 36,
FG_WHITE = 37,
BG_BLACK = 40,
BG_RED = 41,
BG_GREEN = 42,
BG_YELLOW = 43,
BG_BLUE = 44,
BG_MAGENTA = 45,
BG_CYAN = 46,
BG_WHITE = 47
} DisplayParameter;

void move_terminal_cursor(int x, int y);

void normal_display_mode(void);

void reverse_video(void);

void clear_terminal(void);

void clear_to_end_of_line(void);

void set_display_attribute(DisplayParameter parameter);

void hide_cursor(void);

void show_cursor(void);

void enable_scrolling_for_whole_display(void);

void set_scroll_region(int8_t y1, int8_t y2);

void scroll_down(void);

void scroll_up(void);

void draw_horizontal_line(int8_t y, int8_t startx, int8_t endx);

void draw_vertical_line(int8_t x, int8_t starty, int8_t endy);

#endif