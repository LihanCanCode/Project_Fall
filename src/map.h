#ifndef MAP_H
#define MAP_H

#include <raylib.h>

class Map {
public:
    Texture2D background;
    bool textureLoaded;

    Map();
    void Load(const char* filename);
    void Draw(Vector2 cameraPosition);
    void Unload();
    ~Map();
};

#endif // MAP_H
