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
glm::vec3 const& Transform::getPosition() const {
    return this->position;
}
glm::vec3 const& Transform::getOrientation() const {
    return this->orientation;
}
glm::vec3 const& Transform::getDimensions() const {
    return this->dimensions;
}
