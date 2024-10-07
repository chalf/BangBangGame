#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

using namespace std;

//bbg = bang bang game
namespace bbg
{
	// width, height của cửa sổ
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

	//phát hiện va chạm
	bool checkCollision(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b);

	//hủy khởi tạo các thư viện, gọi hàm này ngay trước khi thoát khỏi main()
	void deinitialize();

}

namespace colliders
{
	//bộ collider của tank
	vector<SDL_Rect> pegasusColliders();

	//bộ collider của map
	vector<SDL_Rect> hoangDaDaiDiaColliders();
}