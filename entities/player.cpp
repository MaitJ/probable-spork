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

//Rename and replace with movement velocity
void Player::performMovement(float& player_axis, float& camera_axis, float const& camera_front_axis, bool in_positive_dir) {
    glm::vec3& velocity = this->velocity;

    if (in_positive_dir) {
        player_axis += camera_front_axis * 5.f;
        camera_axis += camera_front_axis * 5.f;
        return;
    }

    player_axis -= camera_front_axis * 5.f;
    camera_axis -= camera_front_axis * 5.f;
}

void Player::handleCollisions(glm::vec3 const& mov_dir, bool in_positive_dir) {
    glm::vec3& player_pos = this->game_ent->transform.getPosition();
    glm::vec3& player_dim = this->game_ent->transform.getDimensions();
    glm::vec3& camera_pos = camera.getCameraPos();

    performMovement(player_pos.z, camera_pos.z, mov_dir.z, in_positive_dir);

    //Check for z axis collisions
    for (auto& collidable: CollisionManager::getCollidables(*this->game_ent, this->game_ent->ctx)) {
        
        if (in_positive_dir ? mov_dir.z > 0.0f : mov_dir.z < 0.0f) {
            //Need to add player dimension because the position
            //is centered in world space
            //Set players right to collidables left
            player_pos.z = collidable->transform.left().z - player_dim.z;
            camera_pos.z = collidable->transform.left().z - player_dim.z;
            this->velocity = glm::vec3(0.f);
            continue;
        }

        //Set players left to collidables right
        camera_pos.z = collidable->transform.right().z + player_dim.z;
        player_pos.z = collidable->transform.right().z + player_dim.z;
        this->velocity = glm::vec3(0.f);
    }

    performMovement(player_pos.x, camera_pos.x, mov_dir.x, in_positive_dir);

    //Check for x axis collisions
    for (auto& collidable: CollisionManager::getCollidables(*this->game_ent, this->game_ent->ctx)) {
        
        if (in_positive_dir ? mov_dir.x > 0.0f : mov_dir.x < 0.0f) {
            player_pos.x = collidable->transform.left().x - player_dim.x;
            camera_pos.x = collidable->transform.left().x - player_dim.x;
            this->velocity = glm::vec3(0.f);
            continue;
        }

        player_pos.x = collidable->transform.right().x + player_dim.x;
        camera_pos.x = collidable->transform.right().x + player_dim.x;
        this->velocity = glm::vec3(0.f);
    }

}

void Player::updateMovement(DeltaTime const& dt) {
    this->velocity = (this->velocity * this->friction) * (float)dt.get();
}

void Player::setVelocity(float const x, float const y, float const z) {
    this->velocity = glm::vec3(x, y, z);
}
void Player::setVelocity(glm::vec3 const velocity) {
    this->velocity = velocity;
}

glm::vec3& Player::getVelocity() {
    return this->velocity;
}
void Player::onMove(Direction dir) {
    using namespace std;

    glm::vec3 mov_dir = camera.getCameraFront();
    glm::vec3 mov_dir_cross = glm::cross(mov_dir, glm::vec3(.0f, 1.f, .0f));
    mov_dir_cross.y = 0.f;
    mov_dir.y = 0.f;

    switch (dir) {
        case Direction::FORWARD:
            this->handleCollisions(mov_dir, true);
            break;
        case Direction::BACK:
            this->handleCollisions(mov_dir, false);
        break;
        case Direction::LEFT:
            this->handleCollisions(mov_dir_cross, false);
        break;
        case Direction::RIGHT:
            this->handleCollisions(mov_dir_cross, true);
        break;
    }
}
