#pragma once

#include "Tank.hpp"

class PlayerTank : public Tank
{
public:
	//x và y là vị trí ban đầu của tank
	PlayerTank(string name, Strength strength, TankType type, Specification spec, int x, int y, vector<SDL_Rect> tankCollider);

    //xoay theo con trỏ chuột
    void rotateHead(int mouseX, int mouseY) override;

    //xử lý sự kiện di chuyển cho tank
    void handleTankMovement(SDL_Event& event) override;
    void move(int mapWidth, int mapHeight, vector<Tank*> tanks, vector<SDL_Rect> mapColliders, float deltaTime) override;
    //xử lý sự kiện bắn đạn
    void handleBulletShooting(SDL_Event& event) override;
};

