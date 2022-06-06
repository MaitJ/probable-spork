#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include "shader.hpp"
#include <tiny_gltf.h>

namespace Renderable {

    class Primitive {
    public:
        virtual void render(glm::mat4 TRS) = 0;
        virtual void genGlBuffers() = 0;
        virtual void bindBuffers() = 0;

        unsigned int vbo, vao;
        unsigned int vertices = 0;

        glm::mat4 local_transform;
    };

    class ColoredPrimitive : public Primitive {
    public:
        ColoredPrimitive(Shader const& shader);

        void genGlBuffers() override;
        void bindBuffers() override;

        void render(glm::mat4 TRS) override;
        void loadPrimitive(std::vector<glm::vec3> positions,
                           std::vector<glm::vec3> normals,
                           std::vector<unsigned int> indices);
        void loadMaterial(tinygltf::Material const& material);
        glm::vec4 color = {.9f, .9f, .9f, 1.f};
        Shader const& shader;

        std::vector<float>
        assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
                         std::vector<unsigned int> indices);
    };

    class TexturedPrimitive : public Primitive {
    public:
        TexturedPrimitive(Shader const& shader);

        void genGlBuffers() override;
        void bindBuffers() override;

        void render(glm::mat4 TRS) override;
        void loadPrimitive(std::vector<glm::vec3> positions,
                           std::vector<glm::vec3> normals,
                           std::vector<glm::vec2> tex_coords,
                           std::vector<unsigned int> indices);
        void loadMaterial(tinygltf::Material const& material);
        unsigned int to;
        Shader const& shader;

        std::vector<float>
        assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
                         std::vector<glm::vec2> tex_coords,
                         std::vector<unsigned int> indices);
    };
}

#endif
