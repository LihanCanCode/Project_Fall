#include "ball.h"

Ball::Ball(float x, float y, float radius)
    : x(x), y(y), radius(radius), speedX(5.0f), speedY(5.0f), color(WHITE) {}

void Ball::Update(int screenWidth, int screenHeight, Player& player1, Player& player2, int& score1, int& score2) {
    x += speedX;
    y += speedY;

    if (y - radius <= 0 || y + radius >= screenHeight) {
        speedY *= -1;
    }

    if (CheckCollisionCircleRec(Vector2{x, y}, radius, player1.GetRect()) || 
        CheckCollisionCircleRec(Vector2{x, y}, radius, player2.GetRect())) {
        speedX *= -1;
    }

    if (x - radius <= 0) {
        score2++;
        x = screenWidth / 2;
        y = screenHeight / 2;
        speedX = -5.0f;
        speedY = 5.0f;
    }

    if (x + radius >= screenWidth) {
        score1++;
        x = screenWidth / 2;
        y = screenHeight / 2;
        speedX = 5.0f;
        speedY = 5.0f;
    }
}

void Ball::Draw() const {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, color);
}