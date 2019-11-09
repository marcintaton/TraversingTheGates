#pragma once

#include "../../../src/engine/GameEngine.h"

class GameEvent1 : public Event::Event<GameEvent1>
{
  public:
    int x = 0;
    int y = 1;
};

class GameEvent2 : public Event::Event<GameEvent2>
{
  public:
    bool a = 0;
    float b = 1;
};

class Player : public ECS::Entity::Entity<Player>
{
};

class Enemy : public ECS::Entity::Entity<Enemy>
{
  public:
    int x = 45;
    Enemy() : Entity<Enemy>() {}
    Enemy(int b) : Entity<Enemy>() {}
};

class AComponent : public ECS::Component::Component<AComponent>
{
  public:
    int a = 102;
    AComponent() {}
    AComponent(int _a) { a = _a; }
};

class BComponent : public ECS::Component::Component<BComponent>
{
  public:
    bool b = true;
};

class CComponent : public ECS::Component::Component<CComponent>
{
  public:
    bool b = true;
};

class foo
{
  public:
    int x = 4;
    void bar(const GameEvent1* event)
    {
        std::cout << x << " " << event->x << std::endl;
    }

    Event::EventDelegate<foo, GameEvent1> sub()
    {
        return Event::EventDelegate<foo, GameEvent1>(this, &foo::bar);
    }
};

class baz
{
  public:
    int x = 5;
    void bar(const GameEvent1* event) { std::cout << x << std::endl; }

    Event::EventDelegate<baz, GameEvent1> sub()
    {
        return Event::EventDelegate<baz, GameEvent1>(this, &baz::bar);
    }
};

class SystemA_U : public ECS::System::System<SystemA_U>
{
  private:
    void do_on_update() { std::cout << "SystemA_U updating" << std::endl; }

  protected:
    virtual void update() override { do_on_update(); }

  public:
    SystemA_U() { set_priority(8); }
    ~SystemA_U() {}
    virtual void on_enable() override {}
};

class SystemB_U : public ECS::System::System<SystemB_U>
{
  private:
    void do_on_enable() { std::cout << "SystemB_U updating" << std::endl; }

  protected:
    virtual void update() override { do_on_enable(); }

  public:
    SystemB_U() { set_priority(7); }
    virtual void on_enable() override
    {
        std::cout << "enable B_U" << std::endl;
    }
};

class SystemC_E : public ECS::System::System<SystemC_E>
{
  public:
    SystemC_E() { set_priority(5); }
    virtual void on_enable() override
    {
        std::cout << "enable C_E" << std::endl;
    }
};

class IndSystemA : public ECS::System::IndependentSystem<IndSystemA>
{

  public:
    void foo() {}
};