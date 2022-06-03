#include "renderable_manager.hpp"
#include "context.hpp"
#include <functional>



namespace RenderableManager {
    using namespace glm;
    namespace {
        std::vector<Node*> renderables;
        std::vector<std::reference_wrapper<const Wireframe>> wireframes;
        mat4 view_proj = mat4(1.f);
        mat4 persp_mat = mat4(1.f);
    }

    void initPerspectiveMatrix(float window_width, float window_height, float fov) {
        persp_mat = glm::perspective(glm::radians(fov), window_width/window_height, 0.1f, 1000.f);
    }

    void addWireframe(Wireframe const& wireframe) {
        wireframes.push_back(std::cref(wireframe));
    }

    mat4& getViewProjMat() {
        return view_proj;
    }
    mat4 const& getPerspectiveMat() {
        return persp_mat;
    }

    void addRenderable(Node* obj) {
        renderables.push_back(obj);
    }


    void renderObjects(Context& ctx) {
        for (Node* obj : renderables) {
            obj->render(ctx);
        }

        for (auto& wireframe_ref : wireframes) {
            Wireframe const& wireframe = wireframe_ref.get();
            wireframe.render(ctx);
            
        }
    }

    void enableDimensionWireframes() {
        //Not implemented yet.
        return;
    }
}

