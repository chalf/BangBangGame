#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
using namespace std;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL)
{
	this->window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  p_w, p_h, SDL_WINDOW_SHOWN);
	if(this->window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(this->renderer, p_filePath);
	if(texture == NULL)
		cout << "Failed to load texture. Error: " << IMG_GetError() << endl;
	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

void RenderWindow::clear()
{
	SDL_RenderClear(this->renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
	SDL_RenderCopy(this->renderer, p_tex, NULL, NULL);
}

void RenderWindow::display()
{
	SDL_RenderPresent(this->renderer);
}