#include "game.hpp"
#include "config.h"

Game::Game() : player(characterSheet), score(0), keys(0), state(PLAYING) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Game Demo");
  SetTargetFPS(60);
  characterSheet = LoadTexture("assets/character_sprite.png");
  environmentSheet = LoadTexture("assets/environment_sprite.png");

  bgLayers = {
    {LoadTexture("assets/bg_05.png"), 0.1f, 0},
    {LoadTexture("assets/bg_04.png"), 0.3f, 0},
    {LoadTexture("assets/bg_03.png"), 0.6f, 0},
    {LoadTexture("assets/bg_02.png"), 0.7f, 0},
    {LoadTexture("assets/bg_01.png"), 0.8f, 0}
  };

  camera.target = {0, 0};
  camera.offset = {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;

  CreateLevel();
}

void Game::CreateLevel() {
  // Ground platforms
  platforms.push_back({0, 600, 800, 120});
  platforms.push_back({900, 550, 400, 120});
  platforms.push_back({1400, 500, 300, 120});
  platforms.push_back({1800, 450, 200, 20});
  platforms.push_back({2100, 400, 200, 20});
  platforms.push_back({2400, 350, 500, 120});

  // Floating platforms
  platforms.push_back({300, 450, 100, 20});
  platforms.push_back({500, 350, 100, 20});
  platforms.push_back({700, 250, 100, 20});

  // Collectibles
  coins.emplace_back(Vector2{350, 400});
  coins.emplace_back(Vector2{550, 300});
  coins.emplace_back(Vector2{750, 200});
  coins.emplace_back(Vector2{1000, 500});
  coins.emplace_back(Vector2{1500, 450});

  // Doors
  doors.emplace_back(750.0f, 536.0f, 0);
  doors.emplace_back(2800.0f, 286.0f, 1);

  // Enemies
  enemies.emplace_back(Enemy{1000, 502, 150});
  enemies.emplace_back(Enemy{1600, 452, 100});

  // Key pickup
  coins.emplace_back(Vector2{2200, 350});
}

void Game::Update(float deltaTime) {
  if (state != PLAYING)
    return;

  player.Update(deltaTime, platforms);
  camera.target = {player.position.x, player.position.y - 100};

  if (IsKeyPressed(KEY_P))
    state = PAUSED;

  for (auto &coin : coins) {
    coin.Update(deltaTime);
    if (coin.CheckCollision(player.GetBounds())) {
      coin.collected = true;
      score += 10;
      if (coin.position.x > 2100 && coin.position.x < 2300) {
        keys++;
      }
    }
  }

  for (auto &door : doors) {
    door.Update(player, keys);
  }

  for (auto &enemy : enemies) {
    enemy.Update(deltaTime, player);
  }

  if (doors.size() > 1 && doors[1].isOpen &&
      CheckCollisionRecs(player.GetBounds(),
                         {doors[1].position.x, doors[1].position.y,
                          doors[1].width, doors[1].height})) {
    // level complete
  }

  if (IsKeyPressed(KEY_P))
    state = PAUSED;

  for (auto &layer: bgLayers){
    layer.offsetX = -player.position.x * layer.speed;
  }

}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(SKYBLUE);

  for (auto &layer: bgLayers){
    float x = fmod(layer.offsetX, layer.texture.width);
    DrawTexture(layer.texture, x, 0, WHITE);
    DrawTexture(layer.texture, x + layer.texture.width, 0, WHITE);
  }

  BeginMode2D(camera);

  for (const auto &plat : platforms) {
    Rectangle source = {0, 64, 32, 32};
    for (float x = plat.x; x < plat.x + plat.width; x += 32) {
      for (float y = plat.y; y < plat.y + plat.height; y += 32) {
        DrawTexturePro(environmentSheet, source, {x, y, 32, 32}, {0, 0}, 0, WHITE);
      }
    }
  }

  for (auto &door : doors) {
    door.Draw(environmentSheet);
  }

  for (auto &coin : coins) {
    coin.Draw(environmentSheet);
  }

  for (auto &enemy : enemies) {
    enemy.Draw(characterSheet);
  }

  player.Draw(characterSheet);

  if (player.state == ATTACKING) {
    Rectangle atk = player.GetAttackHitBox();
    DrawRectangleRec(atk, ColorAlpha(RED, 0.3));
  }

  EndMode2D();

  DrawText(TextFormat("SCORE %d", score), 20, 20, 20, WHITE);
  DrawText(TextFormat("KEYS %d", keys), 20, 50, 20, YELLOW);

  DrawText("A/D Move | Space: Jump | J: ATTACK | E: Interact", 20,
           SCREEN_HEIGHT - 30, 16, WHITE);

  EndDrawing();
}

void Game::HandleInput() {
  if (state == PAUSED && IsKeyPressed(KEY_P)) {
    state = PLAYING;
  }
}

Game::~Game() {
  UnloadTexture(characterSheet);
  UnloadTexture(environmentSheet);
  for (auto &layer: bgLayers){
    UnloadTexture(layer.texture);
  }
  CloseWindow();
}

bool Game::ShouldClose() const { return WindowShouldClose(); }