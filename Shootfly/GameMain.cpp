#include "GameMain.h"
#include "ImpTimer.h"
#include "ExplosionObject.h"
#include "Geometric.h"
#include "TCommon.h"
#include "Sound.h"

GameMain* GameMain::m_Instance = NULL;

GameMain::GameMain()
{
    m_Window = NULL;
    m_Screen = NULL;
    m_GameState = GameStatus::GAME_START;
    srand((unsigned int)time(0));
    m_Frame1s = 0;
    m_Event.type = -1;
    m_Font30 = NULL;
    m_Mark = 0;
}

GameMain::~GameMain()
{
    
}


GameMain* GameMain::GetInstance()
{
    if (m_Instance == NULL)
        m_Instance = new GameMain();
    return m_Instance;
}

bool GameMain::Init()
{
    int iCheck = SDL_Init(SDL_INIT_EVERYTHING);
    if (iCheck < 0)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //Create window
    m_Window = SDL_CreateWindow("Shootfly", 200, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (m_Window == NULL)
    {
        return false;
    }

    m_Screen = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Screen == NULL)
    {
        return false;
    }

    Uint8 uR, uG, uB, uA;
    uR = uG = uB = uA = RENDER_DRAW_COLOR;
    SDL_SetRenderDrawColor(m_Screen, uR, uG, uB, uA);

    int jCheck = IMG_Init(IMG_INIT_PNG);
    if (jCheck == 0)
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }

    m_Font30 = TTF_OpenFont(g_MenuFont, 20);

    if (SoundGame::GetInstance()->Init() == false)
    {
        return false;
    }

    return true;
}

void GameMain::InitFrameInfo()
{
    m_Rect.rect_ = { 0, 0, SCREEN_WIDTH, FRAME_HEIGHT };
    m_Rect.color_ = TCommon::GetBaseColor(ColorBase::GRAY_COLOR);

    m_RectOutLine.rect_ = { 1, 1, SCREEN_WIDTH - 1, FRAME_HEIGHT - 2 };
    m_RectOutLine.color_ = TCommon::GetBaseColor(ColorBase::WHITE_COLOR);
}

void GameMain::InitStartGame()
{
    m_StartMenu.LoadBkgn("image\\bkgn_start.png", m_Screen);

    VT(BaseObj*) menu_list;
    BaseObj* playObj = new BaseObj();
    BaseObj* GuideObj = new BaseObj();
    BaseObj* ExitObj = new BaseObj();

    int x_pos = H_WIDTH- 64;
    int y_pos = H_HEIGHT + 100;

    bool b1a = playObj->LoadImg("image\\play.png", m_Screen);
    bool b1b = playObj->LoadImg("image\\play_s.png", m_Screen, 1);
    if (b1a && b1b)
    {
        playObj->SetRect(x_pos, y_pos);
        menu_list.push_back(playObj);
    }

    bool b3a = ExitObj->LoadImg("image\\exit.png", m_Screen);
    bool b3b = ExitObj->LoadImg("image\\exit_s.png", m_Screen, 1);
    if (b3a && b3b)
    {
        y_pos += 50;
        ExitObj->SetRect(x_pos, y_pos);
        menu_list.push_back(ExitObj);
    }

    m_StartMenu.SetImgOptionList(menu_list);
}

void GameMain::InitPauseGame()
{
    m_PauseMenu.SetIsBkgn(false);
    VT(BaseObj*) pause_list;
    BaseObj* resumeObj = new BaseObj();
    BaseObj* quitObj = new BaseObj();

    bool ret1 = resumeObj->LoadImg("image\\resume.png", m_Screen);
    bool ret2 = resumeObj->LoadImg("image\\resume_s.png", m_Screen, 1);
    if (ret1 && ret2)
    {
        pause_list.push_back(resumeObj);
    }

    bool ret3 = quitObj->LoadImg("image\\exit.png", m_Screen);
    bool ret4 = quitObj->LoadImg("image\\exit_s.png", m_Screen, 1);
    if (ret3 && ret4)
    {
        pause_list.push_back(quitObj);
    }

    m_PauseMenu.SetImgOptionList(pause_list);
    m_PauseMenu.InitFrameGeo();
}

void GameMain::InitEndGame()
{
    // End menu;
    m_EndMenu.SetIsBkgn(false);
    m_EndMenu.SetFont(m_Font30);

    BaseObj* qObj = new BaseObj();
    bool ret1 = qObj->LoadImg("image\\exit.png", m_Screen);
    bool ret2 = qObj->LoadImg("image\\exit_s.png", m_Screen, 1);
    VT(BaseObj*) end_list;
    if (ret1 && ret2)
    {
        qObj->SetRect((const int)(SCREEN_WIDTH * 0.5 - 60), (const int)(H_HEIGHT + 50));
        end_list.push_back(qObj);
    }

    TextObject* tInfoObj = new TextObject(ColorBase::WHITE_COLOR, "Game Over");
    int xp = H_WIDTH - 65;
    int yp = H_HEIGHT;
    tInfoObj->SetPos(xp, yp);


    m_EndMenu.AddTextObj(tInfoObj);

    m_EndMenu.SetImgOptionList(end_list);
}

