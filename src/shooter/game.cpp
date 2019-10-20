#include "game.h"

#include <SFML/Window.hpp>

namespace shooter {

void Game::start() {
    sf::Window window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}

} // namespace shooter