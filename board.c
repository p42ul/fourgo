#include "board.h"
#include "fourgo.h"

static uint8_t board[HEIGHT][WIDTH];

void init_board(void)
{
  uint8_t w, h;
  for (w = 0; w < WIDTH; w++)
    for (h = 0; h < HEIGHT; h++)
      board[h][w] = PX;
}

/* Check board for a win.
 * If a win is found, sets x1... to the coordinates
 * of the start and end of the winning move
 * and returns the winning player.
 * Otherwise, returns PX (0).
 */
uint8_t check_win(uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2)
{
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
uint8_t make_move(uint8_t player, uint8_t column, uint8_t* x, uint8_t* y)
{
  int16_t row = 0;
  while (board[row][column] == PX && row < HEIGHT)
    row++;
  row--;
  if (row >= 0)
  {
    board[row][column] = player;
    *x = column;
    *y = row;
    return TRUE;
  }
  return FALSE;
}
