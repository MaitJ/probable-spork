#include "node.hpp"
#include <fmt/core.h>
#include "./mesh.hpp"

//#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"

namespace Renderable {
    Node::Node() : local_transform(1.f) {}

    void Node::render(Context const& ctx, glm::mat4 global_transform) {
        for (auto const& primitive : this->primitives) {
            primitive->render(global_transform, this->local_transform, ctx);
        }

        glm::mat4 recursive_transform = global_transform * this->local_transform;
        for (auto& node : this->nodes) {
            node.render(ctx, recursive_transform);
        }
        
    }
}




