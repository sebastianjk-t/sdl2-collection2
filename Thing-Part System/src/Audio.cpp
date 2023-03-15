#include "Audio.h"

using namespace std;

Audio::Audio(Sound* s)
{
    if (s)
        addSound(s);
}

Audio::Audio(std::vector<Sound*> s)
{
    setSounds(s);
}

Audio::Audio(std::string file)
{
    addSound(file);
}

void Audio::setSounds(std::vector<Sound*> s)
{
    sounds = s;
    ownSounds = vector<bool>(sounds.size(), false);
}

void Audio::addSound(Sound* s)
{
    sounds.push_back(s);
    ownSounds.push_back(false);
}

void Audio::addSound(std::string file)
{
    sounds.push_back(new Sound(file));
    ownSounds.push_back(true);
}

bool Audio::playSound(int i)
{
    if (i < 0 || (i && i >= sounds.size()))
        return false;

    return sounds[i] -> play();
}

Audio::~Audio()
{
    for (int i = 0; i < sounds.size(); i++)
    {
        if (ownSounds[i])
            delete sounds[i];
    }
}