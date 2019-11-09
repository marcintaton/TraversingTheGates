#include "Test.h"

void Tests::Engine::mockup_test()
{
    spdlog::info("This is mockup test");
}

void Tests::Engine::test_create_entity()
{
    ECS::ECEngine::get_instance().create_entity<Player>();
    spdlog::info("Tests::Engine::Create Entity::Valid : Passed");

    ECS::ECEngine::get_instance().create_entity<Enemy>(10);
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
