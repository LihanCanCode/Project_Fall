#ifndef IDLE_H
#define IDLE_H

#include "player.h"

class Idle : public Player {
public:
    Idle();
    void LoadTextures() override;
    void Move(float deltaTime) override;
    void Draw(Vector2 cameraPosition) override;
};

#endif // IDLE_H
