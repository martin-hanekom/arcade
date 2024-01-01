#include <cstdlib>
#include "bubbles/bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Enemy::Enemy(Bubbles* game):
    Enemy(game, borderPosition(), random<int>(Enemy::MinHealth, Enemy::MaxHealth))
{
}

Enemy::Enemy(Bubbles* game, sf::Vector2f pos, int health):
    game(game),
    originalHealth(health)
{
    body.setPosition(pos);
    setHealth(originalHealth);
    setup();
}

void Enemy::setup()
{
    body.setFillColor(sf::Color::Red + sf::Color::Yellow);
}

void Enemy::update(float dt, sf::Vector2f const playerPos)
{
    if (0 == --updateCounter)
    {
        updateCounter = Enemy::MaxCounter;
        sf::Vector2f direction {playerPos - body.getPosition()};
        momentum = (Enemy::SpeedOffset - Enemy::SpeedRatio * health) * direction / vectorAbs(direction);
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

void Enemy::die()
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

MultiEnemy::MultiEnemy(Bubbles* game):
    Enemy(game)
{
    setup();
}

MultiEnemy::MultiEnemy(Bubbles* game, sf::Vector2f pos, int health):
    Enemy(game, pos, health)
{
    setup();
}

void MultiEnemy::setup()
{
    body.setFillColor(sf::Color::Red);
}

bool MultiEnemy::hit(std::shared_ptr<Bullet>& bullet)
{
    if (!Enemy::hit(bullet))
    {
        return false;
    }

    game->enemies.emplace_back(std::make_shared<MultiEnemy>(game, body.getPosition() + polarVector<float>(radius(health) * 2, random<float>(0.0f, M_PI * 2)), health));
    return true;
}

LifeEnemy::LifeEnemy(Bubbles* game):
    Enemy(game)
{
    setup();
}

LifeEnemy::LifeEnemy(Bubbles* game, sf::Vector2f pos, int health):
    Enemy(game, pos, health)
{
    setup();
}

void LifeEnemy::setup()
{
    body.setFillColor(sf::Color::Magenta);
}

void LifeEnemy::die()
{
}

}