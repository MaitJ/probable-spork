#include "player.hpp"
#include "renderable_manager.hpp"
#include "../events/event_handler.hpp"
#include "../world/context.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "../collisions/collision_manager.hpp"

#define PLAYER_MODEL "assets/koksal.obj"
#define PLAYER_TEXTURE "assets/koksal_baba.jpg"


Player::Player(Camera& camera, Context& ctx) : game_ent(ctx.createEntity().lock()), camera(camera), render_obj(true) {}

Player::Player(glm::mat4& view_proj, Shader* shader, Camera& camera, Context& ctx) :  game_ent(ctx.createEntity().lock()), camera(camera), render_obj(true) {
    this->setupRenderable(view_proj, shader);
    EventHandler::registerSubscriber<Direction, EventType::MOVEMENT>(this, &Player::onMove);
}

void Player::setupRenderable(glm::mat4& view_proj, Shader* shader) {
    this->game_ent->loadModel(PLAYER_MODEL, PLAYER_TEXTURE);
    this->is_visible = true;

}

bool Player::isVisible() {
    return this->is_visible;
}

void Player::handleCollisions(glm::vec3 const& camera_front, bool in_positive_dir) {
    glm::vec3& player_pos = this->game_ent->transform.getPosition();
    glm::vec3& player_dim = this->game_ent->transform.getDimensions();
    glm::vec3& camera_pos = camera.getCameraPos();


    if (in_positive_dir) {
        player_pos.z += camera_front.z * 5.f;
        camera_pos.z += camera_front.z * 5.f;
    } else {
        player_pos.z -= camera_front.z * 5.f;
        camera_pos.z -= camera_front.z * 5.f;
    }

    //Check for z axis collisions
    for (auto& collidable: CollisionManager::getCollidables(*this->game_ent, this->game_ent->ctx)) {
        
        if (in_positive_dir ? camera_front.z > 0.0f : camera_front.z < 0.0f) {
            player_pos.z = collidable->transform.left().z - player_dim.z;
            camera_pos.z = collidable->transform.left().z - player_dim.z;
        }
        else {
            player_pos.z = collidable->transform.right().z + player_dim.z;
            camera_pos.z = collidable->transform.right().z + player_dim.z;
        }
    }

    if (in_positive_dir) {
        player_pos.x += camera_front.x * 5.f;
        camera_pos.x += camera_front.x * 5.f;
    } else {
        player_pos.x -= camera_front.x * 5.f;
        camera_pos.x -= camera_front.x * 5.f;
    }
    //Check for x axis collisions
    for (auto& collidable: CollisionManager::getCollidables(*this->game_ent, this->game_ent->ctx)) {
        
        if (in_positive_dir ? camera_front.x > 0.0f : camera_front.x < 0.0f) {
            player_pos.x = collidable->transform.left().x - player_dim.x;
            camera_pos.x = collidable->transform.left().x - player_dim.x;
        }
        else {
            player_pos.x = collidable->transform.right().x + player_dim.x;
            camera_pos.x = collidable->transform.right().x + player_dim.x;
        }
    }

}
void Player::onMove(Direction dir) {
    using namespace std;

    glm::vec3 camera_front = camera.getCameraFront();
    glm::vec3 camera_front_cross = glm::cross(camera_front, glm::vec3(.0f, 1.f, .0f));
    //camera_front_cross.y = 0.f;
    camera_front.y = 0.f;

    switch (dir) {
        case Direction::FORWARD: {
            this->handleCollisions(camera_front, true);
            }
            break;
        case Direction::BACK:
            this->handleCollisions(camera_front, false);
        break;
        case Direction::LEFT:
            this->handleCollisions(camera_front_cross, false);
        break;
        case Direction::RIGHT:
            this->handleCollisions(camera_front_cross, true);
        break;
    }
}
