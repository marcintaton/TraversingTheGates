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
        subscribe<int, int>(event_manager.get_event<int, int>(
                                EventType::on_end_of_level_reached),
                            f1_bind);

        subscribe<int, int>(
            event_manager.get_event<int, int>(EventType::on_player_death),
            f1_bind);

        std::function<void(bool)> f2_bind =
            std::bind(&enemy::bool_function, this, std::placeholders::_1);
        subscribe<bool>(event_manager.get_event<bool>(EventType::on_game_saved),
                        f2_bind);
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

    event_manager.get_event<int, int>(EventType::on_end_of_level_reached)
        .Invoke(42, 5);
    event_manager.get_event<bool>(EventType::on_game_saved).Invoke(false);
    std::cout << std::endl;

    e1.unsubscribe<int, int>(
        event_manager.get_event<int, int>(EventType::on_end_of_level_reached));
    e2.unsubscribe<bool>(
        event_manager.get_event<bool>(EventType::on_game_saved));

    event_manager.get_event<int, int>(EventType::on_end_of_level_reached)
        .Invoke(40, 5);
    event_manager.get_event<bool>(EventType::on_game_saved).Invoke(false);
    std::cout << std::endl;

    std::function<void()> bind = std::bind(&enemy::void_function, &e1);
    e1.subscribe(event_manager.get_event<>(EventType::on_new_game_started),
                 bind);

    event_manager.get_event<>(EventType::on_new_game_started).Invoke();
    e1.unsubscribe(event_manager.get_event<>(EventType::on_new_game_started));

    event_manager.get_event<int, int>(EventType::on_player_death).Invoke(4, 20);

    return 0;
}