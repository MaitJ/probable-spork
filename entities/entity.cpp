#include "entity.hpp"

Entity::Entity() {}

Entity::~Entity() {
    if (renderable != nullptr)
        delete renderable;
}

void Entity::attachRenderable(RenderableObject* renderable) {
    this->renderable = renderable;
}

bool Entity::isVisible() {
    return this->is_visible;
}
