#pragma once

#include <SDL2/SDL.h>

const int BULLET_WIDTH = 50;
const int BULLET_HEIGHT = 20;

class Bullet
{
private:
	SDL_Texture* m_pImage;	//hình ảnh của đạn
	SDL_Rect m_BulletRect;	//kích thước và vị trí đạn
	bool m_bIsMove;

public:
	Bullet(int width, int height);	//tạo bullet với width và height của texture bullet
	bool loadTexture(SDL_Renderer* renderer, const char* filePath);
	void handleEvent(SDL_Event& event);
	void move();
	void clean();
	//getter
	SDL_Texture* getImage();
	SDL_Rect getBulletRect();
	void setBulletRect(SDL_Rect rect);
	void setPos(int p_x, int p_y);	//set vị trí của đạn vào m_BulletRect.x và m_BulletRect.y
};