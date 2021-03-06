#ifndef WORLD_LIGHT_H
#define WORLD_LIGHT_H

#include <glm/glm.hpp>
#include "shader.hpp"

struct WorldLight {
    WorldLight();

    glm::vec3 position;

    void setPosition(float x, float y, float z);
};

#endif
