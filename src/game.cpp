
#include "game.h"
#include <iostream>

Game::Game() {
    initialized = false;
    showDebugInfo = true;
    cameraPosition = {0, 0};
    camera = {0};
}

void Game::Initialize() {
    SetTraceLogLevel(LOG_DEBUG);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "IUT Chronicles");

    if (!IsWindowReady()) {
        std::cout << "Failed to initialize window!" << std::endl;
        return;
    }

    player.position = {135, 2200};

    player.LoadTextures();
    idle.LoadTextures();
    map.Load("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/map.png");

    camera.target = player.position;
    camera.offset = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    initialized = true;
}

void Game::UpdateCamera() {
    camera.target = player.position;

    if (camera.target.x < GetScreenWidth() / 2) camera.target.x = GetScreenWidth() / 2;
    if (camera.target.y < GetScreenHeight() / 2) camera.target.y = GetScreenHeight() / 2;
    if (camera.target.x > map.background.width - GetScreenWidth() / 2) camera.target.x = map.background.width - GetScreenWidth() / 2;
    if (camera.target.y > map.background.height - GetScreenHeight() / 2) camera.target.y = map.background.height - GetScreenHeight() / 2;
}

void Game::Run() {
    Initialize();

    if (!initialized) {
        std::cout << "Game failed to initialize properly. Exiting." << std::endl;
        return;
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F1)) {
            showDebugInfo = !showDebugInfo;
        }

        if (IsKeyPressed(KEY_EQUAL)) {
            camera.zoom += 0.1f;
        }

        if (IsKeyPressed(KEY_MINUS)) {
            camera.zoom -= 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        }

        float deltaTime = GetFrameTime();
        player.Move(deltaTime);
        UpdateCamera();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        map.Draw(cameraPosition);
        player.Draw(cameraPosition);
        Image gg = LoadImage("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/idle.png");
        Texture2D texture = LoadTextureFromImage(gg);
        Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Rectangle rr = {402,2010, 64, 64};
       // idle.Draw(cameraPosition); // Draw the idle character
        DrawTexturePro(texture, source, rr, {0, 0}, 0.0f, WHITE);

        EndMode2D();

        if (showDebugInfo) {
            DrawText("IUT Chronicles - RPG", 10, 10, 20, BLACK);
            DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 16, BLACK);
        }
        
        DrawText(TextFormat("Player position: (%.2f, %.2f)", player.position.x, player.position.y), GetScreenWidth() - 300, 10, 20, BLACK);

        EndDrawing();
    }

    map.Unload();
    player.Unload();
    idle.Unload(); // Unload the idle character texture
    CloseWindow();
}
