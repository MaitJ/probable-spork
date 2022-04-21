#include "transform.hpp"


Transform::Transform() {}

Transform::Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions) {
    this->position = position;
    this->orientation = orientation;
    this->dimensions = dimensions;
}

Transform::Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions, RenderableObject* renderable) {
    this->position = position;
    this->orientation = orientation;
    this->dimensions = dimensions;
    this->is_renderable = true;
    this->renderable = renderable;
}

void Transform::attachRenderable(RenderableObject* obj) {
    this->renderable = obj;
    this->is_renderable = true;
}
void Transform::setOrientation(float yaw, float pitch, float roll) {
    this->orientation.y = yaw;
    this->orientation.x = pitch;
    this->orientation.z = roll;

    if (this->is_renderable)
        this->renderable->setOrientation(pitch, yaw, roll);

}
void Transform::setPosition(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;

    if (this->is_renderable)
        this->renderable->setPos(x, y, z);
}
void Transform::setDimensions(float width, float height, float length) {
    this->dimensions.x = width;
    this->dimensions.y = height;
    this->dimensions.z = length;

    if (this->is_renderable)
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
