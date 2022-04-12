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
    std::function<void()> callback_fn = std::bind(&WorldLight::onLightToggle, this);
    EventHandler::registerSubscriber<EventType::LIGHT_TOGGLE>(callback_fn);

    std::function<void(int)> move_left_callback = std::bind(&WorldLight::onMoveLeft, this, std::placeholders::_1);
    EventHandler::registerSubscriber<int, EventType::MOVE_LEFT>(move_left_callback);
}

void WorldLight::onLightToggle() const {
    std::cout << "Got light toggle event" << std::endl;
}

void WorldLight::onMoveLeft(int units) {
    std::cout << "Move left, units: " << units << std::endl;
}



