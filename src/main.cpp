#include <raylib.h>
#include <vector>
#include <string>
#include <iostream>

// Screen dimensions
int screenWidth = 1000;
int screenHeight = 950;

// Sprite animation direction mapping
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

// Player class with sprite animations
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

    Player() {
        position = {100, 100};
        speed = 100.0f;
        currentDirection = DOWN;
        lastDirection = DOWN;
        isMoving = false;
        textureLoaded = false;

        frameCount = 3;
        currentFrame = 0;
        frameTime = 0.15f;
        timer = 0.0f;
        frameWidth = 32;
        frameHeight = 32;
        spriteRows = 6;
        spriteCols = 6;
    }

    void LoadTextures() {
        // Use an absolute path for debugging
        spriteSheet = LoadTexture("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/player.png");
        if (spriteSheet.id == 0) {
            TraceLog(LOG_ERROR, "Failed to load character sprite sheet!");
            textureLoaded = false;
        } else {
            textureLoaded = true;
            TraceLog(LOG_INFO, "Character sprite sheet loaded successfully");

            frameWidth = spriteSheet.width / spriteCols;
            frameHeight = spriteSheet.height / spriteRows;

            TraceLog(LOG_INFO, "Sprite sheet dimensions: %dx%d", spriteSheet.width, spriteSheet.height);
            TraceLog(LOG_INFO, "Frame dimensions: %dx%d", frameWidth, frameHeight);
        }
    }

    void UpdateDirection() {
        bool up = IsKeyDown(KEY_UP);
        bool down = IsKeyDown(KEY_DOWN);
        bool left = IsKeyDown(KEY_LEFT);
        bool right = IsKeyDown(KEY_RIGHT);

        isMoving = up || down || left || right;

        if (!isMoving) {
            return;
        }

        if (up && right) currentDirection = UP_RIGHT;
        else if (up && left) currentDirection = UP_LEFT;
        else if (down && right) currentDirection = DOWN_RIGHT;
        else if (down && left) currentDirection = DOWN_LEFT;
        else if (up) currentDirection = UP;
        else if (down) currentDirection = DOWN;
        else if (left) currentDirection = LEFT;
        else if (right) currentDirection = RIGHT;

        lastDirection = currentDirection;
    }

    void Move(float deltaTime) {
        Vector2 movement = {0, 0};

        if (IsKeyDown(KEY_RIGHT)) movement.x += 1;
        if (IsKeyDown(KEY_LEFT)) movement.x -= 1;
        if (IsKeyDown(KEY_UP)) movement.y -= 1;
        if (IsKeyDown(KEY_DOWN)) movement.y += 1;

        if (movement.x != 0 && movement.y != 0) {
            movement.x *= 0.7071f;
            movement.y *= 0.7071f;
        }

        position.x += movement.x * speed * deltaTime;
        position.y += movement.y * speed * deltaTime;

        if (position.x < 0) position.x = 0;
        if (position.x > screenWidth) position.x = screenWidth;
        if (position.y < 0) position.y = 0;
        if (position.y > screenHeight) position.y = screenHeight;

        UpdateDirection();

        if (isMoving) {
            timer += deltaTime;

            if (timer >= frameTime) {
                timer = 0.0f;
                currentFrame = (currentFrame + 1) % frameCount;
            }
        } else {
            currentFrame = 0;
        }
    }

    int GetDirectionRow() {
        switch (currentDirection) {
            case DOWN: return 0;
            case LEFT: return 1;
            case RIGHT: return 2;
            case UP: return 3;
            case DOWN_LEFT: return 4;
            case DOWN_RIGHT: return 5;
            case UP_LEFT: return 6;
            case UP_RIGHT: return 7;
            default: return 0;
        }
    }

    void Draw() {
        if (!textureLoaded) {
            DrawCircleV(position, 15, RED);
            return;
        }

        int row = GetDirectionRow();

        DrawText(TextFormat("Direction: %d, Frame: %d", row, currentFrame), 10, 70, 16, BLACK);

        Rectangle source = {
            (float)(currentFrame * frameWidth-10),
            (float)(row * frameHeight),
            (float)frameWidth,
            (float)frameHeight
        };

        Rectangle dest = {
            position.x - frameWidth,
            position.y - frameHeight,
            (float)frameWidth * 2,
            (float)frameHeight * 2
        };

        DrawTexturePro(
            spriteSheet,
            source,
            dest,
            {0, 0},
            0.0f,
            WHITE
        );

        DrawCircleV(position, 2, RED);
    }

    void Unload() {
        if (textureLoaded) {
            UnloadTexture(spriteSheet);
            textureLoaded = false;
        }
    }

    ~Player() {
        Unload();
    }
};

