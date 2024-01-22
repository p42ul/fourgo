#ifndef FOURGO_DRAWING_H_
#define FOURGO_DRAWING_H_

#include <gb/gb.h>

#include "fourgo.h"
#include "board.h"
#include "sprites/puck_map.h"
#include "sprites/puck_tiles.h"

/* for a 7x6 board, this finds the upper-left pixel of
   the current selection, given a column number */
#define column_to_pixel( col_ ) (col_ * 16 + 40)
#define row_to_pixel( row_ ) (row_ * 16 + 48)

#define SELECT_RESOLVE_TIME 5
#define SELECT_Y 32

/* 3 bkg tiles of 8x8 pixels turns out to be the perfect margin
   for a 7x6 grid */
#define BKG_MARGIN 3

void board_to_bkg(uint8_t* row, uint8_t* col);
void init_drawing(void);
void draw_selection(uint8_t column, uint8_t player);
void draw_puck(uint8_t row, uint8_t col, uint8_t tile_index);
void draw_board(Board* board);
uint8_t lerp(uint8_t start, uint8_t end);
uint8_t draw_move(uint8_t col, uint8_t row, uint8_t player);
uint8_t get_base_tile(uint8_t player);

#endif /* FOURGO_DRAWING_H_ */
