#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>


class Transform {
    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 orientation = glm::vec3(1.f);
    glm::vec3 dimensions = glm::vec3(1.f);

public:
    Transform();
    Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 dimensions);

    void setOrientation(float yaw, float pitch, float roll);
    void setPosition(float x, float y, float z);
    void setDimensions(float width, float height, float length);

    glm::vec3& getOrientation();
    glm::vec3& getPosition();
    glm::vec3& getDimensions();

    glm::vec3 left() const;
    glm::vec3 right() const;
    void setLeft(glm::vec3 left);
    void setRight(glm::vec3 right);

};

#endif

