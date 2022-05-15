#ifndef RENDERABLE_MANAGER_H
#define RENDERABLE_MANAGER_H

#include "renderable_object.hpp"
#include "wireframe.hpp"

namespace RenderableManager {

    void addRenderable(RenderableObject* obj);
    void addWireframe(Wireframe const& wireframe);
    void renderObjects();
    void enableDimensionWireframes();
    void initPerspectiveMatrix(float window_width, float window_height, float fov);
    glm::mat4 const& getPerspectiveMat();
    glm::mat4& getViewProjMat();

}

#endif