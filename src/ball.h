#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include "player.h"

class Ball {
public:
    Ball(float x, float y, float radius);
    void Update(int screenWidth, int screenHeight, Player& player1, Player& player2, int& score1, int& score2);
    void Draw() const;

private:
    float x, y;
    float radius;
    float speedX, speedY;
    Color color;
};

#endif // BALL_H