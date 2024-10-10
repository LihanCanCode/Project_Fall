#include "enemy.h"

Enemy::Enemy(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(2.0f), color(RED) {}

void Enemy::Update(float playerX, float playerY) {
    if (x < playerX) {
        x += speed;
    } else {
        x -= speed;
    }
    if (y < playerY) {
        y += speed;
    } else {
        y -= speed;
    }
}

void Enemy::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

Rectangle Enemy::GetRect() const {
    return Rectangle{x, y, width, height};
}