#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Player::Player():
    pos(Resource::videoSize() / 2.0f)
{
    body.setFillColor(sf::Color::Cyan);
    hat.setFillColor(sf::Color::Black);
    hat.setOrigin(Player::HatRadius, Player::HatRadius);

    gun.setFillColor(sf::Color::Magenta);
    gun.setOutlineColor(sf::Color::Yellow);

    setHealth(Player::MaxHealth);
}

Player::Player(int health): Player()
{
    setHealth(health);
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

bool Player::hit(std::shared_ptr<Enemy>& enemy)
{
    if (enemy->strikeCooldown > 0.0f)
    {
        return false;
    }

    float radii {body.getRadius() + enemy->body.getRadius()};
    if (distanceSquared<float>(body.getPosition(), enemy->body.getPosition()) > radii * radii)
    {
        return false;
    }

    setHealth(health - enemy->damage);
    enemy->strikeCooldown = Enemy::StrikeCooldown;
    return true;
}

void Player::setHealth(int value)
{
    health = value;
    body.setRadius(radius(health));
    body.setOrigin(radius(health), radius(health));
    gun.setOrigin(-radius(health), 0);
}

sf::Vector2f Player::gunPosition() const
{
    return pos + polarVector<float>(radius(health), gun.getRotation(), true);
}

void Player::rotateGun()
{
    sf::Vector2f direction {Resource::mousePos() - gunPosition()};
    gun.setRotation(toDegrees(vectorAngle(direction)) - Player::GunOffset);
}

}