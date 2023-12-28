#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include <iostream>
#include <memory>
#include <array>
#include <stack>
#include <list>
#include <string>
#include "entity.hpp"

namespace bubbles
{

class Bubbles;

class Bullet
{
public:
    Bullet(sf::Vector2f pos, float degrees);
    void update(float dt);
    void draw() const;

    bool onScreen() const;

    static constexpr float Speed {500.0f};
    inline static const sf::Vector2f BulletSize {5.0f, 2.0f};
    static constexpr int Damage {1};

    sf::RectangleShape body;
    sf::Vector2f momentum;
    float damage {Damage};
    bool used {false};
};

class Enemy
{
public:
    Enemy();
    Enemy(sf::Vector2f pos);
    void update(float dt, sf::Vector2f const playerPos);
    void draw() const;

    bool hit(std::shared_ptr<Bullet>& bullet);
    virtual void die(Bubbles* game);
    void setHealth(int value);
    int killReward() const;
    void cooldown(float dt);
    sf::Vector2f borderPosition() const;

    static constexpr int MaxHealth {5};
    static constexpr int MinHealth {1};
    static constexpr float SpeedOffset {50.0f};
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
};

class MultiEnemy: public Enemy
{
public:
    MultiEnemy();
    MultiEnemy(sf::Vector2f pos);

    void die(Bubbles* game) override;
};

class Player
{
public:
    Player();
    Player(int health);
    void update(float dt);
    void draw() const;

    bool hit(std::shared_ptr<Enemy>& enemy);
    sf::Vector2f gunPosition() const;
    void setHealth(int value);
    void rotateGun();

    static constexpr int MaxHealth {4};
    static constexpr unsigned HatRadius {8u};
    static constexpr float Speed {100.0f};
    inline static const sf::Vector2f GunSize {3.0f, 15.0f};
    static constexpr float GunOffset {90.0f};
    static constexpr float MaxCooldown {0.5f};
    static constexpr unsigned Reload {10};

    int health {MaxHealth};
    int cash {0};
    unsigned bullets {50};
    unsigned kills {0};

    sf::Vector2f pos;
    sf::Vector2f momentum;
    sf::CircleShape body {MaxHealth};
    sf::CircleShape hat {HatRadius};
    sf::RectangleShape gun {Player::GunSize};
};

class Action: public Entity
{
public:
    Action(Bubbles* game);
    virtual bool handle(sf::Event const& event) { return true; };
    virtual void update(float dt) {};
    virtual void draw() const {};

    Bubbles* game;
};

class SetupAction: public Action
{
public:
    SetupAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void draw() const override;
};

class PlayAction: public Action
{
public:
    PlayAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void update(float dt) override;
    void draw() const override;
};

class PauseAction: public Action
{
public:
    PauseAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void draw() const override;
};

class EndAction: public Action
{
public:
    EndAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void draw() const override;
};

class Bubbles: public Entity
{
public:
    Bubbles();
    bool handle(sf::Event const& event);
    void update(float dt);
    void draw() const;

    void reset();
    void end();
    void spawnEnemy(float const dt);
    void reload();
    void updateInfo();

    enum class State: unsigned
    {
        Setup = 0u,
        Play,
        Pause,
        End
    };

    static constexpr float EnemyCooldown {2.0f};
    static constexpr float BulletCooldown {0.3f};

    std::array<std::unique_ptr<Action>, 4> const action {
        std::make_unique<SetupAction>(this),
        std::make_unique<PlayAction>(this),
        std::make_unique<PauseAction>(this),
        std::make_unique<EndAction>(this)
    };
    State state {State::Setup};

    unsigned round {1};
    float enemyCooldown {EnemyCooldown};
    float bulletCooldown {BulletCooldown};

    Player player;
    std::list<std::shared_ptr<Bullet>> bullets;
    std::list<std::shared_ptr<Enemy>> enemies;

    sf::Text splash;
    sf::Text pauseMenu;
    sf::Text info;
    sf::Text endSummary;
};

}

#endif