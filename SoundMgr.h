#ifndef SOUNDMGR_H_INCLUDED
#define SOUNDMGR_H_INCLUDED

#include "DebugParams.h"
#include <SDL3_mixer/SDL_mixer.h>

class Mix_Chunk;

class SoundMgr
{
private:
    MIX_Mixer *m_mxr {nullptr};

    MIX_Audio *ping {nullptr},
        *pong {nullptr},
        *knock {nullptr},
        *crash {nullptr};

public:
    enum TypeChunk
    {
        tcPing,
        tcPong,
        tcKnock,
        tcCrash
    };

    SoundMgr();
    ~SoundMgr();

    void playSound(TypeChunk typechunk);    
};

#endif
