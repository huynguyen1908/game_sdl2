
#include "TCommon.h"

SDL_Color TCommon::GetBaseColor(int type)
{
    SDL_Color color;
    if (type == RED_COLOR)
    {
        color = { 255, 0, 0 };
    }
    else if (type == WHITE_COLOR)
    {
        color = { 255, 255, 255 };
    }
    else if (type == GREEN_COLOR)
    {
        color = { 0, 255, 0 };
    }
    else if (type == BLUE_COLOR)
    {
        color = { 0, 0, 255 };
    }
    else if (type == ORANGE_COLOR)
    {
        color = { 20, 200, 100 };
    }
    else if (type == GRAY_COLOR)
    {
        color = { 36, 36, 36 };
    }
    else
    {
        color = { 0, 0, 0 };
    }

    return color;
}

bool TCommon::CheckCollision(SDL_Rect rect1, SDL_Rect rect2)
{
    int left_a = rect1.x;
    int right_a = rect1.x + rect1.w;
    int top_a = rect1.y;
    int bottom_a = rect1.y + rect1.h;

    int left_b = rect2.x;
    int right_b = rect2.x + rect2.w;
    int top_b = rect2.y;
    int bottom_b = rect2.y + rect2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (top_a == top_b && bottom_a == bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (top_a == top_b && bottom_a == bottom_b)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

int TCommon::GetRandomValueSpace(int x1, int x2)
{
    int xMax = std::max(x1, x2);
    int xMin = std::min(x1, x2);
    int xRand = rand() % (xMax - xMin + 1) + xMin;

    return xRand;
}

SDL_Point TCommon::GetRandomPosSpace(int x1, int y1, int x2, int y2)
{
    int yMax = std::max(y1, y2);
    int yMin = std::min(y1, y2);

    int xMax = std::max(x1, x2);
    int xMin = std::min(x1, x2);

    int xRand = rand() % (xMax - xMin + 1) + xMin;
    int yRand = rand() % (yMax - yMin + 1) + yMin;

    SDL_Point pt = { xRand, yRand };

    return pt;
}