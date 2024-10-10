#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <vector>
#include "item.h"
#include "npc.h"
#include "bullet.h"
#include "gate.h" // Include the Gate header

class Player {
public:
    Player(float x, float y, float width, float height);
    void Update(const std::vector<Rectangle>& boundaries, std::vector<NPC>& npcs, const Gate& gate, bool& changeMap);
    void Draw() const;
    void AddItem(const Item& item);
    Rectangle GetRect() const;
    float GetX() const;
    float GetY() const;
    void DecrementHealth();
    int GetHealth() const;
    void Shoot();

private:
    float x, y;
    float width, height;
    float speed;
    int health;
    Color color;
    std::vector<Item> inventory;
    std::vector<Bullet> bullets;
};

#endif // PLAYER_H