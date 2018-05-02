#include "SoundMgr.h"

#include <SDL2/SDL_mixer.h>

SoundMgr::SoundMgr()
{
    knock = Mix_LoadWAV("assets/snd/knock.wav");
    ping = Mix_LoadWAV("assets/snd/ping.wav");
    pong = Mix_LoadWAV("assets/snd/pong.wav");
}

SoundMgr::~SoundMgr()
{
    Mix_FreeChunk(knock);
    Mix_FreeChunk(ping);
    Mix_FreeChunk(pong);
}

void SoundMgr::playSound(TypeChunk typeChunk)
{
    switch (typeChunk)
    {
    case tcPing: Mix_PlayChannel(-1, ping, 0); break;
    case tcPong: Mix_PlayChannel(-1, pong, 0); break;
    case tcKnock: Mix_PlayChannel(-1, knock, 0); break;
    }
}