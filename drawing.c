#include "drawing.h"

#include "fourgo.h"
#include "board.h"

#include "gb/gb.h"

void board_to_bkg(uint8_t* row, uint8_t* col)
{
  *row *= 2;
  *col *= 2;
}

void init_drawing(void)
{
  set_bkg_data(0*puck_tiles_count, puck_tiles_count, puck_px);
  set_bkg_data(1*puck_tiles_count, puck_tiles_count, puck_p1);
  set_bkg_data(2*puck_tiles_count, puck_tiles_count, puck_p2);
  init_bkg(0);
  SHOW_BKG;
}

void draw_puck(uint8_t row, uint8_t col, uint8_t tile_index)
{
  board_to_bkg(&row, &col);
  set_bkg_based_tiles(col, row, puck_map_width, puck_map_height, puck_map, tile_index);
}

void draw_board(Board* board)
{
  set_bkg_based_tiles(0, 0, puck_map_width, puck_map_height, puck_map, 1);
  uint8_t row, col;
  uint8_t tile_index;
  for (col = 0; col < BOARD_WIDTH; col++)
  {
    for (row = 0; row < BOARD_HEIGHT; row++)
    {
      switch(board[row][col]) {
        case PX:
          tile_index = 0*puck_tiles_count;
        break;
        case P1:
          tile_index = 1*puck_tiles_count;
        break;
        case P2:
          tile_index = 2*puck_tiles_count;
        break;
      }
      draw_puck(row, col, tile_index);
    }
  }
}
