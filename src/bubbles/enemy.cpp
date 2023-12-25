#include <cstdlib>
#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Enemy::Enemy(): Enemy(borderPosition())
{
}

Enemy::Enemy(sf::Vector2f pos):
    health(random<int>(Enemy::MinHealth, Enemy::MaxHealth)),
    body(health)
{
    body.setPosition(pos);
}

void Enemy::update(float dt)
{
    body.move(momentum * dt);
}

void Enemy::draw() const
{
    Resource::window.draw(body);
}

sf::Vector2f Enemy::borderPosition() const
{
    switch (std::rand() % 4)
    {
        case 0: return sf::Vector2f(0.0f, random<float>(0.0f, Resource::videoSize().y));
        case 1: return sf::Vector2f(Resource::videoSize().x, random<float>(0.0f, Resource::videoSize().y));
        case 2: return sf::Vector2f(random<float>(0.0f, Resource::videoSize().x), 0.0f);
        default: return sf::Vector2f(random<float>(0.0f, Resource::videoSize().x), Resource::videoSize().y);
    }
}

}