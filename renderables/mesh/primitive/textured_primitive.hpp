#ifndef POELITE_TEXTURED_PRIMITIVE_HPP
#define POELITE_TEXTURED_PRIMITIVE_HPP

#include "tiny_gltf.h"
#include "primitive.hpp"

namespace Renderable {

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
