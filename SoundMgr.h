#ifndef SOUNDMGR_H_INCLUDED
#define SOUNDMGR_H_INCLUDED

#include "DebugParams.h"

class Mix_Chunk;

class SoundMgr
{
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

private:
    Mix_Chunk *ping, *pong, *knock, *crash;
};

#endif