bool GameMain::LoadData()
{
    std::string bk_path = "image\\bkgn.png";
    bool ret = m_Bkgn.LoadImg(bk_path, m_Screen, false);
    if (ret == false)
    {
        return false;
    }

    // Load data for player
    VT(std::string) player_path_list = { "image\\player.png" };
    SDL_Point pl_pos = { 300, SCREEN_HEIGHT - 100 };
    m_Player.Init(player_path_list, 4, pl_pos, m_Screen);

    InitFrameInfo();

    InitStartGame();
    InitPauseGame();
    InitEndGame();

    InitTObj();

    m_PlayerBlood.Init(m_Screen);

    m_TextMark.SetColor(ColorBase::GREEN_COLOR);
    m_TextMark.SetPos(H_WIDTH - 120, 15);

    m_TextGoal.SetColor(ColorBase::RED_COLOR);
    m_TextGoal.SetPos(H_WIDTH + 20, 17);

    return true;
}

void GameMain::InitTObj()
{
    TrObject* tObj1a = new TrObject();
    VT(std::string) tr_path_lista = { "image\\air_static.png" };
    SDL_Point posa = { 10, 100 };
    tObj1a->Init(tr_path_lista, 4, posa, m_Screen);

    TrObject* tObj1b = new TrObject();
    VT(std::string) tr_path_listb = { "image\\air_static.png" };
    SDL_Point posb = { 450, 100 };
    tObj1b->Init(tr_path_listb, 4, posb, m_Screen);


    SDL_Point p1 = { 100, 200 };
    SDL_Point p2 = { 400, 200 };
    TrObject* tObj2 = new TrObject(TrObject::TOBJ_MOV_HORI, p1, p2);
    VT(std::string) tr_path_list2 = { "image\\air_green.png" };
    SDL_Point pos2 = { 300, 200 };
    tObj2->Init(tr_path_list2, 4, pos2, m_Screen);


    SDL_Point pp1 = { 300, 50 };
    SDL_Point pp2 = { 300, 350 };
    TrObject* tObj3 = new TrObject(TrObject::TOBJ_MOV_VERTI, pp1, pp2);

    VT(std::string) tr_path_list3 = { "image\\air_green.png" };
    SDL_Point pos3 = { 300, 100 };
    tObj3->Init(tr_path_list3, 4, pos3, m_Screen);


    m_TObjList.push_back(tObj1a);
    m_TObjList.push_back(tObj1b);
    m_TObjList.push_back(tObj2);
    m_TObjList.push_back(tObj3);


    VT(std::string) tr_path_listRand = { "image\\air_red.png" };
    SDL_Point pos00 = { 0, 0 };

    for (int i = 0; i < 7; i++)
    {
        TrObject* tObj_rand = new TrObject();
        tObj_rand->SetType(TrObject::TOBJ_MOV_END);
        tObj_rand->Init(tr_path_listRand, 4, pos00, m_Screen);
        m_TObjList.push_back(tObj_rand);
    }
}


