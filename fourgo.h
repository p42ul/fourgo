#ifndef FOURGO_H_
#define FOURGO_H_

#include <gb/gb.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6

#define DEFAULT_COLUMN 3

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
void play_sound(void);
void init_sound(void);

#endif /* _FOURGO_H_ */
