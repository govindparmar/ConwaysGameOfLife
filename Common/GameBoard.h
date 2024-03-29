/** 
 * Definitions, macro functions, and structures common to both CGOL and BoardEditor for drawing the game board.
 */
#pragma once
#include <Windows.h>
#ifndef GRIDSIZE
#define GRIDSIZE 50
#endif
#ifndef CELLSIZE
#define CELLSIZE 13
#endif
#ifndef B4TODW_LE
#define B4TODW_LE(c0, c1, c2, c3) (DWORD) ((DWORD) (BYTE) (c0) | ((DWORD) (BYTE) (c1) << 8) | ((DWORD) (BYTE) (c2) << 16) | ((DWORD) (BYTE) (c3) << 24))
#endif
#pragma pack(push, 1)

#define LOW_ORDER_BIT_MASK 0xFFE00000
#define GGL_FILE_MAGIC MAKEWORD(0x07, 0x02)

typedef struct _BOARDFILEHEADER
{
	WORD wSig;     // 0x07 0x02 = 'G''B' (alphabetic) = Govind Board
	WORD wVersion; // This version 0x0001
	BYTE bGridSize; // Grid size
	DWORD wNumberCells; // Number of cells in the file
} BOARDFILEHEADER, *PBOARDFILEHEADER;

typedef struct _BOARDCOORDS
{
	BYTE bX;
	BYTE bY;
} BOARDCOORDS, *PBOARDCOORDS;
#pragma pack(pop)
