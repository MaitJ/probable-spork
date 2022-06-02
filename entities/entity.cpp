#include "entity.hpp"
#include "renderable_manager.hpp"
#include "../collisions/collision_manager.hpp"
#include <functional>


Entity::Entity(int entity_id, Context const& ctx) :    entity_id{entity_id}, wireframe(this->transform, entity_id), renderable(false), ctx(ctx) {
    this->entity_id = entity_id;
}
Entity::Entity(Entity const& old_ent) :  entity_id{old_ent.entity_id}, wireframe(this->transform, old_ent.entity_id), renderable(old_ent.renderable), ctx(old_ent.ctx){
}

void Entity::enableWireframe() {
    this->is_wireframed = true;
    RenderableManager::addWireframe(this->wireframe);
}
void Entity::loadModel(const std::string obj_file, const std::string texture_file) {
    //Currently doesn't have a MVP matrix
    this->renderable.loadModel(obj_file, texture_file);
    //this->transform.attachRenderable(&this->renderable);
}

//
/* 
void Entity::enableCollisions() {
    CollisionManager::addCollidable(*this);
}
*/

bool Entity::isVisible() {
    return this->is_visible;
}
Node& Entity::getRenderableObject() {
    return this->renderable;
}

namespace PrimitiveObjects {

	template <PrimitiveShape>
	void loadPrimitive(Entity& ent) {}

	template <>
	void loadPrimitive<PLANE>(Entity& ent) {
        Node& ent_renderable = ent.getRenderableObject();
        ent_renderable.genBuffers();
        ent_renderable.glBind();

        ent_renderable.view_proj = RenderableManager::getViewProjMat();
        float plane_vertices[] = {
            -1.0f, 0.0f, 1.0f, .0f, .0f, .0f, 1.0f, .0f,
            1.0f, 0.0f, 1.0f, .0f, .0f, .0f, 1.0f, .0f,
            1.0f, 0.0f, -1.0f, .0f, .0f, .0f, 1.0f, .0f,

            -1.0f, 0.0f, 1.0f, .0f, .0f, .0f, 1.0f, .0f,
            -1.0f, 0.0f, -1.0f, .0f, .0f, .0f, 1.0f, .0f,
            1.0f, 0.0f, -1.0f, .0f, .0f, .0f, 1.0f, .0f
        };

        ent_renderable.total_vertices.push_back(6);
        ent_renderable.primitive_offsets = new unsigned int[1] {0};
        ent_renderable.primitives_count = 1;

        glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        RenderableManager::addRenderable(&ent_renderable);
        ent.transform.attachRenderable(&ent_renderable);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
}
