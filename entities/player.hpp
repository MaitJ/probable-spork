#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"

struct Player {

    Player();
    Player(glm::mat4* view_proj, Shader* shader);
    void makeRenderable(glm::mat4* view_proj, Shader* shader);
    void render();
    bool isVisible();
    
    Transform transform;

private:
    bool is_visible = false;

    RenderableObject render_obj;
    void setupRenderable(glm::mat4* view_proj, Shader* shader);

};

#endif
