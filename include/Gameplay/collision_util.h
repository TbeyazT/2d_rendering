#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <glm/glm.hpp>

// Axis-Aligned Bounding Box collision detection
namespace CollisionUtils {

    // Check if two rectangles overlap using AABB
    bool checkAABBCollision(const glm::vec2& posA, const glm::vec2& sizeA, const glm::vec2& posB, const glm::vec2& sizeB) {
        // Check if the bounding boxes overlap
        bool collisionX = posA.x + sizeA.x > posB.x && posB.x + sizeB.x > posA.x;
        bool collisionY = posA.y + sizeA.y > posB.y && posB.y + sizeB.y > posA.y;
        return collisionX && collisionY;
    }

    // Check if the player is colliding with any walls in a grid-based system
    bool isCollidingWithWalls(const glm::vec2& playerPos, const glm::vec2& playerSize, const std::vector<std::vector<int>>& wallGrid, float tileSize) {
        int gridWidth = wallGrid.size();
        int gridHeight = wallGrid[0].size();

        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                if (wallGrid[i][j] == 1) {  // Check if it's a wall tile
                    glm::vec2 wallPos = glm::vec2(i * tileSize, j * tileSize);
                    glm::vec2 wallSize = glm::vec2(tileSize, tileSize);

                    if (checkAABBCollision(playerPos, playerSize, wallPos, wallSize)) {
                        return true;  // Collision detected
                    }
                }
            }
        }
        return false;
    }
}

#endif  // COLLISION_UTILS_H
