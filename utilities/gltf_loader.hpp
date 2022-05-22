#ifndef GLTF_LOADER
#define GLTF_LOADER

#include <tiny_gltf.h>
#include <glm/glm.hpp>
class GLTFLoader {
public:
    GLTFLoader(std::string file_name, bool& loaded);

    std::vector<float> getMeshVertexData();

    int num_of_tris;

private:
    tinygltf::Model model;

    template<typename ComponentType>
    std::vector<ComponentType> getMeshIndices(tinygltf::Accessor const& indice_accessor);

    template <typename T>
    void getAttribData(int accessor_indice, int num_of_components, std::vector<T>& o_vec);

    std::vector<glm::vec3> getPositionData();

};

#endif
