#include "mouse.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <event_handler.hpp>
#include <iostream>
#include <cmath>

glm::highp_vec2 Mouse::prev_pos = glm::highp_vec2(.0f);
float Mouse::sensitivity = 1.0f;
glm::vec3 Mouse::rotation(.0f, .0f, .0f);

void Mouse::movement_callback(GLFWwindow* window, double xpos, double ypos) {
    
    
    glm::highp_vec2 new_pos(xpos, ypos);
    glm::highp_vec2 difference = (Mouse::prev_pos - new_pos) / 5.0f;
    difference *= Mouse::sensitivity;

    if (difference.x > 1.0f)
        difference.x = 1.0f;
    else if (difference.x < -1.0f)
        difference.x = -1.0f;

    if (difference.y > 1.0f)
        difference.y = 1.0f;
    else if (difference.y < -1.0f)
        difference.y = -1.0f;


    EventHandler::emitEvent<glm::vec2>(Event<glm::vec2>(EventType::CAMERA_ORIENTATION, difference));

    Mouse::prev_pos.x = xpos;
    Mouse::prev_pos.y = ypos;
}
