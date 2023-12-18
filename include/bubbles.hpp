#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include "game.hpp"

class Bubbles: public Game
{
public:
    Bubbles();
    void handle(sf::Event const& event);
    void update(sf::Int64 us);
    void draw(sf::RenderWindow const& window) const;
};

#endif