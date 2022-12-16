#ifndef POELITE_PRIMITIVE_HPP
#define POELITE_PRIMITIVE_HPP
#include "glm/glm/glm.hpp"
#include "context.hpp"

namespace Renderable {
    class Primitive {
    public:
        virtual void render(glm::mat4& global_transform, glm::mat4& model_matrix, Context const& ctx) = 0;
        virtual void genGlBuffers() = 0;
        virtual void bindBuffers() = 0;
        void unbindBuffers();

        size_t vertices = 0;
    protected:
        unsigned int vbo, vao;

        glm::mat4 local_transform;
    };
}

#endif
