/** 
 * Definitions, macro functions, and structures common to both CGOL and BoardEditor for drawing the game board.
 */
#pragma once
#include <stdint.h>
#ifndef GRIDSIZE
#define GRIDSIZE 50
#endif
#ifndef CELLSIZE
#define CELLSIZE 13
#endif
#ifndef B4TODW_LE
#define B4TODW_LE(c0, c1, c2, c3) (uint32_t) ((uint32_t) (uint8_t) (c0) | ((uint32_t) (uint8_t) (c1) << 8) | ((uint32_t) (uint8_t) (c2) << 16) | ((uint32_t) (uint8_t) (c3) << 24))
#endif
#pragma pack(push, 1)
typedef struct
{
	uint16_t wSig;     // 0x07 0x02 = 'G''B' (alphabetic) = Govind Board
	uint16_t wVersion; // This version 0x0001
	uint8_t bGridSize; // Grid size
	uint32_t wNumberCells; // Number of cells in the file
} BOARDFILEHEADER, *PBOARDFILEHEADER;

typedef struct
{
	uint8_t bX;
	uint8_t bY;
} BOARDCOORDS, *PBOARDCOORDS;
#pragma pack(pop)
