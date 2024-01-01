#ifndef BUBBLES_SHOT_HPP
#define BUBBLES_SHOT_HPP

#include <SFML/Graphics.hpp>

namespace bubbles
{

class Shot
{
public:
    Shot(sf::Vector2f pos, float degrees);
    void update(float dt);
    void draw() const;
    bool onScreen() const;

    virtual float cooldown() const = 0;
    virtual float speed() const = 0;
    virtual int damage() const = 0;

    sf::CircleShape body;
    sf::Vector2f momentum;
    bool used {false};
};

class Bullet: public Shot
{
public:
    Bullet(sf::Vector2f pos, float degrees);

    float cooldown() const override { return 0.2f; }
    float speed() const override { return 500.0f; }
    int damage() const override { return 1; }
};

class Grenade: public Shot
{
public:
    Grenade(sf::Vector2f pos, float degrees);

    float cooldown() const override { return 3.0f; }
    float speed() const override { return 200.0f; }
    int damage() const override { return 2; }
};

}

#endif