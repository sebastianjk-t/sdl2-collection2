#ifndef AUDIBLE
#define AUDIBLE

#include "Sound.h"
#include <vector>

class Audible
{
    public:
    void setSounds(std::vector<Sound*> s);
    
    void addSound(Sound* s);
    void addSound(std::string file);

    bool playSound(int i = 0);

    protected:
    std::vector<Sound*> sounds;
};

#endif