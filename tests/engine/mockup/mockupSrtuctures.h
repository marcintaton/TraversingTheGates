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

class GameEvent3 : public Event::Event<GameEvent3>
{
  public:
    bool d = 0;
    float c = 1;
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

class Entity1 : public ECS::Entity::Entity<Entity1>
{
  public:
    int x = 45;
    Entity1() : Entity<Entity1>() {}
    Entity1(int b) : Entity<Entity1>() {}
};

class Entity2 : public ECS::Entity::Entity<Entity2>
{
};

class Entity3 : public ECS::Entity::Entity<Entity3>
{
  public:
    Entity3()
    {
        auto comp = ECS::ECEngine::get_instance().do_add_component<AComponent>(
            get_entity_id());
        add_component_info<AComponent>(comp->get_component_id());
    }
};

class foo
{
  public:
    int x = 4;
    void bar(const GameEvent1* event)
    {
        std::cout << "GameEvent1 received" << std::endl;
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
    void bar(const GameEvent3* event)
    {
        // std::cout << "GameEvent3 received" << std::endl;
    }

    Event::EventDelegate<baz, GameEvent3> sub()
    {
        return Event::EventDelegate<baz, GameEvent3>(this, &baz::bar);
    }
};

class bag
{
  public:
    int x = 5;
    void bar(const GameEvent2* event)
    {
        // std::cout << "GameEvent2 received" << std::endl;
    }

    Event::EventDelegate<bag, GameEvent2> sub()
    {
        return Event::EventDelegate<bag, GameEvent2>(this, &bag::bar);
    }
};

class SystemA_U : public ECS::System::System<SystemA_U>
{
  private:
    void do_on_update()
    {
        // std::cout << "SystemA_U updating" << std::endl;
    }

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

class IndSystemB : public ECS::System::IndependentSystem<IndSystemB>
{

  public:
    void bar() {}
    virtual void on_enable() override { bar(); }
};

class IndSystemC : public ECS::System::IndependentSystem<IndSystemC>
{

  public:
    void baz() {}
    virtual void on_enable() override {}
};