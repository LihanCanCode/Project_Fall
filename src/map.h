#ifndef MAP_H
#define MAP_H

#include <raylib.h>

class Map {
public:
    Map(int screenWidth, int screenHeight);
    void Draw() const;

private:
    int screenWidth, screenHeight;
};

#endif // MAP_H