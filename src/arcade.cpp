#include "arcade.hpp"

Arcade::Arcade(unsigned int width, unsigned int height, std::string const& title)
    : window(sf::VideoMode(width, height), title)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void Arcade::run()
{
    game.reset(new Bubbles());
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                window.close();
            }
        }

        window.clear();
        update(clock.restart().asMicroseconds());
        draw();
        window.display();
    }
}

void Arcade::update(sf::Int64 us)
{
    game->update(us);
}

void Arcade::draw() const
{
    game->draw(window);
}