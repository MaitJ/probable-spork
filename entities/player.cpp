#include "player.hpp"
#include "renderable_manager.hpp"
#include "../events/event_handler.hpp"
#include "../world/context.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "../collisions/collision_manager.hpp"
#include "../controls/keyboard.hpp"

#define PLAYER_MODEL "assets/chair.gltf"


Player::Player(Camera& camera, Context& ctx) : game_ent(ctx.createEntity().lock()), camera(camera) {}

Player::Player(glm::mat4& view_proj, Camera& camera, Context& ctx) :  game_ent(ctx.createEntity().lock()), camera(camera) {
    Shader const& textured_shader = ShaderManager::getShader("textured");
    this->setupRenderable(view_proj, &textured_shader);
}

void Player::setupRenderable(glm::mat4& view_proj, Shader const* shader) {
    this->game_ent->mesh.loadGLTFModel(PLAYER_MODEL);
    this->is_visible = true;

}

bool Player::isVisible() {
    return this->is_visible;
}

//Rename and replace with movement velocity
void Player::performMovement(float& player_axis, float& camera_axis, float const& camera_front_axis) {
    player_axis += camera_front_axis;
    camera_axis += camera_front_axis;
}

void Player::resolveCollision(CollisionAxis collision_axis) {
    glm::vec3& player_pos = this->game_ent->transform.getPosition();
    glm::vec3& player_dim = this->game_ent->transform.getDimensions();
    glm::vec3& camera_pos = camera.getCameraPos();


    for (auto& collidable: CollisionManager::getCollidables(*this->game_ent, this->game_ent->ctx)) {
        
        //velocity[collision_axis] works because, vec3 is array [x, y, z]
        if ((collision_axis == CollisionAxis::Y ? 
                -this->velocity[collision_axis] : 
                this->velocity[collision_axis]) > 0.0f) {
            //Need to add player dimension because the position
            //is in players center
            //Set players right to collidables left
            player_pos[collision_axis] = collidable->transform.left()[collision_axis] - (player_dim[collision_axis] / 2.0f);
            camera_pos[collision_axis] = collidable->transform.left()[collision_axis] - (player_dim[collision_axis] / 2.0f);

            if (collision_axis == CollisionAxis::Y) {
                camera_pos[collision_axis] += this->head_offset;
            }
            continue;
        }

        //Set players left to collidables right
        camera_pos[collision_axis] = collidable->transform.right()[collision_axis] + (player_dim[collision_axis] / 2.0f);
        player_pos[collision_axis] = collidable->transform.right()[collision_axis] + (player_dim[collision_axis] / 2.0f);
        if (collision_axis == CollisionAxis::Y) {
            camera_pos[collision_axis] += this->head_offset;
        }
    }
}

void Player::handleCollisions() {
    glm::vec3& player_pos = this->game_ent->transform.getPosition();
    glm::vec3& camera_pos = camera.getCameraPos();

    performMovement(player_pos.z, camera_pos.z, this->velocity.z);
    resolveCollision(CollisionAxis::Z);

    performMovement(player_pos.x, camera_pos.x, this->velocity.x);
    resolveCollision(CollisionAxis::X);

    performMovement(player_pos.y, camera_pos.y, -this->velocity.y);
    resolveCollision(CollisionAxis::Y);

}

void Player::getMovementInputs() {
    using namespace std;

    glm::vec3 mov_dir = camera.getCameraFront();
    glm::vec3 mov_dir_cross = glm::cross(mov_dir, glm::vec3(.0f, 1.f, .0f));
    mov_dir_cross.y = 0.f;
    mov_dir.y = 0.f;

    if (Keyboard::key_states[GLFW_KEY_W]) {
        this->acceleration += mov_dir;
    }
    if (Keyboard::key_states[GLFW_KEY_S]) {
        this->acceleration += -mov_dir;
    }
    if (Keyboard::key_states[GLFW_KEY_A]) {
        this->acceleration += -mov_dir_cross;
    }
    if (Keyboard::key_states[GLFW_KEY_D]) {
        this->acceleration += mov_dir_cross;
    }

    float len_of_dir = sqrt(
            (this->acceleration.x * this->acceleration.x) +
            (this->acceleration.y * this->acceleration.y) +
            (this->acceleration.z * this->acceleration.z));

    if (len_of_dir > 1.f)
        this->acceleration = glm::normalize(this->acceleration);

    //Apply gravity
    this->acceleration.y += game_ent->ctx.gravity;

    this->acceleration *= this->speed;

}

void Player::limitMovement() {

    if (abs(this->velocity.x) < 0.005f)
        this->velocity.x = 0.f;
    if (abs(this->velocity.y) < 0.005f)
        this->velocity.y = 0.f;
    if (abs(this->velocity.z) < 0.005f)
        this->velocity.z = 0.f;

}

void Player::updateMovement(DeltaTime const& dt) {

    this->getMovementInputs();


    this->velocity += this->acceleration * (float)dt.get();
    this->velocity *= this->friction;

    //Set velocity to 0 if it's near 0 
    limitMovement();

    this->handleCollisions();

    this->acceleration = glm::vec3(0.f, 0.f, 0.f);
}

void Player::resetCameraPos() {
    glm::vec3& camera_pos = this->camera.getCameraPos();
    glm::vec3 const& player_pos = this->game_ent->transform.getPosition();
    camera_pos.x = player_pos.x;
    camera_pos.y = player_pos.y + this->head_offset;
    camera_pos.z = player_pos.z;
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
