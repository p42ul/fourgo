#include "fourgo.h"

#include "drawing.h"
#include "board.h"

static int8_t selected_column = 0;
static uint8_t current_player = P1;

void select_column(uint8_t selection)
{
  selected_column = selection;
  if (selected_column >= BOARD_WIDTH)
    selected_column = BOARD_WIDTH - 1;
  if (selected_column < 0)
    selected_column = 0;
}

void main(void)
{
  uint8_t key, last = 0;
  uint8_t row, column;
  uint8_t x1, y1, x2, y2;
  init_drawing();
  Board* board;
  board = init_board();
  while(1)
  {
    vsync();
    draw_board(board);
    key = joypad();
    if(key & J_LEFT)
    {
      if (!(last & J_LEFT))
      {
        select_column(selected_column - 1);
        last |= J_LEFT;
      }
    } else {
      last &= ~J_LEFT;
    }
    if(key & J_RIGHT)
    {
      if (!(last & J_RIGHT))
      {
        select_column(selected_column + 1);
        last |= J_RIGHT;
      }
    } else {
      last &= ~J_RIGHT;
    }
    if (key & J_A)
    {
      if (!(last & J_A))
      {
        last |= J_A;
        if (make_move(board, current_player, selected_column, &column, &row))
        {
          if (check_win(board, &x1, &y1, &x2, &y2))
              break;
          if (current_player == P1)
            current_player = P2;
          else
            current_player = P1;
          select_column(selected_column);
        }
      }
    } else {
      last &= ~J_A;
    }
  }
  reset();
}
