#ifndef FOURGO_DRAWING_H_
#define FOURGO_DRAWING_H_

#include <gb/gb.h>

#include "fourgo.h"
#include "board.h"
#include "sprites/puck_map.h"
#include "sprites/puck_tiles.h"

void board_to_bkg(uint8_t* row, uint8_t* col);
void init_drawing(void);
void draw_selection(uint8_t selected_column, uint8_t player);
void draw_puck(uint8_t row, uint8_t col, uint8_t tile_index);
void draw_board(Board* board);

#endif /* FOURGO_DRAWING_H_ */
