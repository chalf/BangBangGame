#include "Bullet.hpp"

void Bullet::loadTexture(SDL_Renderer* renderer, std::string path)
{
    this->texture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "At bullet.cpp: Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        this->texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( this->texture == NULL )
        {
            printf( "At bullet.cpp: Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            this->rect.w = loadedSurface->w;
            this->rect.h = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
}

void Bullet::shiftColliders()
{
    int r = 0;
    for (SDL_Rect& collider : colliders) {
        collider.x = rect.x + (rect.w - collider.w) / 2;
        collider.y = rect.y + r;
        r += collider.h;
    }
}

Bullet::Bullet(SDL_Renderer* renderer, std::string imagePath, std::vector<SDL_Rect> colliders)
{
    active = false;
    rect = {0, 0, 0, 0};
    loadTexture(renderer, imagePath);
    this->colliders = colliders;
}

void Bullet::fly(const int bulletSpeed, const int range, std::vector<SDL_Rect>& tankColliders, std::vector<SDL_Rect> mapColliders, float deltaTime)
{
    if(active == true)
    {
        float angleRad = angle * M_PI / 180.0f; //chuyển sang radian
        float dx = cos(angleRad) * bulletSpeed * deltaTime;
        float dy = sin(angleRad) * bulletSpeed * deltaTime;
        rect.x += dx;
        rect.y += dy;
        shiftColliders();
        if(bbg::checkCollision(this->colliders, tankColliders) || bbg::checkCollision(this->colliders, mapColliders) || bbg::distanceBetweenTwoPoint({initPosX, initPosY}, {rect.x, rect.y}) >= range*1.0)
        {
            active = false;
        }
    }
}

void Bullet::clean()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* Bullet::getTexture()
{
	return texture;
}

bool Bullet::isActive()
{
    return active;
}

void Bullet::setActive(bool flag)
{
    active = flag;
}

SDL_Rect Bullet::getRect()
{
    return rect;
}

void Bullet::setRect(SDL_Rect rect)
{
    this->rect = rect;
}

void Bullet::setInitPos(int x, int y)
{
    initPosX = x;
    initPosY = y;
}

int Bullet::getWidth()
{
    return rect.w;
}

int Bullet::getHeight()
{
    return rect.h;
}

float Bullet::getAngle()
{
    return angle;
}

void Bullet::setAngle(float angle)
{
    this->angle = angle;
}

std::vector<SDL_Rect>& Bullet::getColliders()
{
    return colliders;
}