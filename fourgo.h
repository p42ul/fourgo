#ifndef _FOURGO_H
#define _FOURGO_H

void draw_board(void);
void init_board(void);
uint8_t make_move(uint8_t player, uint8_t column);
uint8_t check_win(uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2);
void clear_screen(void);
void move_selection(uint8_t selection);
void draw_move(uint8_t x, uint8_t y, uint8_t player);

#endif /* _FOURGO_H */
