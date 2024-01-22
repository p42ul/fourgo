#ifndef FOURGO_DRAWING_H_
#define FOURGO_DRAWING_H_

#include <gb/gb.h>

#include "fourgo.h"
#include "board.h"
#include "sprites/puck_map.h"
#include "sprites/puck_tiles.h"

/* for a 7x6 board, this finds the upper-left pixel of
   the current selection, given a column number */
#define column_to_pixel( col ) (col * 16 + 40)

#define SELECT_RESOLVE_TIME 5
#define SELECT_Y 32

void board_to_bkg(uint8_t* row, uint8_t* col);
void init_drawing(void);
void draw_selection(uint8_t column, uint8_t player);
void draw_puck(uint8_t row, uint8_t col, uint8_t tile_index);
void draw_board(Board* board);
uint8_t lerp(uint8_t start, uint8_t end);

#endif /* FOURGO_DRAWING_H_ */
