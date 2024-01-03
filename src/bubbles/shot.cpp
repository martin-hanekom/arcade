#include "bubbles/bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Shot::Shot(sf::Vector2f pos, sf::Vector2f momentum):
    momentum(momentum)
{
    body.setPosition(pos);
}

void Shot::update(float dt)
{
    body.move(momentum * dt);
}

void Shot::draw() const
{
    Resource::window.draw(body);
}

bool Shot::onScreen() const
{
    return Resource::onScreen(body.getPosition());
}

Bullet::Bullet(sf::Vector2f pos, float degrees):
    Shot(pos, polarVector<float>(Bullet::Speed, degrees, true))
{
    body.setRotation(degrees);
    body.setRadius(1.0f);
    body.setScale(5.0f, 1.0f);
    body.setFillColor(sf::Color::Yellow);
}

Grenade::Grenade(sf::Vector2f pos, float degrees):
    Shot(pos, polarVector<float>(Grenade::Speed, degrees, true))
{
    body.setRotation(degrees);
    body.setRadius(10.0f);
    body.setFillColor(sf::Color::Red);
}

}