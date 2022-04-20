#include "player.hpp"

#define PLAYER_MODEL "assets/koksal.obj"
#define PLAYER_TEXTURE "assets/koksal_baba.jpg"


Player::Player() {}

Player::Player(glm::mat4* view_proj, Shader* shader) {
   this->render_obj.setRenderVars(view_proj, shader);
   this->render_obj.loadModel(PLAYER_MODEL, PLAYER_TEXTURE);
   this->is_visible = true;
}


void Player::makeRenderable(glm::mat4* view_proj, Shader* shader) {
   this->render_obj.setRenderVars(view_proj, shader);
   this->render_obj.loadModel(PLAYER_MODEL, PLAYER_TEXTURE);
   this->is_visible = true;
}

void Player::render() {
    if (is_visible)
        this->render_obj.render();
}

void Player::setOrientation(float yaw, float pitch, float roll) {
    this->orientation.y = yaw;
    this->orientation.x = pitch;
    this->orientation.z = roll;
    this->render_obj.setOrientation(pitch, yaw, roll);
}

glm::vec3& Player::getOrientation() {
    return this->orientation;
}

void Player::setPosition(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->render_obj.setPos(x, y, z);
}

glm::vec3& Player::getPosition() {
    return this->position;
}

void Player::setDimensions(float width, float height, float length) {
    this->dimensions.x = width;
    this->dimensions.y = height;
    this->dimensions.z = length;
}
glm::vec3& Player::getDimensions() {
    return this->dimensions;
}
bool Player::isVisible() {
    return this->is_visible;
}
