#ifndef EDITOR_H
#define EDITOR_H

#include <glm/glm.hpp>
#include <vector>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <Gameplay/math_utils.h>

// Enum for editor modes
enum class EditorMode { EDIT, PLAY };

// Tile Type Enum
enum class TileType { EMPTY, WALL };

class Editor {
public:
    EditorMode currentMode;  // Track the current mode (EDIT or PLAY)
    glm::vec2 cursorPosition;  // Track the mouse position
    std::vector<std::vector<TileType>> tileMap;  // 2D grid for wall tiles
    int gridWidth, gridHeight;  // Dimensions of the grid
    float tileSize;  // Size of each tile in pixels

    GLuint wallTexture;  // Texture ID for the wall image

    Editor(int width, int height, float tileSize) 
        : gridWidth(width), gridHeight(height), tileSize(tileSize), currentMode(EditorMode::EDIT) {
            tileMap.resize(gridWidth, std::vector<TileType>(gridHeight, TileType::EMPTY));
            MathUtils::loadTexture("images/wall.jpg");
    }

    // Render the editor grid and tools
    void renderGrid() {
        glColor3f(0.8f, 0.8f, 0.8f);
        glBegin(GL_LINES);
        for (int i = 0; i <= gridWidth; ++i) {
            glVertex2f(i * tileSize, 0);
            glVertex2f(i * tileSize, gridHeight * tileSize);
        }
        for (int j = 0; j <= gridHeight; ++j) {
            glVertex2f(0, j * tileSize);
            glVertex2f(gridWidth * tileSize, j * tileSize);
        }
        glEnd();
    }

    // Render the wall tiles with the loaded texture
    void renderTiles() {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glColor3f(1.0f, 1.0f, 1.0f);  // Ensure the color is white for proper texturing

        glBegin(GL_QUADS);
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                if (tileMap[i][j] == TileType::WALL) {
                    float x = i * tileSize;
                    float y = j * tileSize;

                    // Define the textured quad for the wall
                    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
                    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + tileSize, y);
                    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + tileSize, y + tileSize);
                    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + tileSize);
                }
            }
        }
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    // Place a wall at the given position
    void placeWall(float x, float y) {
        int gridX = static_cast<int>(x / tileSize);
        int gridY = static_cast<int>(y / tileSize);

        if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight) {
            tileMap[gridX][gridY] = TileType::WALL;  // Mark the tile as a wall
        }
    }

    // Remove a wall at the given position
    void removeWall(float x, float y) {
        int gridX = static_cast<int>(x / tileSize);
        int gridY = static_cast<int>(y / tileSize);

        if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight) {
            tileMap[gridX][gridY] = TileType::EMPTY;  // Mark the tile as empty
        }
    }

    // Save the current tile map to a file
    void saveToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Failed to open file for saving: " << filename << std::endl;
            return;
        }

        outFile << gridWidth << " " << gridHeight << "\n";
        for (int j = 0; j < gridHeight; ++j) {
            for (int i = 0; i < gridWidth; ++i) {
                outFile << static_cast<int>(tileMap[i][j]) << " ";
            }
            outFile << "\n";
        }

        outFile.close();
        std::cout << "Saved tile map to " << filename << std::endl;
    }

    // Load the tile map from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Failed to open file for loading: " << filename << std::endl;
            return;
        }

        int width, height;
        inFile >> width >> height;

        if (width != gridWidth || height != gridHeight) {
            std::cerr << "Loaded map dimensions do not match editor dimensions." << std::endl;
            inFile.close();
            return;
        }

        for (int j = 0; j < gridHeight; ++j) {
            for (int i = 0; i < gridWidth; ++i) {
                int tileType;
                inFile >> tileType;
                tileMap[i][j] = static_cast<TileType>(tileType);
            }
        }

        inFile.close();
        std::cout << "Loaded tile map from " << filename << std::endl;
    }
};

#endif  // EDITOR_H
