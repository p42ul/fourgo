#include "fourgo.h"

#include "drawing.h"
#include "board.h"

static int8_t selected_column = DEFAULT_COLUMN;
static uint8_t current_player = P1;

static uint8_t key_cur;
static uint8_t key_last;

static Board* board;

void select_column(uint8_t selection)
{
  selected_column = selection;
  if (selected_column >= BOARD_WIDTH)
    selected_column = BOARD_WIDTH - 1;
  if (selected_column < 0)
    selected_column = 0;
}

void inc_column(void)
{
  select_column(selected_column + 1);
}

void dec_column(void)
{
  select_column(selected_column - 1);
}

void try_make_move(void)
{
  if (make_move(board, current_player, selected_column))
  {
    if (current_player == P1)
      current_player = P2;
    else
      current_player = P1;
  }
}

void handle_key_debounce(uint8_t debounce_mask, void (*action)(void))
{
    if (key_cur & debounce_mask) {
        if (!(key_last & debounce_mask)) {
            action();
            key_last |= debounce_mask;
        }
    } else {
        key_last &= ~debounce_mask;
    }
}

void main(void)
{
  /* coordinates of winning move */
  uint8_t x1, y1, x2, y2;
  init_drawing();
  board = init_board();
  while(1)
  {
    vsync();
    draw_selection(selected_column, current_player);
    draw_board(board);
    key_cur = joypad();
    handle_key_debounce(J_LEFT, dec_column);
    handle_key_debounce(J_RIGHT, inc_column);
    handle_key_debounce(J_A, try_make_move);
    if (check_win(board, &x1, &y1, &x2, &y2))
        break;
  }
  draw_board(board);
  waitpad(J_START);
  reset();
}
