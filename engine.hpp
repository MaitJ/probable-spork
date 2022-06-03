#ifndef ENGINE_H
#define ENGINE_H

#include <glm/glm.hpp>
#include "shader.hpp"
#include "window.hpp"
#include "entities/camera.hpp"
#include "entities/world_light.hpp"
#include "entities/player.hpp"
#include "entities/renderable_manager.hpp"
#include "world/context.hpp"
#include "deltatime.hpp"
#include <chrono>
#include "shaders/shader_manager.hpp"

#define VERTEX_SHADER_FILE "vertex_shader.vert"
#define FRAGMENT_SHADER_FILE "fragment_shader.frag"

class Engine {

    GameWindow game_window;
    glm::mat4& view_proj;
    glm::mat4 const& persp_proj;
    Camera camera;
    WorldLight world_light;
    Context ctx;
    DeltaTime dt;
    ShaderManager shader_manager;


    glm::mat4 createPerspectiveMatrix(float window_width, float window_height, float fov);

    void initializeShaders();

public:
    Engine(float window_width, float window_height, float fov);
    void start();
    void close();
    void updateDt(std::chrono::time_point<std::chrono::high_resolution_clock> begin, std::chrono::time_point<std::chrono::high_resolution_clock> end);
};

#endif
