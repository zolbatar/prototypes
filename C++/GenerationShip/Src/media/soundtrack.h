#ifndef __Generation_Ship__soundtrack__
#define __Generation_Ship__soundtrack__

#include <stdio.h>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "../assets/assets.h"

class SoundTrack: public NonCopyable {
public:
    SoundTrack();
    void Play(Assets& assets);
private:
    int mTrackNumber { 1 };
};

#endif
