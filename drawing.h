#ifndef FOURGO_DRAWING_H_
#define FOURGO_DRAWING_H_

#include <gb/gb.h>

#include "fourgo.h"
#include "board.h"
#include "sprites/puck_map.h"
#include "sprites/puck_tiles.h"

void draw_board(Board* board);
void init_drawing(void);

#endif /* FOURGO_DRAWING_H_ */
