#include "gate.h"

Gate::Gate(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), color(GREEN) {}

void Gate::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

Rectangle Gate::GetRect() const {
    return Rectangle{x, y, width, height};
}