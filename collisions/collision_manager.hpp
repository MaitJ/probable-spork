#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "../entities/entity.hpp"


class CollisionManager {
    static std::vector<std::reference_wrapper<Entity>> collision_objects;
public:
    static void addCollidable(Entity& ent);
    static void checkCollisions();
};

#endif