void GameMain::Loop()
{
    ImpTimer fps;
    bool bQuit = false;

    ExpAds* pExpAds = ExpAds::GetInstance();
    bool is_end_game = false;
    while (bQuit == false)
    {
        while (SDL_PollEvent(&m_Event) != 0)
        {
            if (m_Event.type == SDL_QUIT)
            {
                bQuit = true;
                continue;
            }
            if (m_Event.type == SDL_KEYDOWN)
            {
                if (m_Event.key.keysym.sym == SDLK_SPACE)
                {
                    m_GameState = GAME_PAUSE;
                    SoundGame::GetInstance()->PlaySoundGame(SoundGame::GAME_PAUSE);
                    SetStateGame();
                }
            }

            if (m_GameState == GameStatus::GAME_START)
            {
                m_StartMenu.MenuAction(m_Event, m_Screen);
                int a = 5;
            }
            else if (m_GameState == GameStatus::GAME_PLAYING)
            {
                m_Player.InputKey(m_Event, m_Screen);
            }
            else if (m_GameState == GameStatus::GAME_PAUSE)
            {
                m_PauseMenu.MenuAction(m_Event, m_Screen);
            }
            else if (m_GameState == GameStatus::GAME_END)
            {
                m_EndMenu.MenuAction(m_Event, m_Screen);
            }
        }

        Uint8 uR, uG, uB, uA;
        uR = uG = uB = uA = RENDER_DRAW_COLOR;
        SDL_SetRenderDrawColor(m_Screen, uR, uG, uB, uA);
        SDL_RenderClear(m_Screen);

        if (m_GameState == GAME_START)
        {
            m_StartMenu.Render(m_Screen);
            int is = m_StartMenu.GetSelect();
            if (is == 0)
            {
                m_GameState = GAME_PLAYING;
                m_StartMenu.SetIsSelect(-1);

                SetStateGame();
            }
            else if (is == 1)
            {
                m_GameState = GAME_GUIDE;
                m_StartMenu.SetIsSelect(-1);
                SetStateGame();
            }
            else if (is == 2)
            {
                bQuit = true;
                m_StartMenu.SetIsSelect(-1);
                SetStateGame();
                continue;
            }
        }
        else if (m_GameState == GameStatus::GAME_PLAYING)
        {
            fps.start();
            m_Bkgn.Render(m_Screen, NULL);
          
            m_Player.Show(m_Screen);
            m_Player.Update(SCREEN_WIDTH, SCREEN_HEIGHT);
            m_Player.DoBullet(m_Screen);

            VT(BulletObj*) player_bullet = m_Player.GetBullets();

            for (size_t t = 0; t < m_TObjList.size(); t++)
            {
                TrObject* tObj = m_TObjList.at(t);
                if (tObj != NULL)
                {
                    if (tObj->GetIsDie() == false)
                    {
                        tObj->SetStateGame(m_GameState);
                        tObj->Show(m_Screen);
                        tObj->Update(SCREEN_WIDTH, SCREEN_HEIGHT);
                        tObj->DoBullet(m_Screen);

                        SDL_Rect r2 = tObj->GetRectFrame();

                        for (size_t iBul = 0; iBul < player_bullet.size(); iBul++)
                        {
                            BulletObj* pBull = player_bullet.at(iBul);
                            if (pBull != NULL)
                            {
                                SDL_Rect r1 = pBull->GetRect();
                                r1.y -= 2;
                                bool ret = TCommon::CheckCollision(r1, r2);
                                if (ret == true)
                                {
                                    bool bTrDie = false;
                                    if (tObj->GetType() == TrObject::TOBJ_STATIC)
                                    {
                                        if (tObj->GetBulletGet() < 4)
                                        {
                                            tObj->PlusGetBullet();
                                        }
                                        else
                                        {
                                            tObj->SetBulletGet(0);
                                            bTrDie = true;
                                            m_Mark += 3;
                                        }

                                        if (pBull->GetBLType() == BulletObj::BL_CIRCLE)
                                        {
                                            pBull->set_is_move(false);
                                        }
                                    }
                                    else
                                    { 
                                        bTrDie = true;
                                        m_Mark++;
                                        if (pBull->GetBLType() == BulletObj::BL_CIRCLE)
                                        {
                                            pBull->set_is_move(false);
                                        }
                                    }

                                    if (bTrDie == true)
                                    {
                                        SoundGame::GetInstance()->PlaySoundGame(SoundGame::EXP_BOOM);
                                        ExplosionObject* pExp = new ExplosionObject(4);
                                        bool ret = pExp->LoadImg("image\\ex.png", m_Screen);
                                        if (ret)
                                        {
                                            pExp->SetXP(r1);
                                            ExpAds::GetInstance()->Add(pExp);
                                        }

                                        if (tObj->GetType() == TrObject::TOBJ_MOV_END)
                                        {
                                            tObj->InitRandomPos();
                                        }
                                        else
                                        {
                                            tObj->SetDie(true);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (tObj->GetType() != TrObject::TOBJ_MOV_END)
                        {
                            tObj->Free();
                            m_TObjList.erase(m_TObjList.begin() + t);
                        }
                    }
                }
            }

            SDL_Rect player_rect = m_Player.GetRectFrame();
            for (auto t : m_TObjList)
            {
                if (t != NULL)
                {
                    if (t->GetIsDie() == false)
                    {
                        bool ret = t->CheckCollisionBullet(player_rect);
                        if (ret == true)
                        {
                            m_Player.PlusCol();
                        }
                    }

                    SDL_Rect tRect = t->GetRectFrame();
                    bool rr = TCommon::CheckCollision(player_rect, tRect);
                    if (rr == true)
                    {
                        m_Player.PlusCol(3);
                        t->InitRandomPos();
                    }
                }
            }

            int colVal = m_Player.GetCol();
            if (colVal >= 3 && m_PlayerBlood.IsEmpty() == false)
            {
                colVal = colVal - 3;
                m_Player.SetCol(colVal);
                m_PlayerBlood.MinusUpdate();
            }

            pExpAds->Render(m_Screen);

            Gemometric::RenderRectange(m_Rect, m_Screen);
            Gemometric::RenderOutline(m_RectOutLine, m_Screen);

            m_PlayerBlood.Show(m_Screen);

            if (m_PlayerBlood.IsEmpty() == true && m_Player.GetIsDie() == false)
            {
                ExplosionObject* playExp = new ExplosionObject(8);
                bool ret = playExp->LoadImg("image\\ex_player.png", m_Screen);
                if (ret)
                {
                    SDL_Rect expRect = player_rect;
                    expRect.x += (int)(player_rect.w * 0.5);
                    expRect.y += (int)(player_rect.h * 0.5);

                    playExp->SetXP(expRect);
                    ExpAds::GetInstance()->Add(playExp);
                }

                m_Player.SetIsDie(true);
                is_end_game = true;
                std::string sData = "Game Over";
                SoundGame::GetInstance()->PlaySoundGame(SoundGame::GAME_FAIL);
                m_EndMenu.SetTextContent(sData, 0);
            }

            RenderMark();

            if (pExpAds->IsEmpty())
            {
                if (is_end_game == true)
                {
                    m_GameState = GameStatus::GAME_END;
                    SDL_Delay(2000);
                    is_end_game = false;
                }
            }       
        }
        else if (m_GameState == GameStatus::GAME_PAUSE)
        {
            m_Bkgn.Render(m_Screen, NULL);

            Gemometric::RenderRectange(m_Rect, m_Screen);
            Gemometric::RenderOutline(m_RectOutLine, m_Screen);

            m_PlayerBlood.Show(m_Screen);

            m_Player.Show(m_Screen);
            m_Player.DoBullet(m_Screen);

            VT(BulletObj*) player_bullet = m_Player.GetBullets();

            for (size_t t = 0; t < (int)m_TObjList.size(); t++)
            {
                TrObject* tObj = m_TObjList.at(t);

                if (tObj != NULL && tObj->GetIsDie() == false)
                {
                    tObj->Show(m_Screen);
                    tObj->DoBullet(m_Screen);
                }
            }

            pExpAds->Render(m_Screen);
            RenderMark();

            m_PauseMenu.Render(m_Screen);
            
            int is = m_PauseMenu.GetSelect();
            if (is == 0)
            {
                m_GameState = GAME_PLAYING;
                m_PauseMenu.SetIsSelect(-1);
                SetStateGame();
            }
            else if (is == 1)
            {
                m_PauseMenu.SetIsSelect(-1);
                bQuit = true;
            }
        }
        else if (m_GameState == GAME_END)
        {
            m_EndMenu.Render(m_Screen);
            int is = m_EndMenu.GetSelect();
            if (is == 0)
            {
                bQuit = true;
            }
        }
       
        SDL_RenderPresent(m_Screen);

        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
        {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
        }
    }
}

void GameMain::RenderMark()
{
    std::string sMark = std::to_string(m_Mark);
    std::string sPoint = "Point: " + sMark;
    m_TextMark.SetText(sPoint);
    m_TextMark.LoadFromRenderedText(m_Font30, m_Screen);
    m_TextMark.RenderText(m_Screen);

    std::string sMarkGoal = std::to_string(m_MarkGoal);
    std::string sSlash = "[" + sMarkGoal + "]";
    m_TextGoal.SetText(sSlash);
    m_TextGoal.LoadFromRenderedText(m_Font30, m_Screen);
    m_TextGoal.RenderText(m_Screen);
}


void GameMain::Close()
{
    m_Player.Free();
    m_Player.FreeData();

    m_Bkgn.Free();
    
    for (auto x : m_TObjList)
    {
        x->Free();
    }

    m_TObjList.clear();

    m_TextMark.Free();

    m_StartMenu.FreeData();
    m_PauseMenu.FreeData();
    m_EndMenu.FreeData();

    m_PlayerBlood.FreeData();

    if (m_Font30 != NULL)
    {
        TTF_CloseFont(m_Font30);
        m_Font30 = NULL;
    }

    SDL_DestroyRenderer(m_Screen);
    m_Screen = NULL;

    SDL_DestroyWindow(m_Window);
    m_Window = NULL;

    IMG_Quit();
    SDL_Quit();

}

void GameMain::FreeInstance()
{
    if (m_Instance != NULL)
    {
        delete m_Instance;
        m_Instance = NULL;
    }
}

void GameMain::SetStateGame()
{
    m_Player.SetStateGame(m_GameState);
    for (size_t t = 0; t < m_TObjList.size(); t++)
    {
        TrObject* tObj = m_TObjList.at(t);

        if (tObj != NULL && tObj->GetIsDie() == false)
        {
            tObj->SetStateGame(m_GameState);
        }
    }
}