#include "renderable_manager.hpp"
#include "context.hpp"
#include <functional>
#include "mesh/mesh.hpp"

namespace RenderableManager {
    using namespace glm;
    namespace {
        std::vector<Renderable::Mesh*> renderables;
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

    void addRenderableMesh(Renderable::Mesh* obj) {
        renderables.push_back(obj);
    }


    void renderObjects(Context& ctx, glm::mat4 const& VP) {
        for (Renderable::Mesh* obj : renderables) {
            obj->render(ctx, VP);
        }

        for (auto& wireframe_ref : wireframes) {
            Wireframe const& wireframe = wireframe_ref.get();
            wireframe.render(ctx);
            
        }
    }
}

