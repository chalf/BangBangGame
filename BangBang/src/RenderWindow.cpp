#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

using namespace std;

RenderWindow::RenderWindow()
{
	
}

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL)
{
	this->window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  p_w, p_h, SDL_WINDOW_SHOWN);
	if(this->window == NULL)
		cout << "Window failed to create. Error: " << SDL_GetError() << endl;
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->renderer == NULL)
		cout << "Renderer failed to create. Error: " << SDL_GetError() << endl;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(this->renderer, p_filePath);
	if(texture == NULL)
		cout << "Failed to load texture. Error: " << IMG_GetError() << endl;
	return texture;
}

void RenderWindow::render(SDL_Texture* p_tex, SDL_Rect* texture_rect, SDL_Rect* renderer_rect)
{
	SDL_RenderCopy(this->renderer, p_tex, texture_rect, renderer_rect);
}

void RenderWindow::set_renderer_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void RenderWindow::fill_renderer()
{
	SDL_RenderClear(this->renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(this->renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}