#ifndef BUBBLES_SHOT_HPP
#define BUBBLES_SHOT_HPP

#include <SFML/Graphics.hpp>

namespace bubbles
{

class Shot
{
public:
    Shot(sf::Vector2f pos, sf::Vector2f momentum);
    void update(float dt);
    void draw() const;
    bool onScreen() const;

    virtual int damage() const = 0;

    sf::CircleShape body;
    sf::Vector2f momentum;
    bool used {false};
};

class Bullet: public Shot
{
public:
    Bullet(sf::Vector2f pos, float degrees);

    static constexpr float Cooldown {0.2f};
    static constexpr float Speed {500.0f};
    int damage() const override { return 1; }
};

class Grenade: public Shot
{
public:
    Grenade(sf::Vector2f pos, float degrees);

    static constexpr float Cooldown {3.0f};
    static constexpr float Speed {200.0f};
    static constexpr int Price {10};

    int damage() const override { return 2; }
};

}

#endif