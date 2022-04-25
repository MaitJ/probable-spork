#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class RenderableObject;
#include "../entities/renderable_object.hpp"

class Transform {

    bool is_renderable = false;
    RenderableObject* renderable = nullptr;
    glm::vec3 position = glm::vec3(1.f);
    glm::vec3 orientation = glm::vec3(1.f);
    glm::vec3 dimensions = glm::vec3(1.f);

public:
    Transform();
    Transform(RenderableObject* renderable);
    Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions);
    Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions, RenderableObject* renderable);

    void attachRenderable(RenderableObject* obj);

    void setOrientation(float yaw, float pitch, float roll);
    void setPosition(float x, float y, float z);
    void setDimensions(float width, float height, float length);

    glm::vec3& getOrientation();
    glm::vec3& getPosition();
    glm::vec3& getDimensions();
};

#endif

