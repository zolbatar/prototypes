#include "galaxy.h"

#include <ctime>

Galaxy::Galaxy(Random& random, float x, float y, float size, float scale, const sf::Texture& texture) {
    mSize = size;
    mX = x - (size / 2);
    mY = y - (size / 2);
    mSprite = new sf::Sprite(texture);
    mSprite->setPosition(mX, mY);
    mSprite->setScale(scale, scale);
    mSprite->setRotation(random.GetRandom0_1() * 360.0);
    mSprite->setOrigin(size, size);
    mRot = 0;
}

Galaxy::~Galaxy() {
    delete mSprite;
}

void Galaxy::Render(sf::RenderWindow& window) {
    mSprite->setRotation(mRot);
    window.draw(*mSprite);
    mRot += 2.5f;
}

float Galaxy::GetSize() {
    return mSize;
}

float Galaxy::GetX() {
    return mX;
}

float Galaxy::GetY() {
    return mY;
}

