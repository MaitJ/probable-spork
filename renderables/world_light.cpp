#include "world_light.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <functional>
#include <events.hpp>
#include <event_handler.hpp>

void WorldLight::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

WorldLight::WorldLight() {
}



