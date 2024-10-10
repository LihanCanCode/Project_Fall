#include "obstacle.h"

Obstacle::Obstacle(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(5.0f), color(RED) {}

void Obstacle::Update() {
    y += speed;
}

void Obstacle::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

bool Obstacle::CheckCollision(const Car& car) const {
    return CheckCollisionRecs(Rectangle{x, y, width, height}, car.GetRect());
}

bool Obstacle::IsOffScreen() const {
    return y > GetScreenHeight();
}