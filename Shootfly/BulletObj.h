
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObj.h"
#include "define.h"

class BulletObj : public BaseObj
{
public:
	BulletObj();
	~BulletObj();
    BulletObj(int type, int dir_type, int x_speed, int y_speed, int scope = 0);
    enum BulletDir
    {
        BL_DIR_NONE = 20,
        BL_DIR_UP,
        BL_DIR_DOWN,
    };

    enum BulletType
    {
        BL_NONE = 1000,
        BL_CIRCLE,
        BL_LASER,
    };

    bool Init(VT(std::string) path_list, int xp, int yp, SDL_Renderer* screen);
    void Update(const int& xScreen, const int& yScreen);
    void setScope(const int& scp) { m_Scope = scp; };
    void set_x_val(const int& x_val) { m_Xval = x_val; };
    void set_y_val(const int& y_val) { m_Yval = y_val; };
    void set_is_move(const bool& is_move) { m_bMoving = is_move; };
    bool get_is_move()const { return m_bMoving; };
    void SetBLDirType(const int& dir_type) { m_BLDirType = dir_type; };
    void SetBLType(const int& type) { m_BLType = type; };
    int GetBLType() const { return m_BLType; };
    void Show(SDL_Renderer* des);
private:
    int m_Scope;
    int m_plus_dis;
    int m_Xval;
    int m_Yval;
    bool m_bMoving;
    int m_BLDirType;
    int m_BLType;

};

#endif

