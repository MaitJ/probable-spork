#include "player.hpp"
#include "renderable_manager.hpp"
#include "../events/event_handler.hpp"
#include <glm/ext/matrix_transform.hpp>

#define PLAYER_MODEL "assets/koksal.obj"
#define PLAYER_TEXTURE "assets/koksal_baba.jpg"


Player::Player(Camera& camera) : camera(camera), render_obj(true) {}

Player::Player(glm::mat4& view_proj, Shader* shader, Camera& camera) :  camera(camera), render_obj(true) {
    this->setupRenderable(view_proj, shader);
    EventHandler::registerSubscriber<Direction, EventType::MOVEMENT>(this, &Player::onMove);
}

void Player::setupRenderable(glm::mat4& view_proj, Shader* shader) {
    this->game_ent.loadModel(PLAYER_MODEL, PLAYER_TEXTURE);
    this->is_visible = true;

}

bool Player::isVisible() {
    return this->is_visible;
}

void Player::onMove(Direction dir) {
    glm::vec3 camera_front = camera.getCameraFront();
    glm::vec3 camera_front_cross = glm::cross(camera_front, glm::vec3(.0f, 1.f, .0f));
    //camera_front_cross.y = 0.f;
    camera_front.y = 0.f;
    switch (dir) {
        case Direction::FORWARD:
            camera.getCameraPos() += camera_front * 5.f;
            this->game_ent.transform.getPosition() += camera_front * 5.f;
        break;
        case Direction::BACK:
            camera.getCameraPos() -= camera_front * 5.f;
            this->game_ent.transform.getPosition() -= camera_front * 5.f;
        break;
        case Direction::LEFT:
            camera.getCameraPos() -= camera_front_cross * 5.f;
            this->game_ent.transform.getPosition() -= camera_front_cross * 5.f;
        break;
        case Direction::RIGHT:
            camera.getCameraPos() += camera_front_cross * 5.f;
            this->game_ent.transform.getPosition() += camera_front_cross * 5.f;
        break;
    }
}
