#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "math_utils.h"

class Camera {
public:
    glm::vec2 position;  // Camera position
    float viewportWidth;  // Viewport width
    float viewportHeight; // Viewport height
    float zoomLevel;      // Zoom level

    Camera(float width, float height) 
        : viewportWidth(width), viewportHeight(height), position(0.0f, 0.0f), zoomLevel(1.0f){}

    glm::mat4 getViewMatrix() {
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
        return view;
    }

    // Returns the projection matrix for 2D orthographic view
    glm::mat4 getProjectionMatrix() {
        glm::mat4 projection = glm::ortho(0.0f, viewportWidth, 0.0f, viewportHeight, -1.0f, 1.0f);
        return MathUtils::MatrixUtils::getZoomMatrix(zoomLevel) * projection;  // Apply zoom
    }

    // Update camera position to follow the target smoothly using lerp
    void lerpFollow(const glm::vec2& target, float lerpFactor = 0.1f) {
        glm::vec2 targetPosition = target - glm::vec2(viewportWidth / 2.0f, viewportHeight / 2.0f);
        position = MathUtils::VectorUtils::lerp(position, targetPosition, lerpFactor);
    }

    // Set zoom level
    void setZoom(float zoom) {
        zoomLevel = MathUtils::clamp(zoom, 0.1f, 10.0f);  // Clamp zoom level to prevent extreme values
    }
};

#endif  // CAMERA_H
