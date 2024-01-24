#include "drawing.h"

#include <gb/gb.h>
#include <gb/metasprites.h>

#include "fourgo.h"
#include "board.h"
#include "sprites/puck.h"
#include "sprites/winner_lines.h"

static uint8_t last_selected_column = DEFAULT_COLUMN;
static uint8_t selection_current_x = column_to_pixel(DEFAULT_COLUMN);
static uint8_t selection_current_y = SELECT_Y;
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
  if (selection_move_tick_count >= SELECT_RESOLVE_TIME)
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
  set_sprite_data(2*puck_tiles_count, winner_lines_count, winner_lines);
  init_bkg(0);
  SHOW_BKG;
  SHOW_SPRITES;
}

uint8_t get_base_tile(uint8_t player)
{
  if (player == P1)
    return 0*puck_tiles_count;
  else
    return 1*puck_tiles_count;
}

void draw_selection(uint8_t column, uint8_t player)
{
  uint8_t base_tile, next_x;
  if (column != last_selected_column)
  {
    selection_move_tick_count = 0;
    last_selected_column = column;
  }
  base_tile = get_base_tile(player);
  next_x = lerp(selection_current_x, column_to_pixel(column));
  selection_current_x = next_x;
  move_metasprite_ex(puck_metasprite, base_tile, 0, 0, next_x, SELECT_Y);
}

void hide_selection(void)
{
  hide_metasprite(puck_metasprite, 0);
}

void draw_win_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  const metasprite_t* ms;
  if (y1 == y2)
    ms = horiz_line_metasprite;
  else if (x1 == x2)
    ms = vert_line_metasprite;
  else if (y1 < y2) /* board and pixels use different coordinate systems */
    ms = diag_up_line_metasprite;
  else
    ms = diag_down_line_metasprite;
  x1 = column_to_pixel(x1);
  x2 = column_to_pixel(x2);
  y1 = row_to_pixel(y1);
  y2 = row_to_pixel(y2);
  move_metasprite_ex(ms, 2*puck_tiles_count, 0, puck_tiles_count, x1, y1);
}

uint8_t draw_move(uint8_t col, uint8_t row, uint8_t player)
{
  uint8_t base_tile, x, y;
  base_tile = get_base_tile(player);
  x = column_to_pixel(col);
  y = row_to_pixel(row);
  if (selection_current_y >= y)
  {
    selection_current_y = SELECT_Y;
    return TRUE;
  }
  selection_current_y += 4;
  move_metasprite_ex(puck_metasprite, base_tile, 0, 0, x, selection_current_y);
  return FALSE;
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
