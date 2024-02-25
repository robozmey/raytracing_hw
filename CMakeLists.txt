cmake_minimum_required(VERSION 3.16.3)
project(raytracing_hw)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME "${PROJECT_NAME}")
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(include glm)
add_executable(raytracing_hw
        src/main.cpp
        src/Position.cpp
        src/Rotation.cpp
        src/Primitives.cpp
        src/Color.cpp
        src/Scene.cpp
        src/SceneRender.cpp)
