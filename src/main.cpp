#include <memory>
#include <SFML/Graphics.hpp>
#include "game.hpp"

int main(int argc, char** argv)
{
    game::Game game(sf::Vector2u(1600u, 900u), "Arcade");
    game.run();
    return 0;
}