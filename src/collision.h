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
void ResolvePlayerClassroomCollision(Rectangle& playerRect, const Rectangle& libraryRect, bool& insideLibrary, bool& playerPositionUpdated);
void InsideHospital(Rectangle& playerRect, const std::vector<Rectangle>& hospitalCollisions);
void InsideLibrary(Rectangle& playerRect, const std::vector<Rectangle>& libraryCollisions);
void InsideClassroom(Rectangle& playerRect, const std::vector<Rectangle>& classroomCollisions);
void ResolvePlayerBookCollision(Rectangle& playerRect, Rectangle& bookRect, bool& bookFound);
void ResolvePlayerUsbCollision(Rectangle& playerRect, Rectangle& usbRect, bool& usbFound, bool& showcipher);
void ResolvePlayerHallCollision(Rectangle& playerRect, const Rectangle& hallRect, bool& insideHall, bool& playerPositionUpdated);


#endif // COLLISION_H
