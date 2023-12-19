#include <iostream>
#include "resource.hpp"

sf::Font const& Resource::font()
{
    static sf::Font font;
    std::cout << font.getInfo().family << std::endl;
    if (font.getInfo().family.empty())
    {
        if (font.loadFromFile("data/font.ttf"))
        {
            throw std::invalid_argument("Failed to load font");
        }
    }
    return font;
}