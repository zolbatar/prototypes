#ifndef __Generation_Ship__galaxy__
#define __Generation_Ship__galaxy__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "../library/random.h"
#include "../library/non_copyable.h"

class Galaxy: public NonCopyable {
public:
    Galaxy(Random& random, float x, float y, float size, float scale, const sf::Texture& texture);
    ~Galaxy();
    void Render(sf::RenderWindow& window);
    float GetSize();
    float GetX();
    float GetY();
private:
    Random r;
    float mSize, mX, mY, mRot;
    sf::Sprite *mSprite;
};

#endif
