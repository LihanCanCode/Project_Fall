
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "idle.h"
#include "map.h"

class Game {
public:
    Player player;
    Idle idle;
    Map map;
    bool initialized;
    bool showDebugInfo;
    Vector2 cameraPosition;
    Camera2D camera;

    Game();
    void Initialize();
    void UpdateCamera();
    void Run();
};

#endif // GAME_H
