#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Camera {
private:
    int x, y;
    int mapWidth, mapHeight;
    int screenWidth, screenHeight;
public:
    Camera(int mapWidth, int mapHeight, int screenWidth, int screenHeight);
    //Cập nhật vị trí camera dựa trên vị trí mới của tank
    void update(int targetX, int targetY);
    // const tức là method này không thay đổi bất kì thuộc tính nào của đối tượng gọi method (this)
    SDL_Rect getViewport() const; //trả về {vị trí x, y, dài, rộng cửa sổ (màn hình)}

};