#include <glm/glm.hpp>

namespace Matrices {
    using namespace::glm;
    mat4 lookat(vec3 const& from, vec3 const& to, vec3 const& up = vec3(.0f, .1f, .0f)) {
        vec3 forward = normalize(to - from);
        vec3 right = normalize(cross(forward, up));
        vec3 up_vec = normalize(cross(right, forward));

        mat4 cam_mat(1.f);
        cam_mat[0][0] = right.x;
        cam_mat[1][0] = right.y;
        cam_mat[2][0] = right.z;

        cam_mat[0][1] = up_vec.x;
        cam_mat[1][1] = up_vec.y;
        cam_mat[2][1] = up_vec.z;

        cam_mat[0][2] = -forward.x;
        cam_mat[1][2] = -forward.y;
        cam_mat[2][2] = -forward.z;

        cam_mat[3][0] = -dot(right, from);
        cam_mat[3][1] = -dot(up_vec, from);
        cam_mat[3][2] = dot(forward, from);

        return cam_mat;
    }
}

