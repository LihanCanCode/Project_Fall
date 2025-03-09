#include "game.h"
#include "collision.h"
#include "idle.h"
#include <iostream>
#include <vector>
using namespace std;
enum GameState {
    MAP,
    HOSPITAL
};

vector<Rectangle> buildings = { Rectangle{422,640,250,550}, //
                                Rectangle{240,2075,1330,200},   //lake er bam
                                Rectangle{1185,855,235,250},     //mosque
                                Rectangle{660,640,515,100},//lake er upor
                                Rectangle{1274,640,370,100},//lake er dan
                                Rectangle{1464,735,180,400},//lake er dan niche
                                Rectangle{760, 1190,570,225},
                                Rectangle{1473,1190,180,225},
                                Rectangle{1695, 1530, 520, 460},//right e hall
                                Rectangle{1260, 1496, 340, 190},//cds
                                Rectangle{1733, 1115, 530, 240},//right mid hall
                                Rectangle{1918, 1080, 280, 40},//right mid hall upor
                                Rectangle{1722, 634, 500, 300},//right mid hall dan
                                Rectangle{1399, 56, 270, 270}, //medical
                                Rectangle{100, 70, 550, 280}, //female
                                Rectangle{420,1190, 250, 215},
                                Rectangle{672, 740, 450, 260},//auditorium
                                Rectangle{1338, 1825, 200, 170},//right mid hall
                                };
Rectangle idleRect = {1142, 1045, 70, 95}; // Define the idle character's collision rectangle
Rectangle keyRect = {1300, 80, 32, 32}; // Define the key's collision rectangle
Rectangle mazeRect={1335, 1820, 210, 180};
Rectangle hospitalRect = {1395, 50, 280, 280}; // Define the hospital's collision rectangle
Rectangle cdsRect ={1390,1670,80,30};
Rectangle libraryRect={1940,914,150,30};
Rectangle bookRect = {1585,364,32,32}; // Define the book's collision rectangle
Rectangle classroomRect ={1965,1355,100,40};

//Inside Hospital Rectangles
vector<Rectangle> hospitalCollisions = {
    {711, 585, 260, 280},
    {1272, 227, 240, 60},
    {1042, 231, 232, 60},
    {752, 229, 208, 60},
    {939, 364, 25, 110},
    {1050, 425, 450, 25},
    {1060, 450, 245, 405},
    {690,423,225,50},
    {713,865,230,70},
    {1295,855,20,140},
    {725,56,480,65},
    {1323,56,100,40},
    {1392,98,30,100},
    {1274,287,210,70}
};

vector<Rectangle> libraryCOllisions ={
    {1450,56,750,84},
    {740,56,625,84},
    {740,145,115,495},
    {1950,145,250,45},
    {757,727,95,284},
    {727,1100,123,550},
    {727,1750,122,253},
    {850,1912,161,1003},
    {1970,895,230,580}
};

vector<Rectangle> classroomCollisions ={
    {}
};






Game::Game() {
    initialized = false;
    showDebugInfo = true;
    insideHospital = false;
    insideCDS = false; 
    insideLibrary = false;
    cameraPosition = {0, 0};
    camera = {0};
    showConversation = false;  // Initialize the conversation flag
    conversationPosition = {0, 0};  // Initialize the conversation position
    conversationStep = 0;  // Initialize the conversation step
    firstCollisionOccurred = false;  // Initialize the first collision flag
    keyFound = false;  // Initialize the key found flag
    keyVisible = false; // Initialize the key visibility flag
    bookFound = false; // Initialize the book found flag
    showMystery= false;
    showMystery2= false;
    insideClassroom=false;

}

void Game::Initialize() {
    SetTraceLogLevel(LOG_DEBUG);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "IUT Chronicles");

    if (!IsWindowReady()) {
        std::cout << "Failed to initialize window!" << std::endl;
        return;
    }

    player.position = {135, 2200};

    player.LoadTextures();
    idle.LoadTextures();
    map.Load("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/map2.png");

    camera.target = player.position;
    camera.offset = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    //collision rect for player 
    SetTargetFPS(60);
    initialized = true;

    
       

    // Load the conversation textures
    conversationTexture1 = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/conversation1.png");
    conversationTexture2 = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/conversation2.png");
    conversationTexture3 = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/conversation3.png");
    conversationTexture4 = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/conversation4.png");
    keyTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/key.png"); // Load the key texture
    hospitalTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/hospital.png");
    libraryTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/library.png");
    cdsTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/cds.png");
    bookTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/book.png");
    mysteryTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/mystery.png");
    mysteryTexture2 = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/mystery2.png");
    classroomTexture = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/classroom.png");
    source1={0.0f,0.0f,(float)mysteryTexture2.width,(float)mysteryTexture2.height};


}

