#include "BE.h"

SIZE_T WINAPI GetTotalBytesNeeded()
{
	return (SIZE_T) (((GRIDSIZE / CHAR_BIT) + 1) * 2);

	// FMT: Hdr (incl. GRIDSIZE), # of cells following, x,y coords of cells
}
