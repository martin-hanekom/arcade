#ifndef BUBBLES_ENEMY_HPP
#define BUBBLES_ENEMY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "bubbles.hpp"
#include "shot.hpp"

namespace bubbles
{

class Enemy
{
public:
    Enemy(Bubbles* game);
    Enemy(Bubbles* game, sf::Vector2f pos, int health);
    void update(float dt, sf::Vector2f const playerPos);
    void draw() const;

    virtual void setup();
    virtual bool hit(std::shared_ptr<Bullet>& bullet);
    virtual void die();
    void setHealth(int value);
    int killReward() const;
    void cooldown(float dt);
    sf::Vector2f borderPosition() const;

    static constexpr int MaxHealth {5};
    static constexpr int MinHealth {1};
    static constexpr float SpeedRatio {10.0f};
    static constexpr float SpeedOffset {75.0f};
    static constexpr unsigned MaxCounter {5};
    static constexpr int MaxReward {2};
    static constexpr float StrikeCooldown {2.0f};

    int health;
    int originalHealth;
    unsigned updateCounter {MaxCounter};
    float damage {1};
    float strikeCooldown {0.0f};

    sf::Vector2f momentum;
    sf::CircleShape body;

protected:
    Bubbles* game;
};

class MultiEnemy: public Enemy
{
public:
    MultiEnemy(Bubbles* game);
    MultiEnemy(Bubbles* game, sf::Vector2f pos, int health);

    void setup() override;
    bool hit(std::shared_ptr<Bullet>& bullet) override;
};

class LifeEnemy: public Enemy
{
public:
    LifeEnemy(Bubbles* game);
    LifeEnemy(Bubbles* game, sf::Vector2f pos, int health);

    void setup() override;
    void die() override;
};

}

#endif