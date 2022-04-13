#include "mouse.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <event_handler.hpp>

glm::highp_vec2 Mouse::prev_pos = glm::highp_vec2(.0f);
float Mouse::sensitivity = 1.0f;

void Mouse::movement_callback(GLFWwindow* window, double xpos, double ypos) {
    glm::highp_vec2 new_pos(xpos, ypos);
    glm::highp_vec2 difference = Mouse::prev_pos - new_pos;

    glm::mat4 camera_movement(1.0f);
    if (difference.x < prev_pos.x) {
        camera_movement = glm::rotate(camera_movement, glm::radians(difference.x), glm::vec3(.0f, -1.0f, .0f));
    } else if (difference.x > prev_pos.x) {
        camera_movement = glm::rotate(camera_movement, glm::radians(difference.x), glm::vec3(.0f, 1.0f, .0f));
    } 
    if (difference.y < prev_pos.y) {
        camera_movement = glm::rotate(camera_movement, glm::radians(-difference.y), glm::vec3(1.0f, .0f, .0f));
    } else {
        camera_movement = glm::rotate(camera_movement, glm::radians(difference.y), glm::vec3(1.0f, .0f, .0f));
    }


    EventHandler::emitEvent<glm::mat4>(Event<glm::mat4>(EventType::CAMERA_MOVEMENT, camera_movement));

    Mouse::prev_pos.x = xpos;
    Mouse::prev_pos.y = ypos;
}
