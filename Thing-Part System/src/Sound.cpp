#include "Sound.h"

using namespace std;

Sound::Sound(string file)
{
    SDL_LoadWAV(("assets/" + file).c_str(), &audioSpec, &waveStart, &waveLength);
    device = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
}

bool Sound::set(string file)
{
    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(waveStart);

    if (SDL_LoadWAV(("assets/" + file).c_str(), &audioSpec, &waveStart, &waveLength) == nullptr)
        return false;

    device = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);

    return true;
}

bool Sound::play(bool forced)
{
    if (!forced && SDL_GetQueuedAudioSize(device))
        return false;

    unpause();
    SDL_QueueAudio(device, waveStart, waveLength);

    return true;
}

void Sound::pause()
{
    SDL_PauseAudioDevice(device, true);
}

void Sound::unpause()
{
    SDL_PauseAudioDevice(device, false);
}

Sound::~Sound()
{
    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(waveStart);
}