
#ifndef BASE_OBJ_H_
#define BASE_OBJ_H_
#include "define.h"


#define NUM_TEXTURE 5 // Ex: 0 wal, 1 run, 2 die, 3 fly....

class DataResize
{
public:
    int xr_;
    int yr_;
    bool is_resize_;
};

class BaseObj
{
public:
    BaseObj();
    ~BaseObj();

    virtual bool LoadImg(std::string path, SDL_Renderer* screen, const int& idx = 0);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

    void Free();

    void SetRect(const int& x, const int& y);
    void SetAngle(float angle);
    void SetIsFlip(int& flip);

    int GetFlip() const;
    SDL_Rect GetRect();
    SDL_Texture* GetObject(int idx);

    void SetTextureIndex(int idx) 
    { 
        if (idx == 1)
        {
            int a = 5;
            a++;
        }
        m_textureIdx = idx; 
    }
    void SetStateGame(int state) { m_stateGame = state; }

protected:
    int m_textureIdx;

    float m_Angle;
    SDL_Point m_CenterPt;
    int  m_Flip;

    SDL_Texture* m_Texture[NUM_TEXTURE];
    SDL_Surface* m_Surface[NUM_TEXTURE];

    SDL_Rect m_Rect;
    int m_stateGame;

};

#endif

