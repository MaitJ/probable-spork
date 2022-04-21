#include "player.hpp"
#include "renderable_manager.hpp"

#define PLAYER_MODEL "assets/koksal.obj"
#define PLAYER_TEXTURE "assets/koksal_baba.jpg"


Player::Player() {}

Player::Player(glm::mat4* view_proj, Shader* shader) {
    this->setupRenderable(view_proj, shader);
    this->transform.attachRenderable(&this->render_obj);
}

void Player::setupRenderable(glm::mat4* view_proj, Shader* shader) {
   this->render_obj.setRenderVars(view_proj, shader);
   this->render_obj.loadModel(PLAYER_MODEL, PLAYER_TEXTURE);
   this->is_visible = true;
   RenderableManager::addRenderable(&this->render_obj);
}

void Player::makeRenderable(glm::mat4* view_proj, Shader* shader) {
    this->setupRenderable(view_proj, shader);
    this->transform.attachRenderable(&this->render_obj);
}

void Player::render() {
    if (is_visible)
        this->render_obj.render();
}
bool Player::isVisible() {
    return this->is_visible;
}
