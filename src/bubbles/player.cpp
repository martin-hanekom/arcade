#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Player::Player():
    pos(Resource::videoSize() / 2.0f),
    body(health),
    hat(HatRadius),
    gun(GunSize),
    info("Health", Resource::font())
{
    body.setFillColor(sf::Color::White);
    hat.setFillColor(sf::Color::Red);
    hat.setOrigin(HatRadius, HatRadius);
    gun.setFillColor(sf::Color::Magenta);
    gun.setOutlineColor(sf::Color::Yellow);

    info.setCharacterSize(12u);
    info.setFillColor(sf::Color::White);
    info.setPosition(sf::Vector2f(5.0f, 5.0f));

    setHealth(MaxHealth);
}

bool Player::handle(sf::Event const& event)
{
    momentum.x = 0.0f;
    momentum.y = 0.0f;

    if (Resource::isKeyPressed(Resource::Key::Left))
    {
        momentum.x = Speed;
    }

    if (Resource::isKeyPressed(Resource::Key::Right))
    {
        momentum.x = -Speed;
    }

    if (Resource::isKeyPressed(Resource::Key::Up))
    {
        momentum.y = -Speed;
    }

    if (Resource::isKeyPressed(Resource::Key::Down))
    {
        momentum.y = Speed;
    }

    if (sf::Event::MouseMoved == event.type)
    {
        sf::Vector2f direction = Resource::mousePos() - gunPos();
        gun.setRotation(toDegrees(vectorAngle(direction)) - 90.0f);
    }

    return true;
}

void Player::update(float dt)
{
    pos += momentum * dt;
    body.setPosition(pos);
    hat.setPosition(pos);
    gun.setPosition(pos);
}

void Player::draw() const
{
    Resource::window.draw(body);
    Resource::window.draw(hat);
    Resource::window.draw(gun);
    Resource::window.draw(info);
}

void Player::setHealth(int value)
{
    health = value;

    body.setRadius(health);
    body.setOrigin(health, health);
    gun.setOrigin(-health, 0);

    info.setString("Health: " + std::to_string(health));
}

sf::Vector2f Player::gunPos() const
{
    return pos + polarVector<float>(health, gun.getRotation(), true);
}

}