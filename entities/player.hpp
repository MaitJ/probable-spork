#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"
#include "entity.hpp"

struct Player {

    Player();
    Player(glm::mat4& view_proj, Shader* shader);
    bool isVisible();
    
    Entity game_ent;

private:
    bool is_visible = false;

    RenderableObject render_obj;
    void setupRenderable(glm::mat4& view_proj, Shader* shader);

};

#endif
