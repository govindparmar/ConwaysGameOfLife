#pragma once
#include <stdint.h>
#ifndef GRIDSIZE
#define GRIDSIZE 48
#endif
#ifndef CELLSIZE
#define CELLSIZE 12
#endif
#pragma pack(push, 1)
typedef struct
{
	uint16_t wSig;     // 0x07 0x02 = Govind Board
	uint16_t wVersion; // This version 0x0001
	uint8_t bGridSize; // Grid size
} BOARDFILEHEADER, *PBOARDFILEHEADER;
#pragma pack(pop)