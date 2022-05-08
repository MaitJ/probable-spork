#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"
#include "entity.hpp"
#include "camera.hpp"

class Context;

struct Player {

    Player(Camera& camera, Context& ctx);
    Player(glm::mat4& view_proj, Shader* shader, Camera& camera, Context& ctx);
    bool isVisible();
    void onMove(Direction dir);
    
    Entity& game_ent;
    Camera& camera;

private:
    bool is_visible = false;

    RenderableObject render_obj;
    void setupRenderable(glm::mat4& view_proj, Shader* shader);

};

#endif
