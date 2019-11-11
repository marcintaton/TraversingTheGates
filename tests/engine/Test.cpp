#include "Test.h"

void Tests::Engine::mockup_test()
{
    spdlog::info("This is mockup test");
}

void Tests::Engine::test_create_entity()
{
    auto id1 = ECS::ECEngine::get_instance().create_entity<Player>();
    spdlog::info("Tests::Engine::Create Entity::Valid : Passed");

    auto id2 = ECS::ECEngine::get_instance().create_entity<Enemy>(10);
    spdlog::info("Tests::Engine::Create Entity::Valid with args : Passed");

    // following create compilation error:

    // ECS::ECEngine::get_instance().create_entity<Enemy>("dupa");
    // spdlog::info(
    //     "Tests::Engine::Create Entity::Valid with invalid args : Passed");

    // ECS::ECEngine::get_instance().create_entity<SystemA_U>();
    // spdlog::info("Tests::Engine::Create Entity::Invalid type : Passed");
}

void Tests::Engine::test_get_entities_of_type()
{
    // setup
    ECS::ECEngine::get_instance().create_entity<Player>();
    //

    ECS::ECEngine::get_instance().get_entities_of_type<Player>();
    spdlog::info("Tests::Engine::Get entities of type::Valid : Passed");

    // returns empty container
    auto x = ECS::ECEngine::get_instance().get_entities_of_type<SystemA_U>();
    spdlog::info("Tests::Engine::Get entities of type::Invalid type : Passed");

    ECS::ECEngine::get_instance().get_entities_of_type<Enemy>();
    spdlog::info("Tests::Engine::Get entities of type::Valid but no entities "
                 "of type: Passed");
}

void Tests::Engine::test_remove_entity()
{
    // setup
    auto id = ECS::ECEngine::get_instance().create_entity<Player>();
    //

    ECS::ECEngine::get_instance().remove_entity(id);
    spdlog::info("Tests::Engine::Remove entity::Valid : Passed");

    ECS::ECEngine::get_instance().remove_entity(id);
    spdlog::info("Tests::Engine::Remove entity::Invalid id : Passed");
}

void Tests::Engine::test_get_entity()
{
    // setup
    auto id = ECS::ECEngine::get_instance().create_entity<Player>();
    //

    auto entity = ECS::ECEngine::get_instance().get_entity(id);
    spdlog::info("Tests::Engine::Get entity::Valid : Passed");

    auto entity2 = ECS::ECEngine::get_instance().get_entity(id + 1);
    spdlog::info("Tests::Engine::Get entity::Invalid id : Passed");
}

void Tests::Engine::test_add_component()
{
    // setup
    auto id1 = ECS::ECEngine::get_instance().create_entity<Player>();
    auto id2 = ECS::ECEngine::get_instance().create_entity<Player>();
    //

    auto comp1 = ECS::ECEngine::get_instance().add_component<BComponent>(id1);
    spdlog::info("Tests::Engine::Add component::Valid : Passed");

    // compile error
    // auto comp2 = ECS::ECEngine::get_instance().add_component<SystemA_U>(id);
    // spdlog::info("Tests::Engine::Add component::Invalid type : Passed");

    auto comp3 =
        ECS::ECEngine::get_instance().add_component<AComponent>(id1, 10);
    spdlog::info("Tests::Engine::Add component::Valid with args : Passed");

    // compile error
    // auto comp4 =
    //     ECS::ECEngine::get_instance().add_component<AComponent>(id2, "dupa");
    // spdlog::info("Tests::Engine::Add component::With invalid args : Passed");

    auto comp5 =
        ECS::ECEngine::get_instance().add_component<AComponent>(id2 + 1);
    spdlog::info("Tests::Engine::Add component::Invalid Entity id : Passed");

    auto comp6 = ECS::ECEngine::get_instance().add_component<BComponent>(id1);
    spdlog::info("Tests::Engine::Add component::Adding to entity that already "
                 "has this component : Passed");
}

void Tests::Engine::test_do_add_component()
{
    auto id = ECS::ECEngine::get_instance().create_entity<Tile>();
    spdlog::info(
        "Tests::Engine::Do add component::Calling in costructor : Passed");

    ECS::ECEngine::get_instance().do_add_component<AComponent>(id);
    spdlog::info("Tests::Engine::Do add component::Adding component to entity "
                 "that already has this component type : Passed");
}

