#include <functional>
#include <algorithm>
#include <vector>
#include <string>

#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Bubbles::Bubbles():
    splash("Press Space to Play!", Resource::font()),
    info("Health", Resource::font())
{
    splash.setCharacterSize(20u);
    splash.setFillColor(sf::Color::White);
    setOriginMiddle(splash);
    splash.setPosition(Resource::videoSize() / 2.0f);

    info.setCharacterSize(12u);
    info.setFillColor(sf::Color::White);
    info.setPosition(sf::Vector2f(5.0f, 5.0f));
}

bool Bubbles::handle(sf::Event const& event)
{
    if (sf::Event::KeyPressed == event.type ||
        sf::Event::KeyReleased == event.type)
    {
        return handleKey(event);
    }

    if (sf::Event::MouseMoved == event.type)
    {
        player.rotateGun();
    }

    if (sf::Event::MouseButtonPressed == event.type)
    {
        bullets.emplace_back(player.gunPosition(), player.gun.getRotation() + Player::GunOffset);
    }

    return true;
}

bool Bubbles::handleKey(sf::Event const& event)
{
    if (std::find(std::begin(Resource::keys), std::end(Resource::keys), event.key.code))
    {
        player.momentum.x = (Resource::isKeyPressed(Resource::Key::Left))
            ? Player::Speed
            : (Resource::isKeyPressed(Resource::Key::Right))
            ? -Player::Speed
            : 0.0f;

        player.momentum.y = (Resource::isKeyPressed(Resource::Key::Down))
            ? Player::Speed
            : (Resource::isKeyPressed(Resource::Key::Up))
            ? -Player::Speed
            : 0.0f;
    }

    if (sf::Keyboard::Escape == event.key.code)
    {
        return false;
    }

    return true;
}

void Bubbles::update(float dt)
{
    player.update(dt);
    std::for_each(bullets.begin(), bullets.end(), std::bind(&Bullet::update, std::placeholders::_1, dt));
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](Bullet bullet) { return !Resource::onScreen(bullet.body.getPosition()); }),
                  bullets.end());
    info.setString("Bullets: " + std::to_string(bullets.size()));
}

void Bubbles::draw() const
{
    player.draw();
    std::for_each(bullets.begin(), bullets.end(), std::bind(&Bullet::draw, std::placeholders::_1));
    Resource::window.draw(info);
}

}