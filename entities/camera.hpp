#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

enum Direction {
    FORWARD,
    BACK,
    LEFT,
    RIGHT
};

class Camera {
    glm::mat4 camera_mat = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 orientation = glm::vec3(.0f);
    glm::vec3 camera_front = glm::vec3(.0f, .0f, -1.f);
    glm::vec3 camera_up = glm::vec3(.0f, 1.0f, .0f);

    void recalcMatrix();

public:
    Camera();
    void setPosition(float x, float y, float z);
    void setRotation(float angle, glm::vec3 axis);
    glm::mat4& getCameraMat();
    void onOrientationChange(glm::vec2 angles);
    void onMove(Direction dir);
};

#endif
