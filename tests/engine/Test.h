#pragma once

#include "../../src/engine/GameEngine.h"
#include "mockup/mockupSrtuctures.h"

// Due to engine implementation using Singleton objects, please run only one
// test function per application run.
// At least till clearing mechanizms are implemented

namespace Tests
{
namespace Engine
{
void mockup_test();

void test_create_entity();
void test_get_entities_of_type();
void test_remove_entity();
void test_get_entity();

void test_add_component();
void test_get_components_of_type();
void test_remove_component();
void test_get_component();
void test_get_component_cluster();

void test_create_system();
void test_create_active_system();
void test_destroy_system();
void test_enable_system();
void test_disable_system();

void test_create_independent_syste();
void test_destroy_independent_syste();
void test_enable_independent_syste();
void test_disable_independent_syste();
void test_get_independent_system();

void test_send_event();
void test_add_listener();
void test_remove_listener();
}; // namespace Engine
}; // namespace Tests
