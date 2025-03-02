#include "game.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Rectangle> buildings = {Rectangle{402, 2010, 90, 95},//idle 
                                Rectangle{422,640,280,550}, //nicher math
                                Rectangle{240,2075,1405,200},   //lake er bam
                                Rectangle{1185,855,235,250},    //mosque
                                Rectangle{700,640,480,100},//lake er upor
                                Rectangle{1274,640,370,100},//lake er dan
                                Rectangle{1464,735,180,400},//lake er dan niche
                                Rectangle{810, 1190,520,225},
                                Rectangle{1473,1190,180,225},
                                Rectangle{1695, 1530, 520, 460},//right e hall
                                Rectangle{1309, 1496, 320, 180},//cds
                                Rectangle{1733, 1115, 500, 240},//right mid hall
                                Rectangle{1918, 1080, 280, 40},//right mid hall upor
                                Rectangle{1722, 634, 500, 300},//right mid hall dan
                                Rectangle{1399, 56, 270, 270}, //medical
                                Rectangle{100, 70, 550, 280}, //medical
                                Rectangle{420,1190, 270, 215}
                                 };
Rectangle idleRect = {1142, 1045, 70, 95}; // Define the idle character's collision rectangle

void ResolvePlayerBuildingCollision(Rectangle& destrect, const vector<Rectangle>& buildings) {
    // Loop through all buildings to check for collision
    for (const auto& building : buildings) {
        // Calculate the overlap between player and building
        float overlapX = (destrect.x + destrect.width / 2) - (building.x + building.width / 2);
        float overlapY = (destrect.y + destrect.height / 2) - (building.y + building.height / 2);

        // Half-widths and half-heights of the player and building
        float halfWidthSum = (destrect.width + building.width) / 2;
        float halfHeightSum = (destrect.height + building.height) / 2;

        // Check for overlap (collision detection)
        if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
            // Calculate penetration distances
            float penetrationX = halfWidthSum - fabs(overlapX);
            float penetrationY = halfHeightSum - fabs(overlapY);

            // Resolve collision by moving player back based on smaller penetration distance
            if (penetrationX < penetrationY) {
                // Resolve X-axis collision
                if (overlapX > 0) {
                    destrect.x += penetrationX;  // Move player to the right
                } else {
                    destrect.x -= penetrationX;  // Move player to the left
                }
            } else {
                // Resolve Y-axis collision
                if (overlapY > 0) {
                    destrect.y += penetrationY;  // Move player down
                } else {
                    destrect.y -= penetrationY;  // Move player up
                }
            }
        }
    }
}

void ResolvePlayerIdleCollision(Rectangle& playerRect, const Rectangle& idleRect, Vector2& conversationPosition, bool& showConversation) {
    // Calculate the overlap between player and idle character
    float overlapX = (playerRect.x + playerRect.width / 2) - (idleRect.x + idleRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (idleRect.y + idleRect.height / 2);

    // Half-widths and half-heights of the player and idle character
    float halfWidthSum = (playerRect.width + idleRect.width) / 2;
    float halfHeightSum = (playerRect.height + idleRect.height) / 2;

    // Check for overlap (collision detection)
    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        // Calculate penetration distances
        float penetrationX = halfWidthSum - fabs(overlapX);
        float penetrationY = halfHeightSum - fabs(overlapY);

        // Print collision message
        std::cout << "Collision with idle character detected!" << std::endl;

        // Resolve collision by moving player back based on smaller penetration distance
        if (penetrationX < penetrationY) {
            // Resolve X-axis collision
            if (overlapX > 0) {
                playerRect.x += penetrationX;  // Move player to the right
            } else {
                playerRect.x -= penetrationX;  // Move player to the left
            }
        } else {
            // Resolve Y-axis collision
            if (overlapY > 0) {
                playerRect.y += penetrationY;  // Move player down
            } else {
                playerRect.y -= penetrationY;  // Move player up
            }
        }

        // Set conversation position and show the image
        conversationPosition = {playerRect.x-50, playerRect.y -280}; // Slightly above the player
        showConversation = true;
    }
}

