#include "collision_manager.hpp"
#include <functional>
#include <fmt/core.h>

std::vector<std::reference_wrapper<Entity>> CollisionManager::collision_objects = {};
void CollisionManager::addCollidable(Entity& ent) {
    CollisionManager::collision_objects.push_back(std::ref(ent));
}

void CollisionManager::checkCollisions() {
    for (auto& cur_collidable_wrap : CollisionManager::collision_objects) {

        Entity const& cur_collidable = cur_collidable_wrap.get();

        glm::vec3 cur_collidable_left = cur_collidable.transform.left();
        glm::vec3 cur_collidable_right = cur_collidable.transform.right();

        for (auto& collidable_wrap : CollisionManager::collision_objects) {
            Entity const& collidable = collidable_wrap.get();
            if (&cur_collidable == &collidable)
                continue;

            glm::vec3 collidable_left = collidable.transform.left();
            glm::vec3 collidable_right = collidable.transform.right();

            if (cur_collidable_left.x <= collidable_right.x && cur_collidable_right.x >= collidable_left.x) {
                fmt::print("X axis collision\n");
            } else {
                fmt::print("No collision \n");
            }
        }
    }
}
