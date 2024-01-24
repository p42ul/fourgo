#include "winner_lines.h"
#include <gb/metasprites.h>

const unsigned char winner_lines[] =
{
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
  0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
  0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
  0x01,0x01,0x02,0x02,0x04,0x04,0x08,0x08,
  0x10,0x10,0x20,0x20,0x40,0x40,0x80,0x80,
  0x80,0x80,0x40,0x40,0x20,0x20,0x10,0x10,
  0x08,0x08,0x04,0x04,0x02,0x02,0x01,0x01
};

const metasprite_t horiz_line_metasprite[] = {
    {.dy=-4, .dx=-8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
    {.dy=0, .dx=8, .dtile=1, .props=0},
	METASPR_TERM
};

const metasprite_t vert_line_metasprite[] = {
    {.dx=-4, .dy=-8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
    {.dx=0, .dy=8, .dtile=0, .props=0},
	METASPR_TERM
};

const metasprite_t diag_up_line_metasprite[] = {
    {.dx=-4, .dy=-8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
    {.dx=8, .dy=8, .dtile=3, .props=0},
	METASPR_TERM
};

const metasprite_t diag_down_line_metasprite[] = {
    {.dx=-4, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
    {.dx=8, .dy=-8, .dtile=2, .props=0},
	METASPR_TERM
};
