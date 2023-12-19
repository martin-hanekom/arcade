#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include <iostream>
#include <unordered_map>
#include <string>

#include "entity.hpp"

class Gun: public Entity
{
public:
    void draw(sf::RenderWindow& window) const override;

private:
    sf::RectangleShape body;
};

class Player: public Entity
{
public:
    Player(sf::Vector2f initPos);
    bool handle(sf::Event const& event) override;
    void update(sf::Int64 us) override;
    void draw(sf::RenderWindow& window) const override;
    void resize();

private:
    static constexpr unsigned MaxHealth {25u};
    static constexpr unsigned HatRadius {10u};

    sf::CircleShape body;
    sf::CircleShape hat;
    Gun gun;
    sf::Vector2f pos;
    unsigned health;
};

class Menu: public Entity
{
public:
    Menu(sf::Vector2f size, sf::Font const& font);
    bool handle(sf::Event const& event) override;
    void draw(sf::RenderWindow& window) const override;
    
private:
    static std::string_view constexpr splashText {"Press Space to Play!"};

    void setSplash(std::string const& text);

    sf::Text splash;
    sf::Vector2f size;
};

class Bubbles: public Entity
{
public:
    enum class State: unsigned
    {
        Pause,
        Play,
    };

    Bubbles(sf::Vector2f size, sf::Font const& font);
    bool handle(sf::Event const& event) override;
    void update(sf::Int64 us) override;
    void draw(sf::RenderWindow& window) const override;

private:
    State state;
    Player player;
    Menu menu;
    sf::Vector2f size;
};

#endif