void Tests::Engine::test_get_components_of_type()
{
    // setup
    auto id1 = ECS::ECEngine::get_instance().create_entity<Player>();
    auto id2 = ECS::ECEngine::get_instance().create_entity<Enemy>();
    ECS::ECEngine::get_instance().add_component<AComponent>(id1);
    ECS::ECEngine::get_instance().add_component<AComponent>(id2);
    //

    auto components1 =
        ECS::ECEngine::get_instance().get_components_of_type<AComponent>();
    spdlog::info("Tests::Engine::Get components of type::Valid : Passed");

    auto components2 =
        ECS::ECEngine::get_instance().get_components_of_type<BComponent>();
    spdlog::info("Tests::Engine::Get components of type::Type with no added "
                 "components : Passed");

    auto components3 =
        ECS::ECEngine::get_instance().get_components_of_type<SystemA_U>();
    spdlog::info("Tests::Engine::Get components of type::Invalid type : "
                 "components : Passed");
}

void Tests::Engine::test_remove_component()
{
    // setup
    auto id1 = ECS::ECEngine::get_instance().create_entity<Player>();
    auto id2 = ECS::ECEngine::get_instance().create_entity<Enemy>();
    ECS::ECEngine::get_instance().add_component<AComponent>(id1);
    ECS::ECEngine::get_instance().add_component<AComponent>(id2);
    //

    auto e1 = ECS::ECEngine::get_instance().get_entity(id1);

    ECS::ECEngine::get_instance().remove_component<AComponent>(id1);
    spdlog::info("Tests::Engine::Remove component::Valid : Passed");

    ECS::ECEngine::get_instance().remove_component<AComponent>(id2 + 1);
    spdlog::info("Tests::Engine::Remove component::Invalid entity id : Passed");

    ECS::ECEngine::get_instance().remove_component<SystemA_U>(id2);
    spdlog::info(
        "Tests::Engine::Remove component::Invalid Component Type : Passed");

    ECS::ECEngine::get_instance().remove_component<BComponent>(id2);
    spdlog::info("Tests::Engine::Remove component::From entity without this "
                 "component : Passed");
}

void Tests::Engine::test_get_component()
{
    // setup
    auto id1 = ECS::ECEngine::get_instance().create_entity<Player>();
    ECS::ECEngine::get_instance().add_component<AComponent>(id1);
    //

    auto comp1 = ECS::ECEngine::get_instance().get_component<AComponent>(id1);
    spdlog::info("Tests::Engine::Get component::Valid : Passed");

    auto comp2 =
        ECS::ECEngine::get_instance().get_component<AComponent>(id1 + 1);
    spdlog::info(
        "Tests::Engine::Get component::From Nonexistent entity : Passed");

    auto comp3 = ECS::ECEngine::get_instance().get_component<SystemA_U>(id1);
    spdlog::info("Tests::Engine::Get component::Invalid type : Passed");

    auto comp4 = ECS::ECEngine::get_instance().get_component<BComponent>(id1);
    spdlog::info("Tests::Engine::Get component::From entity without this "
                 "component : Passed");
}

void Tests::Engine::test_get_component_cluster()
{
    // setup
    auto id1 = ECS::ECEngine::get_instance().create_entity<Player>();
    auto id2 = ECS::ECEngine::get_instance().create_entity<Enemy>();
    ECS::ECEngine::get_instance().add_component<AComponent>(id1);
    ECS::ECEngine::get_instance().add_component<AComponent>(id2);
    ECS::ECEngine::get_instance().add_component<BComponent>(id1);
    //

    auto cluster1 = ECS::ECEngine::get_instance()
                        .get_component_cluster<AComponent, BComponent>();
    spdlog::info("Tests::Engine::Get component clusters::Valid : Passed");

    // compile error
    // auto cluster2 = ECS::ECEngine::get_instance()
    //                     .get_component_cluster<AComponent, AComponent>();
    // spdlog::info("Tests::Engine::Get component::Doubled type : Passed");

    // compile error
    // auto cluster3 = ECS::ECEngine::get_instance().get_component_cluster<>();
    // spdlog::info("Tests::Engine::Get component::No types : Passed");

    auto cluster4 = ECS::ECEngine::get_instance()
                        .get_component_cluster<AComponent, CComponent>();
    spdlog::info(
        "Tests::Engine::Get component clusters::No fitting entities : Passed");
}

void Tests::Engine::test_create_system()
{
    ECS::SystemEngine::get_instance().create_system<SystemA_U>();
    spdlog::info("Tests::Engine::Create system::Valid : Passed");

    ECS::SystemEngine::get_instance().create_system<SystemA_U>();
    spdlog::info("Tests::Engine::Create system::Already existing : Passed");

    // compile error
    // ECS::SystemEngine::get_instance().create_system<AComponent>();
    // spdlog::info("Tests::Engine::Create system::Invalid type : Passed");
}

