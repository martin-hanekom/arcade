#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include "entity.hpp"

namespace bubbles
{

class Enemy
{
public:
    Enemy(sf::Vector2f pos) noexcept;

    sf::RectangleShape body;
};

class Bullet: public Entity
{
public:
    Bullet(sf::Vector2f pos, float degrees) noexcept;

    void update(float dt);
    void draw() const;


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
    static constexpr unsigned HatRadius {10u};
    static constexpr float Speed {100.0f};
    inline static const sf::Vector2f GunSize {3.0f, 15.0f};
    static constexpr float GunOffset {90.0f};
    static constexpr float MaxCooldown {0.5f};

    int health {MaxHealth};
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

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    sf::Text splash;
    sf::Text info;
};

}

#endif