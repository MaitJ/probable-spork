#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "../entities/entity.hpp"
#include <memory>


class CollisionManager {
    static std::vector<std::reference_wrapper<Entity>> collision_objects;
public:
    static void addCollidable(Entity& ent);
    static std::vector<std::shared_ptr<Entity const>> getCollidables(Entity const& p_collidable, Context const& ctx);
};

#endif
