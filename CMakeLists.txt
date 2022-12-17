cmake_minimum_required(VERSION 3.20)
project(PoeLite)
set(CMAKE_CXX_STANDARD 17)
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(SOURCE_FILES shader.cpp window.cpp engine.cpp shaders/shader_manager.cpp)

set(ENTITY_FILES renderables/mesh/node.cpp renderables/world_light.cpp
        renderables/entities/camera.cpp renderables/entities/player.cpp renderables/renderable_manager.cpp
        renderables/entities/entity.cpp renderables/wireframe.cpp renderables/mesh/mesh.cpp
        renderables/mesh/primitive/primitive.cpp renderables/mesh/primitive/colored_primitive.cpp renderables/mesh/primitive/textured_primitive.cpp
        renderables/entities/primitive_entity_factory.cpp)
set(EVENT_FILES events/event_handler.cpp events/subscriber.cpp)
set(CONTROL_FILES controls/mouse.cpp controls/keyboard.cpp)
set(UTILITY_FILES utilities/obj.cpp utilities/matrices.cpp
    utilities/deltatime.cpp utilities/gltf_loader.cpp utilities/logger.cpp)
set(WORLD_FILES world/context.cpp)
set(COMPONENT_FILES components/transform.cpp)
set(COLLISION_FILES collisions/collision_manager.cpp)

set(INCLUDE_PATHS utilities renderables events components collisions world deps ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATHS})

add_library(source ${SOURCE_FILES} ${ENTITY_FILES} ${EVENT_FILES}
    ${CONTROL_FILES} ${UTILITY_FILES} ${INCLUDE_PATHS} ${COMPONENT_FILES}
    ${COLLISION_FILES} ${WORLD_FILES})
target_link_libraries(${PROJECT_NAME} source)
target_include_directories(source PRIVATE ${INCLUDE_PATHS})

add_subdirectory("${DEPS_DIR}/glfw")
target_link_libraries(source glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(source OpenGL::GL)

find_package(fmt)
target_link_libraries(source fmt::fmt)

add_custom_target(assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} assets)

add_custom_target(shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)
add_dependencies(${PROJECT_NAME} shaders)

add_library(glad STATIC "${DEPS_DIR}/glad/glad.c")
target_include_directories(glad PUBLIC "${DEPS_DIR}/")
target_link_libraries(source glad)

add_subdirectory("${DEPS_DIR}/glm")
target_link_libraries(source glm)

add_subdirectory(tests)
