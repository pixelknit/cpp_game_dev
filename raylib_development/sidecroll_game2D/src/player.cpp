#include "player.hpp"
#include "config.h"
#include <vector>


Player::Player(Texture2D &spriteSheet)
    : position({100, 300}), velocity({0, 0}), width(80),
      height(80), facingRight(true), isGrounded(false),
      canAttack(true), attackTimer(0), state(IDLE),
      idleAnim({{0, 0, PLAYER_SIZE, PLAYER_SIZE}, 4}),
      runAnim(
          {{0, PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE}, 6}),
      jumpAnim(
          {{0, PLAYER_SIZE * 2, PLAYER_SIZE, PLAYER_SIZE},
           11}),
      attackAnim(
          {{0, PLAYER_SIZE * 3, PLAYER_SIZE, PLAYER_SIZE},
           4}) {
  currentAnim = &idleAnim;
}

void Player::Update(float deltaTime, const std::vector<Rectangle> &platforms) {
  // input handling
  velocity.x = 0;

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    velocity.x = -PLAYER_SPEED;
    facingRight = false;
    if (isGrounded && state != ATTACKING)
      state = RUNNING; // TODO check the proper anim state.
  }

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    velocity.x = PLAYER_SPEED;
    facingRight = true;
    if (isGrounded && state != ATTACKING)
      state = RUNNING; // TODO check the proper anim state.
  }

  // jump mechanism

  if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W)) && isGrounded &&
      state != ATTACKING) {
    velocity.y = JUMP_FORCE;
    isGrounded = false;
    state = JUMPING;
    // log for key pressed
  }

  // attack
  if (IsKeyDown(KEY_J) && canAttack) {
    state = ATTACKING;
    canAttack = false;
    attackTimer = 0.4f;
  }

  // gravity
  velocity.y += GRAVITY * deltaTime;

  // Update position
  position.x += velocity.x * deltaTime;
  position.y += velocity.y * deltaTime;

  // Platform collision
  isGrounded = false;
  Rectangle playerRect = GetBounds();

  for (const auto &platform : platforms) {
    if (CheckCollisionRecs(playerRect, platform)) {
      // land on top
      if (velocity.y > 0 &&
          playerRect.y + playerRect.height - velocity.y * deltaTime <=
              platform.y) {
        position.y = platform.y - height;
        velocity.y = 0;
        isGrounded = true;
        if (state == JUMPING)
          state = IDLE; // TODO change the animation state based on design
      }

      // Hitting head
      else if (velocity.y < 0 && playerRect.y - velocity.y * deltaTime >=
                                     platform.y + platform.height) {
        position.y = platform.y + platform.height;
        velocity.y = 0;
      }

      // Side collision
      else if (velocity.x > 0) {
        position.x = platform.x - width;
      } else if (velocity.x < 0) {
        position.x = platform.x + platform.width;
      }
    }
  }

  // Screen Boundaries
  if (position.x < 0)
    position.x = 0;
  if (position.x > 5000)
    position.x = 5000;

  // Attack timer
  if (!canAttack) {
    attackTimer -= deltaTime;
    if (attackTimer <= 0) {
      canAttack = true;
      if (isGrounded)
        state = IDLE;
      else
        state = JUMPING;
    }
  }

  switch (state) {
  case IDLE:
    currentAnim = &idleAnim;
    break;
  case RUNNING:
    currentAnim = &runAnim;
    break;
  case JUMPING:
    currentAnim = &jumpAnim;
    break;
  case ATTACKING:
    currentAnim = &attackAnim;
    break;
  }

  currentAnim->Update(deltaTime);
}

void Player::Draw(Texture2D &spriteSheet) {
  Rectangle source = currentAnim->GetCurrentFrame();

  if (!facingRight)
    source.width = -source.width;

  Rectangle dest = {position.x, position.y, width, height};
  Vector2 origin = {0, 0};

  DrawTexturePro(spriteSheet, source, dest, origin, 0.0f, WHITE);
}

Rectangle Player::GetBounds() const {
  return {position.x, position.y, width, height};
}

Rectangle Player::GetAttackHitBox() const {
  if (state != ATTACKING)
    return {0, 0, 0, 0};

  float attackRange = 30.0f;
  if (facingRight) {
    return {position.x + width, position.y + 10, attackRange, height - 20};
  } else {
    return {position.x - attackRange, position.y + 10, attackRange,
            height - 20};
  }
}