void Tests::Engine::test_create_active_system()
{
    ECS::SystemEngine::get_instance().create_active_system<SystemA_U>();
    spdlog::info("Tests::Engine::Create active system::Valid : Passed");

    ECS::SystemEngine::get_instance().create_active_system<SystemA_U>();
    spdlog::info(
        "Tests::Engine::Create active system::Already existing : Passed");

    // compile error
    // ECS::SystemEngine::get_instance().create_active_system<AComponent>();
    // spdlog::info("Tests::Engine::Create active system::Invalid type :
    // Passed");
}

void Tests::Engine::test_destroy_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_active_system<SystemA_U>();
    ECS::SystemEngine::get_instance().create_system<SystemB_U>();
    //

    ECS::SystemEngine::get_instance().destroy_system<SystemB_U>();
    spdlog::info("Tests::Engine::Destroy system::Valid inactive : Passed");

    ECS::SystemEngine::get_instance().destroy_system<SystemA_U>();
    spdlog::info("Tests::Engine::Destroy system::Valid active : Passed");

    ECS::SystemEngine::get_instance().destroy_system<SystemA_U>();
    spdlog::info("Tests::Engine::Destroy system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().destroy_system<AComponent>();
    spdlog::info("Tests::Engine::Destroy system::Invalid type : Passed");
}

void Tests::Engine::test_enable_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_system<SystemA_U>();
    //

    ECS::SystemEngine::get_instance().enable_system<SystemA_U>();
    spdlog::info("Tests::Engine::Enable system::Valid : Passed");

    ECS::SystemEngine::get_instance().enable_system<SystemA_U>();
    spdlog::info("Tests::Engine::Enable system::Already Enabled : Passed");

    ECS::SystemEngine::get_instance().enable_system<SystemB_U>();
    spdlog::info("Tests::Engine::Enable system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().enable_system<AComponent>();
    spdlog::info("Tests::Engine::Enable system::Invalid type : Passed");
}

void Tests::Engine::test_disable_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_active_system<SystemA_U>();
    //

    ECS::SystemEngine::get_instance().disable_system<SystemA_U>();
    spdlog::info("Tests::Engine::Disable system::Valid : Passed");

    ECS::SystemEngine::get_instance().disable_system<SystemA_U>();
    spdlog::info("Tests::Engine::Disable system::Already Disabled : Passed");

    ECS::SystemEngine::get_instance().disable_system<SystemB_U>();
    spdlog::info("Tests::Engine::Disable system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().disable_system<AComponent>();
    spdlog::info("Tests::Engine::Disable system::Invalid type : Passed");
}

void Tests::Engine::test_create_independent_system()
{
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemA>();
    spdlog::info("Tests::Engine::Create Independent system::Valid : Passed");

    ECS::SystemEngine::get_instance().create_independent_system<IndSystemA>();
    spdlog::info(
        "Tests::Engine::Create Independent system::Already existing : Passed");

    // compile error
    // ECS::SystemEngine::get_instance().create_independent_system<SystemA_U>();
    // spdlog::info(
    //     "Tests::Engine::Create Independent system::Invalid type : Passed");
}

void Tests::Engine::test_destroy_independent_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemA>();
    //

    ECS::SystemEngine::get_instance().destroy_independent_system<IndSystemA>();
    spdlog::info("Tests::Engine::Destroy Independent system::Valid : Passed");

    ECS::SystemEngine::get_instance().destroy_independent_system<IndSystemB>();
    spdlog::info(
        "Tests::Engine::Destroy Independent system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().destroy_independent_system<SystemA_U>();
    spdlog::info(
        "Tests::Engine::Destroy Independent system::Invalid type : Passed");
}

void Tests::Engine::test_disable_independent_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemB>();
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemA>();
    //

    ECS::SystemEngine::get_instance().disable_independent_system<IndSystemA>();
    spdlog::info("Tests::Engine::Disable Independent system::Valid : Passed");

    ECS::SystemEngine::get_instance().disable_independent_system<IndSystemA>();
    spdlog::info(
        "Tests::Engine::Disable Independent system::Already disabled : Passed");

    ECS::SystemEngine::get_instance().disable_independent_system<IndSystemC>();
    spdlog::info(
        "Tests::Engine::Disable Independent system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().disable_independent_system<SystemA_U>();
    spdlog::info(
        "Tests::Engine::Disable Independent system::Invalid type : Passed");
}

void Tests::Engine::test_enable_independent_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemB>();
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemA>();
    ECS::SystemEngine::get_instance().disable_system<IndSystemA>();
    //

    ECS::SystemEngine::get_instance().enable_independent_system<IndSystemA>();
    spdlog::info("Tests::Engine::Enable Independent system::Valid : Passed");

    ECS::SystemEngine::get_instance().enable_independent_system<IndSystemB>();
    spdlog::info(
        "Tests::Engine::Enable Independent system::Already Enabled : Passed");

    ECS::SystemEngine::get_instance().enable_independent_system<IndSystemC>();
    spdlog::info(
        "Tests::Engine::Enable Independent system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().enable_independent_system<SystemC_E>();
    spdlog::info(
        "Tests::Engine::Enable Independent system::Invalid type : Passed");
}

