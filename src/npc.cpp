#include "npc.h"

NPC::NPC(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), color(RED) {}

void NPC::Update() {
    // NPC logic here
}

void NPC::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

Rectangle NPC::GetRect() const {
    return Rectangle{x, y, width, height};
}