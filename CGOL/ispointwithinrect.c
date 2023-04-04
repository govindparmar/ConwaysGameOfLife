#include "CGOL.h"

// Similar to "IsWithinRect", except rather than taking (x, y) coordinates it takes a `POINT p` and uses p.x and p.y

_Ret_range_(FALSE, TRUE)

BOOL WINAPI IsPointWithinRect(_In_ RECT rect, _In_ POINT p)
{
	return (((p.x >= rect.left) && (p.x <= rect.right)) && ((p.y >= rect.top) && (p.y <= rect.bottom)));
}
