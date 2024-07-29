
#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_

#include "define.h"
#include "BaseObj.h"
#include "PlayerObj.h"
#include "TrObject.h"
#include "Geometric.h"
#include "PlayerBlood.h"
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
	void SetStateGame();
	void InitStartGame();
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

	unsigned int m_Frame1s;

	MenuGameStart m_StartMenu;
};


#endif

