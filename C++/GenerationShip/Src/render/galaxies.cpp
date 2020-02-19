#include "galaxies.h"

Galaxies::Galaxies(Random& random, Assets& assets, int w, int h) {
    mNumberOfGalaxies = (double)w * (double)h * cGalaxyDensity;
    if (mNumberOfGalaxies > assets.cNumberGalaxies) {
        mNumberOfGalaxies = assets.cNumberGalaxies;
    }

    // Vector of all possible galaxy textures
	std::vector<int> n;
	for (int i = 1; i <= assets.cNumberGalaxies; i++) {
        n.push_back(i);
    }
    
    // Create galaxies
	for (int i = 0; i < mNumberOfGalaxies; i++) {
		int ra = random.GetRandom(n.size());
		int type = n.at(ra);
        n.erase(n.begin() + ra);
        float size = random.GetRandom0_1() * 256 + 16;
        float scale = size / 512;
        
        // Want? Near other galaxies?
        bool want;
        float x, y;
        do {
            x = (random.GetRandom0_1() * (w - 300)) + 150;
            y = (random.GetRandom0_1() * (h - 300)) + 150;
            
            // Too close?
            want = true;
            for (auto g : mGalaxies) {
                if (DistanceBetweenPoints(x, y, g->GetX(), g->GetY()) < (g->GetSize() + size) * 0.75) {
                    want = false;
                    break;
                }
            }
        } while (!want);
        
        // Add
        mGalaxies.push_back(new Galaxy {random, x, y, size, scale, assets.GetGalaxy(type)});
    }
    std::cout << "INIT: Galaxies generated.\n";
}

Galaxies::~Galaxies() {
    for (auto g : mGalaxies) {
        delete g;
    }
}

void Galaxies::Render(sf::RenderWindow& window) {
    for (auto g : mGalaxies) {
        g->Render(window);
    }
}
