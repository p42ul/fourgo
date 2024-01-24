#ifndef FOURGO_WINNER_LINES_H
#define FOURGO_WINNER_LINES_H

#include <gb/metasprites.h>

#define winner_lines_count 4

#define winner_lines_metasprite_size 8

extern const unsigned char winner_lines[];

extern const metasprite_t horiz_line_metasprite[];
extern const metasprite_t vert_line_metasprite[];
extern const metasprite_t diag_up_line_metasprite[];
extern const metasprite_t diag_down_line_metasprite[];

#endif
