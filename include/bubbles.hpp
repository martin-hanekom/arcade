#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include "entity.hpp"

namespace bubbles
{

class Bullet: public Entity
{
public:
    Bullet(sf::Vector2f pos, float angle);
    void update(float dt);
    void draw() const;

    static constexpr float Speed {1000.0f};
    inline static const sf::Vector2f BulletSize {1.0f, 5.0f};

    sf::RectangleShape body;
    sf::Vector2f const momentum;
};

class Player: public Entity
{
public:
    Player();
    bool handle(sf::Event const& event);
    void update(float dt);
    void draw() const;
    void setHealth(int value);
    sf::Vector2f gunPos() const;

    static constexpr unsigned MaxHealth {25u};
    static constexpr unsigned HatRadius {10u};
    inline static const sf::Vector2f GunSize {3.0f, 15.0f};
    static constexpr float Speed {100.0f};

    int health;
    sf::Vector2f pos;
    sf::Vector2f momentum;
    sf::CircleShape body;
    sf::CircleShape hat;
    sf::RectangleShape gun;
    sf::Text info;
};

class Bubbles: public Entity
{
public:
    Bubbles();
    bool handle(sf::Event const& event);
    void update(float dt);
    void draw() const;

private:
    Player player;
    std::vector<Bullet> bullets;
    sf::Text splash;
};

}

#endif