#include "car.h"

Car::Car(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(5.0f), color(BLUE) {}

void Car::Update() {
    if (IsKeyDown(KEY_RIGHT) && x + width < GetScreenWidth()) {
        x += speed;
    }
    if (IsKeyDown(KEY_LEFT) && x > 0) {
        x -= speed;
    }
}

void Car::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

Rectangle Car::GetRect() const {
    return Rectangle{x, y, width, height};
}