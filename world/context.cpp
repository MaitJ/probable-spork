#include "context.hpp"
#include "entities/entity.hpp"
#include <stdexcept>

int Context::ent_counters[2] = {0, 0};

Context::Context() {
}
std::weak_ptr<Entity> Context::createStaticEntity() {
    this->static_ents.push_back(std::make_shared<Entity>(Entity {Context::getNewEntId(EntityType::STATIC), *this}));
    return this->static_ents.back();
}

std::weak_ptr<Entity> Context::createEntity() {
    this->world_ents.push_back(std::make_shared<Entity>(Entity {Context::getNewEntId(EntityType::REGULAR), *this}));
    return this->world_ents.back();
}

std::weak_ptr<Entity> Context::getEntity(int entity_id) {
    for (auto& ent : this->world_ents) {
        if (ent->entity_id == entity_id)
            return ent;
    }
    throw std::invalid_argument("An entity with this id doesn't exist");
}

int Context::getNewEntId(EntityType ent_type) {
    switch (ent_type) {
        case EntityType::REGULAR:
            return ent_counters[EntityType::REGULAR]++;
        case EntityType::STATIC:
            return ent_counters[EntityType::STATIC]++;
    }

    return EntityType::REGULAR;
}
std::vector<std::shared_ptr<Entity>> const& Context::getWorldEnts() const {
    return this->world_ents;
}
