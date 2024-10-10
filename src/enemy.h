#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

class Enemy {
public:
    Enemy(float x, float y, float width, float height);
    void Update(float playerX, float playerY);
    void Draw() const;
    Rectangle GetRect() const;

private:
    float x, y;
    float width, height;
    float speed;
    Color color;
};

#endif // ENEMY_H