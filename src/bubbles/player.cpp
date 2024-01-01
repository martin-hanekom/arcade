#include "bubbles/bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Player::Player():
    pos(Resource::videoSize() / 2.0f)
{
    body.setFillColor(Player::Skin);

    /*
    hat.setOutlineThickness(3.0f);
    hat.setOutlineColor(sf::Color::White);
    hat.setFillColor(Player::Skin);
    hat.setOrigin(Player::HatRadius, Player::HatRadius);

    eyes.first.setFillColor(sf::Color::White);
    eyes.first.setOrigin(Player::EyeRadius - 5.0f, Player::EyeRadius - 8.0f);
    eyes.second.setFillColor(sf::Color::White);
    eyes.second.setOrigin(Player::EyeRadius - 5.0f, Player::EyeRadius + 8.0f);
    */

    gun.setFillColor(sf::Color::White);

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
    //eyes.first.setPosition(pos);
    //eyes.second.setPosition(pos);
    //hat.setPosition(pos);
    gun.setPosition(pos);

    if (nullVector != momentum)
    {
        rotateGun();
    }
}

void Player::draw() const
{
    Resource::window.draw(body);
    Resource::window.draw(gun);
    //Resource::window.draw(hat);
    //Resource::window.draw(eyes.first);
    //Resource::window.draw(eyes.second);
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
    setSpeed();
}

void Player::setSpeed()
{
    sf::Vector2f const direction {(Resource::isKeyPressed(Resource::Key::Right))
            ? 1.0f
            : (Resource::isKeyPressed(Resource::Key::Left))
            ? -1.0f
            : 0.0f,
        (Resource::isKeyPressed(Resource::Key::Down))
            ? 1.0f
            : (Resource::isKeyPressed(Resource::Key::Up))
            ? -1.0f
            : 0.0f};

    momentum = (Player::SpeedOffset - Player::SpeedRatio * health) * unitVector(direction);
}

sf::Vector2f Player::gunPosition() const
{
    return pos + polarVector<float>(radius(health), gun.getRotation(), true);
}

void Player::rotateGun()
{
    float const direction {toDegrees(vectorAngle(Resource::mousePos() - gunPosition()))};
    gun.setRotation(direction - Player::GunOffset);
    //eyes.first.setRotation(direction);
    //eyes.second.setRotation(direction);
    //hat.setRotation(direction);
}

}