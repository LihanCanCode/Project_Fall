#include "map.h"

// Screen dimensions
int screenWidth = 1000;
int screenHeight = 950;

Map::Map() {
    textureLoaded = false;
}

void Map::Load(const char* filename) {
    background = LoadTexture(filename);
    if (background.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load background image!");
        textureLoaded = false;
    } else {
        textureLoaded = true;
        TraceLog(LOG_INFO, "Map background loaded successfully");
    }
}

void Map::Draw(Vector2 cameraPosition) {
    if (textureLoaded) {
        DrawTexturePro(background,
                       {0, 0, (float)background.width, (float)background.height},
                       {0 - cameraPosition.x, 0 - cameraPosition.y, (float)background.width, (float)background.height},
                       {0, 0}, 0, WHITE);
    } else {
        DrawRectangle(0, 0, screenWidth, screenHeight, LIGHTGRAY);
        DrawText("Map texture not loaded", screenWidth / 2 - 100, screenHeight / 2, 20, DARKGRAY);
    }
}

void Map::Unload() {
    if (textureLoaded) {
        UnloadTexture(background);
        textureLoaded = false;
    }
}

Map::~Map() {
    Unload();
}