// Map class
class Map {
public:
    Texture2D background;
    bool textureLoaded;

    Map() {
        textureLoaded = false;
    }

    void Load(const char* filename) {
        background = LoadTexture(filename);
        if (background.id == 0) {
            TraceLog(LOG_ERROR, "Failed to load background image!");
            textureLoaded = false;
        } else {
            textureLoaded = true;
            TraceLog(LOG_INFO, "Map background loaded successfully");
        }
    }

    void Draw() {
        if (textureLoaded) {
            DrawTexturePro(background,
                           {0, 0, (float)background.width, (float)background.height},
                           {0, 0, (float)screenWidth, (float)screenHeight},
                           {0, 0}, 0, WHITE);
        } else {
            DrawRectangle(0, 0, screenWidth, screenHeight, LIGHTGRAY);
            DrawText("Map texture not loaded", screenWidth / 2 - 100, screenHeight / 2, 20, DARKGRAY);
        }
    }

    void Unload() {
        if (textureLoaded) {
            UnloadTexture(background);
            textureLoaded = false;
        }
    }

    ~Map() {
        Unload();
    }
};

// Game class
class Game {
public:
    Player player;
    Map map;
    bool initialized;
    bool showDebugInfo;

    Game() {
        initialized = false;
        showDebugInfo = true;
    }

    void Initialize() {
        SetTraceLogLevel(LOG_DEBUG);
        InitWindow(screenWidth, screenHeight, "IUT Chronicles");

        if (!IsWindowReady()) {
            std::cout << "Failed to initialize window!" << std::endl;
            return;
        }

        player.position = {(float)screenWidth / 2, (float)screenHeight / 2};

        player.LoadTextures();
        map.Load("C:/Users/Lihan/Desktop/Semester 2-1/Oop Lab/Project_Fall/Project_Fall/src/map.png");

        SetTargetFPS(60);
        initialized = true;
    }

    void Run() {
        Initialize();

        if (!initialized) {
            std::cout << "Game failed to initialize properly. Exiting." << std::endl;
            return;
        }

        while (!WindowShouldClose()) {
            if (IsKeyPressed(KEY_F1)) {
                showDebugInfo = !showDebugInfo;
            }

            float deltaTime = GetFrameTime();
            player.Move(deltaTime);

            BeginDrawing();
            ClearBackground(RAYWHITE);

            map.Draw();
            player.Draw();

            if (showDebugInfo) {
                DrawText("IUT Chronicles - RPG", 10, 10, 20, BLACK);
                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 16, BLACK);
                DrawText("Press F1 to toggle debug info", 10, screenHeight - 30, 16, BLACK);

                if (player.textureLoaded) {
                    DrawText("Sprite Sheet Grid:", screenWidth - 200, 10, 16, BLACK);

                    int gridX = screenWidth - 200;
                    int gridY = 30;
                    int gridScale = 2;

                    DrawTexturePro(
                        player.spriteSheet,
                        {0, 0, (float)player.spriteSheet.width, (float)player.spriteSheet.height},
                        {(float)gridX, (float)gridY,
                         (float)player.spriteSheet.width * gridScale,
                         (float)player.spriteSheet.height * gridScale},
                        {0, 0}, 0, WHITE
                    );

                    for (int i = 0; i <= player.spriteCols; i++) {
                        DrawLine(
                            gridX + i * player.frameWidth * gridScale,
                            gridY,
                            gridX + i * player.frameWidth * gridScale,
                            gridY + player.spriteSheet.height * gridScale,
                            RED
                        );
                    }

                    for (int i = 0; i <= player.spriteRows; i++) {
                        DrawLine(
                            gridX,
                            gridY + i * player.frameHeight * gridScale,
                            gridX + player.spriteSheet.width * gridScale,
                            gridY + i * player.frameHeight * gridScale,
                            RED
                        );
                    }

                    int currentRow = player.GetDirectionRow();
                    if (currentRow < player.spriteRows) {
                        DrawRectangleLines(
                            gridX + player.currentFrame * player.frameWidth * gridScale,
                            gridY + currentRow * player.frameHeight * gridScale,
                            player.frameWidth * gridScale,
                            player.frameHeight * gridScale,
                            GREEN
                        );
                    }
                }
            }

            EndDrawing();
        }

        map.Unload();
        player.Unload();
        CloseWindow();
    }
};

int main() {
    try {
        Game game;
        game.Run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
    }

    return 0;
}
