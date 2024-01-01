#include "bubbles/bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

template<class T>
Shot::Shot(sf::Vector2f pos, float degrees):
    momentum(polarVector<float>(T::speed(), degrees, true))
{
    body.setPosition(pos);
    body.setRotation(degrees);
}

template<class T>
void Shot::update(float dt)
{
    body.move(momentum * dt);
}

template<class T>
void Shot::draw() const
{
    Resource::window.draw(body);
}

template<class T>
bool Shot::onScreen() const
{
    return Resource::onScreen(body.getPosition());
}

Bullet::Bullet(sf::Vector2f pos, float degrees):
    Shot(pos, degrees)
{
    body.setRadius(1.0f);
    body.setScale(5.0f, 1.0f);
    body.setFillColor(sf::Color::Yellow);
}

Grenade::Grenade(sf::Vector2f pos, float degrees):
    Shot(pos, degrees)
{
    body.setRadius(4.0f);
    body.setFillColor(sf::Color::Red);
}

}