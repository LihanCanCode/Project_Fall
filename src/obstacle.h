#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <raylib.h>
#include "car.h"

class Obstacle {
public:
    Obstacle(float x, float y, float width, float height);
    void Update();
    void Draw() const;
    bool CheckCollision(const Car& car) const;
    bool IsOffScreen() const;

private:
    float x, y;
    float width, height;
    float speed;
    Color color;
};

#endif // OBSTACLE_H