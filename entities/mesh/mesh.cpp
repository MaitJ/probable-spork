#include "mesh.hpp"
#include <vector>
#include "glm/glm/glm.hpp"
#include "renderable_manager.hpp"
#include <fmt/core.h>

namespace Renderable {

    void Mesh::render(const Context &ctx, glm::mat4 const& VP) {
        //View projection matrix and camera matrix are missing
        glm::mat4 model_matrix = this->transform.getTransformationMatrix();

        for (auto& node : this->nodes){
            node.render(ctx, VP, model_matrix);
        }
    }

    //TODO Make error handling better
    void Mesh::loadGLTFModel(std::string const& file_name) {

        if (file_name.find(GLTFLoader::FILE_EXTENSION) == std::string::npos) {
            fmt::print("[ERROR]: GLTFLoader (loadGLTFModel): file isn't of type .gltf");
            return;
        }

        GLTFLoader model(file_name);
        model.loadMesh(*this);
        RenderableManager::addRenderableMesh(this);
    }
}

