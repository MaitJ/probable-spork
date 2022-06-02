#ifndef RENDERABLE_MANAGER_H
#define RENDERABLE_MANAGER_H

#include "node.hpp"
#include "wireframe.hpp"

namespace RenderableManager {

    void addRenderable(Node* obj);
    void addWireframe(Wireframe const& wireframe);
    void renderObjects();
    void enableDimensionWireframes();
    void initPerspectiveMatrix(float window_width, float window_height, float fov);
    void setShaderManager(ShaderManager* shader_manager);
    glm::mat4 const& getPerspectiveMat();
    glm::mat4& getViewProjMat();

}

#endif
