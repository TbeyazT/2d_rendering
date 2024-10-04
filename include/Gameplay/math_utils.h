#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Utility functions for general math
namespace MathUtils {

    // Linear interpolation
    template<typename T>
    T lerp(const T& a, const T& b, float t) {
        return a + t * (b - a);
    }

    // Clamp a value between a minimum and maximum
    template<typename T>
    T clamp(const T& value, const T& min, const T& max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    unsigned int loadTexture(const char* path) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load image using stb_image
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << stbi_failure_reason() << path << std::endl;
        }
        stbi_image_free(data);
        return texture;
    }

    // Utility functions for glm vectors
    namespace VectorUtils {

        // Get the magnitude (length) of a vector
        float magnitude(const glm::vec2& vec) {
            return glm::length(vec);
        }

        // Normalize a vector
        glm::vec2 normalize(const glm::vec2& vec) {
            return glm::normalize(vec);
        }

        // Calculate the distance between two vectors
        float distance(const glm::vec2& a, const glm::vec2& b) {
            return glm::length(b - a);
        }

        // Lerp between two vectors
        glm::vec2 lerp(const glm::vec2& a, const glm::vec2& b, float t) {
            return MathUtils::lerp(a, b, t);
        }

        // Apply a zoom transformation to a 2D vector
        glm::vec2 applyZoom(const glm::vec2& point, float zoomFactor) {
            return point * zoomFactor;
        }

        // Rotate a 2D vector by a given angle (in radians)
        glm::vec2 rotate(const glm::vec2& point, float angle) {
            float cosTheta = cos(angle);
            float sinTheta = sin(angle);
            return glm::vec2(
                cosTheta * point.x - sinTheta * point.y,
                sinTheta * point.x + cosTheta * point.y
            );
        }
    }

    // Utility functions for transformation matrices
    namespace MatrixUtils {
        
        // Generate a zoom matrix for 2D transformation
        glm::mat4 getZoomMatrix(float zoomFactor) {
            return glm::scale(glm::mat4(1.0f), glm::vec3(zoomFactor, zoomFactor, 1.0f));
        }

        // Generate a rotation matrix for 2D transformation
        glm::mat4 getRotationMatrix(float angle) {
            return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    }
}

#endif  // MATH_UTILS_H
