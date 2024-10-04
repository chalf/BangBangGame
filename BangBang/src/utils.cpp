#include "Utils.hpp"

const char* bbg::TITLE = "BangBang v1.0";

bool bbg::init_SDL()
{
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	return true;
}

//khởi tạo SDL_image cho định dạng JPG
bool bbg::init_SDL_image_JPG()
{
	if( IMG_Init( IMG_INIT_JPG ) == 0 )
	{
		return false;
	}
	return true;
}

//khởi tạo SDL_image cho định dạng PNG
bool bbg::init_SDL_image_PNG()
{
	if( IMG_Init(IMG_INIT_PNG) == 0 )
		return false;

	return true;
}

//khởi tạo SDL_mixer
bool bbg::init_SDL_mixer()
{
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) == -1 )
		return false;
	return true;
}

//khởi tạo SDL_ttf
bool bbg::init_SDL_ttf()
{
	if( TTF_Init() == -1)
		return false;
	return true;
}