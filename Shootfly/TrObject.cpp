
#include "TrObject.h"

TrObject::TrObject()
{
    m_FrameIdx = 0;
    m_FrameHeight = 0;
    m_FrameWidth = 0;
    m_Visible = true;
    m_IsDie = false;
    m_xVal = 0;
    m_yVal = 0;
    m_TimeWait = 0;
    m_FrameNum = 4;

    m_Type = TOBJ_STATIC;
    m_Speed = 5;
    InitFrame();

    m_GetBullet = 0;
}

TrObject::TrObject(int mov_type, SDL_Point p1, SDL_Point p2)
{
    m_FrameIdx = 0;
    m_FrameHeight = 0;
    m_FrameWidth = 0;
    m_Visible = true;
    m_IsDie = false;
    m_xVal = 0;
    m_yVal = 0;
    m_TimeWait = 0;
    m_FrameNum = 4;

    m_Type = mov_type;
    m_Pt1.x = p1.x;
    m_Pt1.y = p1.y;

    m_Pt2.x = p2.x;
    m_Pt2.y = p2.y;

    m_Speed = 5;
    InitFrame();

    m_GetBullet = 0;
}

TrObject::~TrObject()
{

}

void TrObject::SetXVal(int xval)
{
    m_xVal = xval;
}

void TrObject::SetYval(int yval)
{
    m_yVal = yval;
}

int TrObject::GetXVal()const
{
    return m_xVal;
}

int TrObject::GetYVal()const
{
    return m_yVal;
}

bool TrObject::Init(VT(std::string) path_list, int frame_num, SDL_Point pos, SDL_Renderer* screen)
{
    if (frame_num <= 0)
        return false;
    if (path_list.size() == 0)
        return false;
    if (m_Type == TOBJ_MOV_END)
    {
        InitRandomPos();
    }
    else
    {
        m_Rect.x = pos.x;
        m_Rect.y = pos.y;
    }
    m_FrameNum = frame_num;

    bool ret = LoadImg(path_list, screen);
    if (ret == false)
        return false;

    InitFrame();
    MakeClip();

    if (m_Type != TOBJ_MOV_END)
    {
        AddBullet(screen);
    }

    return true;
}

void TrObject::InitRandomPos()
{
    int x1 = 150, x2 = TCommon::GetRandomValueSpace(300, 600);
    int y1 = 0, y2 = TCommon::GetRandomValueSpace(300, 600);

    SDL_Point pt = TCommon::GetRandomPosSpace(x1, y1, x2, y2);

    int xPos = pt.x;
    int yPos = -1 * pt.y;

    m_Rect.x = xPos;
    m_Rect.y = yPos;

    m_Visible = false;
}

void TrObject::SetFrameNum(int num)
{
    m_FrameNum = num;
    InitFrame();
}

void TrObject::InitFrame()
{
    m_PassedTime = 0;
    if (m_FramesData.empty() == false)
    {
        m_FramesData.clear();
    }

    for (int i = 0; i < m_FrameNum; i++)
    {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
        m_FramesData.push_back(rect);

        int dLay = 100;
        m_FrameDelay.push_back(dLay);
    }
}

void TrObject::MakeClip()
{
    if (m_FrameWidth > 0 && m_FrameHeight > 0)
    {
        for (int i = 0; i < m_FrameNum; i++)
        {
            m_FramesData[i].x = m_FrameWidth * i;
            m_FramesData[i].y = 0;
            m_FramesData[i].w = m_FrameWidth;
            m_FramesData[i].h = m_FrameHeight;
        }
    }
}


bool TrObject::LoadImg(VT(std::string) path_list, SDL_Renderer* screen)
{
    bool ret = false;
    for (size_t i = 0; i < path_list.size(); i++)
    {
        ret = BaseObj::LoadImg(path_list.at(i), screen, i);
        if (i == 0 && ret == true && m_FrameNum > 0)
        {
            m_FrameWidth = m_Rect.w / m_FrameNum;
            m_FrameHeight = m_Rect.h;
        }
    }

    return ret;
}


void TrObject::Show(SDL_Renderer* screen)
{
    if (m_Visible == false)
        return;

    if (m_IsDie == false)
    {
        // Create delay times when next frame
        if (SDL_GetTicks() - m_FrameDelay[m_FrameIdx] > m_PassedTime)
        {
            m_PassedTime = SDL_GetTicks();
            ++m_FrameIdx;
            if (m_FrameIdx > m_FrameNum - 1)
            {
                m_FrameIdx = 0;
            }
        }

        SDL_Rect* currentClip = &m_FramesData[m_FrameIdx];
        BaseObj::Render(screen, currentClip);
    }
}

