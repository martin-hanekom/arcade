#include "bubbles.hpp"

void Gun::draw(sf::RenderWindow& window) const
{

}

Player::Player(sf::Vector2f initPos)
    : pos(initPos), health(MaxHealth), body(MaxHealth), hat(HatRadius)
{
    body.setFillColor(sf::Color::White);
    hat.setFillColor(sf::Color::Red);
    hat.setOrigin(HatRadius, HatRadius);
    resize();
}

bool Player::handle(sf::Event const& event)
{
    return true;
}

void Player::update(sf::Int64 us)
{
    body.setPosition(pos);
    hat.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(body);
    window.draw(hat);
}

void Player::resize()
{
    body.setRadius(health);
    body.setOrigin(health, health);
} 

Menu::Menu(sf::Vector2f size, sf::Font const& font)
    : size(size), splash(std::string(splashText), font)
{
    splash.setCharacterSize(24u);
    splash.setFillColor(sf::Color::White);
    splash.setPosition(size / 2.0f);
    sf::FloatRect splashBounds {splash.getLocalBounds()};
    splash.setOrigin(splashBounds.width / 2.0f, splashBounds.height / 2.0f);
}

bool Menu::handle(sf::Event const& event)
{
    return true;
}

void Menu::draw(sf::RenderWindow& window) const
{
    window.draw(splash);
}

Bubbles::Bubbles(sf::Vector2f size, sf::Font const& font)
    : state(State::Pause), size(size), player(size / 2.0f), menu(size, font)
{
}

bool Bubbles::handle(sf::Event const& event)
{
    if (sf::Event::KeyPressed == event.type && sf::Keyboard::Space == event.key.code)
    {
        state = (State::Play == state) ? State::Pause : State::Play;
        return true;
    }

    switch (state)
    {
        case State::Pause:
            return menu.handle(event);
        case State::Play:
            return player.handle(event);
        default: return true;
    }
}

void Bubbles::update(sf::Int64 us)
{
    switch (state)
    {
        case State::Pause:
            menu.update(us);
            break;
        case State::Play:
            player.update(us);
            break;
        default: break;
    }
}

void Bubbles::draw(sf::RenderWindow& window) const
{
    switch (state)
    {
        case State::Pause:
            menu.draw(window);
            break;
        case State::Play:
            player.draw(window);
            break;
        default: break;
    }
}