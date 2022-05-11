#include "context.hpp"
#include <stdexcept>

int Context::ent_counter = 0;

Context::Context() {
}

std::weak_ptr<Entity> Context::createEntity() {
    this->world_ents.push_back(std::make_shared<Entity>(Entity {Context::getNewEntId(), *this}));
    return this->world_ents.back();
}

std::weak_ptr<Entity> Context::getEntity(int entity_id) {
    for (auto& ent : this->world_ents) {
        if (ent->entity_id == entity_id)
            return ent;
    }
    throw std::invalid_argument("An entity with this id doesn't exist");
}

int Context::getNewEntId() {
    return ent_counter++;
}
std::vector<std::shared_ptr<Entity>> const& Context::getWorldEnts() const {
    return this->world_ents;
}
