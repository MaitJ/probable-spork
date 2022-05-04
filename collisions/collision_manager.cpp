#include "collision_manager.hpp"
#include <functional>
#include <fmt/core.h>

std::vector<std::reference_wrapper<Entity>> CollisionManager::collision_objects = {};
void CollisionManager::addCollidable(Entity& ent) {
    CollisionManager::collision_objects.push_back(std::ref(ent));
}

void CollisionManager::checkCollisions() {
    for (auto& cur_collidable_wrap : CollisionManager::collision_objects) {

        Entity& cur_collidable = cur_collidable_wrap.get();

        glm::vec3 cur_collidable_left = cur_collidable.transform.left();
        glm::vec3 cur_collidable_right = cur_collidable.transform.right();

        for (auto& collidable_wrap : CollisionManager::collision_objects) {
            Entity& collidable = collidable_wrap.get();
            if (&cur_collidable == &collidable)
                continue;

            glm::vec3 collidable_left = collidable.transform.left();
            glm::vec3 collidable_right = collidable.transform.right();

            if ((cur_collidable_left.x <= collidable_right.x && cur_collidable_right.x >= collidable_left.x) &&
               (cur_collidable_left.y <= collidable_right.y && cur_collidable_right.y >= collidable_left.y) &&
               (cur_collidable_left.z <= collidable_right.z && cur_collidable_right.z >= collidable_left.z)) {

                glm::vec3 new_right(.0f);

                if (cur_collidable_left.x <= collidable_right.x && cur_collidable_right.x >= collidable_left.x) {
                    new_right.x = collidable_left.x;
                }

                if (cur_collidable_left.y <= collidable_right.y && cur_collidable_right.y >= collidable_left.y) {
                    new_right.y = collidable_left.y;
                }

                if (cur_collidable_left.z <= collidable_right.z && cur_collidable_right.z >= collidable_left.z) {
                    new_right.z = collidable_left.z;
                }

                cur_collidable.transform.setRight(new_right);
            } else {
                fmt::print("No collision \n");
            }
        }
    }
}
