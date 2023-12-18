#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
    virtual void update(sf::Int64 us) = 0;
    virtual void draw(sf::RenderWindow const& window) const = 0;
};

class Game
{
public:
    virtual void handle(sf::Event const& event) = 0;
    virtual void update(sf::Int64 us) = 0;
    virtual void draw(sf::RenderWindow const& window) const = 0;
};

#endif