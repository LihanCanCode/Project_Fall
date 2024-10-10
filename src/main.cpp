#include <raylib.h>
#include "player.h"
#include "npc.h"
#include "item.h"
#include "map.h"
#include "gate.h"
#include <vector>

void LoadMap1(Player& player, std::vector<NPC>& npcs, std::vector<Item>& items, std::vector<Rectangle>& boundaries, Gate& gate) {
    player = Player(100, 100, 20, 20);
    npcs = { NPC(300, 300, 20, 20) };
    items = { 
        Item(200, 200, 10, 10), 
        Item(400, 400, 10, 10), 
        Item(600, 100, 10, 10), 
        Item(100, 500, 10, 10), 
        Item(700, 200, 10, 10) 
    };
    boundaries = {
        {50, 50, 100, 20},
        {200, 150, 20, 100},
        {400, 300, 100, 20},
        {600, 450, 20, 100}
    };
    gate = Gate(750, 550, 50, 50); // Position the gate
}

void LoadMap2(Player& player, std::vector<NPC>& npcs, std::vector<Item>& items, std::vector<Rectangle>& boundaries, Gate& gate) {
    player = Player(50, 100, 20, 20);
    npcs = { NPC(200, 200, 20, 20), NPC(500, 500, 20, 20) };
    items = { 
        Item(300, 300, 10, 10), 
        Item(500, 100, 10, 10), 
        Item(700, 400, 10, 10) 
    };
    boundaries = {
        {100, 100, 100, 20},
        {300, 200, 20, 100},
        {500, 300, 100, 20},
        {700, 400, 20, 100}
    };
    gate = Gate(750, 550, 50, 50); // Position the gate
}

int main() 
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Adventure Game");
    SetTargetFPS(60);
    
    Player player(100, 100, 20, 20);
    std::vector<NPC> npcs;
    std::vector<Item> items;
    std::vector<Rectangle> boundaries;
    Gate gate(750, 550, 50, 50);
    bool changeMap = false;
    bool map1Loaded = true;

    LoadMap1(player, npcs, items, boundaries, gate);
    
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.GetX() + player.GetRect().width / 2, player.GetY() + player.GetRect().height / 2 };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    while (!WindowShouldClose())
    {
        if (changeMap) {
            if (map1Loaded) {
                LoadMap2(player, npcs, items, boundaries, gate);
            } else {
                LoadMap1(player, npcs, items, boundaries, gate);
            }
            map1Loaded = !map1Loaded;
            changeMap = false;
        }

        player.Update(boundaries, npcs, gate, changeMap);
        
        for (auto& npc : npcs) {
            npc.Update();
        }
        
        int collectedItems = 0;
        for (auto& item : items) {
            if (item.CheckCollision(player)) {
                player.AddItem(item);
                item.PickUp();
            }
            if (item.IsPickedUp()) {
                collectedItems++;
            }
        }
        
        if (collectedItems == items.size()) {
            // Game finished logic here
        }
        
        if (player.GetHealth() <= 0) {
            // Game over logic here
        }

        // Update camera to follow player
        camera.target = (Vector2){ player.GetX() + player.GetRect().width / 2, player.GetY() + player.GetRect().height / 2 };
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);
                player.Draw();
                for (const auto& npc : npcs) {
                    npc.Draw();
                }
                for (const auto& item : items) {
                    if (!item.IsPickedUp()) {
                        item.Draw();
                    }
                }
                for (const auto& boundary : boundaries) {
                    DrawRectangleRec(boundary, RED);
                }
                gate.Draw();
            EndMode2D();
            
            // Draw player's health
            DrawText(TextFormat("Health: %d", player.GetHealth()), 10, 30, 20, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}