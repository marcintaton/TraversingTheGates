#include "unitTests.h"

#include "../src/ecs/events/IEventSubscriber.h"
#include "../src/ecs/events/eventManager.h"
#include "../src/ecs/events/eventType.h"

#include <functional>
#include <iostream>

////

class sample_class : public IEventSubscriber
{
  public:
    void f_int_int(int x, int y) {}
    void f_bool(bool x) {}
    void f_none() {}
    void f_int_int_2(int x, int y) {}
};

void sample_func(bool x) {}

////

void try_invoke_empty()
{
    EventManager manager;
    sample_class s1;

    // invoke empty event
    try {
        EventManager manager;
        sample_class s1;
        manager.get_event<>(EventType::on_new_game_started).Invoke();

        std::cout << "UNIT_TESTS::EVENTS::INVOKE_EMPTY::PASSED" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "UNIT_TESTS::EVENTS::INVOKE_EMPTY::FAILED" << std::endl;
    }
}

void try_sub_empty_event()
{
    EventManager manager;
    sample_class s1;

    // subscribe empty evnet
    try {
        std::function<void(int, int)> listener =
            std::bind(&sample_class::f_int_int, &s1, std::placeholders::_1,
                      std::placeholders::_2);
        s1.subscribe<int, int>(
            manager.get_event<int, int>(EventType::on_end_of_level_reached),
            listener);

        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_EMPTY::PASSED"
                  << std::endl;

    } catch (const std::exception& e) {
        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_EMPTY::FAILED"
                  << std::endl;
    }
}

void try_sub_non_empty_event()
{
    EventManager manager;
    sample_class s1, s2;
    std::function<void(int, int)> listener =
        std::bind(&sample_class::f_int_int, &s1, std::placeholders::_1,
                  std::placeholders::_2);
    s1.subscribe<int, int>(
        manager.get_event<int, int>(EventType::on_end_of_level_reached),
        listener);

    // subscribe non empty event
    try {
        std::function<void(int, int)> listener2 =
            std::bind(&sample_class::f_int_int, &s2, std::placeholders::_1,
                      std::placeholders::_2);
        s2.subscribe<int, int>(
            manager.get_event<int, int>(EventType::on_end_of_level_reached),
            listener);

        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_NON_EMPTY::PASSED"
                  << std::endl;

    } catch (const std::exception& e) {
        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_NON_EMPTY::FAILED"
                  << std::endl;
    }
}

void try_sub_already_subbed_event()
{

    EventManager manager;
    sample_class s1;
    std::function<void(int, int)> listener =
        std::bind(&sample_class::f_int_int, &s1, std::placeholders::_1,
                  std::placeholders::_2);
    s1.subscribe<int, int>(
        manager.get_event<int, int>(EventType::on_end_of_level_reached),
        listener);

    // subscribe already subscribed event
    try {
        std::function<void(int, int)> listener2 =
            std::bind(&sample_class::f_int_int_2, &s1, std::placeholders::_1,
                      std::placeholders::_2);
        s1.subscribe<int, int>(
            manager.get_event<int, int>(EventType::on_end_of_level_reached),
            listener);

        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_ALREADY_SUBSCRIBED_EVENT::"
                     "PASSED"
                  << std::endl;
    } catch (const std::exception& e) {
        std::cout
            << "UNIT_TESTS::EVENTS::SUBSCRIBED_ALREADY_SUBSCRIBED_EVENT::FAILED"
            << std::endl;
    }
}

void try_sub_with_function()
{
    EventManager manager;
    sample_class s1;

    // subscribe with function
    try {
        std::function<void(bool)> listener = sample_func;
        s1.subscribe<bool>(manager.get_event<bool>(EventType::on_game_saved),
                           listener);

        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_WITH_INDEPENDENT_FUNCTION:"
                     ":PASSED"
                  << std::endl;
    } catch (const std::exception& e) {
        std::cout << "UNIT_TESTS::EVENTS::SUBSCRIBED_WITH_INDEPENDENT_FUNCTION:"
                     ":FAILED"
                  << std::endl;
    }
}

void try_invoke_non_empty_event()
{
    EventManager manager;
    sample_class s1;
    std::function<void(int, int)> listener =
        std::bind(&sample_class::f_int_int, &s1, std::placeholders::_1,
                  std::placeholders::_2);
    s1.subscribe<int, int>(
        manager.get_event<int, int>(EventType::on_end_of_level_reached),
        listener);

    // invoke non empty event
    try {
        manager.get_event<int, int>(EventType::on_end_of_level_reached)
            .Invoke(4, 20);

        std::cout << "UNIT_TESTS::EVENTS::INVOKE_NON_EMPTY_EVENT::PASSED"
                  << std::endl;

    } catch (const std::exception& e) {
        std::cout << "UNIT_TESTS::EVENTS::INVOKE_NON_EMPTY_EVENT::FAILED"
                  << std::endl;
    }
}

void try_unsub_from_subbed_event()
{
    EventManager manager;
    sample_class s1;
    std::function<void(int, int)> listener =
        std::bind(&sample_class::f_int_int, &s1, std::placeholders::_1,
                  std::placeholders::_2);
    s1.subscribe<int, int>(
        manager.get_event<int, int>(EventType::on_end_of_level_reached),
        listener);

    // unsubscribe from subscribed event
    try {
        s1.unsubscribe<int, int>(
            manager.get_event<int, int>(EventType::on_end_of_level_reached));

        std::cout
            << "UNIT_TESTS::EVENTS::UNSUBSCRIBED_FROM_SUBSCRIBED_EVENT::PASSED"
            << std::endl;
    } catch (const std::exception& e) {
        std::cout
            << "UNIT_TESTS::EVENTS::UNSUBSCRIBED_FROM_SUBSCRIBED_EVENT::FAILED"
            << std::endl;
    }
}

void try_unsub_from_non_subbed_event()
{
    EventManager manager;
    sample_class s1;

    // unsubscribe form not subscribed event
    try {
        s1.unsubscribe<int, int>(
            manager.get_event<int, int>(EventType::on_end_of_level_reached));

        std::cout << "UNIT_TESTS::EVENTS::UNSUBSCRIBED_FROM_NOT_SUBSCRIBED_"
                     "EVENT::PASSED"
                  << std::endl;
    } catch (const std::exception& e) {
        std::cout << "UNIT_TESTS::EVENTS::UNSUBSCRIBED_FROM_NOT_SUBSCRIBED_"
                     "EVENT::FAILED"
                  << " " << e.what() << std::endl;
    }
}

void event_tests()
{

    std::cout << "UNIT_TESTS::EVENTS::STARTED " << std::endl;

    try_invoke_empty();

    try_sub_empty_event();

    try_sub_non_empty_event();

    try_sub_already_subbed_event();

    try_sub_with_function();

    try_invoke_non_empty_event();

    try_unsub_from_subbed_event();

    try_unsub_from_non_subbed_event();

    std::cout << "UNIT_TESTS::EVENTS::DONE " << std::endl;
}