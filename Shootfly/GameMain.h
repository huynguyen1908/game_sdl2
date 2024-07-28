
#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_

#include "define.h"
#include "BaseObj.h"
#include "PlayerObj.h"
#include "TrObject.h"
#include "Geometric.h"
#include "PlayerBlood.h"
#include "TextObject.h"
#include "MenuGame.h"

class GameMain
{
public:
	GameMain();
	~GameMain();

	static GameMain* GetInstance();

public:
	bool Init();
	bool LoadData();
	void Loop();
	void Close();
	void FreeInstance();
	void InitTObj();
	void InitFrameInfo();

	// Time
	void RenderTimeDown(bool is_active = true);
	void RenderMark();
	void SetStateGame();
	void InitStartGame();
	void InitPauseGame();
	void InitEndGame();
private:
	static GameMain* m_Instance;
	int m_GameState;

	SDL_Window* m_Window;
	SDL_Renderer* m_Screen;
	SDL_Event   m_Event;

	BaseObj  m_Bkgn;
	PlayerObj m_Player;

	VT(TrObject*) m_TObjList;

	GeoFormat m_Rect;
	GeoFormat m_RectOutLine;

	PlayerBlood m_PlayerBlood;

	// Time down
	unsigned int m_Frame1s;
	TextObject m_TTime;
	int m_TimeDown;
	TTF_Font* m_Font30;

	// Mark
	Uint32 m_Mark;
	Uint32 m_MarkGoal;
	TextObject m_TextMark;
	TextObject m_TextGoal;

	MenuGameStart m_StartMenu;
	MenuGamePause m_PauseMenu;
	MenuGameEnd m_EndMenu;
};


#endif

