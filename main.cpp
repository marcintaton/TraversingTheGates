#include <functional>
#include <iostream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

template<typename T>
class Entity
{
};

class enemy : public Entity<enemy>
{
  private:
    int id;

  public:
    enemy(int _id) { this->id = _id; }
    void announce(int announcment, int shieet)
    {
        std::cout << announcment << shieet << " " << id << std::endl;
    }
};

template<typename... T_args>
class Event
{
  private:
    std::vector<std::function<void(T_args...)>> functions;

  public:
    void Subscribe(std::function<void(T_args...)> subscriber)
    {
        functions.push_back(subscriber);
    }

    void Unsubscribe(std::function<void(T_args...)> to_unsub) {}

    void Invoke(T_args... args)
    {
        for (auto function : functions) {
            function(std::forward<T_args>(args)...);
        }
    }
};

class EventManager
{
  public:
    Event<int, int> some_event_1;
    Event<> some_event_2;
};

void xtuff(int a, int b) {}

int main(void)
{
    // std::cout << typeid(enemy).name() << std::endl;
    // std::cout << typeid(Entity<enemy>).name() << std::endl;

    EventManager manager;

    enemy e1(0), e2(1);

    manager.some_event_1.Subscribe(std::bind(
        &enemy::announce, &e1, std::placeholders::_1, std::placeholders::_2));
    manager.some_event_1.Subscribe(std::bind(
        &enemy::announce, &e2, std::placeholders::_1, std::placeholders::_2));
    manager.some_event_1.Subscribe(xtuff);

    manager.some_event_1.Invoke(42, 5);

    std::cout << std::endl;

    manager.some_event_1.Unsubscribe(std::bind(
        &enemy::announce, &e2, std::placeholders::_1, std::placeholders::_2));

    manager.some_event_1.Invoke(42, 5);

    return 0;
}