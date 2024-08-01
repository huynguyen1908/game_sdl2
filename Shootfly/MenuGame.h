

#ifndef MENU_GAME_H_
#define MENU_GAME_H_
#include "define.h"
#include "BaseObj.h"
#include "Geometric.h"


class MenuGame
{
public:
	MenuGame(bool is_bkgn = true);
	~MenuGame();

	enum MenuTyle
	{
		MENU_START = 200,
		MENU_PAUSE,
		MENU_END,
	};

	virtual void Render(SDL_Renderer* screen);
	virtual void MenuAction(SDL_Event events, SDL_Renderer* screen);
	virtual void LoadBkgn(const char* file, SDL_Renderer* screen);

	void Free();
	bool OnRect(int x, int y, SDL_Rect& rect);
	void SetIsBkgn(bool is_bkgn) { m_isDrawBkgn = is_bkgn; }
	void SetIsSelect(int idx) { m_Select = idx; };
	int GetSelect() { return m_Select; }
protected:
	int m_Type;
	BaseObj m_Background;
	bool m_isDrawBkgn;
	int m_Select;
};


class MenuGameStart : public MenuGame
{
public:
	MenuGameStart();
	~MenuGameStart();
	void SetImgOptionList(const VT(BaseObj*)& img_list);
	void FreeData();
	void Render(SDL_Renderer* screen);
	void MenuAction(SDL_Event events, SDL_Renderer* screen);
private:
	VT(BaseObj*) m_ImgOptionList;
};

// MENU END GAME

class MenuGameEnd : public MenuGame
{
public:
	MenuGameEnd();
	~MenuGameEnd();

	void SetImgOptionList(const VT(BaseObj*)& img_list);
	void FreeData();
	void Render(SDL_Renderer* screen);
	//void MenuAction(SDL_Event events, SDL_Renderer* screen);

private:
	VT(BaseObj*) m_ImgOptionList;

};
#endif

