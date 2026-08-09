#include "isaac-fps/entities/player.hpp"
#include <raylib.h>

int main(void) {
  const int _screen_width = 800;
  const int _screen_height = 600;

  InitWindow(_screen_width, _screen_height, "Ventana Raylib");
  SetTargetFPS(60);
  DisableCursor();

  // INSTANCIA DEL JUGADOR
  Player player({0.0f, 0.0f, 0.0f});

  while (!WindowShouldClose()) {

    player.Update();
    BeginDrawing();

    ClearBackground(BLACK);
    BeginMode3D(player.GetCamera());
    DrawGrid(50, 1.0f);
    EndMode3D();

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
