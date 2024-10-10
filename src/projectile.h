#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>
#include "enemy.h"

class Projectile {
public:
    Projectile(float x, float y, float width, float height, int direction);
    void Update();
    void Draw() const;
    bool CheckCollision(const Enemy& enemy) const;
    bool IsOffScreen(int screenWidth, int screenHeight) const;

private:
    float x, y;
    float width, height;
    float speed;
    int direction; // 0: up, 1: right, 2: down, 3: left
    Color color;
};

#endif // PROJECTILE_H