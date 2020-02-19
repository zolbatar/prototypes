#ifndef __Generation_Ship__assets__
#define __Generation_Ship__assets__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "../library/non_copyable.h"

class Assets: public NonCopyable {
public:
    Assets();
    ~Assets();
    void Load();
	sf::Music* GetMusic(const int i);
	sf::Texture& GetGalaxy(const int i);
	sf::Texture& GetNebula(const int i);

	const int cNumberGalaxies = 14;
	const int cNumberNebulae = 25;
	const int cNumberTracks = 1;
private:
    std::unordered_map<int, sf::Texture> mGalaxies;
	std::unordered_map<int, sf::Texture> mNebulae;
	std::unordered_map<int, sf::Music*> mMusic;
	void LoadTextureSet(const std::string prefix, const int count, std::unordered_map<int, sf::Texture> &map);
	void LoadMusicSet(const std::string prefix, const int count, std::unordered_map<int, sf::Music*> &map);
};

#endif