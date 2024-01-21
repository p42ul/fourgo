#include "drawing.h"

#include <gb/gb.h>
#include <gb/metasprites.h>

#include "fourgo.h"
#include "board.h"

const metasprite_t player1_puck_metasprite[] = {
    {.dy=-8, .dx=-8, .dtile=0, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=8, .dx=-8, .dtile=2, .props=0},
    {.dy=0, .dx=8, .dtile=3, .props=0},
	METASPR_TERM
};

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
  set_sprite_data(0*puck_tiles_count, puck_tiles_count, puck_p1);
  set_sprite_data(1*puck_tiles_count, puck_tiles_count, puck_p2);
  init_bkg(0);
  SHOW_BKG;
  SHOW_SPRITES;
}

void draw_selection(uint8_t selected_column, uint8_t player)
{
  uint8_t base_tile;
  if (player == P1)
    base_tile = 0*puck_tiles_count;
  else
    base_tile = 1*puck_tiles_count;
  move_metasprite_ex(player1_puck_metasprite, base_tile, 0, 0, selected_column * 16 + 40, 32);
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
