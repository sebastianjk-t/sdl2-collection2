#ifndef AUDIO
#define AUDIO

#include "Part.h"
#include "Sound.h"

class Audio : public Part
{
    public:
    Audio(Sound* s = nullptr);
    Audio(std::vector<Sound*> s);
    Audio(std::string file);

    void setSounds(std::vector<Sound*> s);
    
    void addSound(Sound* s);
    void addSound(std::string file);

    bool playSound(int i = 0);

    ~Audio();

    protected:
    std::vector<Sound*> sounds;
    std::vector<bool> ownSounds;
};

#endif