#ifndef GLTF_LOADER
#define GLTF_LOADER

#include <tiny_gltf.h>
#include <glm/glm.hpp>
class GLTFLoader {
public:
    GLTFLoader(std::string const& file_name, bool& loaded);

    std::vector<float> getMeshVertexData();

    size_t num_of_tris;

private:
    tinygltf::Model model;

    template<typename ComponentType>
    std::vector<ComponentType> getMeshIndices(tinygltf::Accessor const& indice_accessor);

    template <typename T>
    void getAttribData(int accessor_index, int num_of_components, std::vector<T>& o_vec);

    static void groupVec3Floats(std::vector<float> const& floats, std::vector<glm::vec3>& o_vertices);
    static void groupVec2Floats(std::vector<float> const& floats, std::vector<glm::vec2>& o_vertices);

    glm::quat nodeQuatToGLQuat(std::vector<double> quaternion);
    void nodeTransformMesh(glm::vec3 translation, glm::quat rotation, glm::vec3 scale,
                           std::vector<glm::vec3> &position_vertices);


    glm::vec3 nodeTransformToGLVec3F(std::vector<double> transform);

    void applyNodeTransformations(tinygltf::Node &node, std::vector<glm::vec3> &position_vertices);
};

#endif
