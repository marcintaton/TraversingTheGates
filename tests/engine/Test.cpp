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
        "Tests::Engine::Get component::From non existent entity : Passed");

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
    spdlog::info("Tests::Engine::Destroy system::Non existent : Passed");

    ECS::SystemEngine::get_instance().destroy_system<AComponent>();
    spdlog::info("Tests::Engine::Destroy system::Invalid type : Passed");
}