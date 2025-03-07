#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"
#include <vector>

void ResolvePlayerBuildingCollision(Rectangle& destrect, const std::vector<Rectangle>& buildings);
void ResolvePlayerIdleCollision(Rectangle& playerRect, const Rectangle& idleRect, Vector2& conversationPosition, bool& showConversation, int& conversationStep, bool& firstCollisionOccurred);
void ResolvePlayerKeyCollision(Rectangle& playerRect, Rectangle& keyRect, bool& keyFound);
void ResolvePlayerHospitalCollision(Rectangle& playerRect, const Rectangle& hospitalRect, bool& insideHospital, bool& playerPositionUpdated);
void ResolvePlayerCDSCollision(Rectangle& playerRect, const Rectangle& cdsRect, bool& insideCDS, bool& playerPositionUpdated);
void ResolvePlayerLibraryCollision(Rectangle& playerRect, const Rectangle& libraryRect, bool& insideLibrary, bool& playerPositionUpdated);
void InsideHospital(Rectangle& playerRect, const std::vector<Rectangle>& hospitalCollisions);
void ResolvePlayerBookCollision(Rectangle& playerRect, Rectangle& bookRect, bool& bookFound);

#endif // COLLISION_H
