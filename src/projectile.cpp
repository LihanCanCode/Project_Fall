#include "projectile.h"

Projectile::Projectile(float x, float y, float width, float height, int direction)
    : x(x), y(y), width(width), height(height), speed(10.0f), direction(direction), color(YELLOW) {}

void Projectile::Update() {
    switch (direction) {
        case 0: y -= speed; break;
        case 1: x += speed; break;
        case 2: y += speed; break;
        case 3: x -= speed; break;
    }
}

void Projectile::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

bool Projectile::CheckCollision(const Enemy& enemy) const {
    return CheckCollisionRecs(Rectangle{x, y, width, height}, enemy.GetRect());
}

bool Projectile::IsOffScreen(int screenWidth, int screenHeight) const {
    return x < 0 || x > screenWidth || y < 0 || y > screenHeight;
}