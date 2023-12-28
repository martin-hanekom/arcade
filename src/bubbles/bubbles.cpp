#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Bubbles::Bubbles():
    splash("Bubbles Shooter\n---------------", Resource::font()),
    pauseMenu("Play - <Space>\n\nExit - <Esc>", Resource::font()),
    info("Health", Resource::font()),
    endSummary("Game over!", Resource::font())
{
    splash.setCharacterSize(24u);
    splash.setFillColor(sf::Color::White);
    setOriginMiddle(splash);
    splash.setPosition(Resource::videoSize() / 2.0f + sf::Vector2f(0.0f, -100.0f));

    pauseMenu.setCharacterSize(16u);
    pauseMenu.setFillColor(sf::Color::White);
    setOriginMiddle(pauseMenu);
    pauseMenu.setPosition(Resource::videoSize() / 2.0f);

    info.setCharacterSize(12u);
    info.setFillColor(sf::Color::White);
    info.setPosition(sf::Vector2f(5.0f, 5.0f));

    endSummary.setCharacterSize(16u);
    endSummary.setFillColor(sf::Color::White);
    setOriginMiddle(endSummary);
    endSummary.setPosition(Resource::videoSize() / 2.0f + sf::Vector2f(-50.0f, -100.0f));
}

bool Bubbles::handle(sf::Event const& event)
{
    return action[static_cast<unsigned>(state)]->handle(event);
}

void Bubbles::update(float dt)
{
    action[static_cast<unsigned>(state)]->update(dt);
}

void Bubbles::draw() const
{
    action[static_cast<unsigned>(state)]->draw();
}

void Bubbles::reset()
{
    player = std::move(Player());
    bullets.clear();
    enemies.clear();
    enemyCooldown = Bubbles::EnemyCooldown;
    bulletCooldown = Bubbles::BulletCooldown;
}

void Bubbles::end()
{
    state = Bubbles::State::End;
    endSummary.setString("  Game over!\n\nYou killed " + std::to_string(player.kills) + " enemies");
}

void Bubbles::spawnEnemy(float const dt)
{
    enemyCooldown -= dt;
    if (enemyCooldown < 0.0f)
    {
        switch (random<unsigned>(0, 2))
        {
            case 1:
                enemies.emplace_back(std::make_shared<MultiEnemy>());
                break;
            default:
                enemies.emplace_back(std::make_shared<Enemy>());
                break;
        }

        enemyCooldown = random<float>(Bubbles::EnemyCooldown / 2.0f, Bubbles::EnemyCooldown);
    }
}

void Bubbles::reload()
{
    if (player.cash >= Player::Reload)
    {
        player.cash -= Player::Reload;
        player.bullets += Player::Reload;
    }
}

void Bubbles::updateInfo()
{
    static Player oldPlayer {0};

    if (oldPlayer.cash == player.cash &&
        oldPlayer.health == player.health &&
        oldPlayer.bullets == player.bullets &&
        oldPlayer.kills == player.kills)
    {
        return;
    }

    info.setString("Cash: $" + std::to_string(player.cash) +
                   "\n\nHealth: " + std::to_string(player.health) +
                   "\n\nBullets: " + std::to_string(player.bullets) +
                   "\n\nKills: " + std::to_string(player.kills));

    oldPlayer.cash = player.cash;
    oldPlayer.health = player.health;
    oldPlayer.bullets = player.bullets;
    oldPlayer.kills = player.kills;
}

}