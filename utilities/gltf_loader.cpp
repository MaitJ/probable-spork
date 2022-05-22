#include "gltf_loader.hpp"
#include <fmt/core.h>

GLTFLoader::GLTFLoader(std::string file_name, bool& loaded) {
    tinygltf::TinyGLTF loader;
    std::string warn;
    std::string err;

    loaded = loader.LoadASCIIFromFile(&this->model, &err, &warn, file_name);

    if (!warn.empty())
        fmt::print("[WARNING]: {0}\n", warn);

    if (!err.empty())
        fmt::print("[ERROR]: {0}\n", err);

}
template<typename ComponentType>
std::vector<ComponentType> GLTFLoader::getMeshIndices(tinygltf::Accessor const& indice_accessor) {
    using namespace tinygltf;

    std::vector<ComponentType> indices;
    indices.reserve(indice_accessor.count);
    BufferView& indice_bf_view = this->model.bufferViews[indice_accessor.bufferView];
    std::vector<unsigned char>& i_buffer_data = this->model.buffers[indice_bf_view.buffer].data;

    unsigned char* cur_byte = &i_buffer_data[indice_bf_view.byteOffset];

    for (int i = 0; i < indice_accessor.count; ++i) {
        ComponentType value = *reinterpret_cast<ComponentType*>(cur_byte);
        indices.insert(indices.begin() + i, value);

        cur_byte += sizeof(ComponentType) + indice_bf_view.byteStride;
    }

    return indices;
}

template <typename T>
void GLTFLoader::getAttribData(int accessor_indice, std::vector<T>& o_vec) {
    using namespace tinygltf;
    Accessor& accessor = this->model.accessors[accessor_indice];
    BufferView& bf_view = this->model.bufferViews[accessor.bufferView];
    std::vector<unsigned char>& p_buffer_data = this->model.buffers[bf_view.buffer].data;

    o_vec.reserve(accessor.count);

    unsigned char* cur_byte = &p_buffer_data[bf_view.byteOffset];

    for (int i = 0; i < accessor.count; ++i) {
        T value = *reinterpret_cast<T*>(cur_byte);
        o_vec.insert(o_vec.begin() + i, value);

        cur_byte += sizeof(float) + bf_view.byteStride;
    }
}

std::vector<float> GLTFLoader::getMeshVertexData() {
    using namespace tinygltf;
    std::vector<tinygltf::Accessor>& accessors = this->model.accessors;

    std::vector<float> vertex_data;
    
    for (tinygltf::Mesh& mesh : this->model.meshes) {

        for (tinygltf::Primitive& primitive : mesh.primitives) {

            std::vector<float> pos;
            std::vector<float> normals;
            std::vector<float> tex;
            

            for (auto& [key, value] : primitive.attributes) {

                if (key == "POSITION")
                    getAttribData<float>(value, pos);

                if (key == "NORMAL")
                    getAttribData<float>(value, normals);

                if (key == "TEXCOORD_0")
                    getAttribData<float>(value, tex);

            }

            Accessor& indice_accessor = accessors[primitive.indices];

            switch (indice_accessor.componentType) {
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                    std::vector<unsigned short> mesh_indices = getMeshIndices<unsigned short>(indice_accessor);
                    vertex_data.reserve(mesh_indices.size() * 12);

                    for (int i = 0; i < mesh_indices.size(); ++i) {
                        vertex_data.insert(vertex_data.end(), {pos[i], pos[i + 1], pos[i + 2]});
                        vertex_data.insert(vertex_data.end(), {tex[i], tex[i + 1]});
                        vertex_data.insert(vertex_data.end(), {normals[i], normals[i + 1], normals[i + 2]});
                    }

                break;

            }

        }
        

    }

    return vertex_data;
}
