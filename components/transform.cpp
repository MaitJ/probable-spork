#include "transform.hpp"

Transform::Transform() {}

Transform::Transform(RenderableObject* renderable) : renderable(renderable) {}

Transform::Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions) {
    this->position = position;
    this->orientation = orientation;
    this->dimensions = dimensions;
}

Transform::Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions, RenderableObject* renderable) {
    this->position = position;
    this->orientation = orientation;
    this->dimensions = dimensions;
    this->renderable = renderable;
}

void Transform::attachRenderable(RenderableObject* obj) {
    this->renderable = obj;
}
void Transform::setOrientation(float yaw, float pitch, float roll) {
    this->orientation.y = yaw;
    this->orientation.x = pitch;
    this->orientation.z = roll;

    if (this->renderable != nullptr)
        this->renderable->setOrientation(pitch, yaw, roll);

}
void Transform::setPosition(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;

    if (this->renderable != nullptr)
        this->renderable->setPos(x, y, z);
}
void Transform::setDimensions(float width, float height, float length) {
    this->dimensions.x = width;
    this->dimensions.y = height;
    this->dimensions.z = length;

    if (this->renderable != nullptr)
        this->renderable->setScale(width, height, length);
}
glm::vec3& Transform::getPosition() {
    return this->position;
}
glm::vec3& Transform::getOrientation() {
    return this->orientation;
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
