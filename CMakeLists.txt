cmake_minimum_required(VERSION 3.15.0)
project("traversing_the_gates")

# Flags constants
SET(CUSTOM_COMPILE_FLAGS "-std=c++17")
SET(CUSTOM_LINK_FLAGS "-lGL -lglfw")

# Adding flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINK_FLAGS}") 

# Source files
file(GLOB PROJECT_SOURCE_FILES
    "main.cpp"
    # ecs
    "src/engine/ecs/ECSEngine/ECEngine.cpp"
    "src/engine/ecs/ECSEngine/SystemEngine.cpp"
    # # Component 
    "src/engine/ecs/component/IComponent.cpp"
    "src/engine/ecs/component/ComponentManager.cpp"
    # # Entity
    "src/engine/ecs/entity/IEntity.cpp"
    "src/engine/ecs/entity/EntityManager.cpp"
    # # System
    "src/engine/ecs/system/ISystem.cpp"
    "src/engine/ecs/system/SystemManager.cpp"

    # utility
    "src/engine/utility/Logging.cpp"

    # tests 
    "tests/MainTest.cpp"

)

# Setting executable
add_executable(
    "${PROJECT_NAME}" 
    "${PROJECT_SOURCE_FILES}"
)