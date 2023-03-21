#include "CGOL.h"

_Ret_range_(FALSE, TRUE)

BOOL WINAPI IsPointWithinRect(_In_ RECT rect, _In_ POINT p)
{
	return (((p.x >= rect.left) && (p.x <= rect.right)) && ((p.y >= rect.top) && (p.y <= rect.bottom)));
	//return IsWithinRect(rect, p.x, p.y);
}
