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
    bool showConversation;
    Texture2D conversationTexture1;
    Texture2D conversationTexture2;
    Texture2D conversationTexture3;
    Texture2D conversationTexture4;
    Texture2D keyTexture;
    Texture2D hospitalTexture;
    Texture2D libraryTexture;
    Texture2D cdsTexture;
    Texture2D bookTexture;
    bool keyFound;
    bool bookFound;
    bool keyVisible;
    Vector2 conversationPosition;
    bool firstCollisionOccurred;
    bool mazeActive;
    bool insideHospital;
    bool insideCDS;
    bool insideLibrary;


    int conversationStep = 0;

    Game();
    void Initialize();
    void UpdateCamera();
    void Run();
    
};

#endif // GAME_H
