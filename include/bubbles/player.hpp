#ifndef BUBBLES_PLAYER_HPP
#define BUBBLES_PLAYER_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "enemy.hpp"

namespace bubbles
{

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
    void setSpeed();
    void rotateGun();

    inline static const sf::Color Skin {61u, 144u, 39u};
    static constexpr int MaxHealth {4};
    static constexpr float EyeRadius {5.0f};
    static constexpr unsigned HatRadius {5u};
    static constexpr float SpeedRatio {10.0f};
    static constexpr float SpeedOffset {150.0f};
    inline static const sf::Vector2f GunSize {3.0f, 15.0f};
    static constexpr float GunOffset {90.0f};
    static constexpr float MaxCooldown {0.5f};
    static constexpr unsigned Reload {50};

    int health {MaxHealth};
    int cash {0};
    unsigned bullets {50};
    unsigned kills {0};
    std::pair<float, float> bulletCooldown {0.0f, 0.0f};

    sf::Vector2f pos;
    sf::Vector2f momentum;
    sf::CircleShape body {MaxHealth};
    std::pair<sf::CircleShape, sf::CircleShape> eyes {EyeRadius, EyeRadius};
    sf::CircleShape hat {HatRadius};
    sf::RectangleShape gun {Player::GunSize};
};

}

#endif