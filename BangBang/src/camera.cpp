#include "Camera.hpp"

Camera::Camera(int mapWidth, int mapHeight, int screenWidth, int screenHeight)
: mapWidth(mapWidth), mapHeight(mapHeight), screenWidth(screenWidth), screenHeight(screenHeight) 
{
    x = 0;
    y = 0;
}

void Camera::update(int targetX, int targetY) {
    // Center the camera on the target (e.g., the tank)
    x = targetX - screenWidth / 2;
    y = targetY - screenHeight / 2;

    // Keep the camera within the map bounds
    x = std::max(0, std::min(x, mapWidth - screenWidth));
    y = std::max(0, std::min(y, mapHeight - screenHeight));
}

SDL_Rect Camera::getViewport() const 
{
    return {x, y, screenWidth, screenHeight};
}