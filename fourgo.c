#include <gb/gb.h>
#include <gb/drawing.h>

#include "fourgo.h"

#define WIDTH 7
#define HEIGHT 6

#define TRUE 1
#define FALSE 0

#define PX 0
#define P1 1
#define P2 2

#define PX_COLOR BLACK
#define P1_COLOR LTGREY
#define P2_COLOR DKGREY

#define WIN_LENGTH 4

/* radius of the pucks, in pixels */
#define CIRCLE_RADIUS 6
#define HORIZ_SPACING 15
#define VERT_SPACING 15
#define MARGIN 30


static uint8_t board[HEIGHT][WIDTH];
static int8_t selected_column = 0;
static uint8_t current_player = P1;


void init_board(void)
{
  uint8_t w, h;
  for (w = 0; w < WIDTH; w++)
    for (h = 0; h < HEIGHT; h++)
      board[h][w] = PX;
}

void clear_screen(void)
{
  color(WHITE, WHITE, SOLID);
  box(0, 0, GRAPHICS_WIDTH-1, GRAPHICS_HEIGHT-1, M_FILL);
}

void draw_board(void)
{
  uint8_t x, y;
  color(BLACK, BLACK, SOLID);
  for (x = 0; x < WIDTH; x++)
  {
    for (y = 0; y < HEIGHT; y++)
    {
      circle(CIRCLE_RADIUS + MARGIN + HORIZ_SPACING*x,
          CIRCLE_RADIUS + MARGIN + VERT_SPACING*y,
          CIRCLE_RADIUS, M_NOFILL);
    }
  }
}

void draw_move(uint8_t x, uint8_t y, uint8_t player)
{
  if (player == P1)
    color(P1_COLOR, P1_COLOR, SOLID);
  else
    color(P2_COLOR, P2_COLOR, SOLID);
  circle(CIRCLE_RADIUS + MARGIN + HORIZ_SPACING*x,
      CIRCLE_RADIUS + MARGIN + VERT_SPACING*y,
      CIRCLE_RADIUS, M_FILL);
}


void move_selection(uint8_t selection)
{
  color(WHITE, WHITE, SOLID);
  circle(CIRCLE_RADIUS + MARGIN + HORIZ_SPACING*selected_column,
      CIRCLE_RADIUS + MARGIN - VERT_SPACING,
      CIRCLE_RADIUS,
      M_FILL);
  selected_column = selection;
  if (selected_column >= WIDTH)
    selected_column = WIDTH - 1;
  if (selected_column < 0)
    selected_column = 0;
  if (current_player == P1)
    color(P1_COLOR, P1_COLOR, SOLID);
  else
    color(P2_COLOR, P2_COLOR, SOLID);
  circle(CIRCLE_RADIUS + MARGIN + HORIZ_SPACING*selected_column,
      CIRCLE_RADIUS + MARGIN - VERT_SPACING,
      CIRCLE_RADIUS,
      M_FILL);

}

uint8_t check_win(uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2)
{
  /* check vertical
   * check horizontal
   * check diagonal
   */
  uint8_t w, h, p, i;
  for (p = P1; p <= P2; p++)
  {
    /* check vertical */
    for (w = 0; w < WIDTH; w++)
      for (h = 0; h < HEIGHT - WIN_LENGTH + 1; h++)
      {
        for (i = 0; i < WIN_LENGTH; i++)
          if (board[h+i][w] != p)
            break;
        if (i == WIN_LENGTH)
        {
          *x1 = w;
          *x2 = w;
          *y1 = h;
          *y2 = h+i-1;
          return p;
        }
      }
    /* check horizontal */
    for (h = 0; h < HEIGHT; h++)
      for (w = 0; w < WIDTH - WIN_LENGTH + 1; w++)
      {
        for (i = 0; i < WIN_LENGTH; i++)
          if (board[h][w+i] != p)
            break;
        if (i == WIN_LENGTH)
        {
          *y1 = h;
          *y2 = h;
          *x1 = w;
          *x2 = w+i-1;
          return p;
        }
      }
    /* check up-right diagonal / */
    for (w = 0; w < WIDTH - WIN_LENGTH + 1; w++)
      for (h = HEIGHT - WIN_LENGTH + 1; h < HEIGHT; h++)
      {
        for (i = 0; i < WIN_LENGTH; i++)
          if (board[h-i][w+i] != p)
            break;
        if (i == WIN_LENGTH)
        {
          *x1 = w;
          *y1 = h;
          *x2 = w+i-1;
          *y2 = h-i+1;
          return p;
        }
      }
    /* check down-right diagonal \ */
    for (w = 0; w < WIDTH - WIN_LENGTH + 1; w++)
      for (h = 0; h < HEIGHT - WIN_LENGTH + 1; h++)
      {
        for (i = 0; i < WIN_LENGTH; i++)
          if (board[h+i][w+i] != p)
            break;
        if (i == WIN_LENGTH)
        {
          *x1 = w;
          *y1 = h;
          *x2 = w+i-1;
          *y2 = h+i-1;
          return p;
        }
      }

  }
  return PX;
}

/*
 * Tries to make a move on the board.
 * If the move is invalid, returns FALSE.
 * Otherwise, returns TRUE.
 */
uint8_t make_move(uint8_t player, uint8_t column)
{
  int16_t row = 0;
  while (board[row][column] == PX && row < HEIGHT)
    row++;
  row--;
  if (row >= 0)
  {
    board[row][column] = player;
    draw_move(column, row, player);
    return TRUE;
  }
  return FALSE;
}


void main(void)
{
  uint8_t key, last = 0;
  uint8_t x1, y1, x2, y2;
  init_board();
  draw_board();
  move_selection(selected_column);
  while(1)
  {
    vsync();
    key = joypad();
    if(key & J_LEFT)
    {
      if (!(last & J_LEFT))
      {
        move_selection(selected_column - 1);
        last |= J_LEFT;
      }
    } else {
      last &= ~J_LEFT;
    }
    if(key & J_RIGHT)
    {
      if (!(last & J_RIGHT))
      {
        move_selection(selected_column + 1);
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
        if (make_move(current_player, selected_column))
        {
          if (check_win(&x1, &y1, &x2, &y2))
              break;
          if (current_player == P1)
            current_player = P2;
          else
            current_player = P1;
          move_selection(selected_column);
        }
      }
    } else {
      last &= ~J_DOWN;
    }
  }
  /* winner found */
  color(BLACK, BLACK, XOR);
  for (key = 0; key < 8; key++)
  {
    line(CIRCLE_RADIUS + MARGIN + HORIZ_SPACING*x1,
         CIRCLE_RADIUS + MARGIN + VERT_SPACING *y1,
         CIRCLE_RADIUS + MARGIN + HORIZ_SPACING*x2,
         CIRCLE_RADIUS + MARGIN + VERT_SPACING *y2);
    delay(300);
  }
  reset();
}
