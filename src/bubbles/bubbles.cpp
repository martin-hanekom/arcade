#include <functional>
#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Bubbles::Bubbles():
    splash("Press Space to Play!", Resource::font())
{
    splash.setCharacterSize(20u);
    splash.setFillColor(sf::Color::White);
    setOriginMiddle(splash);
    splash.setPosition(Resource::videoSize() / 2.0f);
}

bool Bubbles::handle(sf::Event const& event)
{
    if (sf::Event::KeyPressed == event.type)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
                return false;
            default: return player.handle(event);
        }
    }

    if (sf::Event::MouseButtonPressed == event.type)
    {
        bullets.emplace_back(player.gunPos(), player.gun.getRotation());
    }

    return player.handle(event);
}

void Bubbles::update(float dt)
{
    player.update(dt);
    std::for_each(bullets.begin(), bullets.end(), std::bind(&Bullet::update, std::placeholders::_1, dt));
}

void Bubbles::draw() const
{
    player.draw();
    std::for_each(bullets.begin(), bullets.end(), std::bind(&Bullet::draw, std::placeholders::_1));
}

}