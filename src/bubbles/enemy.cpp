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
    originalHealth(random<int>(Enemy::MinHealth, Enemy::MaxHealth)),
    body(radius(health))
{
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(pos);
    body.setOrigin(radius(health), radius(health));

    setHealth(originalHealth);
}

void Enemy::update(float dt, sf::Vector2f const playerPos)
{
    if (0 == --updateCounter)
    {
        updateCounter = Enemy::MaxCounter;
        sf::Vector2f direction {playerPos - body.getPosition()};
        momentum = Enemy::SpeedOffset * direction / vectorAbs(direction);
    }

    body.move(momentum * dt);
}

void Enemy::draw() const
{
    Resource::window.draw(body);
}

bool Enemy::hit(std::shared_ptr<Bullet>& bullet)
{
    if (distanceSquared<float>(body.getPosition(), bullet->body.getPosition()) > body.getRadius() * body.getRadius())
    {
        return false;
    }

    bullet->used = true;
    setHealth(health - bullet->damage);
    return true;
}

void Enemy::die(Bubbles* game)
{
}

void Enemy::setHealth(int value)
{
    health = value;
    body.setRadius(radius(health));
    body.setOrigin(radius(health), radius(health));
}

int Enemy::killReward() const
{
    return originalHealth + random<int>(0, Enemy::MaxReward);
}

void Enemy::cooldown(float dt)
{
    if (strikeCooldown > 0.0f)
    {
        strikeCooldown = std::max(0.0f, strikeCooldown - dt);
    }
}

sf::Vector2f Enemy::borderPosition() const
{
    static const std::pair<float, float> xBorders {-Enemy::MaxHealth * 2, Resource::videoSize().x + Enemy::MaxHealth * 2};
    static const std::pair<float, float> yBorders {-Enemy::MaxHealth * 2, Resource::videoSize().y + Enemy::MaxHealth * 2};

    switch (std::rand() % 4)
    {
        case 0: return sf::Vector2f(xBorders.first, random<float>(yBorders.first, yBorders.second));
        case 1: return sf::Vector2f(xBorders.second, random<float>(yBorders.first, yBorders.second));
        case 2: return sf::Vector2f(random<float>(xBorders.first, xBorders.second), yBorders.first);
        default: return sf::Vector2f(random<float>(xBorders.first, xBorders.second), yBorders.second);
    }
}

MultiEnemy::MultiEnemy(): MultiEnemy(borderPosition())
{
}

MultiEnemy::MultiEnemy(sf::Vector2f pos): Enemy(pos)
{
    body.setFillColor(sf::Color::Red);
}

void MultiEnemy::die(Bubbles* game)
{
    game->enemies.emplace_back(std::make_shared<Enemy>(body.getPosition() + randomVector2<float>(-20.0f, 20.0f)));
    game->enemies.emplace_back(std::make_shared<Enemy>(body.getPosition() + randomVector2<float>(-20.0f, 20.0f)));
}

}