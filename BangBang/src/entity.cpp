#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Entity.hpp"
using namespace std;

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
: x(p_x), y(p_y), tex(p_tex)
{
	this->currentFrame.x = 0;
	this->currentFrame.y = 0;
	this->currentFrame.w = 1096; // chiều dài và rộng của background image
	this->currentFrame.h = 708;
}