#include "drawing.h"

#include <gb/gb.h>
#include <gb/metasprites.h>

#include "fourgo.h"
#include "board.h"

static uint8_t last_selected_column = DEFAULT_COLUMN;
static uint8_t selection_current_x = column_to_pixel(DEFAULT_COLUMN);
static uint8_t selection_move_tick_count = 0;

void board_to_bkg(uint8_t* row, uint8_t* col)
{
  *row = *row * puck_map_height + BKG_MARGIN;
  *col = *col * puck_map_width + BKG_MARGIN;
}

/* linear interpolation that resolves after
   SELECT_RESOLVE_TIME ticks */
uint8_t lerp(uint8_t start, uint8_t end)
{
  if (selection_move_tick_count > SELECT_RESOLVE_TIME)
    return end;
  return start + (selection_move_tick_count++ * (end - start)) / SELECT_RESOLVE_TIME;
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

void draw_selection(uint8_t column, uint8_t player)
{
  uint8_t base_tile, desired_x;
  if (column != last_selected_column)
  {
    selection_move_tick_count = 0;
    last_selected_column = column;
  }
  if (player == P1)
    base_tile = 0*puck_tiles_count;
  else
    base_tile = 1*puck_tiles_count;
  desired_x = lerp(selection_current_x, column_to_pixel(column));
  selection_current_x = desired_x;
  move_metasprite_ex(puck_metasprite, base_tile, 0, 0, desired_x, SELECT_Y);
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
