#ifndef GLTF_LOADER
#define GLTF_LOADER

#include <tiny_gltf.h>
#include <glm/glm.hpp>
#include <memory>

namespace Renderable {
    class Node;
    class Primitive;
    class TexturedPrimitive;
    class ColoredPrimitive;
    class Mesh;
}

class GLTFLoader {
public:
    GLTFLoader(std::string const& file_name);

    void loadMesh(Renderable::Mesh& mesh);

private:
    tinygltf::Model model;

    template<typename ComponentType>
    std::vector<ComponentType> getMeshIndices(tinygltf::Accessor const& indice_accessor);

    template <typename T>
    void getAttribData(int accessor_index, int num_of_components, std::vector<T>& o_vec);

    static void groupVec3Floats(std::vector<float> const& floats, std::vector<glm::vec3>& o_vertices);
    static void groupVec2Floats(std::vector<float> const& floats, std::vector<glm::vec2>& o_vertices);

    auto nodeQuatToGLQuat(std::vector<double> quaternion) -> glm::quat;
    auto nodeTransformToGLVec3F(std::vector<double> transform) -> glm::vec3;

    void loadMeshRecursive(Renderable::Node& node, int traverse_node_index);
    void loadPrimitives(std::vector<Renderable::Primitive>& primitives, int mesh_index);
    void loadTexturedPrimitive(tinygltf::Primitive const& primitive, tinygltf::Material const& material,
                               std::shared_ptr<Renderable::TexturedPrimitive> const& textured_primitive);
    void loadColoredPrimitive(tinygltf::Primitive const& primitive, tinygltf::Material const& material,
                              std::shared_ptr<Renderable::ColoredPrimitive> const& colored_primitive);
    void setNodeTransform(tinygltf::Node const& t_node, Renderable::Node& node);
};

#endif
