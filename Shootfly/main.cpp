
#include "GameMain.h"

#undef main
int main()
{
    bool bInit = GameMain::GetInstance()->Init();
    bool bLoadData = GameMain::GetInstance()->LoadData();
    if (bInit == true && bLoadData == true)
    {
        // Call Loop Function here
        GameMain::GetInstance()->Loop();
    }

    GameMain::GetInstance()->Close();
    GameMain::GetInstance()->FreeInstance();
    return 0;
}