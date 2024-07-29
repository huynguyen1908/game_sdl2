#include "MenuGame.h"

MenuGame::MenuGame(bool is_bkgn /*= true*/)
{
	m_Type = 0;
	m_isDrawBkgn = is_bkgn;
    m_Select = -1;
}

MenuGame::~MenuGame()
{

}

void MenuGame::LoadBkgn(const char* file, SDL_Renderer* screen)
{
    if (m_isDrawBkgn == true)
    {
        m_Background.LoadImg(file, screen);
    }
}

void MenuGame::Render(SDL_Renderer* screen)
{
    if (m_isDrawBkgn == true)
    {
        m_Background.Render(screen);
    }
}

void MenuGame::MenuAction(SDL_Event events, SDL_Renderer* screen)
{

}

void MenuGame::Free()
{
    m_Background.Free();
}

bool MenuGame::OnRect(int x, int y, SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////

MenuGameStart::MenuGameStart()
{
    m_Select = -1;
}

MenuGameStart::~MenuGameStart()
{
    FreeData();
}

void MenuGameStart::SetImgOptionList(const VT(BaseObj*)& img_list)
{
    FreeData();
    m_ImgOptionList = img_list;
}

void MenuGameStart::FreeData()
{
    if (m_ImgOptionList.empty())
    {
        for (auto x : m_ImgOptionList)
        {
            if (x != NULL)
            {
                x->Free();
            }
        }
        m_ImgOptionList.clear();
    }
}

void MenuGameStart::Render(SDL_Renderer* screen)
{
    MenuGame::Render(screen);
    for (auto x : m_ImgOptionList)
    {
        x->Render(screen);
    }
}

void MenuGameStart::MenuAction(SDL_Event events, SDL_Renderer* screen)
{
    switch (events.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                m_Select = i;
                break;
            }
        }
        break;
    }
    case SDL_MOUSEMOTION:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                ;
            }
            else
            {
                ;
            }
        }
        break;
    }
    default: break;
    }
}
