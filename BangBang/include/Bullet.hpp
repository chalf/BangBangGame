#pragma once
#include <stdio.h>
#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bullet
{
private:
    SDL_Texture* texture;	//hình ảnh của đạn
    bool active;	//kiểm soát việc ko thể xuất hiện nhiều hơn 1 viên đạn khi bắn, active = true tức là đạn đang tồn tại
    SDL_Rect rect;	//vị trí và kích thước

    void loadTexture(SDL_Renderer* renderer, std::string path);
public:
	//tạo bullet với width và height của texture bullet
	Bullet(SDL_Renderer* renderer, std::string imagePath);
	void clean();
	//getter
	SDL_Texture* getTexture();
	bool isActive();
	void setActive(bool flag);
	SDL_Rect getRect();
	void setRect(SDL_Rect rect);
	//lấy width và height của đạn từ rect
	int getWidth();	
	int getHeight();
};