#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <event_handler.hpp>
#include <functional>
#include <iostream>
#include "../utilities/matrices.cpp"

void Camera::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    recalcMatrix();
}

//This bugs the camera out
void Camera::setRotation(float angle, glm::vec3 axis) {
    this->camera_mat = glm::rotate(this->camera_mat, angle, axis);
}
glm::mat4& Camera::getCameraMat() {
    return this->camera_mat;
}

void Camera::recalcMatrix() {

    if (this->orientation.x >= 180.0f) {
        this->orientation.x = -180.0f;
    } else if (this->orientation.x <= -180.f) {
        this->orientation.x = 180.0f;
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

    //this->camera_mat = glm::lookAt(this->position, this->position + this->camera_front, this->camera_up);
    this->camera_mat = Matrices::lookat(this->position, this->position + this->camera_front, this->camera_up);
}

Camera::Camera(glm::mat4* view_proj) {
    this->view_proj = view_proj;
    recalcMatrix();
    EventHandler::registerSubscriber<glm::vec2, EventType::CAMERA_ORIENTATION>(std::bind(&Camera::onOrientationChange, this, std::placeholders::_1));
    EventHandler::registerSubscriber<Direction, EventType::CAMERA_MOVEMENT>(std::bind(&Camera::onMove, this, std::placeholders::_1));
}

void Camera::onMove(Direction dir) {
    switch (dir) {
        case Direction::FORWARD:
            this->position += this->camera_front * 5.f;
        break;
        case Direction::BACK:
            this->position -= this->camera_front * 5.f;
        break;
        case Direction::LEFT:
            this->position -= glm::cross(camera_front, camera_up) * 5.f;
        break;
        case Direction::RIGHT:
            this->position += glm::cross(camera_front, camera_up) * 5.f;
        break;
    }
    recalcMatrix();
}

void Camera::onOrientationChange(glm::vec2 rotation) {
    std::cout << "x: " << orientation.x << " y: " << orientation.y << std::endl;
    this->orientation.x += rotation.x;
    this->orientation.y += rotation.y;
    recalcMatrix();
}
