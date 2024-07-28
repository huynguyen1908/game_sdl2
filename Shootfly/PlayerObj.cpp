

#include "PlayerObj.h"
#include "Sound.h"

PlayerObj::PlayerObj()
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
    InitFrame();
    m_Coll = 0;
}

PlayerObj::~PlayerObj()
{

}

void PlayerObj::SetXVal(int xval)
{
	m_xVal = xval;
}

void PlayerObj::SetYval(int yval)
{
	m_yVal = yval;
}

int PlayerObj::GetXVal()const
{
	return m_xVal;
}

int PlayerObj::GetYVal()const
{
	return m_yVal;
}

void PlayerObj::SetFrameNum(int num)
{
    m_FrameNum = num;
    InitFrame();
}

bool PlayerObj::Init(VT(std::string) path_list, int frame_num, SDL_Point pos, SDL_Renderer* screen)
{
    if (frame_num <= 0)
        return false;

    if (path_list.empty() == true)
        return false;

    m_FrameNum = frame_num;

    m_Rect.x = pos.x;
    m_Rect.y = pos.y;
    bool ret = LoadImg(path_list, screen);
    if (ret == false)
        return false;

    InitFrame();
    MakeClip();

    return ret;
}

SDL_Rect PlayerObj::GetRectFrame()
{
    SDL_Rect rect = m_Rect;
    rect.h = m_FrameHeight;
    rect.w = m_FrameWidth;

    return rect;
}

void PlayerObj::InitFrame()
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

void PlayerObj::MakeClip()
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


bool PlayerObj::LoadImg(VT(std::string) path_list, SDL_Renderer* screen)
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

void PlayerObj::InputKey(SDL_Event event, SDL_Renderer* screen)
{
    if (m_Visible == false && m_IsDie == true)
        return;

    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_UP)
        {
            m_MovStyle.sUp = true;
            m_MovStyle.sDown = false;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            m_MovStyle.sUp = false;
            m_MovStyle.sDown = true;
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            m_MovStyle.sLeft = true;
            m_MovStyle.sRight = false;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            m_MovStyle.sLeft = false;
            m_MovStyle.sRight = true;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_LEFT)
        {
            m_MovStyle.sLeft = false;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            m_MovStyle.sRight = false;
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
            m_MovStyle.sUp = false;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            m_MovStyle.sDown = false;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            AddBullet(screen, BulletObj::BL_CIRCLE);
            SoundGame::GetInstance()->PlaySoundGame(SoundGame::GUN_ONE);
        }
        else if (event.button.button == SDL_BUTTON_RIGHT)
        {
            AddBullet(screen, BulletObj::BL_LASER);
            SoundGame::GetInstance()->PlaySoundGame(SoundGame::GUN_LASER);
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {

        }
        else if (event.button.button == SDL_BUTTON_RIGHT)
        {

        }
    }
}

void PlayerObj::Show(SDL_Renderer* screen)
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

void PlayerObj::Update(int xScreen, int yScreen)
{
    if (m_Visible == false)
        return;

    if (m_IsDie == true)
        return;

    if (m_MovStyle.sLeft == true)
    {
        m_xVal = -10;
    }
    else if (m_MovStyle.sRight == true)
    {
        m_xVal = 10;
    }
    else
    {
        m_xVal = 0;
    }

    if (m_MovStyle.sUp == true)
    {
        m_yVal = -10;
    }
    else if (m_MovStyle.sDown == true)
    {
        m_yVal = 10;
    }
    else
    {
        m_yVal = 0;
    }

    m_Rect.x += m_xVal;
    if (m_Rect.x < 0)
    {
        m_Rect.x = 0;
    }
    else if (m_Rect.x + m_FrameWidth > xScreen)
    {
        m_Rect.x = xScreen - m_FrameWidth;
    }

    m_Rect.y += m_yVal;
    if (m_Rect.y < 0)
    {
        m_Rect.y = 0;
    }
    else if (m_Rect.y + m_FrameHeight > yScreen)
    {
        m_Rect.y = yScreen - m_FrameHeight;
    }
}

// Bullet

void PlayerObj::AddBullet(SDL_Renderer* screen, int type)
{
    VT(std::string) path_list;
    path_list.push_back("image//bul_circle.png");
    path_list.push_back("image//bul_laser.png");

    BulletObj* pBul = new BulletObj(type, BulletObj::BL_DIR_UP, 0, 20);
    pBul->setScope(300);
    int xp = (int)(m_Rect.x + 0.46 * m_FrameWidth);
    int yp = m_Rect.y - 1;
    pBul->Init(path_list, xp, yp, screen);

    m_BulletList.push_back(pBul);
}

void PlayerObj::DoBullet(SDL_Renderer* screen)
{
    if (m_Visible == false || m_IsDie == true)
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
                m_BulletList.erase(m_BulletList.begin() + iBul);
                delete pBul;
                pBul = NULL;
                continue;
            }
        }
    }
}

void PlayerObj::FreeData()
{
    for (size_t i = 0; i < m_BulletList.size(); i++)
    {
        BulletObj* pBul = m_BulletList[i];
        if (pBul != NULL)
        {
            delete pBul;
            pBul = NULL;
        }
    }

    m_BulletList.clear();
}