#include "wireframe.hpp"
#include "renderable_manager.hpp"
#include <fmt/core.h>
#include "mesh/mesh.hpp"
#include "mesh/primitive/colored_primitive.hpp"

Wireframe::Wireframe(Transform& ent_transform, int entity_id) : entity_id{entity_id}, ent_transform(ent_transform)  {}

Renderable::Node Wireframe::wf_renderable = Renderable::Node();

void Wireframe::initWireframeModel() {
    Shader const& colored_shader = ShaderManager::getShader("colored");
    auto primitive = std::make_shared<Renderable::ColoredPrimitive>(colored_shader);
    wf_renderable.primitives.push_back(primitive);
    primitive->genGlBuffers();
    primitive->bindBuffers();

    std::vector<float> wf_vertices = {
        //Front triangles
        -1.f, -1.0f, 1.f,
        1.f, -1.0f, 1.f,
        -1.f, 1.0f, 1.f,
        1.f, -1.0f, 1.f,
        1.f, 1.0f, 1.f,
        -1.f, 1.0f, 1.f,

        //Back triangles
        -1.f, -1.0f, -1.f,
        1.f, -1.0f, -1.f,
        -1.f, 1.0f, -1.f,
        1.f, -1.0f, -1.f,
        1.f, 1.0f, -1.f,
        -1.f, 1.0f, -1.f,

        //Left side
        -1.f, -1.0f, 1.f,
        -1.f, -1.0f, -1.f,
        -1.f, 1.0f, 1.f,

        -1.f, -1.0f, -1.f,
        -1.f, 1.0f, -1.f,
        -1.f, 1.0f, 1.f,

        //Right side
        1.f, -1.0f, 1.f,
        1.f, -1.0f, -1.f,
        1.f, 1.0f, 1.f,

        1.f, -1.0f, -1.f,
        1.f, 1.0f, -1.f,
        1.f, 1.0f, 1.f,
    };
    primitive->loadPrimitive(wf_vertices, (int) wf_vertices.size() / 3);
    primitive->loadColor(glm::vec4(.0f, 1.F, .0f, 1.F));

    primitive->unbindBuffers();
}


void Wireframe::render(Context& ctx) const {
    wf_renderable.local_transform = this->ent_transform.getTransformationMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    wf_renderable.render(ctx);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//Node Wireframe::wf_renderable = Node();
