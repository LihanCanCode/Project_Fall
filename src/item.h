#ifndef ITEM_H
#define ITEM_H

#include <raylib.h>

class Player;

class Item {
public:
    Item(float x, float y, float width, float height);
    void Draw() const;
    bool CheckCollision(const Player& player) const;
    void PickUp();
    bool IsPickedUp() const;

private:
    float x, y;
    float width, height;
    bool pickedUp;
    Color color;
};

#endif // ITEM_H