
#ifndef TR_OBJECT_H_
#define TR_OBJECT_H_

#include "define.h"
#include "BaseObj.h"
#include "BulletObj.h"
#include "TCommon.h"

class TrObject : public BaseObj
{
public:
	TrObject();
	TrObject(int mov_type, SDL_Point p1, SDL_Point p2);
	~TrObject();

	enum TObjType
	{
		TOBJ_STATIC = 400,
		TOBJ_MOV_HORI,
		TOBJ_MOV_VERTI,
		TOBJ_MOV_END,
	};

	bool Init(VT(std::string) path_list, int frame_num, SDL_Point pos, SDL_Renderer* screen);
	void SetType(int type) { m_Type = type; }
	int GetType() const { return m_Type; }
	int GetBulletGet() { return m_GetBullet; }
	void PlusGetBullet() { m_GetBullet++; }
	void SetBulletGet(int bg) { m_GetBullet = bg; }
	SDL_Rect GetRectFrame();
	void InitRandomPos();

	void Show(SDL_Renderer* screen);
	void Update(int xScreen, int yScreen);

	void SetXVal(int xval);
	void SetYval(int yval);

	int GetXVal()const;
	int GetYVal()const;

	void SetFrameNum(int num);
	void DoBullet(SDL_Renderer* screen);
	void SetScopeMoving(SDL_Point p1, SDL_Point p2);

	void SetDie(bool bDie) { m_IsDie = bDie; }
	bool GetIsDie() const { return m_IsDie; }
	bool CheckCollisionBullet(SDL_Rect rect);

protected:
	bool LoadImg(VT(std::string) path_list, SDL_Renderer* screen);
	SDL_Point InitPos();
	void InitFrame();
	void MakeClip();
	void AddBullet(SDL_Renderer* screen);

private:
	// Basic
	VT(int) m_FrameDelay;
	unsigned long m_PassedTime;

	VT(SDL_Rect) m_FramesData;
	int m_FrameNum;
	int m_TimeWait;
	bool m_Visible;
	bool m_IsDie;

	int m_FrameWidth;
	int m_FrameHeight;

	int m_xVal;
	int m_yVal;

	int m_FrameIdx;

	// Bullet
	VT(BulletObj*) m_BulletList;

	// Advance
	int m_Type;
	SDL_Point m_Pt1;
	SDL_Point m_Pt2;
	int m_Speed;

	// 
	int m_GetBullet;
};

#endif

