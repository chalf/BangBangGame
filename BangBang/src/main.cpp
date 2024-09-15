#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RenderWindow.hpp"
using namespace std;

int main(int argc, char* args[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)	//SDL_Init = 0 is okay
		cout << "Something went wrong: " << SDL_GetError() << endl;
	
	// if(!IMG_Init(IMG_INIT_WEBP))	//IMG_Init = true if okay
	// 	cout << "IMG_init has error: " << SDL_GetError() << endl;

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG ) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
	    cout << "Failed to initialize SDL_image: " << IMG_GetError() << endl;
	}


	RenderWindow window("BangBang v1.0", 1280, 720);
	SDL_Texture* backgroundTexture01 = window.loadTexture("res/gfx/background01.png");
	bool gameRunning = true;
	SDL_Event event;
	while(gameRunning)
	{
		while(SDL_PollEvent(&event) == 1)
		{
			if(event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.clear();
		window.render(backgroundTexture01);
		window.display();

	}

	window.cleanUp();
	SDL_Quit();
	//system("pause"); // stop console from exiting immediately for Windows; or cin.get(); for all.
	
	return 0;
}