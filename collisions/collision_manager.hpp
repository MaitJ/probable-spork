#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "../entities/entity.hpp"


class CollisionManager {
    static std::vector<std::reference_wrapper<const Entity>> collision_objects;
public:
    void addCollidable(Entity const& ent) const;
};

#endif
