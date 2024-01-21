#ifndef FOURGO_H_
#define FOURGO_H_

#include <gb/gb.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
/* 3 bkg tiles of 8x8 pixels turns out to be the perfect margin
   for a 7x6 grid */
#define BKG_MARGIN 3

#define TRUE 1
#define FALSE 0

#define PX 0
#define P1 1
#define P2 2

#define WIN_LENGTH 4

void select_column(uint8_t selection);
void handle_key_debounce(uint8_t debounce_mask, void (*action)(void));
void inc_column(void);
void dec_column(void);
void try_make_move(void);

#endif /* _FOURGO_H_ */
