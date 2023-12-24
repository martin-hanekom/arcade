#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Player::Player():
    pos(Resource::videoSize() / 2.0f)
{
    body.setFillColor(sf::Color::White);
    hat.setFillColor(sf::Color::Red);
    hat.setOrigin(HatRadius, HatRadius);

    gun.setFillColor(sf::Color::Magenta);
    gun.setOutlineColor(sf::Color::Yellow);

    setHealth(MaxHealth);
}

void Player::update(float dt)
{
    pos += momentum * dt;
    body.setPosition(pos);
    hat.setPosition(pos);
    gun.setPosition(pos);

    if (nullVector != momentum)
    {
        rotateGun();
    }
}

void Player::draw() const
{
    Resource::window.draw(body);
    Resource::window.draw(hat);
    Resource::window.draw(gun);
}

void Player::setHealth(int value)
{
    health = value;

    body.setRadius(health);
    body.setOrigin(health, health);
    gun.setOrigin(-health, 0);
}

sf::Vector2f Player::gunPosition() const
{
    return pos + polarVector<float>(health, gun.getRotation(), true);
}

void Player::rotateGun()
{
    sf::Vector2f direction {Resource::mousePos() - gunPosition()};
    gun.setRotation(toDegrees(vectorAngle(direction)) - Player::GunOffset);
}

}