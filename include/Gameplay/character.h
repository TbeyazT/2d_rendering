// File: src/character.h
#ifndef CHARACTER_H
#define CHARACTER_H
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include <Gameplay/math_utils.h>

class Character {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    float size;
    unsigned int textureID;

    Character(glm::vec2 pos, float s, const char* texturePath) : position(pos), size(s) {
        velocity = glm::vec2(0.0f, 0.0f);  // No initial movement
        textureID = MathUtils::loadTexture(texturePath);  // Load character texture
    }

    // Update character position based on velocity
    void update(float deltaTime) {
        position += velocity * deltaTime;
    }

    // Set character velocity
    void setVelocity(const glm::vec2& vel) {
        velocity = vel * 200.0f;  // Scale movement speed by 200 units
    }

    void moveUp() { velocity.y = 200.0f; }
    void moveDown() { velocity.y = -200.0f; }
    void moveLeft() { velocity.x = -200.0f; }
    void moveRight() { velocity.x = 200.0f; }

    void stopX() { velocity.x = 0.0f; }
    void stopY() { velocity.y = 0.0f; }

    // Bind the character texture before rendering
    void bindTexture() {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
};

#endif  // CHARACTER_H
