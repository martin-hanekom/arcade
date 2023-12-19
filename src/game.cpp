#include "game.hpp"
#include "bubbles.hpp"

namespace game
{

Menu::Menu(sf::Vector2f size, sf::Font const& font):
    main("Welcome to Arcade!", font),
    menu("Press B to play Bubbles", font)
{
    main.setCharacterSize(20u);
    main.setFillColor(sf::Color::White);
    menu.setCharacterSize(16u);
    menu.setFillColor(sf::Color::White);
    menu.setPosition(sf::Vector2f(0.0f, 22.0f));
}

void Menu::draw(sf::RenderWindow& window) const
{
    window.draw(main);
    window.draw(menu);
}

Game::Game(sf::Vector2f size, std::string const& title):
    size(size), window(sf::VideoMode(size.x, size.y), title)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    if (!font.loadFromFile(fontfile))
    {
        throw std::invalid_argument("Font not loaded");
    }
}

void Game::run()
{
    sf::Clock clock;
    sf::Font font;

    Menu menu {size, font};
    std::unique_ptr<Entity> game {};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                window.close();
            }
            else if (game)
            {
                game->handle(event);
            }
            else
            {
                if (sf::Event::KeyPressed == event.type)
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::B:
                            game = std::make_unique<Bubbles>(size, font);
                            break;
                    }
                }
            }
        }

        window.clear();
        state.top()->update(clock.restart().asMicroseconds());
        state.top()->draw(window);
        window.display();
}

}