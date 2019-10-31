#include <algorithm>
#include <any>
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

class enemy;

template<typename... T_args>
struct IdentifiedFunction {
    size_t id;
    std::function<void(T_args...)> function;
};

template<typename... T_args>
class Event;

template<typename... T_args>
struct EventSubscriptionBind {
    Event<T_args...> subscribed_event;
    size_t id;
};

template<typename... T_args>
class Event
{
  private:
    size_t function_index = 0;
    std::vector<IdentifiedFunction<T_args...>> functions;

  public:
    int event_id;
    EventSubscriptionBind<T_args...>
    Subscribe(std::function<void(T_args...)> subscriber)
    {
        IdentifiedFunction<T_args...> identified_subscriber =
            IdentifiedFunction<T_args...>(
                {.id = ++function_index, .function = subscriber});
        functions.push_back(identified_subscriber);

        EventSubscriptionBind<T_args...> bind = {.subscribed_event = *this,
                                                 .id = function_index};

        return bind;
    }

    void Unsubscribe(size_t bind_index)
    {
        auto erase_iterator =
            std::find_if(functions.begin(), functions.end(),
                         [&](const auto& val) { return val.id == bind_index; });

        functions.erase(erase_iterator);
    }

    void Invoke(T_args... args)
    {
        for (auto identifier : functions) {
            identifier.function(std::forward<T_args>(args)...);
        }
    }
};

template<typename... T_args>
bool operator==(const Event<T_args...>& a, const Event<T_args...>& b)
{
    return a.event_id == b.event_id;
}

class EventManager
{
  public:
    Event<int, int> some_event_1;
    Event<bool> some_event_2;
    Event<> some_event_3;
};

EventManager event_manager;

class IEventSubscriber
{
  private:
    std::vector<std::any> binds;

  public:
    template<typename... T_args>
    void subscribe(Event<T_args...>& to_event,
                   std::function<void(T_args...)> function)
    {
        EventSubscriptionBind<T_args...> bind = to_event.Subscribe(function);
        binds.push_back(bind);
    }

    template<typename... T_args>
    void unsubscribe(Event<T_args...>& from_event)
    {
        auto bind_it =
            std::find_if(binds.begin(), binds.end(), [&](const auto& bind) {
                try {
                    return (std::any_cast<EventSubscriptionBind<T_args...>>(
                                bind))
                               .subscribed_event == from_event;
                } catch (const std::bad_any_cast& e) {
                    return false;
                }
            });

        from_event.Unsubscribe(
            (std::any_cast<EventSubscriptionBind<T_args...>>(*bind_it)).id);
        binds.erase(bind_it);
    }
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
    // std::cout << typeid(enemy).name() << std::endl;
    // std::cout << typeid(Entity<enemy>).name() << std::endl;

    enemy e1(0);
    enemy e2(1);

    // manager.some_event_1.Subscribe(std::bind(
    //     &enemy::announce, &e2, std::placeholders::_1,
    //     std::placeholders::_2));

    // manager.some_event_1.Invoke(42, 5);

    // manager.some_event_1.Unsubscribe(bind_1);

    event_manager.some_event_1.Invoke(42, 5);
    event_manager.some_event_2.Invoke(false);
    std::cout << std::endl;

    e1.unsubscribe<int, int>(event_manager.some_event_1);
    e2.unsubscribe<bool>(event_manager.some_event_2);

    event_manager.some_event_1.Invoke(40, 5);
    event_manager.some_event_2.Invoke(false);
    std::cout << std::endl;

    std::function<void()> bind = std::bind(&enemy::void_function, &e1);
    e1.subscribe(event_manager.some_event_3, bind);

    event_manager.some_event_3.Invoke();

    return 0;
}