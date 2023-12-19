#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
    virtual bool handle(sf::Event const& event) { return true; }
    virtual void update(sf::Int64 us) {}
    virtual void draw(sf::RenderWindow& window) const = 0;
};

#endif