#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow
{
public:
	RenderWindow();
	RenderWindow(const char* p_title, int p_w, int p_h);
	virtual ~RenderWindow() {};
	SDL_Renderer* getRenderer();

	SDL_Texture* loadTexture(const char* p_filePath);
	void render(SDL_Texture* p_tex, SDL_Rect* texture_rect, SDL_Rect* renderer_rect);
	void renderEx(SDL_Texture * p_tex,
               const SDL_Rect * texture_rect,
               const SDL_Rect * renderer_rect,
               const double angle,
               const SDL_Point *center,
               const SDL_RendererFlip flip = SDL_FLIP_NONE
	);
	void set_renderer_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void fill_renderer();
	void display();
	void cleanUp();
	int getRefreshRate();
protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
