#ifndef POELITE_COLORED_PRIMITIVE_HPP
#define POELITE_COLORED_PRIMITIVE_HPP

#include "primitive.hpp"
#include "tiny_gltf.h"

namespace Renderable {
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
}

#endif
