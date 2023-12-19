#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace game
{

class Menu: public Entity
{
public:
    Menu(sf::Vector2f size, sf::Font const& font);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Text main;
    sf::Text menu;
};

class Game
{
public:
    Game(sf::Vector2f size, std::string const& title);
    void run();

private:
    sf::Vector2f size;
    sf::RenderWindow window;
    Menu menu;
    std::unique_ptr<Entity> game;
};

}

#endif