void Tests::Engine::test_get_independent_system()
{
    // setup
    ECS::SystemEngine::get_instance().create_independent_system<IndSystemB>();
    //

    ECS::SystemEngine::get_instance().get_independent_system<IndSystemB>();
    spdlog::info("Tests::Engine::Get Independent system::Valid : Passed");

    ECS::SystemEngine::get_instance().get_independent_system<IndSystemA>();
    spdlog::info("Tests::Engine::Get Independent system::Nonexistent : Passed");

    ECS::SystemEngine::get_instance().get_independent_system<SystemA_U>();
    spdlog::info(
        "Tests::Engine::Get Independent system::Invalid type : Passed");
}

void Tests::Engine::test_add_listener()
{
    // setup
    foo f1;
    foo f2;
    baz f3;

    auto delegate1 = f1.sub();
    auto delegate2 = f2.sub();
    auto delegate3 = f3.sub();
    //

    Event::EventEngine::get_instance().add_listener<GameEvent1>(&delegate1);
    spdlog::info(
        "Tests::Engine::Add listener::To nonexistent dispatcher : Passed");

    Event::EventEngine::get_instance().add_listener<GameEvent1>(&delegate1);
    spdlog::info(
        "Tests::Engine::Add listener::Already existing in this event : Passed");

    Event::EventEngine::get_instance().add_listener<GameEvent1>(&delegate2);
    spdlog::info("Tests::Engine::Add listener::Valid : Passed");

    Event::EventEngine::get_instance().add_listener<SystemA_U>(&delegate3);
    spdlog::info("Tests::Engine::Add listener::Invalid type : Passed");

    Event::EventEngine::get_instance().add_listener<GameEvent2>(&delegate3);
    spdlog::info("Tests::Engine::Add listener::Type mismatch between template "
                 "and delegate : Passed");
}

void Tests::Engine::test_remove_listener()
{
    // setup
    foo f1;
    foo f2;
    foo f3;
    bag b1;

    auto delegate1 = f1.sub();
    auto delegate2 = f2.sub();
    auto delegate3 = b1.sub();
    auto delegate4 = f3.sub();
    Event::EventEngine::get_instance().add_listener<GameEvent1>(&delegate1);
    Event::EventEngine::get_instance().add_listener<GameEvent1>(&delegate4);
    //

    Event::EventEngine::get_instance().remove_listener<GameEvent1>(&delegate1);
    spdlog::info("Tests::Engine::Remove listener::Valid : Passed");

    Event::EventEngine::get_instance().remove_listener<GameEvent1>(&delegate2);
    spdlog::info("Tests::Engine::Remove listener::Not Registered : Passed");

    Event::EventEngine::get_instance().remove_listener<GameEvent2>(&delegate3);
    spdlog::info(
        "Tests::Engine::Remove listener::Nonexistent dispatcher : Passed");

    Event::EventEngine::get_instance().remove_listener<GameEvent1>(&delegate3);
    spdlog::info("Tests::Engine::Remove listener::Type mismatch between "
                 "Template type and delegate type : Passed");
}

void Tests::Engine::test_send_event()
{
    // setup
    foo f1, f2;
    bag c1;

    auto d_f1 = f1.sub();
    auto d_f2 = f2.sub();
    Event::EventEngine::get_instance().add_listener<GameEvent1>(&d_f1);
    Event::EventEngine::get_instance().add_listener<GameEvent1>(&d_f2);

    auto d_c1 = c1.sub();
    Event::EventEngine::get_instance().add_listener<GameEvent2>(&d_c1);
    Event::EventEngine::get_instance().remove_listener<GameEvent2>(&d_c1);

    GameEvent1 ev1;
    GameEvent2 ev2;
    GameEvent3 ev3;
    AComponent a;
    //

    Event::EventEngine::get_instance().send_event<GameEvent1>(&ev1);
    spdlog::info("Tests::Engine::Send Event::With subs : Passed");

    Event::EventEngine::get_instance().send_event<GameEvent2>(&ev2);
    spdlog::info("Tests::Engine::Send Event::Without any subs : Passed");

    Event::EventEngine::get_instance().send_event<GameEvent3>(&ev3);
    spdlog::info("Tests::Engine::Send Event::Nonexistent dispatcher : Passed");

    // compile error
    // Event::EventEngine::get_instance().send_event<AComponent>(&a);
    // spdlog::info("Tests::Engine::Send Event::Invalid type : Passed");
}