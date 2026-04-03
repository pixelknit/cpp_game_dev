#pragma once

#include "animation.hpp"
#include "config.h"
#include "raylib.h"
#include <cmath>
#include <vector>


struct Player {
  Vector2 position;
  Vector2 velocity;
  float width, height;
  float attackTimer;
  bool facingRight;
  bool isGrounded;
  bool canAttack;

  PlayerState state;
  Animation *currentAnim;
  Animation idleAnim;
  Animation runAnim;
  Animation jumpAnim;
  Animation attackAnim;

  Player(Texture2D &spriteSheet);

  void Update(float deltaTime, const std::vector<Rectangle> &platforms);
  void Draw(Texture2D &spriteSheet);
  Rectangle GetBounds() const;
  Rectangle GetAttackHitBox() const;
};