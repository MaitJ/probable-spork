#include "renderable_manager.hpp"



namespace RenderableManager {
    using namespace glm;
    namespace {
        bool wireframes_enabled = false;
        std::vector<RenderableObject*> renderables;
        mat4 view_proj = mat4(1.f);
        mat4 persp_mat = mat4(1.f);
    }

    void initPerspectiveMatrix(float window_width, float window_height, float fov) {
        persp_mat = glm::perspective(glm::radians(fov), window_width/window_height, 0.1f, 1000.f);
    }

    mat4& getViewProjMat() {
        return view_proj;
    }
    mat4 const& getPerspectiveMat() {
        return persp_mat;
    }

    void addRenderable(RenderableObject* obj) {
        renderables.push_back(obj);
    }

    void renderObjects() {
        if (!wireframes_enabled) {
            for (RenderableObject* obj : renderables) {
                obj->render();
            }
        }
    }

    void enableDimensionWireframes() {
        //Not implemented yet.
        return;
    }
}

