#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include "entity.hpp"

namespace bubbles
{

class Enemy: public Entity
{
public:
    Enemy();
    Enemy(sf::Vector2f pos);
    void update(float dt);
    void draw() const;

    sf::Vector2f borderPosition() const;
    static int randomHealth();

    static constexpr int MaxHealth {25};
    static constexpr int MinHealth {5};

    int health;
    sf::Vector2f momentum;
    sf::CircleShape body;
};

class Bullet: public Entity
{
public:
    Bullet(sf::Vector2f pos, float degrees);
    void update(float dt);
    void draw() const;

    bool onScreen() const;

    static constexpr float Speed {1000.0f};
    inline static const sf::Vector2f BulletSize {5.0f, 1.0f};

    sf::RectangleShape body;
    sf::Vector2f momentum;
};

class Player: public Entity
{
public:
    Player();
    void update(float dt);
    void draw() const;

    sf::Vector2f gunPosition() const;
    void setHealth(int value);
    void rotateGun();

    static constexpr int MaxHealth {25};
    static constexpr int HealthOffset {5};
    static constexpr unsigned HatRadius {10u};
    static constexpr float Speed {100.0f};
    inline static const sf::Vector2f GunSize {3.0f, 15.0f};
    static constexpr float GunOffset {90.0f};
    static constexpr float MaxCooldown {0.5f};

    int health {MaxHealth};
    unsigned bullets {15};
    sf::Vector2f pos;
    sf::Vector2f momentum;
    sf::CircleShape body {MaxHealth};
    sf::CircleShape hat {HatRadius};
    sf::RectangleShape gun {Player::GunSize};
};

class Bubbles: public Entity
{
public:
    Bubbles();
    bool handle(sf::Event const& event);
    void update(float dt);
    void draw() const;

private:
    bool handleKey(sf::Event const& event);
    void updateInfo();

    static constexpr float EnemyCooldown {2.0f};
    static constexpr float BulletCooldown {0.3f};

    unsigned round {1};
    float enemyCooldown {EnemyCooldown};
    float bulletCooldown {BulletCooldown};

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    sf::Text splash;
    sf::Text info;
};

}

#endif