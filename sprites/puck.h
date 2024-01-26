#ifndef FOURGO_PUCK_H_
#define FOURGO_PUCK_H_

#include <gb/metasprites.h>

#define puck_tiles_count 4

#define puck_map_width 2
#define puck_map_height 2

extern metasprite_t puck_metasprite[];
extern char puck_map[];
extern const unsigned char puck_p1_data[];
extern const unsigned char puck_p2_data[];
extern const unsigned char puck_px_data[];
extern const unsigned char puck_p1_win_data[];
extern const unsigned char puck_p2_win_data[];

#endif
