#include "soundtrack.h"

SoundTrack::SoundTrack() {
    
}

void SoundTrack::Play(Assets& assets) {
    sf::Music* music = assets.GetMusic(mTrackNumber);
    music->play();
}