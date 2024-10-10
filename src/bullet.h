#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>

class Bullet {
public:
    Bullet(float x, float y, float speed);
    void Update();
    void Draw() const;
    Rectangle GetRect() const;
    bool IsOffScreen(int screenHeight) const;

private:
    float x, y;
    float speed;
    bool active;
};

#endif // BULLET_H