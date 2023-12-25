#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Bullet::Bullet(sf::Vector2f pos, float degrees):
    body(BulletSize), momentum(polarVector<float>(Bullet::Speed, degrees, true))
{
    body.setPosition(pos);
    body.setRotation(degrees);
}

void Bullet::update(float dt)
{
    body.move(momentum * dt);
}

void Bullet::draw() const
{
    Resource::window.draw(body);
}

bool Bullet::onScreen() const
{
    return Resource::onScreen(body.getPosition());
}

}