#ifndef BUBBLES_BUBBLES_HPP
#define BUBBLES_BUBBLES_HPP

#include <iostream>
#include <memory>
#include <array>
#include <list>
#include <SFML/Graphics.hpp>
#include "../entity.hpp"
#include "action.hpp"
#include "shot.hpp"
#include "enemy.hpp"
#include "player.hpp"

namespace bubbles
{

class Bubbles: public Entity
{
public:
    Bubbles();
    bool handle(sf::Event const& event);
    void update(float dt);
    void draw() const;

    void reset();
    void end();
    void shoot(float dt);
    void spawnEnemy(float const dt);
    void reload();
    void updateInfo();

    enum class State: unsigned
    {
        Setup = 0u,
        Play,
        Pause,
        End
    };

    static constexpr float EnemyCooldown {2.0f};

    std::array<std::unique_ptr<Action>, 4> const action {
        std::make_unique<SetupAction>(this),
        std::make_unique<PlayAction>(this),
        std::make_unique<PauseAction>(this),
        std::make_unique<EndAction>(this)
    };
    State state {State::Setup};

    unsigned round {1};
    float enemyCooldown {EnemyCooldown};

    Player player;
    std::list<std::shared_ptr<Shot>> shots;
    std::list<std::shared_ptr<Enemy>> enemies;

    sf::Text splash;
    sf::Text pauseMenu;
    sf::Text info;
    sf::Text endSummary;
};

}

#endif