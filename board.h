#ifndef FOURGO_BOARD_H_
#define FOURGO_BOARD_H_

#include "fourgo.h"

typedef uint8_t Board[BOARD_WIDTH];

Board* init_board(void);
uint8_t check_win(Board* board, uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2);
uint8_t is_valid_move(Board* board, uint8_t column, uint8_t* row_out);
uint8_t make_move(Board* board, Player player, uint8_t column);

#endif /* FOURGO_BOARD_H_ */
