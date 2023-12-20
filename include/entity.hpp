#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
    virtual bool handle(sf::Event const& event) { return true; }
    virtual void update(float dt) {}
    virtual void draw() const = 0;
};

#endif