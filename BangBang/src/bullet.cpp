#include "Bullet.hpp"

Bullet::Bullet(int width, int height)
{
	m_BulletRect = {0, 0, width, height};
	m_bIsMove = false;
}

bool Bullet::loadTexture(SDL_Renderer* renderer, const char* filePath)
{
	return true;
}

void Bullet::handleEvent(SDL_Event& event)
{
	;
}

void Bullet::move()
{
	;
}

void Bullet::clean()
{
	SDL_DestroyTexture(m_pImage);
}

SDL_Texture* Bullet::getImage()
{
	return m_pImage;
}

SDL_Rect Bullet::getBulletRect()
{
	return m_BulletRect;
}

void Bullet::setBulletRect(SDL_Rect rect)
{
	m_BulletRect = rect;
}

void Bullet::setPos(int p_x, int p_y)
{
	m_BulletRect.x = p_x;
	m_BulletRect.y = p_y;
}