#include "resource.hpp"

sf::Font const& Resource::font()
{
    static sf::Font font;

    if (font.getInfo().family.empty())
    {
        if (!font.loadFromFile(std::string(Resource::fontfile)))
        {
            throw std::invalid_argument("Failed to load font");
        }
    }

    return font;
}

sf::Vector2f Resource::videoSize()
{
    return sf::Vector2f(Resource::window.getSize());
}

bool Resource::onScreen(sf::Vector2f const& pos)
{
    sf::Vector2f videoSize = Resource::videoSize();
    return (pos.x >= 0 && pos.x < videoSize.x &&
            pos.y >= 0 && pos.y < videoSize.y);
}

bool Resource::isKeyPressed(Resource::Key key)
{
    return sf::Keyboard::isKeyPressed(Resource::keys[key]);
}

sf::Vector2f Resource::mousePos()
{
    return sf::Vector2f(sf::Mouse::getPosition(Resource::window));
}