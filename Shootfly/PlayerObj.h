
#include "BaseObj.h"
#include "define.h"
#include "BulletObj.h"
#include "TCommon.h"

class PlayerObj : public BaseObj
{
public:
	PlayerObj();
	~PlayerObj();

	// Basic
	bool Init(VT(std::string) path_list, int frame_num, SDL_Point pos, SDL_Renderer* screen);
	void InputKey(SDL_Event event, SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void Update(int xScreen, int yScreen);

	void SetXVal(int xval);
	void SetYval(int yval);

	int GetXVal()const;
	int GetYVal()const;

	void SetFrameNum(int num);
	SDL_Rect GetRectFrame();

	// Bullet
	VT(BulletObj*) GetBullets() { return m_BulletList; }
	void DoBullet(SDL_Renderer* screen);
	void FreeData();
	void PlusCol(int plus = 1) { m_Coll += plus; }
	void SetCol(int col) { m_Coll = col; }
	int GetCol() const { return m_Coll; }
	bool GetIsDie() const { return m_IsDie; }
	void SetIsDie(bool isDie) { m_IsDie = isDie; }
protected:
	bool LoadImg(VT(std::string) path_list, SDL_Renderer* screen);
	void InitFrame();
	void MakeClip();
	void AddBullet(SDL_Renderer* screen, int type);

private:
	// Basic
	VT(int) m_FrameDelay;
	unsigned long m_PassedTime;

	VT(SDL_Rect) m_FramesData;
	int m_FrameNum;
	bool m_Visible;
	bool m_IsDie;

	int m_FrameWidth;
	int m_FrameHeight;

	int m_xVal;
	int m_yVal;
	MOVING_STYLE m_MovStyle;

	int m_FrameIdx;

	// Bullet
	VT(BulletObj*) m_BulletList;
	int m_Coll;
};

