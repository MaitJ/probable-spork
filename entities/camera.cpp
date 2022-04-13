#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <event_handler.hpp>
#include <functional>

void Camera::setPosition(float x, float y, float z) {
    this->camera_mat = glm::translate(this->camera_mat, glm::vec3(x, y, z));
}
void Camera::setRotation(float angle, glm::vec3 axis) {
    this->camera_mat = glm::rotate(this->camera_mat, angle, axis);
}
glm::mat4& Camera::getCameraMat() {
    return this->camera_mat;
}

Camera::Camera() {
    EventHandler::registerSubscriber<glm::mat4, EventType::CAMERA_MOVEMENT>(std::bind(&Camera::onMove, this, std::placeholders::_1));
}

void Camera::onMove(glm::mat4 movement) {
    this->camera_mat = movement * this->camera_mat;
}
