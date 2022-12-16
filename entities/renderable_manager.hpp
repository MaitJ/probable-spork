#ifndef RENDERABLE_MANAGER_H
#define RENDERABLE_MANAGER_H

#include "mesh/node.hpp"
#include "wireframe.hpp"

namespace RenderableManager {

    void addRenderableMesh(Renderable::Mesh* obj);
    void addWireframe(Wireframe const& wireframe);
    void renderObjects(Context& ctx, glm::mat4 const& VP);
    void initPerspectiveMatrix(float window_width, float window_height, float fov);
    glm::mat4 const& getPerspectiveMat();
    glm::mat4& getViewProjMat();

}

#endif
