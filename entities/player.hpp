#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "renderable_object.hpp"

struct Player {

    Player();
    Player(glm::mat4* view_proj, Shader* shader);
    void makeRenderable(glm::mat4* view_proj, Shader* shader);
    void render();

    void setOrientation(float yaw, float pitch, float roll);
    glm::vec3& getOrientation();
    void setPosition(float x, float y, float z);
    glm::vec3& getPosition();
    void setDimensions(float width, float height, float length);
    glm::vec3& getDimensions();
    bool isVisible();
    
private:
    glm::vec3 orientation = glm::vec3(0.f,0.f,.0f);
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 dimensions = glm::vec3(.0f);
    bool is_visible = false;

    RenderableObject render_obj;
    glm::mat4* view_proj = nullptr;


};

#endif
