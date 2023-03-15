#ifndef SOUND
#define SOUND

#include <SDL2/SDL.h>
#include <string>
#include <queue>

class Sound
{
    public:
    Sound(std::string name);
    
    bool set(std::string name);
    bool play(bool forced = false);

    void pause();
    void unpause();

    ~Sound();

    private:

    SDL_AudioDeviceID device;

    SDL_AudioSpec audioSpec;
    Uint8* waveStart;
    Uint32 waveLength;
};

#endif