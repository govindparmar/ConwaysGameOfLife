#include "CGOL.h"

// Convenient helper method to determine if a point falls within the boundaries of a certain RECT

_Ret_range_(FALSE, TRUE)

BOOL WINAPI IsWithinRect(_In_ RECT rect, _In_ INT x, _In_ INT y)
{
	return (((x >= rect.left) && (x <= rect.right)) && ((y >= rect.top) && (y <= rect.bottom)));
}
