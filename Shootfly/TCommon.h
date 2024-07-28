
#ifndef TCOMMON_H_
#define TCOMMON_H_
#include "define.h"

namespace TCommon
{
	bool CheckCollision(SDL_Rect rect1, SDL_Rect rect2);
	SDL_Point GetRandomPosSpace(int x1, int y1, int x2, int y2);
	int GetRandomValueSpace(int x1, int x2);
	SDL_Color GetBaseColor(int type);
};

#endif

