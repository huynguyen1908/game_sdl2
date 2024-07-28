

#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "define.h"
#include "TCommon.h"

class TextObject
{
public:
    TextObject();
    TextObject(int color, std::string sData);
    ~TextObject();

    std::string GetText() const { return str_val_; }
    bool LoadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);

    void Free();
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);
    void SetText(const std::string& text) { str_val_ = text; }
    void SetPos(int x, int y) { text_pos_.x = x; text_pos_.y = y; }
    void RenderText(SDL_Renderer* screen, SDL_Rect* clip = NULL);
    SDL_Rect GetRect() { return text_pos_; }
private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    SDL_Rect text_pos_;
};

#endif


