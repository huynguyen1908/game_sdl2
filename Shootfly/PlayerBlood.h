


#ifndef PLAYER_BLOOD_H_
#define PLAYER_BLOOD_H_
#include "define.h"
#include "BaseObj.h"

class PlayerBlood
{
public:
	PlayerBlood();
	~PlayerBlood();
	int GetCount() { return m_Count; }

	void MinusUpdate();
	void Init(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	bool IsEmpty();
	void FreeData();
private:
	int m_Count;
	VT(BaseObj*) m_BloodList;
};


#endif

