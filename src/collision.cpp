#include "collision.h"
#include <iostream>
#include <cmath>

void ResolvePlayerBuildingCollision(Rectangle& destrect, const std::vector<Rectangle>& buildings) {
    for (const auto& building : buildings) {
        float overlapX = (destrect.x + destrect.width / 2) - (building.x + building.width / 2);
        float overlapY = (destrect.y + destrect.height / 2) - (building.y + building.height / 2);
        float halfWidthSum = (destrect.width + building.width) / 2;
        float halfHeightSum = (destrect.height + building.height) / 2;

        if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
            float penetrationX = halfWidthSum - fabs(overlapX);
            float penetrationY = halfHeightSum - fabs(overlapY);

            if (penetrationX < penetrationY) {
                if (overlapX > 0) {
                    destrect.x += penetrationX;
                } else {
                    destrect.x -= penetrationX;
                }
            } else {
                if (overlapY > 0) {
                    destrect.y += penetrationY;
                } else {
                    destrect.y -= penetrationY;
                }
            }
        }
    }
}

void ResolvePlayerIdleCollision(Rectangle& playerRect, const Rectangle& idleRect, Vector2& conversationPosition, bool& showConversation, int& conversationStep, bool& firstCollisionOccurred) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (idleRect.x + idleRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (idleRect.y + idleRect.height / 2);
    float halfWidthSum = (playerRect.width + idleRect.width) / 2;
    float halfHeightSum = (playerRect.height + idleRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        float penetrationX = halfWidthSum - fabs(overlapX);
        float penetrationY = halfHeightSum - fabs(overlapY);

        std::cout << "Collision with idle character detected!" << std::endl;

        if (penetrationX < penetrationY) {
            if (overlapX > 0) {
                playerRect.x += penetrationX;
            } else {
                playerRect.x -= penetrationX;
            }
        } else {
            if (overlapY > 0) {
                playerRect.y += penetrationY;
            } else {
                playerRect.y -= penetrationY;
            }
        }

        conversationPosition = {playerRect.x - 50, playerRect.y - 280};
        showConversation = true;

        if (!firstCollisionOccurred) {
            conversationStep = 0;
            firstCollisionOccurred = true;
        } else {
            conversationStep = 2;
        }
    }
}

void ResolvePlayerKeyCollision(Rectangle& playerRect, Rectangle& keyRect, bool& keyFound) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (keyRect.x + keyRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (keyRect.y + keyRect.height / 2);
    float halfWidthSum = (playerRect.width + keyRect.width) / 2;
    float halfHeightSum = (playerRect.height + keyRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with key detected!" << std::endl;
        keyFound = true;
    }
}



void ResolvePlayerBookCollision(Rectangle& playerRect, Rectangle& keyRect, bool& bookFound) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (keyRect.x + keyRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (keyRect.y + keyRect.height / 2);
    float halfWidthSum = (playerRect.width + keyRect.width) / 2;
    float halfHeightSum = (playerRect.height + keyRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with book detected!" << std::endl;
        bookFound = true;
    }
}

void ResolvePlayerUsbCollision(Rectangle& playerRect, Rectangle& usbRect, bool& usbFound, bool& showcipher) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (usbRect.x + usbRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (usbRect.y + usbRect.height / 2);
    float halfWidthSum = (playerRect.width + usbRect.width) / 2;
    float halfHeightSum = (playerRect.height + usbRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with usb detected!" << std::endl;
        usbFound = true;
        showcipher = true; // Show the cipher when the USB is found
    }
}

void ResolvePlayerHospitalCollision(Rectangle& playerRect, const Rectangle& hospitalRect, bool& insideHospital, bool& playerPositionUpdated) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (hospitalRect.x + hospitalRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (hospitalRect.y + hospitalRect.height / 2);
    float halfWidthSum = (playerRect.width + hospitalRect.width) / 2;
    float halfHeightSum = (playerRect.height + hospitalRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with hospital detected!" << std::endl;
        insideHospital = true;

        if (!playerPositionUpdated) {
            playerRect.x = 1259;
            playerRect.y = 56;
            playerPositionUpdated = true;
        }
    }
}

void ResolvePlayerHallCollision(Rectangle& playerRect, const Rectangle& hallRect, bool& insideHall, bool& playerPositionUpdated) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (hallRect.x + hallRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (hallRect.y + hallRect.height / 2);
    float halfWidthSum = (playerRect.width + hallRect.width) / 2;
    float halfHeightSum = (playerRect.height + hallRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with hall detected!" << std::endl;
        insideHall = true;

        if (!playerPositionUpdated) {
            playerRect.x = 1259;
            playerRect.y = 56;
            playerPositionUpdated = true;
        }
    }
}

