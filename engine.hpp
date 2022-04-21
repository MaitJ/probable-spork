#ifndef ENGINE_H
#define ENGINE_H

#include <glm/glm.hpp>
#include "shader.hpp"
#include "window.hpp"
#include "entities/camera.hpp"
#include "entities/world_light.hpp"
#include "entities/player.hpp"
#include "entities/renderable_manager.hpp"

#define VERTEX_SHADER_FILE "vertex_shader.vert"
#define FRAGMENT_SHADER_FILE "fragment_shader.frag"

class Engine {

    GameWindow game_window;
    Shader default_shader;
    glm::mat4 view_proj = glm::mat4(1.0f);
    const glm::mat4 persp_proj;
    Camera camera;
    WorldLight world_light;

    glm::mat4 createPerspectiveMatrix(float window_width, float window_height, float fov);

public:
    Engine(float window_width, float window_height, float fov);
    void start();
    void close();
};

#endif
