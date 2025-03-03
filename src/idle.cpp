#include "idle.h"

Idle::Idle() : Player() {
    position = {402, 2010};
}

void Idle::LoadTextures() {
    spriteSheet = LoadTexture("C:\\Users\\Lihan\\Desktop\\Semester 2-1\\Oop Lab\\Project_Fall\\Project_Fall\\src\\idle.png");
    if (spriteSheet.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load idle sprite sheet!");
        textureLoaded = false;
    } else {
        textureLoaded = true;
        TraceLog(LOG_INFO, "Idle sprite sheet loaded successfully");

        // Single frame settings
        frameCount = 1;
        spriteRows = 1;
        spriteCols = 1;

        frameWidth = spriteSheet.width-10;
        frameHeight = spriteSheet.height+20;	

        TraceLog(LOG_INFO, "Sprite sheet dimensions: %dx%d", spriteSheet.width, spriteSheet.height);
        TraceLog(LOG_INFO, "Frame dimensions: %dx%d", frameWidth, frameHeight);
    }
}

void Idle::Move(float deltaTime) {
    // Override the Move method to prevent movement
}

void Idle::Draw(Vector2 cameraPosition) {
    if (!textureLoaded) {
        DrawCircleV(Vector2Subtract(position, cameraPosition), 15, RED);
    } else {
        Rectangle source = {
            0.0f,
            0.0f,
            (float)frameWidth,
            (float)frameHeight
        };

        Rectangle dest = {
            position.x - frameWidth / 2 - cameraPosition.x,
            position.y - frameHeight / 2 - cameraPosition.y,
            (float)frameWidth * 2,
            (float)frameHeight * 2
        };

        DrawTexturePro(
            spriteSheet,
            source,
            dest,
            {0, 0},
            0.0f,
            WHITE
        );

        DrawCircleV(Vector2Subtract(position, cameraPosition), 2, RED);
    }
}
