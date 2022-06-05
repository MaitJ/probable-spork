#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include "shader.hpp"

namespace Renderable {

    class Primitive {
    public:
        virtual void render(glm::mat4 TRS) = 0;
        virtual void genGlBuffers() = 0;
        virtual void bindBuffers() = 0;

        unsigned int vbo, vao;

        glm::mat4 local_transform;
    };

    class ColoredPrimitive : public Primitive {
    public:
        ColoredPrimitive(Shader const& shader);

        void genGlBuffers() override;
        void bindBuffers() override;

        void render(glm::mat4 TRS) override;
        void loadPrimitive(std::vector<float> positions,
                           std::vector<float> normals,
                           std::vector<float> indices);
        glm::vec4 color = {.9f, .9f, .9f, 1.f};
        Shader const& shader;
    };

    class TexturedPrimitive : public Primitive {
    public:
        TexturedPrimitive(Shader const& shader);

        void genGlBuffers() override;
        void bindBuffers() override;

        void render(glm::mat4 TRS) override;
        void loadPrimitive(std::vector<float> positions,
                           std::vector<float> normals,
                           std::vector<float> tex_coords,
                           std::vector<float> indices);
        unsigned int to;
        Shader const& shader;
    };
}

#endif
