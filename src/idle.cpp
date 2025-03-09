#include "idle.h"

Idle::Idle() : Player() {
    position = {402, 2010};
}

void Idle::LoadTextures() {
    spriteSheet = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/idle.png");
    frameWidth = spriteSheet.width;
    frameHeight = spriteSheet.height;
    textureLoaded = true;
}

void Idle::Move(float deltaTime) {
    // Override the Move method to prevent movement
}

void Idle::Draw(Vector2 cameraPosition) {
    Vector2 idlePosition = {1165, 1090}; // Set the idle character's position

    if (!textureLoaded) {
        DrawCircleV(Vector2Subtract(idlePosition, cameraPosition), 15, RED);
    } else {
        Rectangle source = {
            0.0f,
            0.0f,
            (float)frameWidth-10,
            (float)frameHeight
        };

        Rectangle dest = {
            idlePosition.x - 35 - cameraPosition.x, // Adjust for half the width
            idlePosition.y - 47.5f - cameraPosition.y, // Adjust for half the height
            70.0f, // Set the width to 70
            95.0f // Set the height to 95
        };

        DrawTexturePro(
            spriteSheet,
            source,
            dest,
            {0, 0},
            0.0f,
            WHITE
        );

        DrawCircleV(Vector2Subtract(idlePosition, cameraPosition), 2, RED);
    }
}
