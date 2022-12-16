#include "entity.hpp"
#include "renderable_manager.hpp"
#include "../collisions/collision_manager.hpp"
#include <functional>
#include "mesh/primitive/colored_primitive.hpp"


Entity::Entity(int entity_id, Context const& ctx) :    entity_id{entity_id}, wireframe(this->transform, entity_id), ctx(ctx) {
    this->entity_id = entity_id;
}
Entity::Entity(Entity const& old_ent) :  entity_id{old_ent.entity_id}, wireframe(this->transform, old_ent.entity_id), ctx(old_ent.ctx){
}

void Entity::enableWireframe() {
    RenderableManager::addWireframe(this->wireframe);
}

bool Entity::isVisible() {
    return this->is_visible;
}
Renderable::Mesh& Entity::getRenderableObject() {
    return this->mesh;
}

namespace PrimitiveObjects {

	template <PrimitiveShape>
	void loadPrimitive(Entity& ent) {}

	template <>
	void loadPrimitive<PLANE>(Entity& ent) {
        Renderable::Mesh& ent_renderable = ent.getRenderableObject();
        Shader const& colored_shader = ShaderManager::getShader("colored");
        Renderable::Node base_node;
        auto primitive = std::make_shared<Renderable::ColoredPrimitive>(colored_shader);
        base_node.primitives.push_back(primitive);
        primitive->genGlBuffers();
        primitive->bindBuffers();


        std::vector<float> plane_vertices = {
            -1.0f, 0.0f, 1.0f, .0f, 1.0f, .0f,
            1.0f, 0.0f, 1.0f,  .0f, 1.0f, .0f,
            1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f,

            -1.0f, 0.0f, 1.0f,  .0f, 1.0f, .0f,
            -1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f,
            1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f
        };
        primitive->loadPrimitive(plane_vertices, 6);
        primitive->loadColor(glm::vec4(.9f, .9f, .9f, 1.f));
        ent_renderable.nodes.push_back(base_node);

        RenderableManager::addRenderableMesh(&ent_renderable);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
}
