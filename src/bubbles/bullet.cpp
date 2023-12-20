#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Bullet::Bullet(sf::Vector2f pos, float angle):
    body(BulletSize), momentum(polarVector<float>(Bullet::Speed, angle))
{
    body.setPosition(pos);
    body.setRotation(angle);
}

void Bullet::update(float dt)
{
    body.move(momentum * dt);
}

void Bullet::draw() const
{
    Resource::window.draw(body);
}

}