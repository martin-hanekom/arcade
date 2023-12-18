#include <iostream>
#include "arcade.hpp"

int main(int argc, char** argv)
{
    std::cout << "Arcade" << std::endl;
    Arcade arcade(1200, 800, "Arcade");
    arcade.run();
    return 0;
}