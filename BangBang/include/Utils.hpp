#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

//bbg = bang bang game
namespace bbg
{
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 740;
	extern const char* TITLE;

	//khởi tạo timer, audio, video (cho việc render)
	bool init_SDL();

	//khởi tạo SDL_image cho định dạng JPG
	bool init_SDL_image_JPG();

	//khởi tạo SDL_image cho định dạng PNG
	bool init_SDL_image_PNG();

	//khởi tạo SDL_mixer
	bool init_SDL_mixer();

	//khởi tạo SDL_ttf
	bool init_SDL_ttf();


}