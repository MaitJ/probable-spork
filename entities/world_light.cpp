#include "world_light.hpp"
#include <glm/gtc/type_ptr.hpp>

void WorldLight::setPosition(float x, float y, float z) {
    assert(this->shader != nullptr);

    this->shader->use();
    this->position = glm::vec3(x, y, z);

    int light_pos_loc = glGetUniformLocation(this->shader->id, "light_pos");
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(this->position));
    
    this->shader->unbind();
}
