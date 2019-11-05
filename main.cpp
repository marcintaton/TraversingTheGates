#include <bitset>
#include <functional>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

#include "src/ecs/component/component.h"
#include "src/ecs/component/componentCluster.h"
#include "src/ecs/component/componentIterator.h"
#include "src/ecs/entity/entity.h"

#include "src/ecs/ECSEngine/ECSEngine.h"

#include "src/ecs/events/eventDelegate.h"
#include "src/ecs/events/eventDispatcher.h"
#include "src/ecs/events/eventManager.h"
#include "src/game/gameEvents.h"

class Player : public Entity<Player>
{
};

class Enemy : public Entity<Enemy>
{
  public:
    Enemy() : Entity<Enemy>() {}
    Enemy(Player p, int b) : Entity<Enemy>()
    {
        std::cout << p.get_entity_id() + b << std::endl;
    }
};

class AComponent : public Component<AComponent>
{
  public:
    int a = 102;
    AComponent() {}
    AComponent(int _a) { a = _a; }
};

class BComponent : public Component<BComponent>
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

    EventDelegate<foo, GameEvent1> sub()
    {
        return EventDelegate<foo, GameEvent1>(this, &foo::bar);
    }
};

class baz
{
  public:
    int x = 5;
    void bar(const GameEvent1* event) { std::cout << x << std::endl; }

    EventDelegate<baz, GameEvent1> sub()
    {
        return EventDelegate<baz, GameEvent1>(this, &baz::bar);
    }
};

int main(void)
{
    GameEvent1 ev1;
    GameEvent2 ev2;

    foo f_1;
    foo f_2;
    baz b_1;

    EventDelegate<foo, GameEvent1> e_del1 = f_1.sub();
    EventDelegate<foo, GameEvent1> e_del2 = f_2.sub();
    EventDelegate<baz, GameEvent1> e_del3 = b_1.sub();

    EventDispatcher<GameEvent1> disp1;

    // disp1.add_delegate(&e_del1);
    // disp1.add_delegate(&e_del1);
    // disp1.add_delegate(&e_del2);
    // disp1.add_delegate(&e_del3);

    // disp1.dispatch(&ev1);

    EventManager::get_instance().send_event<GameEvent1>(&ev1);

    EventManager::get_instance().remove_listener<GameEvent1>(&e_del1);

    EventManager::get_instance().send_event<GameEvent1>(&ev1);

    EventManager::get_instance().add_listener<GameEvent1>(&e_del1);
    EventManager::get_instance().add_listener<GameEvent1>(&e_del2);
    EventManager::get_instance().add_listener<GameEvent1>(&e_del3);

    EventManager::get_instance().send_event<GameEvent1>(&ev1);
    // std::cout << e_del1.get_delegate_id() << std::endl;
    // std::cout << e_del2.get_delegate_id() << std::endl;
    // std::cout << e_del3.get_delegate_id() << std::endl;
    // std::cout << (e_del1 == &e_del2) << std::endl;
    // std::cout << (e_del1 == &e_del1) << std::endl;

    return 0;
}