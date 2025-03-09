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
    Texture2D hallTexture;
    Texture2D mysteryTexture;
    Texture2D mysteryTexture2;
    Texture2D classroomTexture;
    Texture2D usbTexture;
    Texture2D cipherTexture;
    Texture2D cipherTexture2;

    Rectangle source1;
    bool keyFound;
    bool bookFound;
    bool keyVisible;
    Vector2 conversationPosition;
    Vector2 mysteryPosition;
    bool firstCollisionOccurred;
    bool mazeActive;
    bool insideHospital;
    bool insideCDS;
    bool insideClassroom;
    bool insideLibrary;
    bool showMystery;
    bool showMystery2;
    bool usbFound;
    bool showcipher;
    bool showcipher2;
    bool insideHall;


    int conversationStep = 0;

    Game();
    void Initialize();
    void UpdateCamera();
    void Run();
    
};

#endif // GAME_H
