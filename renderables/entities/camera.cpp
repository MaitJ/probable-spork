#include "camera.hpp"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/gtx/quaternion.hpp"
#include "event_handler.hpp"
#include <functional>
#include <iostream>
#include "matrices.cpp"
#include <fmt/core.h>

void Camera::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

//This bugs the camera out
void Camera::setRotation(float angle, glm::vec3 axis) {
    this->camera_mat = glm::rotate(this->camera_mat, angle, axis);
}
glm::mat4& Camera::getCameraMat() {
    return this->camera_mat;
}

void Camera::recalcMatrix() {

    if (this->orientation.x > 179.f) {
        this->orientation.x = -179.f;
    } else if (this->orientation.x < -179.f) {
        this->orientation.x = 179.f;
    }
    
    if (this->orientation.y > 89.9f) {
        this->orientation.y = 89.9f;
    } else if (this->orientation.y <= -89.9f) {
        this->orientation.y = -89.9f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(-this->orientation.x)) * cos(glm::radians(this->orientation.y));
    direction.z = sin(glm::radians(-this->orientation.x)) * cos(glm::radians(this->orientation.y));
    direction.y = sin(glm::radians(this->orientation.y));

    this->camera_front = glm::normalize(direction);

    this->camera_mat = Matrices::lookat(this->position, this->position + this->camera_front, this->camera_up);
}

glm::vec3& Camera::getCameraPos() {
    return this->position;
}
glm::vec3& Camera::getCameraFront() {
    return this->camera_front;
}

Camera::Camera(glm::mat4& view_proj) : view_proj(view_proj) {
    EventHandler::registerSubscriber<glm::vec2, EventType::CAMERA_ORIENTATION>(this, &Camera::onOrientationChange);
}

void Camera::onOrientationChange(glm::vec2 rotation) {
    this->orientation.x += rotation.x;
    this->orientation.y += rotation.y;
}
