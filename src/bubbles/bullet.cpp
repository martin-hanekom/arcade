#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Bullet::Bullet(sf::Vector2f pos, float degrees) noexcept:
    body(BulletSize), momentum(polarVector<float>(Bullet::Speed, degrees, true))
{
    body.setPosition(pos);
    body.setRotation(degrees);
}

/*
Bullet::Bullet(Bullet&& other) noexcept:
    body(std::move(other.body)),
    momentum(std::move(other.momentum))
{
}

Bullet& Bullet::operator=(Bullet&& other) noexcept
{
    body = std::move(other.body);
    momentum = std::move(other.momentum);
    return *this;
}
*/

void Bullet::update(float dt)
{
    body.move(momentum * dt);
}

void Bullet::draw() const
{
    Resource::window.draw(body);
}

}