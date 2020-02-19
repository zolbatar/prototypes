#include "game.h"

Game::Game(int w, int h) {
    mWidth = w;
    mHeight = h;
    mAssets.Load();
//    mSoundTrack.Play(mAssets.GetMusicMap());
    mGalaxy = new Galaxies(mRandom, mAssets, w, h);
    
    // Create a graphical text to display
    if (!font.loadFromFile(resourcePath() + "Square.ttf")) {
		exit(EXIT_FAILURE);
    }
    text = *new sf::Text("Hello SFML", font, 50);
    text.setColor(sf::Color::Yellow);
}

Game::~Game() {
    delete mGalaxy;
}

void Game::Generate() {
}

bool Game::NeedsToClose() {
    return mNeedsToClose;
}

void Game::Render(sf::RenderWindow& window) {
    window.clear(sf::Color(200, 0, 0));
    mGalaxy->Render(window);
    window.draw(text);
}

void Game::KeyEvent(sf::Event::KeyEvent& event) {
    switch (event.code) {
        case sf::Keyboard::Escape:
            mNeedsToClose = true;
            break;
        default:
            break;
    }
}

