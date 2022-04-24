#include "player.hpp"
#include "renderable_manager.hpp"

#define PLAYER_MODEL "assets/koksal.obj"
#define PLAYER_TEXTURE "assets/koksal_baba.jpg"


Player::Player() {}

Player::Player(glm::mat4* view_proj, Shader* shader) {
    this->setupRenderable(view_proj, shader);
}

void Player::setupRenderable(glm::mat4* view_proj, Shader* shader) {
    this->game_ent.loadModel(PLAYER_MODEL, PLAYER_TEXTURE);
    this->is_visible = true;

}

bool Player::isVisible() {
    return this->is_visible;
}
