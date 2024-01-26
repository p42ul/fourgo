#include "drawing.h"

#include <gb/gb.h>
#include <gb/metasprites.h>

#include "fourgo.h"
#include "board.h"
#include "sprites/puck.h"

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
  set_bkg_data(0*puck_tiles_count, puck_tiles_count, puck_px_data);
  set_bkg_data(1*puck_tiles_count, puck_tiles_count, puck_p1_data);
  set_bkg_data(2*puck_tiles_count, puck_tiles_count, puck_p2_data);
  set_bkg_data(3*puck_tiles_count, puck_tiles_count, puck_p1_win_data);
  set_bkg_data(4*puck_tiles_count, puck_tiles_count, puck_p2_win_data);
  set_sprite_data(0*puck_tiles_count, puck_tiles_count, puck_p1_data);
  set_sprite_data(1*puck_tiles_count, puck_tiles_count, puck_p2_data);
  init_bkg(0);
  SHOW_BKG;
  SHOW_SPRITES;
}

uint8_t get_puck_bkg_base_tile(Player player)
{
  switch (player) {
    case PX:
      return 0*puck_tiles_count;
    case P1:
      return 1*puck_tiles_count;
    case P2:
      return 2*puck_tiles_count;
    default:
      return 0;
  }
}

uint8_t get_puck_spr_base_tile(Player player)
{
  switch (player) {
    case P1:
      return 0*puck_tiles_count;
    case P2:
      return 1*puck_tiles_count;
    default:
      return 0;
  }
}

uint8_t get_puck_win_bkg_base_tile(Player player)
{
  switch (player) {
    case P1:
      return 3*puck_tiles_count;
    case P2:
      return 4*puck_tiles_count;
    default:
      return 0;
  }
}

void draw_selection(uint8_t column, Player player)
{
  uint8_t base_tile, next_x;
  if (column != last_selected_column)
  {
    selection_move_tick_count = 0;
    last_selected_column = column;
  }
  base_tile = get_puck_spr_base_tile(player);
  next_x = lerp(selection_current_x, column_to_pixel(column));
  selection_current_x = next_x;
  move_metasprite_ex(puck_metasprite, base_tile, 0, 0, next_x, SELECT_Y);
}

void hide_selection(void)
{
  hide_metasprite(puck_metasprite, 0);
}

void draw_win(Player player, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  int row, col, i;
  uint8_t base_tile = get_puck_win_bkg_base_tile(player);
  /* vertical win */
  if (x1 == x2)
  {
    for (row = y1; row <= y2; row++)
      draw_puck(row, x1, base_tile);
  }
  /* horizontal win */
  else if (y1 == y2)
  {
    for (col = x1; col <= x2; col++)
      draw_puck(y1, col, base_tile);
  }
  /* diagonal, going up-right */
  else if (y2 < y1)
  {
    col = x1;
    row = y1;
    for (i = 0; i < WIN_LENGTH; i++)
      draw_puck(row--, col++, base_tile);
  }
  /* diagonal, going down-right */
  else
  {
    col = x1;
    row = y1;
    for (i = 0; i < WIN_LENGTH; i++)
      draw_puck(row++, col++, base_tile);
  }
}

uint8_t draw_move(uint8_t col, uint8_t row, Player player)
{
  uint8_t base_tile, x, y;
  base_tile = get_puck_spr_base_tile(player);
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

void draw_puck(uint8_t row, uint8_t col, uint8_t base_tile)
{
  board_to_bkg(&row, &col);
  set_bkg_based_tiles(col, row, puck_map_width, puck_map_height, puck_map, base_tile);
}

void draw_board(Board* board)
{
  uint8_t row, col;
  uint8_t tile_index = 0;
  for (col = 0; col < BOARD_WIDTH; col++)
  {
    for (row = 0; row < BOARD_HEIGHT; row++)
    {
      tile_index = get_puck_bkg_base_tile(board[row][col]);
      draw_puck(row, col, tile_index);
    }
  }
}
