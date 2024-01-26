#include "board.h"
#include "fourgo.h"

static uint8_t _board[BOARD_HEIGHT][BOARD_WIDTH];

Board* init_board(void)
{
  uint8_t w, h;
  for (w = 0; w < BOARD_WIDTH; w++)
    for (h = 0; h < BOARD_HEIGHT; h++)
      _board[h][w] = PX;
  return _board;
}

/* Check board for a win.
 * If a win is found, sets x1... to the coordinates
 * of the start and end of the winning move
 * and returns the winning player.
 * Otherwise, returns PX (0).
 */
uint8_t check_win(Board* board, uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2)
{
  uint8_t w, h, p, i;
  for (p = P1; p <= P2; p++)
  {
    /* check vertical */
    for (w = 0; w < BOARD_WIDTH; w++)
      for (h = 0; h < BOARD_HEIGHT - WIN_LENGTH + 1; h++)
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
    for (h = 0; h < BOARD_HEIGHT; h++)
      for (w = 0; w < BOARD_WIDTH - WIN_LENGTH + 1; w++)
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
    for (w = 0; w < BOARD_WIDTH - WIN_LENGTH + 1; w++)
      for (h = BOARD_HEIGHT - WIN_LENGTH + 1; h < BOARD_HEIGHT; h++)
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
    for (w = 0; w < BOARD_WIDTH - WIN_LENGTH + 1; w++)
      for (h = 0; h < BOARD_HEIGHT - WIN_LENGTH + 1; h++)
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

uint8_t is_valid_move(Board* board, uint8_t column, uint8_t* row_out)
{
  int16_t row = 0;
  while (board[row][column] == PX && row < BOARD_HEIGHT)
    row++;
  row--;
  if (row >= 0)
  {
    *row_out = row;
    return TRUE;
  }
  return FALSE;
}

/*
 * Tries to make a move on the board.
 * If the move is invalid, returns FALSE.
 * Otherwise, returns TRUE.
 */
uint8_t make_move(Board* board, Player player, uint8_t column)
{
  int16_t row = 0;
  while (board[row][column] == PX && row < BOARD_HEIGHT)
    row++;
  row--;
  if (row >= 0)
  {
    board[row][column] = player;
    return TRUE;
  }
  return FALSE;
}