void Game::UpdateCamera() {
    camera.target = player.position;

    if (camera.target.x < GetScreenWidth() / 2) camera.target.x = GetScreenWidth() / 2;
    if (camera.target.y < GetScreenHeight() / 2) camera.target.y = GetScreenHeight() / 2;
    if (camera.target.x > map.background.width - GetScreenWidth() / 2) camera.target.x = map.background.width - GetScreenWidth() / 2;
    if (camera.target.y > map.background.height - GetScreenHeight() / 2) camera.target.y = map.background.height - GetScreenHeight() / 2;
}




void Game::Run() {
    Initialize();

    if (!initialized) {
        std::cout << "Game failed to initialize properly. Exiting." << std::endl;
        return;
    }

    bool playerPositionUpdated = false; // Flag to ensure the player's position is updated only once

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F1)) {
            showDebugInfo = !showDebugInfo;
        }

        if (IsKeyPressed(KEY_EQUAL)) {
            camera.zoom += 0.1f;
        }

        if (IsKeyPressed(KEY_MINUS)) {
            camera.zoom -= 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        }

        float deltaTime = GetFrameTime();
        
        if (!showConversation && !showMystery) { // Only move the player if conversation is NOT showing
            player.Move(deltaTime);
        }

        // Adjust the collision rectangle to better fit the player's sprite
        Rectangle playerCollisionRect = {player.position.x, player.position.y, 25, 25};
        
        if (!insideHospital && !insideCDS && !insideLibrary && !insideClassroom) {
            // Perform collision detection and resolution
            ResolvePlayerBuildingCollision(playerCollisionRect, buildings);
            ResolvePlayerIdleCollision(playerCollisionRect, idleRect, conversationPosition, showConversation, conversationStep, firstCollisionOccurred);
            if (keyVisible && !keyFound) {
                ResolvePlayerKeyCollision(playerCollisionRect, keyRect, keyFound);
            }
        }


        if(!insideHospital && !insideCDS && !insideLibrary && !insideClassroom){
            ResolvePlayerHospitalCollision(playerCollisionRect, hospitalRect, insideHospital, playerPositionUpdated); // Check for hospital collision
            ResolvePlayerCDSCollision(playerCollisionRect, cdsRect, insideCDS, playerPositionUpdated); // Check for CDS collision
            ResolvePlayerLibraryCollision(playerCollisionRect, libraryRect, insideLibrary, playerPositionUpdated); // Check for library collision
            ResolvePlayerClassroomCollision(playerCollisionRect, classroomRect, insideClassroom, playerPositionUpdated); // Check for library collision	
        }

        if (insideHospital) {
            DrawRectangleLines(711, 585, 260, 280, BLUE);
            DrawRectangleLines(1272, 227, 240, 135, BLUE);
            DrawRectangleLines(1042, 231, 232, 300, BLUE);
            DrawRectangleLines(752, 229, 208, 60, BLUE);
            DrawRectangleLines(939, 364, 25, 110, BLUE);
            DrawRectangleLines(1050, 425, 450, 25, BLUE);
            DrawRectangleLines(1060, 450, 245, 405, BLUE);
            DrawRectangleLines(690,423,225,50,BLUE);
            
            InsideHospital(playerCollisionRect, hospitalCollisions);

            //check
            if(IsKeyPressed(KEY_C)){
                insideHospital=false;
                player.position.x=1517;
                player.position.y=382;
                playerCollisionRect.x = 1517; // Update the collision rectangle position
                playerCollisionRect.y = 382;   // Update the collision rectangle position

                playerPositionUpdated=false;
            }
        }


        if(insideCDS){
            DrawRectangleLines(1390,1670,80,30,BLUE);
            if(IsKeyPressed(KEY_C)){
                insideCDS=false;
                player.position.x=1390;
                player.position.y=1710;
                playerCollisionRect.x = 1390; // Update the collision rectangle position
                playerCollisionRect.y = 1710;   // Update the collision rectangle position

                playerPositionUpdated=false;
            }
        }


        if(insideLibrary){

           
            if(IsKeyPressed(KEY_C)){
                insideLibrary=false;
                player.position.x=1940;
                player.position.y=950;
                playerCollisionRect.x = 1940; // Update the collision rectangle position
                playerCollisionRect.y = 950;   // Update the collision rectangle position

                playerPositionUpdated=false;
            }
            
            InsideLibrary(playerCollisionRect, libraryCOllisions);
            //check bookfound
            
            if(!bookFound){
                ResolvePlayerBookCollision(playerCollisionRect, bookRect, bookFound);
                if(bookFound){
                    showMystery=true;
                    //mysteryPosition={1500,350};
                }
            }
        }

        if(insideClassroom){
            if(IsKeyPressed(KEY_C)){
                insideClassroom=false;
                player.position.x=1965;
                player.position.y=1365;
                playerCollisionRect.x = 1965; // Update the collision rectangle position
                playerCollisionRect.y = 1365;   // Update the collision rectangle position

                playerPositionUpdated=false;
            }
        }

        // Update player position based on the modified collision rectangle
        player.position.x = playerCollisionRect.x;
        player.position.y = playerCollisionRect.y;

        UpdateCamera();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        if (insideHospital) {
            DrawTexture(hospitalTexture, 700, 0, WHITE); // Draw the hospital map
        }
        else if(insideCDS){
            DrawTexture(cdsTexture, 0, 0 , WHITE); // Draw the CDS map
        }
        else if(insideLibrary){
            DrawTexture(libraryTexture, 700, 0 , WHITE); // Draw the library map
            if(!bookFound){
                DrawTexture(bookTexture, 1585,364, WHITE);
                DrawRectangleLines(1585, 364, 32, 32, RED); // Draw the book's collision rectangle
            }
            /*if(!bookFound){
                DrawTexture(bookTexture, bookRect.x, bookRect.y, WHITE);
                DrawRectangleLines(bookRect.x, bookRect.y, 32, 32, RED); // Draw the book's collision rectangle
            }*/
        }
        else if(insideClassroom) {
            Rectangle source = {0.0f, 0.0f, (float)classroomTexture.width, (float)classroomTexture.height};
            Rectangle dest = {0, 500, 2200, 1500}; // Set the destination rectangle to the desired dimensions
            Vector2 origin = {0, 0};
            DrawTexturePro(classroomTexture, source, dest, origin, 0.0f, WHITE); // Draw the classroom map using DrawTexturePro
        }
        else {
            map.Draw(cameraPosition); // Draw the main map
        }
        player.Draw(cameraPosition);

        
        if (!insideHospital && !insideCDS && !insideLibrary && !insideClassroom) {
           // DrawTexturePro(Texture, source, {idleRect.x, idleRect.y, idleRect.width, idleRect.height}, {idleRect.width / 2, idleRect.height / 2}, 0.0f, WHITE);
            idle.Draw(cameraPosition);
        }

        if(showMystery){
            DrawTexture(mysteryTexture, 1100,200, WHITE);
        }

        if(showMystery2){
           
            DrawTexturePro(mysteryTexture2, source1, {1350,250, (float)mysteryTexture2.width+120,(float) mysteryTexture2.height+150}, {0,0}, 0.0f, WHITE);
        }

        
        
        
        //drawing rectangle for collision check
        DrawRectangleLines(idleRect.x, idleRect.y, idleRect.width, idleRect.height, RED);
        DrawRectangleLines(422,640,240,550, RED);
        DrawRectangleLines(240,2051,1330,200, RED);
        DrawRectangleLines(1185,855,220,250, RED);
        DrawRectangleLines(660,640,500,100, RED);

        DrawRectangleLines(1274,640,370,200,RED);
        DrawRectangleLines(1464,735,180,350,RED);
        DrawRectangleLines(760, 1190,550,225,RED);
        DrawRectangleLines(1473,1200,200,225,RED);
        DrawRectangleLines(1695, 1530, 500, 460,RED);
        DrawRectangleLines(1260, 1496, 340, 190,RED);
        DrawRectangleLines(1733, 1115, 530, 240,RED);
        DrawRectangleLines(1918, 1080, 280, 40,RED);
        DrawRectangleLines(1722, 634, 500, 300,RED);
        DrawRectangleLines(1399, 56, 270, 270,RED);
        DrawRectangleLines(100, 70, 550, 280,RED);
        DrawRectangleLines(420,1190, 240, 215,RED);
        DrawRectangleLines(672, 740, 450, 260,RED);
        DrawRectangleLines(1338, 1825, 200, 170,RED);
        DrawRectangleLines(1335, 1820, 210, 180,GREEN);
        DrawRectangleLines(1395, 50, 280, 280,GREEN);
        DrawRectangleLines(1390,1670,80,30,GREEN);
        DrawRectangleLines(1940,914,150,30,GREEN);

        // If conversation is active, draw the appropriate image
        if (showConversation) {
            if (conversationStep == 0) {
                DrawTexture(conversationTexture1, conversationPosition.x+60, conversationPosition.y-50, WHITE);
            } else if (conversationStep == 1) {
                DrawTexture(conversationTexture2, conversationPosition.x+60, conversationPosition.y-50, WHITE);
            } else if (conversationStep == 2) {
                if (keyFound) {
                    DrawTexture(conversationTexture4, conversationPosition.x+60, conversationPosition.y-50, WHITE);
                } else {
                    DrawTexture(conversationTexture3, conversationPosition.x+60, conversationPosition.y-50, WHITE);
                }
            } else if (conversationStep == 3) {
                DrawTexture(conversationTexture4, conversationPosition.x+60, conversationPosition.y-50, WHITE);
            }
        }


        // Draw the key if it is visible and has not been found
        if (keyVisible && !keyFound) {
            DrawTexture(keyTexture, keyRect.x, keyRect.y, WHITE);
            DrawRectangleLines(keyRect.x, keyRect.y, 32, 32, RED); // Draw the key's collision rectangle
        }

        EndMode2D();

        if (showDebugInfo) {
            DrawText("IUT Chronicles - RPG", 10, 10, 20, BLACK);
            DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 16, BLACK);
            DrawText(TextFormat("Player position: (%.2f, %.2f)", player.position.x, player.position.y), GetScreenWidth() - 300, 10, 20, BLACK);
        }

        // Print the current state of showConversation and insideHospital at the top-right corner
        DrawText(TextFormat("Conversation: %s", showConversation ? "ON" : "OFF"), GetScreenWidth() - 200, 50, 20, BLACK);
        DrawText(TextFormat("Inside Hospital: %s", insideHospital ? "YES" : "NO"), GetScreenWidth() - 200, 80, 20, BLACK);
        DrawText(TextFormat("Inside CDS: %s", insideCDS ? "YES" : "NO"), GetScreenWidth() - 200, 110, 20, BLACK);
        DrawText(TextFormat("Inside Library: %s", insideLibrary ? "YES" : "NO"), GetScreenWidth() - 200, 140, 20, BLACK);
        DrawText(TextFormat("Inside Classroom: %s", insideClassroom ? "YES" : "NO"), GetScreenWidth() - 200, 170, 20, BLACK);

        
        // If Enter is pressed, switch to the next conversation step or hide the conversation
        if (showConversation && IsKeyPressed(KEY_ENTER)) {
            if (conversationStep == 0) {
                conversationStep = 1;
            } else if (conversationStep == 1) {
                showConversation = false;
                conversationStep = 2;
                keyVisible = true; // Make the key visible
            } else if (conversationStep == 2) {
                showConversation = false;
                conversationStep = 3;
            } else if (conversationStep == 3) {
                showConversation = false;
                conversationStep = 4;
            }
        }

        // If the key is found, hide it
        if(showMystery && IsKeyPressed(KEY_ENTER)){
            showMystery=false;
            showMystery2=true;
        }
        else if(showMystery2 && IsKeyPressed(KEY_ENTER)){
            showMystery2=false;
        }


        EndDrawing();
    }

    map.Unload();
    player.Unload();
    idle.Unload(); // Unload the idle character texture
    
    UnloadTexture(conversationTexture1); // Unload the first conversation texture
    UnloadTexture(conversationTexture2); // Unload the second conversation texture
    UnloadTexture(conversationTexture3); // Unload the third conversation texture
    UnloadTexture(conversationTexture4); // Unload the fourth conversation texture
    UnloadTexture(keyTexture); // Unload the key texture
    UnloadTexture(hospitalTexture); // Unload the hospital texture
    UnloadTexture(libraryTexture); // Unload the library texture
    UnloadTexture(cdsTexture); // Unload the CDS texture
    UnloadTexture(bookTexture); // Unload the book texture
    UnloadTexture(mysteryTexture); // Unload the mystery texture
    UnloadTexture(mysteryTexture2); // Unload the mystery2 texture
    UnloadTexture(classroomTexture); // Unload the classroom texture
    CloseWindow();
}
