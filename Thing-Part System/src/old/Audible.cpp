#include "Audible.h"

void Audible::setSounds(std::vector<Sound*> s)
{
    sounds = s;
}

void Audible::addSound(Sound* s)
{
    sounds.push_back(s);
}

void Audible::addSound(std::string file)
{
    sounds.push_back(new Sound(file));
}

bool Audible::playSound(int i)
{
    if (i < 0 || (i && i >= sounds.size()))
        return false;

    return sounds[i] -> play();
}