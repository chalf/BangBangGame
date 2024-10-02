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
	const char* TITLE = "BangBang v1.0";

	//khởi tạo timer, audio, video (cho việc render)
	bool init_SDL()
	{
		if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
		{
			return false;
		}
		return true;
	}

	//khởi tạo SDL_image cho định dạng JPG
	bool init_SDL_image_JPG()
	{
		if( IMG_Init( IMG_INIT_JPG ) == 0 )
		{
			return false;
		}
		return true;
	}

	//khởi tạo SDL_image cho định dạng PNG
	bool init_SDL_image_PNG()
	{
		if( IMG_Init(IMG_INIT_PNG) == 0 )
			return false;

		return true;
	}

	//khởi tạo SDL_mixer
	bool init_SDL_mixer()
	{
		if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) == -1 )
			return false;
		return true;
	}

	//khởi tạo SDL_ttf
	bool init_SDL_ttf()
	{
		if( TTF_Init() == -1)
			return false;
		return true;
	}


}