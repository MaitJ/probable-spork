#include "mouse.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <event_handler.hpp>
#include <iostream>

glm::highp_vec2 Mouse::prev_pos = glm::highp_vec2(.0f);
float Mouse::sensitivity = 1.0f;
glm::vec3 Mouse::rotation(.0f, .0f, .0f);

void Mouse::movement_callback(GLFWwindow* window, double xpos, double ypos) {
    glm::highp_vec2 new_pos(xpos, ypos);
    glm::highp_vec2 difference = Mouse::prev_pos - new_pos;
    glm::highp_vec2 norm = glm::normalize(difference) / 5.0f;
    norm *= Mouse::sensitivity;

    EventHandler::emitEvent<glm::vec2>(Event<glm::vec2>(EventType::CAMERA_ORIENTATION, norm));

    Mouse::prev_pos.x = xpos;
    Mouse::prev_pos.y = ypos;
}
