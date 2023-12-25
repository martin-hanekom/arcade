#include <cstdlib>
#include <ctime>
#include "game.hpp"
#include "resource.hpp"
#include "bubbles.hpp"
#include "utils.hpp"

namespace game
{

Game::Game(sf::Vector2u videoSize, std::string const& title):
    main("Welcome to Arcade!", Resource::font()),
    menu("Press B to play Bubbles", Resource::font())
{
    Resource::window.create(sf::VideoMode(videoSize.x, videoSize.y), title);
    Resource::window.setVerticalSyncEnabled(true);
    Resource::window.setFramerateLimit(60);

    main.setCharacterSize(30u);
    main.setFillColor(sf::Color::White);
    setOriginMiddle(main);
    main.setPosition(Resource::videoSize() / 2.0f + sf::Vector2f(0.0f, -30.0f));

    menu.setCharacterSize(14u);
    menu.setFillColor(sf::Color::White);
    setOriginMiddle(menu);
    menu.setPosition(Resource::videoSize() / 2.0f + sf::Vector2f(0.0f, 30.0f));
}

void Game::run()
{
    std::srand(std::time(nullptr));
    sf::Clock clock;

    while (Resource::window.isOpen())
    {
        sf::Event event;
        while (Resource::window.pollEvent(event))
        {
            if (!handle(event))
            {
                Resource::window.close();
            }
        }

        update(clock.restart().asSeconds());
        draw();
    }
}

bool Game::handle(sf::Event const& event)
{

    if (sf::Event::Closed == event.type)
    {
        return false;
    }

    if (game)
    {
        return game->handle(event);
    }

    if (sf::Event::KeyPressed == event.type)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
                return false;
            case sf::Keyboard::B:
                game.reset(new bubbles::Bubbles());
                return true;
            default: return true;
        }
    }

    return true;
}

void Game::update(float dt)
{
    if (game)
    {
        game->update(dt);
    }
}

void Game::draw() const
{
    Resource::window.clear();

    if (game)
    {
        game->draw();
    }
    else
    {
        Resource::window.draw(main);
        Resource::window.draw(menu);
    }

    Resource::window.display();
}

}