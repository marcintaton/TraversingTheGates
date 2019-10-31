#include <iostream>

#include "src/ecs/events/IEventSubscriber.h"
#include "src/ecs/events/eventManager.h"

EventManager event_manager;

template<typename T>
class Entity
{
};

class enemy : public Entity<enemy>, public IEventSubscriber
{
  private:
    int id;

  public:
    enemy(int _id)
    {
        this->id = _id;

        std::function<void(int, int)> f1_bind =
            std::bind(&enemy::int_function, this, std::placeholders::_1,
                      std::placeholders::_2);
        subscribe<int, int>(event_manager.some_event_1, f1_bind);
        subscribe<int, int>(event_manager.some_event_4, f1_bind);

        std::function<void(bool)> f2_bind =
            std::bind(&enemy::bool_function, this, std::placeholders::_1);
        subscribe<bool>(event_manager.some_event_2, f2_bind);
    }

    void int_function(int announcment, int shieet)
    {
        std::cout << id << " " << announcment << shieet << std::endl;
    }

    void bool_function(bool x) { std::cout << id << " " << x << std::endl; }

    void void_function()
    {
        std::cout << id << " "
                  << "void" << std::endl;
    }
};

int main(void)
{

    enemy e1(0);
    enemy e2(1);

    event_manager.some_event_1.Invoke(42, 5);
    event_manager.some_event_2.Invoke(false);
    std::cout << std::endl;

    e1.unsubscribe<int, int>(event_manager.some_event_4);
    e2.unsubscribe<bool>(event_manager.some_event_2);

    event_manager.some_event_1.Invoke(40, 5);
    event_manager.some_event_2.Invoke(false);
    std::cout << std::endl;

    std::function<void()> bind = std::bind(&enemy::void_function, &e1);
    e1.subscribe(event_manager.some_event_3, bind);

    event_manager.some_event_3.Invoke();
    event_manager.some_event_4.Invoke(4, 20);

    return 0;
}