#include "map.h"

Map::Map(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {}

void Map::Draw() const {
    DrawRectangle(0, 0, screenWidth, screenHeight, DARKGREEN);
}