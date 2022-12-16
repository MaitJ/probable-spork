#ifndef MESH
#define MESH

#include "glm/glm/glm.hpp"
#include "shader.hpp"
#include "tiny_gltf.h"
#include "context.hpp"
#include "mesh/node.hpp"

namespace Renderable {

    class Mesh {
    public:
        std::vector<Renderable::Node> nodes;
        Transform transform;


        void loadGLTFModel(std::string const& file_name);
        void render(Context const& ctx, glm::mat4 const& VP);
    };
}

#endif
