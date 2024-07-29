
#include "BaseObj.h"


BaseObj::BaseObj()
{
    m_textureIdx = 0;
    for (int i = 0; i < NUM_TEXTURE; i++)
    {
        m_Texture[i] = NULL;
        m_Surface[i] = NULL;
    }

    m_Rect.x = 0;
    m_Rect.y = 0;
    m_Rect.w = 0;
    m_Rect.h = 0;

    m_Flip = SDL_FLIP_NONE;
    m_Angle = 0.0;
    m_CenterPt.x = 0;
    m_CenterPt.y = 0;

    m_stateGame = -1;
}

BaseObj::~BaseObj()
{
    Free();
}

void BaseObj::SetRect(const int& x, const int& y)
{
    m_Rect.x = x;
    m_Rect.y = y;
}

void BaseObj::SetIsFlip(int& flip)
{
    m_Flip = flip;
}

void BaseObj::SetAngle(float angle)
{
    m_Angle = angle;
}

int BaseObj::GetFlip() const
{
    return m_Flip;
}

SDL_Rect BaseObj::GetRect()
{
    if (m_textureIdx >= 0 && m_textureIdx < NUM_TEXTURE)
    {
        m_Rect.w = m_Surface[m_textureIdx]->w;
        m_Rect.h = m_Surface[m_textureIdx]->h;
    }
    return m_Rect;
}

SDL_Texture* BaseObj::GetObject(int idx)
{
    return m_Texture[idx];
}


bool BaseObj::LoadImg(std::string path, SDL_Renderer* screen, const int& idx)
{
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    m_Surface[idx] = IMG_Load(path.c_str());
    if (m_Surface[idx] != NULL)
    {
        //Color key image
        Uint32 uKey = SDL_MapRGB(m_Surface[idx]->format, COLOR_KEY_RED, COLOR_KEY_GREEN, COLOR_KEY_BLUE);
        SDL_SetColorKey(m_Surface[idx], SDL_TRUE, uKey);

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(screen, m_Surface[idx]);
        if (newTexture != NULL)
        {
            //Get image dimensions
            m_Rect.w = m_Surface[idx]->w;
            m_Rect.h = m_Surface[idx]->h;
            SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        }
    }

    m_Texture[idx] = newTexture;
    bool ret = (m_Texture[idx] != NULL ? true : false);
    return ret;
}

void BaseObj::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/)
{
    if (m_textureIdx >= 0 && m_textureIdx < NUM_TEXTURE)
    {
        if (m_Surface[m_textureIdx] != NULL)
        {
            m_Rect.w = m_Surface[m_textureIdx]->w;
            m_Rect.h = m_Surface[m_textureIdx]->h;

            SDL_Rect renderQuad = { m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h };
            if (clip != NULL)
            {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
            }

            SDL_RenderCopyEx(des, m_Texture[m_textureIdx], clip, &renderQuad, m_Angle, &m_CenterPt, (SDL_RendererFlip)m_Flip);
        }
    }
}


void BaseObj::Free()
{
    for (int i = 0; i < NUM_TEXTURE; i++)
    {
        if (m_Texture[i] != NULL)
        {
            SDL_DestroyTexture(m_Texture[i]);
            m_Texture[i] = NULL;
        }
    }

    for (int i = 0; i < NUM_TEXTURE; i++)
    {
        if (m_Surface[i] != NULL)
        {
            SDL_FreeSurface(m_Surface[i]);
            m_Surface[i] = NULL;
        }
    }
}