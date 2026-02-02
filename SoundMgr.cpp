#include "SoundMgr.h"
#include <iostream>
#include <SDL3_mixer/SDL_mixer.h>

SoundMgr::SoundMgr()
{
    m_mxr = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    knock = MIX_LoadAudio(m_mxr, "assets/snd/knock.wav", true);
    ping = MIX_LoadAudio(m_mxr, "assets/snd/ping.wav", true);
    pong = MIX_LoadAudio(m_mxr, "assets/snd/pong.wav", true);
    crash = MIX_LoadAudio(m_mxr, "assets/snd/crash.wav", true);
}

SoundMgr::~SoundMgr()
{
    MIX_DestroyAudio(knock);
    MIX_DestroyAudio(ping);
    MIX_DestroyAudio(pong);
    MIX_DestroyAudio(crash);

    MIX_DestroyMixer(m_mxr);
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "SoundMgr end\n";
#endif // DEBUG_MESSAGES_SHOW
}

void SoundMgr::playSound(TypeChunk typeChunk)
{
    switch (typeChunk)
    {
    case tcPing: MIX_PlayAudio(m_mxr, ping); break;
    case tcPong: MIX_PlayAudio(m_mxr, pong); break;
    case tcKnock: MIX_PlayAudio(m_mxr, knock); break;
    case tcCrash: MIX_PlayAudio(m_mxr, crash); break;
    }
}
