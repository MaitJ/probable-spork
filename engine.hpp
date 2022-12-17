#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>
#include "shader.hpp"
#include "window.hpp"
#include <glm/glm.hpp>
#include "deltatime.hpp"
#include "world/context.hpp"
#include "shaders/shader_manager.hpp"
#include "renderables/world_light.hpp"
#include "renderables/entities/camera.hpp"
#include "renderables/entities/player.hpp"
#include "renderables/renderable_manager.hpp"

class Engine {

    GameWindow game_window;
    glm::mat4& view_proj;
    glm::mat4 const& persp_proj;
    Camera camera;
    Context ctx;
    DeltaTime dt;

public:
    Engine(float window_width, float window_height);
    void start();
    void close();
    void updateDt(std::chrono::time_point<std::chrono::high_resolution_clock> begin, std::chrono::time_point<std::chrono::high_resolution_clock> end);
};

#endif
