#include "fourgo.h"

#include "drawing.h"
#include "board.h"
#include "sound.h"

static int8_t selected_column = DEFAULT_COLUMN;
static Player current_player = P1;

static uint8_t key_cur;
static uint8_t key_last;

static uint8_t win_checked = TRUE;

static Board* board;

void select_column(uint8_t selection)
{
  selected_column = selection;
  if (selected_column >= BOARD_WIDTH)
    selected_column = BOARD_WIDTH - 1;
  else if (selected_column < 0)
    selected_column = 0;
  else
    play_move_sound(current_player);
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
  uint8_t row;
  if (is_valid_move(board, selected_column, &row))
  {
    play_drop_sound(current_player);
    while(!draw_move(selected_column, row, current_player))
      vsync();
    make_move(board, current_player, selected_column);
    win_checked = FALSE;
    swap_player();
  }
}

void swap_player(void)
{
    if (current_player == P1)
      current_player = P2;
    else
      current_player = P1;
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
  /* start and end coordinates of winning move */
  uint8_t x1, y1, x2, y2;
  init_sound();
  init_drawing();
  draw_board(board);
  board = init_board();
  while(1)
  {
    vsync();
    draw_selection(selected_column, current_player);
    key_cur = joypad();
    handle_key_debounce(J_LEFT, dec_column);
    handle_key_debounce(J_RIGHT, inc_column);
    handle_key_debounce(J_A, try_make_move);
    if (!win_checked)
    {
      draw_board(board);
      if (check_win(board, &x1, &y1, &x2, &y2) )
        break;
      else
        win_checked = TRUE;
    }
  }
  draw_board(board);
  hide_selection();
  swap_player(); /* needed because check_win swaps the player */
  draw_win(current_player, x1, y1, x2, y2);
  waitpad(J_START);
  reset();
}
