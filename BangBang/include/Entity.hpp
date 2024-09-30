#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
private:
	float x;
	float y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
};