#ifndef FOURGO_DRAWING_H_
#define FOURGO_DRAWING_H_

#include "fourgo.h"

void draw_board(void);
void erase_selection(uint8_t column);
void draw_selection(uint8_t column, uint8_t player);
void draw_move(uint8_t x, uint8_t y, uint8_t player);

#endif /* FOURGO_DRAWING_H_ */
