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

Bullet::Bullet(SDL_Renderer* renderer, std::string imagePath)
{
    active = false;
    rect = {0, 0, 0, 0};
    loadTexture(renderer, imagePath);
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

int Bullet::getWidth()
{
    return rect.w;
}

int Bullet::getHeight()
{
    return rect.h;
}