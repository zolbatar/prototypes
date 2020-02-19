#include "assets.h"

Assets::Assets() {
};

Assets::~Assets() {
    for (auto m : mMusic) {
        delete m.second;
    }
}

void Assets::Load() {
    
    // Galaxies
    std::cout << "INIT: Loading galaxy textures...";
    LoadTextureSet("Galaxy", cNumberGalaxies, mGalaxies);
    std::cout << mGalaxies.size() << ", complete.\n";
    
    // Nebulae
    std::cout << "INIT: Loading nebula textures...";
    LoadTextureSet("Nebula", cNumberNebulae, mNebulae);
    std::cout << mNebulae.size() << ", complete.\n";
    
    // Music
    std::cout << "INIT: Loading soundtracks...";
    LoadMusicSet("Music", cNumberTracks, mMusic);
    std::cout << mMusic.size() << ", complete.\n";
}

void Assets::LoadTextureSet(const std::string prefix, const int count, std::unordered_map<int, sf::Texture> &map) {
	for (int i = 1; i <= count; ++i) {
        sf::Texture texture;
        std::ostringstream filename;
        filename << prefix << i << ".png";
        if (!texture.loadFromFile(resourcePath() + filename.str())) {
            std::cerr << "\n\nUnable to load texture: " << filename.str() + ". Quiting.\n";
            exit(EXIT_FAILURE);
        } else {
            texture.setSmooth(true);
            map[i] = texture;
        }
    }
}

void Assets::LoadMusicSet(const std::string prefix, const int count, std::unordered_map<int, sf::Music*> &map) {
	for (int i = 1; i <= count; ++i) {
        sf::Music *music = new sf::Music();
        std::ostringstream filename;
        filename << prefix << i << ".ogg";
        if (!music->openFromFile(resourcePath() + filename.str())) {
            std::cerr << "\n\nUnable to load music: " << filename.str() + ". Quiting.\n";
            exit(EXIT_FAILURE);
        } else {
            map[i] = music;
        }
    }
}

sf::Music* Assets::GetMusic(const int i) {
    return mMusic.at(i);
}

sf::Texture& Assets::GetGalaxy(const int i) {
    return mGalaxies.at(i);
}

sf::Texture& Assets::GetNebula(const int i) {
    return mNebulae.at(i);
}




