#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>

class Entity;
#include "../entities/entity.hpp"

struct Player;
#include "../entities/player.hpp"

class Context {
    static int ent_counter;
    static int getNewEntId();
    std::vector<Entity> world_ents;

public:
    Context();
    Entity& createEntity();
    Entity& getEntity(int entity_id);
};

#endif
