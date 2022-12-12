#include "node.hpp"
#include <fmt/core.h>
#include "./mesh.hpp"

//#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"

namespace Renderable {
    Node::Node() : local_transform(1.f) {}

    void Node::render(Context const& ctx, glm::mat4 VP, glm::mat4 model_matrix) {
        model_matrix = model_matrix * this->local_transform;
        for (auto const& primitive : this->primitives) {
            primitive->render(VP, model_matrix, ctx);
        }

        for (auto& node : this->nodes) {
            node.render(ctx, VP, model_matrix);
        }
        
    }

}




