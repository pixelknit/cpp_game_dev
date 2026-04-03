#pragma once

inline constexpr int   SCREEN_WIDTH = 1280;
inline constexpr int   SCREEN_HEIGHT = 720;
inline constexpr int   PLAYER_SIZE = 170;
// inline constexpr int   PLAYER_SIZE_WIDTH = 32;
// inline constexpr int   PLAYER_SIZE_HEIGHT = 48;
inline constexpr float GRAVITY = 800.0f;
inline constexpr float JUMP_FORCE = -400.0f;
inline constexpr float PLAYER_SPEED = 200.0f;
inline constexpr float ANIMATION_SPEED = 10.0f;

//Game State
enum GameState {PLAYING, PAUSED, GAME_OVER};

//Animation States
enum PlayerState {IDLE, RUNNING, JUMPING, ATTACKING};
