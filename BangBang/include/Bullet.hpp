#pragma once
#include <stdio.h>
#include <cmath>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"

class Bullet
{
private:
    SDL_Texture* texture;	//hình ảnh của đạn
    bool active;	//kiểm soát việc ko thể xuất hiện nhiều hơn 1 viên đạn khi bắn, active = true tức là đạn đang tồn tại
    SDL_Rect rect;	//vị trí và kích thước
    int initPosX, initPosY;	//lưu vị trí ban đầu để tính toán đạn đã bay được bao xa
    float angle; //góc xoay theo hướng con trỏ chuột
    //bộ va chạm của đạn
    std::vector<SDL_Rect> colliders;

    void loadTexture(SDL_Renderer* renderer, std::string path);
    void shiftColliders();
public:
	//tạo bullet và gán width và height cho texture 
	Bullet(SDL_Renderer* renderer, std::string imagePath, std::vector<SDL_Rect> colliders);
	void fly(const int bulletSpeed, const int range, std::vector<SDL_Rect>& tankColliders, std::vector<SDL_Rect> mapColliders, float deltaTime);
	void clean();

	//getter
	SDL_Texture* getTexture();
	bool isActive();
	void setActive(bool flag);
	SDL_Rect getRect();
	void setRect(SDL_Rect rect);
	void setInitPos(int x, int y);
	//lấy width và height của đạn từ rect
	int getWidth();	
	int getHeight();

	float getAngle();
	void setAngle(float angle);
	std::vector<SDL_Rect>& getColliders();
};