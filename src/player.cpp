#include "player.h"
#include "bullet.h"
#include <algorithm>

Player::Player(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(5.0f), health(5), color(BLUE) {}

void Player::Update(const std::vector<Rectangle>& boundaries, std::vector<NPC>& npcs, const Gate& gate, bool& changeMap) {
    float newX = x;
    float newY = y;

    if (IsKeyDown(KEY_W)) {
        newY -= speed;
    }
    if (IsKeyDown(KEY_S)) {
        newY += speed;
    }
    if (IsKeyDown(KEY_A)) {
        newX -= speed;
    }
    if (IsKeyDown(KEY_D)) {
        newX += speed;
    }

    Rectangle newRect = {newX, newY, width, height};
    bool collision = false;
    for (const auto& boundary : boundaries) {
        if (CheckCollisionRecs(newRect, boundary)) {
            collision = true;
            break;
        }
    }

    for (auto& npc : npcs) {
        if (CheckCollisionRecs(newRect, npc.GetRect())) {
            collision = true;
            DecrementHealth();
            break;
        }
    }

    if (!collision) {
        x = newX;
        y = newY;
    }

    // Check for gate collision
    if (CheckCollisionRecs(GetRect(), gate.GetRect())) {
        changeMap = true;
    }

    // Update bullets
    for (auto& bullet : bullets) {
        bullet.Update();
    }

    // Remove bullets that are off-screen
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [screenHeight = GetScreenHeight()](const Bullet& bullet) {
        return bullet.IsOffScreen(screenHeight);
    }), bullets.end());

    // Check for bullet-NPC collisions
    for (auto& bullet : bullets) {
        for (auto it = npcs.begin(); it != npcs.end(); ) {
            if (CheckCollisionRecs(bullet.GetRect(), it->GetRect())) {
                it = npcs.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Shoot bullet
    if (IsKeyPressed(KEY_B)) {
        Shoot();
    }
}

void Player::Draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
    for (const auto& bullet : bullets) {
        bullet.Draw();
    }
}

void Player::AddItem(const Item& item) {
    inventory.push_back(item);
}

Rectangle Player::GetRect() const {
    return Rectangle{x, y, width, height};
}

float Player::GetX() const {
    return x;
}

float Player::GetY() const {
    return y;
}

void Player::DecrementHealth() {
    if (health > 0) {
        health--;
    }
}

int Player::GetHealth() const {
    return health;
}

void Player::Shoot() {
    bullets.emplace_back(x + width / 2 - 2.5f, y, 10.0f);
}