Game::Game() {
    initialized = false;
    showDebugInfo = true;
    cameraPosition = {0, 0};
    camera = {0};
    showConversation = false;  // Initialize the conversation flag
    conversationPosition = {0, 0};  // Initialize the conversation position
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
    //collision rect for player 
    SetTargetFPS(60);
    initialized = true;

    // Load the conversation texture
    conversationTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/conversation1.png");
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
        
        if (!showConversation) { // Only move the player if conversation is NOT showing
            player.Move(deltaTime);
        }

        // Adjust the collision rectangle to better fit the player's sprite
        Rectangle playerCollisionRect = {player.position.x, player.position.y, 25, 25};
        
        // Perform collision detection and resolution
        ResolvePlayerBuildingCollision(playerCollisionRect, buildings);
        ResolvePlayerIdleCollision(playerCollisionRect, idleRect, conversationPosition, showConversation);
        
        // Update player position based on the modified collision rectangle
        player.position.x = playerCollisionRect.x;
        player.position.y = playerCollisionRect.y;

        UpdateCamera();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        map.Draw(cameraPosition);
        player.Draw(cameraPosition);
        Image gg = LoadImage("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/idle.png");
        Texture2D texture = LoadTextureFromImage(gg);
        Rectangle source = {0.0f, 0.0f, (float)texture.width-10, (float)texture.height};
        
        //drawing rectangle for collision check
        DrawRectangleLines(idleRect.x, idleRect.y, idleRect.width, idleRect.height, RED);
        DrawRectangleLines(422,640,270,550, RED);
        DrawRectangleLines(240,2051,1405,200, RED);
        DrawRectangleLines(1185,855,220,250, RED);
        DrawRectangleLines(700,640,464,100, RED);

        DrawRectangleLines(1274,640,370,200,RED);
        DrawRectangleLines(1464,735,180,350,RED);
        DrawRectangleLines(810, 1190,500,225,RED);
        DrawRectangleLines(1473,1200,200,225,RED);
        DrawRectangleLines(1695, 1530, 500, 460,RED);
        DrawRectangleLines(1309, 1496, 320, 180,RED);
        DrawRectangleLines(1733, 1115, 500, 240,RED);
        DrawRectangleLines(1918, 1080, 280, 40,RED);
        DrawRectangleLines(1722, 634, 500, 300,RED);
        DrawRectangleLines(1399, 56, 270, 270,RED);
        DrawRectangleLines(100, 70, 550, 280,RED);
        DrawRectangleLines(420,1190, 270, 215,RED);

        // If conversation is active, draw the image
        if (showConversation) {
            DrawTexture(conversationTexture, conversationPosition.x, conversationPosition.y, WHITE);
        }

        DrawTexturePro(texture, source, idleRect, {0, 0}, 0.0f, WHITE);
        EndMode2D();

        if (showDebugInfo) {
            DrawText("IUT Chronicles - RPG", 10, 10, 20, BLACK);
            DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 16, BLACK);
            DrawText(TextFormat("Player position: (%.2f, %.2f)", player.position.x, player.position.y), GetScreenWidth() - 300, 10, 20, BLACK);
        }

        // Print the current state of showConversation at the top-right corner
        DrawText(TextFormat("Conversation: %s", showConversation ? "ON" : "OFF"), GetScreenWidth() - 200, 50, 20, BLACK);

        // If Enter is pressed, hide the conversation
        if (showConversation && IsKeyPressed(KEY_ENTER)) {
            showConversation = false;
        }

        EndDrawing();
    }

    map.Unload();
    player.Unload();
    idle.Unload(); // Unload the idle character texture
    UnloadTexture(conversationTexture); // Unload the conversation texture
    CloseWindow();
}
