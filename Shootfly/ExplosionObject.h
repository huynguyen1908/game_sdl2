
#pragma once

#include "BaseObj.h"
#include "define.h"

class ExplosionObject : public BaseObj
{
public:
    ExplosionObject();
    ~ExplosionObject();
    ExplosionObject(int frameNum);
public:
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

    int get_frame() const { return frame_; }
    int get_frame_width() const { return frame_width_; }
    int get_frame_height() const { return frame_height_; }

    void set_clips();
    void set_frame(const int& fr) { frame_ = fr; }
    void SetXP(SDL_Rect rect_pos);
    void ImpRender(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetActive(bool bActive) { m_isActive = bActive; }
    bool GetActive() const { return m_isActive; }
private:
    int m_Frame;
    VT(SDL_Rect) frame_clip_;
    int frame_width_;
    int frame_height_;
    unsigned int frame_;
    VT(int) iDelayList;
    unsigned long passed_time_;
    bool m_isActive;
};

class ExpAds
{
public:
    ExpAds();
    ~ExpAds();

    static ExpAds* GetInstance()
    {
        if (instance_ == NULL)
            instance_ = new ExpAds();
        return instance_;
    }

    void Render(SDL_Renderer* screen);
    void Add(ExplosionObject* pObj);
    bool IsEmpty();
private:
    std::vector<ExplosionObject*> m_ExpList;
    static ExpAds* instance_;
};
