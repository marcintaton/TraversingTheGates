cmake_minimum_required(VERSION 3.0.0)
project("traversing_the_gates")

# Flags constants
SET(CUSTOM_COMPILE_FLAGS "-std=c++17")
SET(CUSTOM_LINK_FLAGS "-lGL -lglfw")

# Adding flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINK_FLAGS}") 

# Source files
SET(PROJECT_SOURCE_FILES 
    "main.cpp"
    # ecs
    "src/ecs/ECSEngine.cpp"
    "src/ecs/entity/entityManager.cpp"
    "src/ecs/component/componentManager.cpp"
    # unit tests
    "utests/eventTests.cpp"
)


add_executable(
    "${PROJECT_NAME}" 
    "${PROJECT_SOURCE_FILES}"
)