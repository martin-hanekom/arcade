#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <array>
#include <SFML/Graphics.hpp>

class Resource
{
public:
    enum Key: unsigned
    {
        Left = 0u,
        Right,
        Up,
        Down,
        Reload,
    };

    static sf::Font const& font();
    static sf::Vector2f videoSize();
    static bool onScreen(sf::Vector2f const& pos);
    static bool isKeyPressed(Key key);
    static sf::Vector2f mousePos();

    inline static sf::RenderWindow window;
    inline static constexpr std::array<sf::Keyboard::Key, 5> keys {
        sf::Keyboard::A,
        sf::Keyboard::E,
        sf::Keyboard::Comma,
        sf::Keyboard::O,
        sf::Keyboard::P
    };
    inline static std::array<sf::Keyboard::Key, 5>::const_iterator const moveEnd {std::begin(keys) + 4};

    static constexpr std::string_view fontfile {"data/font.ttf"};
};

#endif