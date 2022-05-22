cmake_minimum_required(VERSION 3.20)
project(PoeLite)
set(CMAKE_CXX_STANDARD 17)
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(SOURCE_FILES shader.cpp window.cpp engine.cpp)

set(ENTITY_FILES entities/renderable_object.cpp entities/world_light.cpp
    entities/camera.cpp entities/player.cpp entities/renderable_manager.cpp
    entities/entity.cpp entities/wireframe.cpp)
set(EVENT_FILES events/event_handler.cpp events/subscriber.cpp)
set(CONTROL_FILES controls/mouse.cpp controls/keyboard.cpp)
set(UTILITY_FILES utilities/obj.cpp utilities/matrices.cpp
    utilities/deltatime.cpp utilities/gltf_loader.cpp)
set(WORLD_FILES world/context.cpp)
set(COMPONENT_FILES components/transform.cpp)
set(COLLISION_FILES collisions/collision_manager.cpp)

set(INCLUDE_PATHS utilities entities events components collisions world deps ${CMAKE_CURRENT_SOURCE_DIR})

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

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex_shader.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex_shader.vert")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment_shader.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment_shader.frag")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/tests/test_obj.obj"
    "${CMAKE_CURRENT_BINARY_DIR}/tests/test_obj.obj")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.sh"
    "${CMAKE_CURRENT_BINARY_DIR}/tests.sh")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/wf_vertex_shader.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/wf_vertex_shader.vert")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/wf_fragment_shader.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/wf_fragment_shader.frag")

add_library(glad STATIC "${DEPS_DIR}/glad/glad.c")
target_include_directories(glad PUBLIC "${DEPS_DIR}/")
target_link_libraries(source glad)

add_subdirectory("${DEPS_DIR}/glm")
target_link_libraries(source glm)

add_subdirectory(tests)
