cmake_minimum_required(VERSION 3.20)
project(PoeLite)
set(CMAKE_CXX_STANDARD 23)
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(SOURCE_FILES shader.cpp window.cpp utilities/obj.cpp
    entities/renderable_object.cpp entities/world_light.cpp entities/camera.cpp
    events/event_handler.cpp events/subscriber.cpp controls/mouse.cpp
    controls/keyboard.cpp utilities/matrices.cpp)
set(INCLUDE_PATHS utilities entities ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE utilities)
target_include_directories(${PROJECT_NAME} PRIVATE entities)
target_include_directories(${PROJECT_NAME} PRIVATE events)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(source ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} source)
target_include_directories(source PRIVATE utilities)
target_include_directories(source PRIVATE entities)
target_include_directories(source PRIVATE events)
target_include_directories(source PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("${DEPS_DIR}/glfw")
target_link_libraries(source glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(source OpenGL::GL)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex_shader.vert"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex_shader.vert")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment_shader.frag"
    "${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment_shader.frag")

add_library(glad STATIC "${DEPS_DIR}/glad/glad.c")
target_include_directories(glad PUBLIC "${DEPS_DIR}/")
target_link_libraries(source glad)

add_subdirectory("${DEPS_DIR}/glm")
target_link_libraries(source glm)

add_subdirectory(tests)
