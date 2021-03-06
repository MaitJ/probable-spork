#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include "shader.hpp"
#include <tiny_gltf.h>
#include "../world/context.hpp"
#include "./node.hpp"

namespace Renderable {

    class Mesh {
    public:
        std::vector<Renderable::Node> nodes;
        Transform transform;


        void loadGLTFModel(std::string const& file_name);
        void render(Context const& ctx, glm::mat4 const& VP);
    };

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

    class ColoredPrimitive : public Primitive {
    public:
        explicit ColoredPrimitive(Shader const& shader);

        void genGlBuffers() override;
        void bindBuffers() override;

        void render(glm::mat4& global_transform, glm::mat4& model_matrix, Context const& ctx) override;
        void loadPrimitive(std::vector<glm::vec3> const& positions,
                           std::vector<glm::vec3> const& normals,
                           std::vector<unsigned short> const& indices);
        void loadMaterial(tinygltf::Material const& material);
        void loadPrimitive(std::vector<float> const& vertex_data, int vertices);
        void loadColor(glm::vec4 color);

        auto assembleVertices(
                std::vector<glm::vec3> const& positions,
                std::vector<unsigned short> const& indices,
                std::vector<glm::vec3> const& normals
                ) -> std::vector<float>;

    private:
        //Default color of mesh is grey
        glm::vec4 color = {.9f, .9f, .9f, 1.f}; // NOLINT
        Shader const& shader;
    };

    class TexturedPrimitive : public Primitive {
    public:
        explicit TexturedPrimitive(Shader const& shader);

        void genGlBuffers() override;
        void bindBuffers() override;

        void render(glm::mat4& global_transform, glm::mat4& model_matrix, Context const& ctx) override;
        void loadPrimitive(std::vector<glm::vec3> const& positions,
                           std::vector<glm::vec2> const& tex_coords,
                           std::vector<glm::vec3> const& normals,
                           std::vector<unsigned short> const& indices);
        void loadMaterial(tinygltf::Image const& image, tinygltf::Sampler const& sampler);

        auto
        assembleVertices(std::vector<glm::vec3> const& positions,
                         std::vector<glm::vec2> const& tex_coords,
                         std::vector<glm::vec3> const& normals,
                         std::vector<unsigned short> const& indices) -> std::vector<float>;
    private:
        unsigned int to;
        Shader const& shader;
    };
}

#endif
