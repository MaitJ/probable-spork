#ifndef SKINNED_NODE_HPP
#define SKINNED_NODE_HPP

#include "mesh/node.hpp"

struct Bone {
    glm::mat4 global_transform_matrix;
    glm::mat4 inverse_bind_matrix;

    glm::mat4 getJointMatrix();
};

class SkinnedNode : public Node {
public:

    void loadGLTFModel(const std::string& file_name);

private:
    std::vector<Bone> bones;

};

#endif
