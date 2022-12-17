#include "entity.hpp"
#include "renderable_manager.hpp"
#include <functional>
#include "mesh/primitive/colored_primitive.hpp"


Entity::Entity(int entity_id, Context const& ctx) :    entity_id{entity_id}, wireframe(this->transform, entity_id), ctx(ctx) {
    this->entity_id = entity_id;
}
Entity::Entity(Entity const& old_ent) :  entity_id{old_ent.entity_id}, wireframe(this->transform, old_ent.entity_id), ctx(old_ent.ctx){
}

void Entity::enableWireframe() {
    RenderableManager::addWireframe(this->wireframe);
}

bool Entity::isVisible() {
    return this->is_visible;
}
Renderable::Mesh& Entity::getRenderableObject() {
    return this->mesh;
}
