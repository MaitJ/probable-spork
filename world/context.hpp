#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <memory>

class Entity;
#include "../entities/entity.hpp"

struct Player;
#include "../entities/player.hpp"

enum EntityType {
    REGULAR = 0,
    STATIC = 1
};

class Context {
    //static int ent_counter;
    // [0] regular entities [1] static entities
    static int ent_counters[];
    static int getNewEntId(EntityType ent_type);
    //If there is a need for static objects without collisions
    //then make separate container for those
    std::vector<std::shared_ptr<Entity>> world_ents;
    std::vector<std::shared_ptr<Entity>> static_ents;

public:
    Context();
    //These can be weak pointers because, there will not be a case
    //where entities should be destroyed before the context
    std::weak_ptr<Entity> createEntity();
    std::weak_ptr<Entity> getEntity(int entity_id);
    std::vector<std::shared_ptr<Entity>> const& getWorldEnts() const;    
    std::weak_ptr<Entity> createStaticEntity();

    //Variables
    float gravity = 3.f;
};

#endif
