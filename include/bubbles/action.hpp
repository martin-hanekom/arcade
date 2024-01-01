#ifndef BUBBLES_ACTION_HPP
#define BUBBLES_ACTION_HPP

namespace bubbles
{

class Bubbles;

class Action: public Entity
{
public:
    Action(Bubbles* game);
    virtual bool handle(sf::Event const& event) { return true; };
    virtual void update(float dt) {};
    virtual void draw() const {};

protected:
    Bubbles* game;
};

class SetupAction: public Action
{
public:
    SetupAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void draw() const override;
};

class PlayAction: public Action
{
public:
    PlayAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void update(float dt) override;
    void draw() const override;
};

class PauseAction: public Action
{
public:
    PauseAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void draw() const override;
};

class EndAction: public Action
{
public:
    EndAction(Bubbles* game);
    bool handle(sf::Event const& event) override;
    void draw() const override;
};

}

#endif