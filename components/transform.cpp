#include "transform.hpp"

#include <glm/gtc/quaternion.hpp>

Transform::Transform() {}

Transform::Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions) {
    this->position = position;
    this->orientation = orientation;
    this->dimensions = dimensions;
}

void Transform::setOrientation(float yaw, float pitch, float roll) {
    this->orientation.x = pitch;
    this->orientation.y = yaw;
    this->orientation.z = roll;


}
void Transform::setPosition(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;

}
void Transform::setDimensions(float width, float height, float length) {
    this->dimensions.x = width;
    this->dimensions.y = height;
    this->dimensions.z = length;

}
glm::vec3& Transform::getPosition() {
    return this->position;
}
glm::vec3& Transform::getOrientation() {
    return this->orientation;
}
glm::quat Transform::getRotation() {
    return glm::quat(glm::vec3(glm::radians(this->orientation.x), glm::radians(this->orientation.y), glm::radians(this->orientation.z)));
}
glm::vec3& Transform::getDimensions() {
    return this->dimensions;
}
glm::vec3 Transform::left() const {
    glm::vec3 left(.0f);

    left.x = this->position.x - (this->dimensions.x / 2.0f);
    left.y = this->position.y - (this->dimensions.y / 2.0f);
    left.z = this->position.z - (this->dimensions.z / 2.0f);
    return left;
}
glm::vec3 Transform::right() const {
    glm::vec3 right(.0f);

    right.x = this->position.x + (this->dimensions.x / 2.0f);
    right.y = this->position.y + (this->dimensions.y / 2.0f);
    right.z = this->position.z + (this->dimensions.z / 2.0f);
    return right;
}

void Transform::setLeft(glm::vec3 left) {
    this->position.x = left.x + (this->dimensions.x / 2.0f);
    this->position.y = left.y + (this->dimensions.y / 2.0f);
    this->position.z = left.z + (this->dimensions.z / 2.0f);
}
void Transform::setRight(glm::vec3 right) {
    this->position.x = right.x - (this->dimensions.x / 2.0f);
    this->position.y = right.y - (this->dimensions.y / 2.0f);
    this->position.z = right.z - (this->dimensions.z / 2.0f);
}

auto Transform::getTransformationMatrix() -> glm::mat4 {
    // Scale -> Rotate -> Transform
    glm::mat4 transformation_matrix(1.f);

    glm::mat4 scale_mat= glm::scale(transformation_matrix, this->dimensions);
    glm::mat4 rotation_mat = glm::mat4_cast(this->getRotation());
    glm::mat4 translation_mat = glm::translate(transformation_matrix, this->position);

    return translation_mat * rotation_mat * scale_mat;
}
