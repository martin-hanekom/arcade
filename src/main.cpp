#include <iostream>
#include "arcade.hpp"

int main(int argc, char** argv)
{
    std::cout << "Arcade" << std::endl;
    Arcade arcade;
    arcade.reload();
    return 0;
}