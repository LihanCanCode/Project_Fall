#ifndef CAR_H
#define CAR_H

#include <raylib.h>

class Car {
public:
    Car(float x, float y, float width, float height);
    void Update();
    void Draw() const;
    Rectangle GetRect() const;

private:
    float x, y;
    float width, height;
    float speed;
    Color color;
};

#endif // CAR_H