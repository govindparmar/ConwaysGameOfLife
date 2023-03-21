#include "BE.h"

/* Deprecated, from an earlier prototype of the file format where the entire grid was packed into a bit matrix

SIZE_T WINAPI GetTotalBytesNeeded()
{
	return (SIZE_T) (((GRIDSIZE / CHAR_BIT) + 1) * 2);

	// FMT: Hdr (incl. GRIDSIZE), # of cells following, x,y coords of cells
}
*/