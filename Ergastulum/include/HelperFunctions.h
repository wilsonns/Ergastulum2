#ifndef HELPER_H
#define HELPER_H

#include <algorithm>

inline float lerp(float begin, float end, float t)
{
	return begin + t * (end - begin);
}

inline float diagonalDistance(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	return std::max(abs(dx), abs(dy));
}



#endif
