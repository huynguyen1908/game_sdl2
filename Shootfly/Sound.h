

#ifndef SOUND_H_
#define SOUND_H_

#include "define.h"

static Mix_Music* g_Sound = NULL;
static Mix_Chunk* gChunkKillRight = NULL;
static Mix_Chunk* gChunkGun_One = NULL;
static Mix_Chunk* gChunkPause = NULL;
static Mix_Chunk* gChunkFail = NULL;
static Mix_Chunk* gChunkTimeout = NULL;
static Mix_Chunk* gChunkGunLaser = NULL;
static Mix_Chunk* gChunkExpBoom = NULL;

static char gSKillRight[] = { "sound\\kill_right.wav" };
static char gSGamePause[] = { "sound\\pause.wav" };
static char gSGameFail[] = { "sound\\game_fail.wav" };
static char gSGameTimeout[] = { "sound\\game_time_out.wav" };
static char gSGameGunOne[] = { "sound\\gun_one.wav" };
static char gSGameGunLaser[] = { "sound\\gun_laser.wav" };
static char gSGameExpBoom[] = { "sound\\explo.wav" };

class SoundGame
{
public:
    SoundGame();
    ~SoundGame();

    enum SoundType
    {
        KILL_RIGHT = 650,
        GAME_PAUSE,
        EXP_BOOM,
        GAME_FAIL,
        GAME_TIMEOUT,
        GUN_ONE,
        GUN_LASER,
    };

    enum MusicState
    {
        MS_PLAY = 0,
        MS_STOP = 1,
        MS_PAUSE = 2,
    };

    static SoundGame* GetInstance();
    bool Init();
    int PlaySoundGame(int soundType);
    int PlayMusic();
    void StopMusic();
    void PauseMusic();
    int GetMusicState() const { m_SoundState; };
    void SetMusicState(int state) { m_SoundState = state; }
    void FreeInstance();
private:
    static SoundGame* instance_;
    int m_SoundState;
};

#endif


