#include "collision_manager.hpp"
#include <functional>
#include <fmt/core.h>

std::vector<std::reference_wrapper<Entity>> CollisionManager::collision_objects = {};
void CollisionManager::addCollidable(Entity& ent) {
    CollisionManager::collision_objects.push_back(std::ref(ent));
}

//Move collisions to context base
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

                glm::vec3& cur_col_pos = cur_collidable.transform.getPosition();
                glm::vec3 cur_col_dim = cur_collidable.transform.getDimensions();

                //Resolve collision on x axis
                if (cur_collidable_left.x <= collidable_right.x && cur_collidable_right.x >= collidable_left.x) {
                    if (cur_collidable_left.x <= collidable_right.x) {
                        //Set cur_collidable left to collidable_right
                        cur_col_pos.x = collidable_right.x;
                        cur_col_pos.x += cur_col_dim.x;
                    }

                    if (cur_collidable_right.x >= collidable_left.x) {
                        cur_col_pos.x = collidable_left.x;
                        cur_col_pos.x -= cur_col_dim.x;
                    }
                }

                if (cur_collidable_left.y <= collidable_right.y && cur_collidable_right.y >= collidable_left.y) {
                    if (cur_collidable_left.y <= collidable_right.y) {
                        cur_col_pos.y = collidable_right.y;
                        cur_col_pos.y += cur_col_dim.y;
                    }

                    if (cur_collidable_right.y >= collidable_left.y) {
                        cur_col_pos.y = collidable_left.y;
                        cur_col_pos.y -= cur_col_dim.y;
                    }
                }


                if (cur_collidable_left.z <= collidable_right.z && cur_collidable_right.z >= collidable_left.z) {
                    if (cur_collidable_left.z <= collidable_right.z) {
                        cur_col_pos.z = collidable_right.z;
                        cur_col_pos.z += cur_col_dim.z;
                    }

                    if (cur_collidable_right.z >= collidable_left.z) {
                        cur_col_pos.z = collidable_left.z;
                        cur_col_pos.z -= cur_col_dim.z;
                    }
                }


                fmt::print("New pos: ({0:.2f}, {1:.2f}, {2:.2f})\n", cur_col_pos.x, cur_col_pos.y, cur_col_pos.z);
                //cur_collidable.transform.setRight(new_right);
            } else {
                //fmt::print("No collision \n");
            }
        }
    }
}
