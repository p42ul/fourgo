#include "fourgo.h"

#include <gb/drawing.h>
#include "drawing.h"
#include "board.h"

static int8_t selected_column = 0;
static uint8_t current_player = P1;

void select_column(uint8_t selection)
{
  erase_selection(selected_column);

  selected_column = selection;
  if (selected_column >= WIDTH)
    selected_column = WIDTH - 1;
  if (selected_column < 0)
    selected_column = 0;

  draw_selection(selected_column, current_player);
}

void main(void)
{
  uint8_t key, last = 0;
  uint8_t row, column;
  uint8_t x1, y1, x2, y2;
  Board* board;
  board = init_board();
  draw_board();
  select_column(selected_column);
  while(1)
  {
    vsync();
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
    if (key & J_DOWN)
    {
      if (!(last & J_DOWN))
      {
        last |= J_DOWN;
        if (make_move(board, current_player, selected_column, &column, &row))
        {
          draw_move(column, row, current_player);
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
      last &= ~J_DOWN;
    }
  }
  /* winner found */
  color(BLACK, BLACK, XOR);
  for (key = 0; key < 9; key++)
  {
    line(CIRCLE_RADIUS + MARGIN + SPACING*x1,
         CIRCLE_RADIUS + MARGIN + SPACING*y1,
         CIRCLE_RADIUS + MARGIN + SPACING*x2,
         CIRCLE_RADIUS + MARGIN + SPACING*y2);
    delay(300);
  }
  waitpad(J_START);
  reset();
}
