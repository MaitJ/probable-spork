#include "world_light.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <functional>
#include <events.hpp>
#include <event_handler.hpp>

void WorldLight::setPosition(float x, float y, float z) {
    assert(this->shader != nullptr);

    this->shader->use();
    this->position = glm::vec3(x, y, z);

    int light_pos_loc = glGetUniformLocation(this->shader->id, "light_pos");
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(this->position));
    
    this->shader->unbind();
}

WorldLight::WorldLight() {
    std::function<void(int)> on_toggle = std::bind(&WorldLight::onLightToggle, this, std::placeholders::_1);
    EventArgs<int> on_toggle_event(EventType::LIGHT_TOGGLE, 5);
    EventHandler::registerSubscriber<int>(on_toggle_event, on_toggle);
}


void WorldLight::onLightToggle(int value) const {
    std::cout << "Received light toggle event in WorldLight, received value: " << value << std::endl;
}
