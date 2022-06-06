#ifndef GLTF_LOADER
#define GLTF_LOADER

#include <tiny_gltf.h>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include <memory>

namespace Renderable {
    class Node;
}

class GLTFLoader {
public:
    GLTFLoader(std::string const& file_name, bool& loaded);

    void loadMesh(Renderable::Node& node, int traverse_node_index);

    std::vector<Renderable::Mesh> getMeshes();
    //std::vector<SkinnedMesh> getSkinnedMeshes();
    void getMeshData(tinygltf::Node const& node, Mesh& t_mesh);


    size_t indices;

private:
    tinygltf::Model model;

    template<typename ComponentType>
    std::vector<ComponentType> getMeshIndices(tinygltf::Accessor const& indice_accessor);

    template <typename T>
    void getAttribData(int accessor_index, int num_of_components, std::vector<T>& o_vec);

    static void groupVec3Floats(std::vector<float> const& floats, std::vector<glm::vec3>& o_vertices);
    static void groupVec2Floats(std::vector<float> const& floats, std::vector<glm::vec2>& o_vertices);

    auto nodeQuatToGLQuat(std::vector<double> quaternion) -> glm::quat;
    void nodeTransformMesh(glm::vec3 translation, glm::quat rotation, glm::vec3 scale,
                           std::vector<glm::vec3> &position_vertices, std::vector<glm::vec3>& normal_vertices);


    auto nodeTransformToGLVec3F(std::vector<double> transform) -> glm::vec3;

    void applyNodeTransformations(tinygltf::Node const& node, std::vector<glm::vec3> &position_vertices, std::vector<glm::vec3>& normal_vertices);

    void setImageMaterial(Mesh &t_mesh, int material_index);

    void loadPrimitives(std::vector<Renderable::Primitive>& primitives, int mesh_index);

    void loadTexturedPrimitive(tinygltf::Primitive const& primitive, tinygltf::Material const& material,
                               std::shared_ptr<Renderable::TexturedPrimitive> const& textured_primitive);

    void loadColoredPrimitive(tinygltf::Primitive const& primitive, tinygltf::Material const& material,
                              std::shared_ptr<Renderable::ColoredPrimitive> const& colored_primitive);
};

#endif
