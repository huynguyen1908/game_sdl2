
#include "Sound.h"


SoundGame* SoundGame::instance_ = NULL;

SoundGame::SoundGame()
{
    m_SoundState = MS_STOP;
}


SoundGame::~SoundGame()
{

}

SoundGame* SoundGame::GetInstance()
{
    if (instance_ == NULL)
    {
        instance_ = new SoundGame();
    }

    return instance_;
}

bool SoundGame::Init()
{

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        return false;
    }

    //gChunkKillRight = Mix_LoadWAV(gSKillRight);
    gChunkPause = Mix_LoadWAV(gSGamePause);
    gChunkFail = Mix_LoadWAV(gSGameFail);
    gChunkTimeout = Mix_LoadWAV(gSGameTimeout);
    gChunkExpBoom = Mix_LoadWAV(gSGameExpBoom);
    gChunkGun_One = Mix_LoadWAV(gSGameGunOne);
    gChunkGunLaser = Mix_LoadWAV(gSGameGunLaser);

    if (gChunkPause == NULL || /*gChunkKillRight == NULL ||*/
        gChunkFail == NULL || gChunkTimeout == NULL ||
        gChunkGun_One == NULL ||
        gChunkGunLaser == NULL ||
        gChunkExpBoom == NULL)
    {
        return false;
    }

    return true;
}

int SoundGame::PlaySoundGame(int soundType)
{
    int ret = 0;
    if (soundType == KILL_RIGHT)
    {
        Mix_PlayChannel(-1, gChunkKillRight, 0);
    }
    else if (soundType == GAME_PAUSE)
    {
        Mix_PlayChannel(-1, gChunkPause, 0);
    }
    else if (soundType == GAME_FAIL)
    {
        Mix_PlayChannel(-1, gChunkFail, 0);
    }
    else if (soundType == GAME_TIMEOUT)
    {
        Mix_PlayChannel(-1, gChunkTimeout, 0);
    }
    else if (soundType == GUN_ONE)
    {
        Mix_PlayChannel(-1, gChunkGun_One, 0);
    }
    else if (soundType == GUN_LASER)
    {
        Mix_PlayChannel(-1, gChunkGunLaser, 0);
    }
    else if (soundType == EXP_BOOM)
    {
        Mix_PlayChannel(-1, gChunkExpBoom, 0);
    }

    return ret;
}

int SoundGame::PlayMusic()
{
    if (m_SoundState == MS_STOP)
    {
        if (Mix_PlayMusic(g_Sound, -1) == -1)
        {
            return -1;
        }
        m_SoundState = MS_PLAY;
    }
    return 0;
}

void SoundGame::StopMusic()
{
    if (m_SoundState != MS_STOP)
    {
        Mix_HaltMusic();
        m_SoundState = MS_STOP;
    }
}

void SoundGame::PauseMusic()
{
    if (m_SoundState != MS_PAUSE)
    {
        Mix_PauseMusic();
        m_SoundState = MS_PAUSE;
    }
    else
    {
        Mix_ResumeMusic();
        m_SoundState = MS_PLAY;
    }
}

void SoundGame::FreeInstance()
{
    if (instance_ != NULL)
    {
        delete instance_;
        instance_ = NULL;
    }
}