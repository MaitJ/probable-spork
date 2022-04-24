#include "entity.hpp"
#include "renderable_manager.hpp"

Entity::Entity() {}

void Entity::enableWireframe() {
    this->renderable.enableWireframe(this->transform);
}
void Entity::loadModel(const std::string obj_file, const std::string texture_file) {
    //Currently doesn't have a MVP matrix
    this->renderable.loadModel(obj_file, texture_file);
    this->transform.attachRenderable(&this->renderable);
}

bool Entity::isVisible() {
    return this->is_visible;
}
RenderableObject& Entity::getRenderableObject() {
    return this->renderable;
}

namespace PrimitiveObjects {

	template <PrimitiveShape>
	void loadPrimitive(Entity& ent) {}

	template <>
	void loadPrimitive<PLANE>(Entity& ent) {
        RenderableObject& ent_renderable = ent.getRenderableObject();
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
        ent_renderable.calcModel();

        ent_renderable.total_vertices = 6;

        glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        RenderableManager::addRenderable(&ent_renderable);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
}
