#include <functional>
#include <algorithm>
#include <numeric>
#include "bubbles.hpp"
#include "resource.hpp"
#include "utils.hpp"

namespace bubbles
{

Action::Action(Bubbles* game): game(game)
{
}

SetupAction::SetupAction(Bubbles* game): Action(game)
{
}

bool SetupAction::handle(sf::Event const& event)
{
    if (sf::Event::KeyPressed == event.type)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
                return false;
            case sf::Keyboard::Space:
                game->reset();
                game->state = Bubbles::State::Play;
                return true;
            default:
                return true;
        }
    }

    return true;
}

void SetupAction::draw() const
{
    Resource::window.draw(game->splash);
    Resource::window.draw(game->pauseMenu);
}

PlayAction::PlayAction(Bubbles* game): Action(game)
{
}

bool PlayAction::handle(sf::Event const& event)
{

    if (sf::Event::KeyPressed == event.type)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Space:
                game->state = Bubbles::State::Pause;
                return true;
            case Resource::keys[Resource::Key::Reload]:
                game->reload();
                return true;
            default:
                break;
        }
    }

    if ((sf::Event::KeyPressed == event.type ||
        sf::Event::KeyReleased == event.type) &&
        std::find(std::begin(Resource::keys), Resource::moveEnd, event.key.code))
    {
        game->player.momentum.x = (Resource::isKeyPressed(Resource::Key::Right))
            ? Player::Speed
            : (Resource::isKeyPressed(Resource::Key::Left))
            ? -Player::Speed
            : 0.0f;

        game->player.momentum.y = (Resource::isKeyPressed(Resource::Key::Down))
            ? Player::Speed
            : (Resource::isKeyPressed(Resource::Key::Up))
            ? -Player::Speed
            : 0.0f;

        return true;
    }

    if (sf::Event::MouseMoved == event.type)
    {
        game->player.rotateGun();
        return true;
    }

    if (sf::Event::MouseButtonPressed == event.type)
    {
        if (game->player.bullets > 0)
        {
            --game->player.bullets;
            game->bullets.emplace_back(std::make_shared<Bullet>(game->player.gunPosition(), game->player.gun.getRotation() + Player::GunOffset));
        }

        return true;
    }

    return true;
}

void PlayAction::update(float dt)
{
    //bulletCooldown -= dt;

    game->player.update(dt);
    std::for_each(game->enemies.begin(), game->enemies.end(), std::bind(&Enemy::update, std::placeholders::_1, dt, game->player.pos));
    std::for_each(game->bullets.begin(), game->bullets.end(), std::bind(&Bullet::update, std::placeholders::_1, dt));

    game->bullets.remove_if(std::not_fn(std::bind(&Bullet::onScreen, std::placeholders::_1)));
    std::for_each(game->bullets.begin(), game->bullets.end(), [&enemies = game->enemies](std::shared_ptr<Bullet>& bullet) {
        std::for_each(enemies.begin(), enemies.end(), [&bullet](std::shared_ptr<Enemy>& enemy) { enemy->hit(bullet); });
    });
    game->bullets.remove_if([](std::shared_ptr<Bullet> const& bullet) { return bullet->used; });

    auto constexpr noHealth = [](std::shared_ptr<Enemy> const& enemy) { return enemy->health <= 0; };

    std::list<std::shared_ptr<Enemy>> dead;
    std::copy_if(game->enemies.begin(), game->enemies.end(), std::back_inserter(dead), noHealth);
    std::for_each(dead.begin(), dead.end(), std::bind(&Enemy::die, std::placeholders::_1, game));

    game->player.kills += dead.size();
    game->player.cash = std::accumulate(dead.begin(), dead.end(), game->player.cash,
        [](int& a, std::shared_ptr<Enemy> const& enemy) { return a + enemy->killReward(); });
    game->enemies.remove_if(noHealth);

    std::for_each(game->enemies.begin(), game->enemies.end(), std::bind(&Enemy::cooldown, std::placeholders::_1, dt));
    std::for_each(game->enemies.begin(), game->enemies.end(), std::bind(&Player::hit, &game->player, std::placeholders::_1));
    if (game->player.health <= 0)
    {
        game->end();
        return;
    }

    game->spawnEnemy(dt);
    game->updateInfo();
}

void PlayAction::draw() const
{
    game->player.draw();
    std::for_each(game->enemies.cbegin(), game->enemies.cend(), std::bind(&Enemy::draw, std::placeholders::_1));
    std::for_each(game->bullets.cbegin(), game->bullets.cend(), std::bind(&Bullet::draw, std::placeholders::_1));
    Resource::window.draw(game->info);
}

PauseAction::PauseAction(Bubbles* game): Action(game)
{
}

bool PauseAction::handle(sf::Event const& event)
{
    if (sf::Event::KeyPressed == event.type)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
                game->state = Bubbles::State::Setup;
                return true;
            case sf::Keyboard::Space:
                game->state = Bubbles::State::Play;
                return true;
            default:
                return true;
        }
    }

    return true;
}

void PauseAction::draw() const
{
    Resource::window.draw(game->info);
    Resource::window.draw(game->pauseMenu);
}

EndAction::EndAction(Bubbles* game): Action(game)
{
}

bool EndAction::handle(sf::Event const& event)
{
    if (sf::Event::KeyPressed == event.type)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
                return false;
            case sf::Keyboard::Space:
                game->state = Bubbles::State::Setup;
                return true;
            default:
                return true;
        }
    }

    return true;
}

void EndAction::draw() const
{
    Resource::window.draw(game->endSummary);
    Resource::window.draw(game->pauseMenu);
}

}