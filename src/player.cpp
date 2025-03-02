#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <raymath.h>

enum Direction {
    DOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN_LEFT = 4,
    DOWN_RIGHT = 5,
    UP_LEFT = 6,
    UP_RIGHT = 7,
    IDLE = 8
};

class Player {
public:
    Vector2 position;
    float speed;
    Texture2D spriteSheet;
    bool textureLoaded;

    int frameCount;
    int currentFrame;
    float frameTime;
    float timer;
    int frameWidth;
    int frameHeight;
    int spriteRows;
    int spriteCols;

    Direction currentDirection;
    Direction lastDirection;
    bool isMoving;

    Player();
    virtual void LoadTextures();
    void UpdateDirection();
    virtual void Move(float deltaTime);
    int GetDirectionRow();
    virtual void Draw(Vector2 cameraPosition);
    void Unload();
    virtual ~Player();
};

#endif // PLAYER_H