void ResolvePlayerCDSCollision(Rectangle& playerRect, const Rectangle& cdsRect, bool& insideCDS, bool& playerPositionUpdated) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (cdsRect.x + cdsRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (cdsRect.y + cdsRect.height / 2);
    float halfWidthSum = (playerRect.width + cdsRect.width) / 2;
    float halfHeightSum = (playerRect.height + cdsRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with CDS detected!" << std::endl;
        insideCDS = true;

        if (!playerPositionUpdated) {
            playerRect.x = 1390;
            playerRect.y = 1685;
            playerPositionUpdated = true;
        }
    }
}

void ResolvePlayerLibraryCollision(Rectangle& playerRect, const Rectangle& libraryRect, bool& insideLibrary, bool& playerPositionUpdated) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (libraryRect.x + libraryRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (libraryRect.y + libraryRect.height / 2);
    float halfWidthSum = (playerRect.width + libraryRect.width) / 2;
    float halfHeightSum = (playerRect.height + libraryRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with library detected!" << std::endl;
        insideLibrary = true;

        if (!playerPositionUpdated) {
            playerRect.x = 1940;
            playerRect.y = 934;
            playerPositionUpdated = true;
        }
    }
}

void ResolvePlayerClassroomCollision(Rectangle& playerRect, const Rectangle& classroomRect, bool& insideClassroom, bool& playerPositionUpdated) {
    float overlapX = (playerRect.x + playerRect.width / 2) - (classroomRect.x + classroomRect.width / 2);
    float overlapY = (playerRect.y + playerRect.height / 2) - (classroomRect.y + classroomRect.height / 2);
    float halfWidthSum = (playerRect.width + classroomRect.width) / 2;
    float halfHeightSum = (playerRect.height + classroomRect.height) / 2;

    if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
        std::cout << "Collision with classroom detected!" << std::endl;
        insideClassroom = true;

        if (!playerPositionUpdated) {
            playerRect.x = 1940;
            playerRect.y = 1370;
            playerPositionUpdated = true;
        }
    }
}

void InsideHospital(Rectangle& playerRect, const std::vector<Rectangle>& hospitalCollisions) {
    for (const auto& rect : hospitalCollisions) {
        float overlapX = (playerRect.x + playerRect.width / 2) - (rect.x + rect.width / 2);
        float overlapY = (playerRect.y + playerRect.height / 2) - (rect.y + rect.height / 2);
        float halfWidthSum = (playerRect.width + rect.width) / 2;
        float halfHeightSum = (playerRect.height + rect.height) / 2;

        if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
            float penetrationX = halfWidthSum - fabs(overlapX);
            float penetrationY = halfHeightSum - fabs(overlapY);

            if (penetrationX < penetrationY) {
                if (overlapX > 0) {
                    playerRect.x += penetrationX;
                } else {
                    playerRect.x -= penetrationX;
                }
            } else {
                if (overlapY > 0) {
                    playerRect.y += penetrationY;
                } else {
                    playerRect.y -= penetrationY;
                }
            }
        }
    }
    if(playerRect.x>=1485) playerRect.x=1485;
    if(playerRect.x<=713) playerRect.x=713;
    if(playerRect.y>=990) playerRect.y=990;
}

void InsideLibrary(Rectangle& playerRect, const std::vector<Rectangle>& libraryCollisions) {
    for (const auto& rect : libraryCollisions) {
        float overlapX = (playerRect.x + playerRect.width / 2) - (rect.x + rect.width / 2);
        float overlapY = (playerRect.y + playerRect.height / 2) - (rect.y + rect.height / 2);
        float halfWidthSum = (playerRect.width + rect.width) / 2;
        float halfHeightSum = (playerRect.height + rect.height) / 2;

        if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
            float penetrationX = halfWidthSum - fabs(overlapX);
            float penetrationY = halfHeightSum - fabs(overlapY);

            if (penetrationX < penetrationY) {
                if (overlapX > 0) {
                    playerRect.x += penetrationX;
                } else {
                    playerRect.x -= penetrationX;
                }
            } else {
                if (overlapY > 0) {
                    playerRect.y += penetrationY;
                } else {
                    playerRect.y -= penetrationY;
                }
            }
        }
    }
}

void InsideClassroom(Rectangle& playerRect, const std::vector<Rectangle>& classroomCollisions) {
    for (const auto& rect : classroomCollisions) {
        float overlapX = (playerRect.x + playerRect.width / 2) - (rect.x + rect.width / 2);
        float overlapY = (playerRect.y + playerRect.height / 2) - (rect.y + rect.height / 2);
        float halfWidthSum = (playerRect.width + rect.width) / 2;
        float halfHeightSum = (playerRect.height + rect.height) / 2;

        if (fabs(overlapX) < halfWidthSum && fabs(overlapY) < halfHeightSum) {
            float penetrationX = halfWidthSum - fabs(overlapX);
            float penetrationY = halfHeightSum - fabs(overlapY);

            if (penetrationX < penetrationY) {
                if (overlapX > 0) {
                    playerRect.x += penetrationX;
                } else {
                    playerRect.x -= penetrationX;
                }
            } else {
                if (overlapY > 0) {
                    playerRect.y += penetrationY;
                } else {
                    playerRect.y -= penetrationY;
                }
            }
        }
    }
}
