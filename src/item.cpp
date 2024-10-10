#include "item.h"
#include "player.h"

Item::Item(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), pickedUp(false), color(GOLD) {}

void Item::Draw() const {
    if (!pickedUp) {
        DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
    }
}

bool Item::CheckCollision(const Player& player) const {
    return CheckCollisionRecs(Rectangle{x, y, width, height}, player.GetRect());
}

void Item::PickUp() {
    pickedUp = true;
}

bool Item::IsPickedUp() const {
    return pickedUp;
}