#ifndef SOUNDMGR_H_INCLUDED
#define SOUNDMGR_H_INCLUDED

class Mix_Chunk;

class SoundMgr
{
public:
    enum TypeChunk
    {
        tcPing,
        tcPong,
        tcKnock
    };

    SoundMgr();
    ~SoundMgr();

    void playSound(TypeChunk typechunk);

private:
    Mix_Chunk *ping, *pong, *knock;
};

#endif