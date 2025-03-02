#include "player.h"
#include <iostream>

Player::Player() {
    position = {135, 2200};
    speed = 100.0f;
    currentDirection = DOWN;
    lastDirection = DOWN;
    isMoving = false;
    textureLoaded = false;

    frameCount = 3;
    currentFrame = 0;
    frameTime = 0.15f;
    timer = 0.0f;
    frameWidth = 32;
    frameHeight = 32;
    spriteRows = 6;
    spriteCols = 6;
}

void Player::LoadTextures() {
    spriteSheet = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/player.png");
    if (spriteSheet.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load character sprite sheet!");
        textureLoaded = false;
    } else {
        textureLoaded = true;
        TraceLog(LOG_INFO, "Character sprite sheet loaded successfully");

        frameWidth = spriteSheet.width / spriteCols;
        frameHeight = spriteSheet.height / spriteRows;

        TraceLog(LOG_INFO, "Sprite sheet dimensions: %dx%d", spriteSheet.width, spriteSheet.height);
        TraceLog(LOG_INFO, "Frame dimensions: %dx%d", frameWidth, frameHeight);
    }
}

void Player::UpdateDirection() {
    bool up = IsKeyDown(KEY_UP);
    bool down = IsKeyDown(KEY_DOWN);
    bool left = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);

    isMoving = up || down || left || right;

    if (!isMoving) {
        return;
    }

    if (up && right) currentDirection = UP_RIGHT;
    else if (up && left) currentDirection = UP_LEFT;
    else if (down && right) currentDirection = DOWN_RIGHT;
    else if (down && left) currentDirection = DOWN_LEFT;
    else if (up) currentDirection = UP;
    else if (down) currentDirection = DOWN;
    else if (left) currentDirection = LEFT;
    else if (right) currentDirection = RIGHT;

    lastDirection = currentDirection;
}

void Player::Move(float deltaTime) {
    Vector2 movement = {0, 0};

    if (IsKeyDown(KEY_RIGHT)) movement.x += 1;
    if (IsKeyDown(KEY_LEFT)) movement.x -= 1;
    if (IsKeyDown(KEY_UP)) movement.y -= 1;
    if (IsKeyDown(KEY_DOWN)) movement.y += 1;

    if (movement.x != 0 && movement.y != 0) {
        movement.x *= 0.7071f;
        movement.y *= 0.7071f;
    }

    position.x += movement.x * speed * deltaTime;
    position.y += movement.y * speed * deltaTime;

    if (position.x < 50) position.x = 50;
    if (position.y < 56) position.y = 56;
    if (position.x > 2200) position.x = 2200;
    if (position.y > 2200) position.y = 2200;

    UpdateDirection();

    if (isMoving) {
        timer += deltaTime;

        if (timer >= frameTime) {
            timer = 0.0f;
            currentFrame = (currentFrame + 1) % frameCount;
        }
    } else {
        currentFrame = 0;
    }
}

int Player::GetDirectionRow() {
    switch (currentDirection) {
        case DOWN: return 0;
        case LEFT: return 1;
        case RIGHT: return 2;
        case UP: return 3;
        case DOWN_LEFT: return 4;
        case DOWN_RIGHT: return 5;
        case UP_LEFT: return 6;
        case UP_RIGHT: return 7;
        default: return 0;
    }
}

void Player::Draw(Vector2 cameraPosition) {
    if (!textureLoaded) {
        DrawCircleV(Vector2Subtract(position, cameraPosition), 15, RED);
    } else {
        int row = GetDirectionRow();

        DrawText(TextFormat("Direction: %d, Frame: %d", row, currentFrame), 10, 70, 16, BLACK);

        Rectangle source = {
            (float)(currentFrame * frameWidth - 10),
            (float)(row * frameHeight),
            (float)frameWidth,
            (float)frameHeight
        };

        Rectangle dest = {
            position.x - frameWidth - cameraPosition.x,
            position.y - frameHeight - cameraPosition.y,
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

        Rectangle playerRect = {
            position.x - cameraPosition.x - frameWidth / 2,
            position.y - cameraPosition.y - frameHeight / 2,
            (float)frameWidth,
            (float)frameHeight
        };

        DrawRectangleLines(playerRect.x, playerRect.y, playerRect.width, playerRect.height, GREEN);
        DrawCircleV(Vector2Subtract(position, cameraPosition), 2, RED);
    }
}

void Player::Unload() {
    if (textureLoaded) {
        UnloadTexture(spriteSheet);
        textureLoaded = false;
    }
}

Player::~Player() {
    Unload();
}
