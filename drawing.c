#include "drawing.h"

#include <gb/drawing.h>


void draw_board(void)
{
  uint8_t x, y;
  color(BLACK, BLACK, SOLID);
  for (x = 0; x < WIDTH; x++)
  {
    for (y = 0; y < HEIGHT; y++)
    {
      circle(CIRCLE_RADIUS + MARGIN + SPACING*x,
          CIRCLE_RADIUS + MARGIN + SPACING*y,
          CIRCLE_RADIUS, M_NOFILL);
    }
  }
}

void erase_selection(uint8_t column)
{
  color(WHITE, WHITE, SOLID);
  circle(CIRCLE_RADIUS + MARGIN + SPACING*column,
      CIRCLE_RADIUS + MARGIN - SPACING,
      CIRCLE_RADIUS,
      M_FILL);
}

void draw_selection(uint8_t column, uint8_t player)
{
  if (player == P1)
    color(P1_COLOR, P1_COLOR, SOLID);
  else
    color(P2_COLOR, P2_COLOR, SOLID);
  circle(CIRCLE_RADIUS + MARGIN + SPACING*column,
      CIRCLE_RADIUS + MARGIN - SPACING,
      CIRCLE_RADIUS,
      M_FILL);
}


void draw_move(uint8_t x, uint8_t y, uint8_t player)
{
  if (player == P1)
    color(P1_COLOR, P1_COLOR, SOLID);
  else
    color(P2_COLOR, P2_COLOR, SOLID);
  circle(CIRCLE_RADIUS + MARGIN + SPACING*x,
      CIRCLE_RADIUS + MARGIN + SPACING*y,
      CIRCLE_RADIUS, M_FILL);
}
