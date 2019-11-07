#include "src/utility/logging.h"

// libs
#include <bitset>
#include <functional>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

// files
#include "src/ecs/component/Component.h"
#include "src/ecs/component/ComponentCluster.h"
#include "src/ecs/component/ComponentIterator.h"
#include "src/ecs/entity/Entity.h"

#include "src/ecs/ECSEngine/ECSEngine.h"

#include "src/ecs/events/EventDelegate.h"
#include "src/ecs/events/EventDispatcher.h"
#include "src/ecs/events/EventManager.h"
#include "src/ecs/system/SystemManager.h"
#include "src/game/gameEvents.h"

class Player : public ECS::Entity::Entity<Player>
{
};

class Enemy : public ECS::Entity::Entity<Enemy>
{
  public:
    Enemy() : Entity<Enemy>() {}
    Enemy(Player p, int b) : Entity<Enemy>()
    {
        std::cout << p.get_entity_id() + b << std::endl;
    }
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
    void do_on_enable() { std::cout << "SystemA_U updating" << std::endl; }

  protected:
    virtual void update() override { do_on_enable(); }

  public:
    SystemA_U() { set_priority(8); }
    virtual void on_enable() override
    {
        std::cout << "enable A_U" << std::endl;
    }
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

int main(void)
{

    utility::logging::setup_logger();

    spdlog::info("aei<3");
    spdlog::warn("aei<3");
    spdlog::error("aei<3");
    spdlog::critical("aei<3");
    ECS::ECSEngine::get_instance().create_system<SystemA_U>();
    auto x = ECS::ECSEngine::get_instance().create_entity<Enemy>();
    ECS::ECSEngine::get_instance().add_component<AComponent>(x);

    {
        GameEvent1 ev1;
        GameEvent2 ev2;

        foo f_1;
        foo f_2;
        baz b_1;

        Event::EventDelegate<foo, GameEvent1> e_del1 = f_1.sub();
        Event::EventDelegate<foo, GameEvent1> e_del2 = f_2.sub();
        Event::EventDelegate<baz, GameEvent1> e_del3 = b_1.sub();

        Event::EventDispatcher<GameEvent1> disp1;

        // disp1.add_delegate(&e_del1);
        // disp1.add_delegate(&e_del1);
        // disp1.add_delegate(&e_del2);
        // disp1.add_delegate(&e_del3);

        // disp1.dispatch(&ev1);

        Event::EventManager::get_instance().send_event<GameEvent1>(&ev1);

        Event::EventManager::get_instance().remove_listener<GameEvent1>(
            &e_del1);

        Event::EventManager::get_instance().send_event<GameEvent1>(&ev1);

        Event::EventManager::get_instance().add_listener<GameEvent1>(&e_del1);
        Event::EventManager::get_instance().add_listener<GameEvent1>(&e_del2);
        Event::EventManager::get_instance().add_listener<GameEvent1>(&e_del3);

        // EventManager::get_instance().send_event<GameEvent1>(&ev1);
        // std::cout << e_del1.get_delegate_id() << std::endl;
        // std::cout << e_del2.get_delegate_id() << std::endl;
        // std::cout << e_del3.get_delegate_id() << std::endl;
        // std::cout << (e_del1 == &e_del2) << std::endl;
        // std::cout << (e_del1 == &e_del1) << std::endl;
    }

    return 0;
}