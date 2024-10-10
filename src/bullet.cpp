#include "bullet.h"

Bullet::Bullet(float x, float y, float speed)
    : x(x), y(y), speed(speed), active(true) {}

void Bullet::Update() {
    if (active) {
        y -= speed;
    }
}

void Bullet::Draw() const {
    if (active) {
        DrawRectangle(static_cast<int>(x), static_cast<int>(y), 5, 10, BLACK);
    }
}

Rectangle Bullet::GetRect() const {
    return Rectangle{x, y, 5, 10};
}

bool Bullet::IsOffScreen(int screenHeight) const {
    return y < 0;
}