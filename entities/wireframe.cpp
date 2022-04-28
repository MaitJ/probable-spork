#include "wireframe.hpp"
#include "renderable_manager.hpp"
#include <fmt/core.h>
#include <glm/gtx/string_cast.hpp>

Wireframe::Wireframe(Transform& ent_transform, int entity_id) : entity_id{entity_id}, ent_transform(ent_transform)  {}

Shader Wireframe::wf_shader;
RenderableObject Wireframe::wf_renderable = RenderableObject(false, Wireframe::wf_shader);

void Wireframe::initWireframeModel() {
    Wireframe::wf_shader.loadAndCompile("wf_vertex_shader.vert", "wf_fragment_shader.frag");
    Wireframe::wf_shader.layout_len = 3;
    wf_renderable.genBuffers();
    wf_renderable.shader.use();
    wf_renderable.glBind();

    wf_renderable.view_proj = RenderableManager::getViewProjMat();
    float wf_vertices[] = {
        //Front triangles
        -1.f, .0f, 1.f,
        1.f, .0f, 1.f,
        -1.f, 1.0f, 1.f,
        1.f, .0f, 1.f,
        1.f, 1.0f, 1.f,
        -1.f, 1.0f, 1.f,

        //Back triangles
        -1.f, .0f, -1.f,
        1.f, .0f, -1.f,
        -1.f, 1.0f, -1.f,
        1.f, .0f, -1.f,
        1.f, 1.0f, -1.f,
        -1.f, 1.0f, -1.f,

        //Left side
        -1.f, .0f, 1.f,
        -1.f, .0f, -1.f,
        -1.f, 1.0f, 1.f,

        -1.f, .0f, -1.f,
        -1.f, 1.0f, -1.f,
        -1.f, 1.0f, 1.f,

        //Right side
        1.f, .0f, 1.f,
        1.f, .0f, -1.f,
        1.f, 1.0f, 1.f,

        1.f, .0f, -1.f,
        1.f, 1.0f, -1.f,
        1.f, 1.0f, 1.f,
    };
    wf_renderable.calcModel();

    wf_renderable.total_vertices = 24;

	glBufferData(GL_ARRAY_BUFFER, sizeof(wf_vertices), wf_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, wf_shader.layout_len * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    Wireframe::wf_shader.unbind();
}


void Wireframe::render() const {
    //Calli wf_renderable this->transformi asjadega ja renderda wf
    wf_renderable.setPos(this->ent_transform.getPosition());
    wf_renderable.setOrientation(this->ent_transform.getOrientation());
    wf_renderable.setScale(this->ent_transform.getDimensions());
    wf_renderable.calcModel();
    //RenderableManager::addWireframe(*this);
    wf_renderable.render();
}

//RenderableObject Wireframe::wf_renderable = RenderableObject();