SDL_Rect TrObject::GetRectFrame()
{
    SDL_Rect rect = m_Rect;
    rect.h = m_FrameHeight;
    rect.w = m_FrameWidth;

    return rect;
}

void TrObject::Update(int xScreen, int yScreen)
{
    if (m_IsDie == true)
    {
        return;
    }

    if (m_Type == TObjType::TOBJ_MOV_HORI)
    {
        if (m_Visible == true)
        {
            m_Rect.x += m_Speed;
            if (m_Rect.x > m_Pt2.x)
            {
                m_Speed *= -1;
            }
            else if (m_Rect.x < m_Pt1.x)
            {
                m_Speed *= -1;
            }
        }
    }
    else if (m_Type == TObjType::TOBJ_MOV_VERTI)
    {
        if (m_Visible == true)
        {
            m_Rect.y += m_Speed;
            if (m_Rect.y > m_Pt2.y)
            {
                m_Speed *= -1;
            }
            else if (m_Rect.y < m_Pt1.y)
            {
                m_Speed *= -1;
            }
        }
    }
    else if (m_Type == TObjType::TOBJ_MOV_END)
    {
        m_Rect.y += m_Speed;

        if (m_Rect.y > 0)
        {
            m_Visible = true;
        }

        if (m_Rect.y + m_Rect.h > yScreen)
        {
            InitRandomPos();
        }
    }
}

// Bullet

void TrObject::AddBullet(SDL_Renderer* screen)
{
    BulletObj* pBul = NULL;
    if (m_Type == TOBJ_STATIC)
    {
        VT(std::string) path_list = { "image//bul_laser2.png" };
        pBul = new BulletObj(BulletObj::BL_CIRCLE, BulletObj::BL_DIR_DOWN, 0, 10);
        SDL_Point pos = InitPos();
        pBul->Init(path_list, pos.x, pos.y, screen);
        m_BulletList.push_back(pBul);
    }
    else
    {
        VT(std::string) path_list = { "image//bul_tr.png" };
        pBul = new BulletObj(BulletObj::BL_CIRCLE, BulletObj::BL_DIR_DOWN, 0, 10);
        SDL_Point pos = InitPos();
        pBul->Init(path_list, pos.x, pos.y, screen);
        m_BulletList.push_back(pBul);
    }
}

SDL_Point TrObject::InitPos()
{
    SDL_Point pos;
    pos.x = m_Rect.x + 0.46 * m_FrameWidth;
    pos.y = m_Rect.y + m_Rect.h - 5;
    return pos;
}

void TrObject::DoBullet(SDL_Renderer* screen)
{
    if (m_IsDie == true || m_Visible == false)
        return;

    for (size_t iBul = 0; iBul < m_BulletList.size(); iBul++)
    {
        BulletObj* pBul = m_BulletList.at(iBul);
        if (pBul != NULL)
        {
            if (pBul->get_is_move() == true)
            {
                if (m_stateGame == GameStatus::GAME_PLAYING)
                {
                    pBul->Update(SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                pBul->Show(screen);
            }
            else
            {
                SDL_Point pos = InitPos();
                pBul->SetRect(pos.x, pos.y);
                pBul->set_is_move(true);
            }
        }
    }
}

void TrObject::SetScopeMoving(SDL_Point p1, SDL_Point p2)
{
    m_Pt1.x = p1.x;
    m_Pt1.y = p1.y;

    m_Pt2.x = p2.x;
    m_Pt2.y = p2.y;
}


bool TrObject::CheckCollisionBullet(SDL_Rect rect)
{
    bool bRet = false;
    for (size_t iBul = 0; iBul < m_BulletList.size(); iBul++)
    {
        BulletObj* pBul = m_BulletList[iBul];
        if (pBul->get_is_move() == true)
        {
            SDL_Rect bul_rect = pBul->GetRect();
            bool ret = TCommon::CheckCollision(bul_rect, rect);
            if (ret == true)
            {
                bRet = true;
                pBul->set_is_move(false);
                break;
            }
        }
        else
        {
            SDL_Point pos = InitPos();
            pBul->SetRect(pos.x, pos.y);
            pBul->set_is_move(true);
        }
    }

    return bRet;
}