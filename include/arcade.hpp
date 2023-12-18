#ifndef ARCADE_H
#define ARCADE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "bubbles.hpp"

class Arcade
{
public:
    Arcade(unsigned int width, unsigned int height, std::string const& title);
    void run();
    void update(sf::Int64 us);
    void draw() const;

private:
    sf::RenderWindow window;
    std::unique_ptr<Game> game;
};

#endif