#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "shader.hpp"
#include <string>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtx/quaternion.hpp"
#include "obj.hpp"
#include "transform.hpp"
#include "gltf_loader.hpp"
#include "shaders/shader_manager.hpp"
#include "context.hpp"

enum PrimitiveShape {
	PLANE,
    CUBE
};

namespace Renderable {
    class Primitive;
}

namespace Renderable {
    class Node {
    public:
        Node();

        std::vector<Renderable::Node> nodes;
        //Don't need to make separate class for mesh because
        //a mesh only has primitives and nothing else
        std::vector<std::shared_ptr<Renderable::Primitive>> primitives;

        glm::mat4 local_transform;

        void render(Context const& ctx, glm::mat4 VP = glm::mat4(1.f), glm::mat4 model_matrix = glm::mat4(1.f));
    };

}

#endif // !RENDERABLE_ENTITY_H