#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "game.hpp"
#include "resource.hpp"
#include "bubbles.hpp"
#include "utils.hpp"

namespace game
{

Game::Game(sf::Vector2u videoSize, std::string const& title):
    main("Welcome to Arcade\n-----------------", Resource::font()),
    menu("Bubbles - <B>", Resource::font())
{
    Resource::window.create(sf::VideoMode(videoSize.x, videoSize.y), title);
    Resource::window.setVerticalSyncEnabled(true);
    Resource::window.setFramerateLimit(60);

    main.setCharacterSize(24u);
    main.setFillColor(sf::Color::White);
    setOriginMiddle(main);
    main.setPosition(Resource::videoSize() / 2.0f + sf::Vector2f(0.0f, -100.0f));

    menu.setCharacterSize(16u);
    menu.setFillColor(sf::Color::White);
    setOriginMiddle(menu);
    menu.setPosition(Resource::videoSize() / 2.0f);
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
        if (!game->handle(event))
        {
            game.reset(nullptr);
        }

        return true;
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
    static constexpr float fus {1000000.0f / 60.0f};

    if (game)
    {
        auto const start {std::chrono::high_resolution_clock::now()};
        game->update(dt);

        if (++counter == 60)
        {
            counter = 0;
            auto const end {std::chrono::high_resolution_clock::now()};
            std::chrono::duration<float, std::micro> interval {end - start};
            std::cout << "\r" << fus << " us | " << std::setw(8) << interval.count() << " us" << std::flush;
        }
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