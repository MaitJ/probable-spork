#include "collision_manager.hpp"
#include <functional>
#include <fmt/core.h>
#include "../world/context.hpp"

std::vector<std::reference_wrapper<Entity>> CollisionManager::collision_objects = {};
void CollisionManager::addCollidable(Entity& ent) {
    CollisionManager::collision_objects.push_back(std::ref(ent));
}


std::vector<std::shared_ptr<Entity const>> CollisionManager::getCollidables(Entity const& p_collidable, Context const& ctx) {
    using namespace std;
    std::vector<std::shared_ptr<Entity const>> collidables;
    
    glm::vec3 p_collidable_left = p_collidable.transform.left();
    glm::vec3 p_collidable_right = p_collidable.transform.right();

    for (shared_ptr<Entity> const& m_collidable : ctx.getWorldEnts()) {
        if (&p_collidable == m_collidable.get())
            continue;

        glm::vec3 m_collidable_left = m_collidable->transform.left();
        glm::vec3 m_collidable_right = m_collidable->transform.right();

        if ((p_collidable_left.x < m_collidable_right.x && p_collidable_right.x > m_collidable_left.x) &&
           (p_collidable_left.y < m_collidable_right.y && p_collidable_right.y > m_collidable_left.y) &&
           (p_collidable_left.z < m_collidable_right.z && p_collidable_right.z > m_collidable_left.z)) {

            collidables.push_back(m_collidable);

        } 
    }

    return collidables;
}

