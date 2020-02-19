#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "game/game.h"

/*
 
 use:
 
 m for members
 c for constants/readonlys
 p for pointer (and pp for pointer to pointer)
 v for volatile
 s for static
 i for indexes and iterators
 e for events
 
 */

int main(int, char const**)
{
	int width = 1366, height = 768;
    std::cout << "INIT: Resource path = " << resourcePath() << std::endl;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Generation Ship");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create game and load assets
    Game game(width, height);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || game.NeedsToClose()) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed) {
                game.KeyEvent(event.key);
            }
        }

        // Render
        game.Render(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
