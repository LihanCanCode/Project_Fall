#ifndef GATE_H
#define GATE_H

#include <raylib.h>

class Gate {
public:
    Gate(float x, float y, float width, float height);
    void Draw() const;
    Rectangle GetRect() const;

private:
    float x, y;
    float width, height;
    Color color;
};

#endif // GATE_H