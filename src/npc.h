#ifndef NPC_H
#define NPC_H

#include <raylib.h>

class NPC {
public:
    NPC(float x, float y, float width, float height);
    void Update();
    void Draw() const;
    Rectangle GetRect() const;

private:
    float x, y;
    float width, height;
    Color color;
};

#endif // NPC_H