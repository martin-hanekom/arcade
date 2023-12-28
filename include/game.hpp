#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

namespace game
{

class Game: public Entity
{
public:
    Game(sf::Vector2u videoSize, std::string const& title);
    void run();
    bool handle(sf::Event const& event);
    void update(float dt);
    void draw() const;

private:
    std::unique_ptr<Entity> game;
    sf::Text main;
    sf::Text menu;
    unsigned counter {0};
};

}

#endif