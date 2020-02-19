#ifndef __Generation_Ship__galaxies__
#define __Generation_Ship__galaxies__

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../assets/assets.h"
#include "../library/random.h"
#include "../library/maths.h"
#include "../library/non_copyable.h"
#include "galaxy.h"

class Galaxies: public NonCopyable {
public:
	Galaxies(Random& random, Assets& assets, int w, int h);
    ~Galaxies();
    void Render(sf::RenderWindow& window);
private:
    const double cGalaxyDensity = 0.0000075;
    int mNumberOfGalaxies;
    std::vector<Galaxy *> mGalaxies;
};

#endif