
#include "BulletObj.h"
BulletObj::BulletObj()
{
    m_Xval = 0;
    m_Yval = 0;
    m_Scope = 0;
    m_BLType = BL_NONE;
    m_BLDirType = BL_DIR_NONE;
    m_bMoving = true;
    m_plus_dis = 0;
}

BulletObj::BulletObj(int type, int dir_type, int x_speed, int y_speed, int scope)
{
    m_Xval = x_speed;
    m_Yval = y_speed;
    m_Scope = scope;
    m_BLType = type;
    m_BLDirType = dir_type;
    m_bMoving = true;
    m_plus_dis = 0;
}

BulletObj::~BulletObj()
{

}

bool BulletObj::Init(VT(std::string) path_list, int xp, int yp, SDL_Renderer* screen)
{
    bool bRet = false;
    for (size_t i = 0; i < path_list.size(); i++)
    {
        std::string path = path_list.at(i);
        bRet = LoadImg(path, screen, i);
    }
    m_Rect.x = xp;
    m_Rect.y = yp;
    return bRet;
}

void BulletObj::Update(const int& xScreen, const int& y_screen)
{
    if (m_Scope > 0)
    {
        if (m_BLDirType == BL_DIR_UP)
        {
            m_Rect.y -= m_Yval;
        }
        else if (m_BLDirType == BL_DIR_DOWN)
        {
            m_Rect.y += m_Yval;
        }

        m_plus_dis += m_Yval;
        if (m_plus_dis >= m_Scope)
        {
            m_bMoving = false;
        }
    }
    else
    {
        if (m_BLDirType == BL_DIR_UP)
        {
            m_Rect.y -= m_Yval;
            if (m_Rect.y < FRAME_HEIGHT)
            {
                m_bMoving = false;
            }
        }
        else if (m_BLDirType == BL_DIR_DOWN)
        {
            m_Rect.y += m_Yval;
            if (m_Rect.y > y_screen)
            {
                m_bMoving = false;
            }
        }
    }
}

void BulletObj::Show(SDL_Renderer* des)
{
    if (m_BLType == BL_CIRCLE)
    {
        m_textureIdx = 0;
    }
    else if (m_BLType == BL_LASER)
    {
        m_textureIdx = 1;
    }

    BaseObj::Render(des);
}