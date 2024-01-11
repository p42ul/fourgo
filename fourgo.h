#ifndef FOURGO_H_
#define FOURGO_H_

#include <gb/gb.h>

#define WIDTH 7
#define HEIGHT 6

#define TRUE 1
#define FALSE 0

#define PX 0
#define P1 1
#define P2 2

#define PX_COLOR BLACK
#define P1_COLOR LTGREY
#define P2_COLOR DKGREY

#define WIN_LENGTH 4

/* radius of the pucks, in pixels */
#define CIRCLE_RADIUS 6
#define SPACING 15
#define MARGIN 30

void select_column(uint8_t selection);

#endif /* _FOURGO_H_ */
