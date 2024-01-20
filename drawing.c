#include "drawing.h"

#include "fourgo.h"
#include "board.h"

#include "gb/gb.h"

void board_to_bkg(uint8_t* row, uint8_t* col)
{
  *row = *row * puck_map_height + BKG_MARGIN;
  *col = *col * puck_map_width + BKG_MARGIN;
}

void init_drawing(void)
{
  set_bkg_data(0*puck_tiles_count, puck_tiles_count, puck_px);
  set_bkg_data(1*puck_tiles_count, puck_tiles_count, puck_p1);
  set_bkg_data(2*puck_tiles_count, puck_tiles_count, puck_p2);
  init_bkg(0);
  SHOW_BKG;
}

void draw_selection(uint8_t selected_column, uint8_t player)
{
  uint8_t row = 0, col, row_bkg, col_bkg, tile_index;
  for (col = 0; col < BOARD_WIDTH; col++)
  {
    tile_index = 0;
    if (col == selected_column)
      tile_index = player * puck_map_tiles;
    col_bkg = col;
    row_bkg = row;
    board_to_bkg(&row_bkg, &col_bkg);
    row_bkg -= puck_map_height;
    set_bkg_based_tiles(col_bkg, row_bkg, puck_map_width, puck_map_height, puck_map, tile_index);
  }
}


void draw_puck(uint8_t row, uint8_t col, uint8_t tile_index)
{
  board_to_bkg(&row, &col);
  set_bkg_based_tiles(col, row, puck_map_width, puck_map_height, puck_map, tile_index);
}

void draw_board(Board* board)
{
  uint8_t row, col;
  uint8_t tile_index = 0;
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
