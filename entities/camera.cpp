#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>

void Camera::setPosition(float x, float y, float z) {
    this->camera_mat = glm::translate(this->camera_mat, glm::vec3(x, y, z));
}
void Camera::setRotation(float angle, glm::vec3 axis) {
    this->camera_mat = glm::rotate(this->camera_mat, angle, axis);
}
glm::mat4& Camera::getCameraMat() {
    return this->camera_mat;
}
