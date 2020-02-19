#ifndef __Generation_Ship__game__
#define __Generation_Ship__game__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "../assets/assets.h"
#include "../media/soundtrack.h"
#include "../render/galaxies.h"
#include "../library/random.h"

class Game: public NonCopyable {
public:
	Game(int w, int h);
    ~Game();
    void Generate();
    void Render(sf::RenderWindow& window);
    void KeyEvent(sf::Event::KeyEvent& event);
    bool NeedsToClose();
private:
    Assets mAssets;
    SoundTrack mSoundTrack;
    Random mRandom;
    Galaxies *mGalaxy;
	int mWidth, mHeight;
    bool mNeedsToClose { false };

    sf::Font font;
    sf::Text text;
};

#endif
