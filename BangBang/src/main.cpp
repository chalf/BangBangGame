#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Utils.hpp"
using namespace std;

bool initialize_the_necessary();

int main(int argc, char* args[])
{
    	
	if( !initialize_the_necessary() )
	{
		cout << "Unable to initialize required libraries!\n";
		system("pause");
		return -1;
	}
	printf("%s\n", "Hello World!!!");

	RenderWindow window(bbg::TITLE, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT);
	window.set_renderer_color(201, 177, 121, 255);
	window.fill_renderer();

	SDL_Texture* map = window.loadTexture("res/gfx/HoangDaDaiDia_background.png");
	SDL_Rect r1 = {0,0,1800,1440};
	window.render(map, NULL, &r1);
	SDL_Texture* pegasus = window.loadTexture("res/gfx/pegasus_none.png");
	bool gameRunning = true;
	SDL_Event event;
	while(gameRunning)
	{
		Uint32 startTick = SDL_GetTicks();
		while(SDL_PollEvent(&event) == 1)
		{
			if(event.type == SDL_QUIT)
				gameRunning = false;
		}
		
		SDL_Rect r = {20, 50, bbg::TANK_WIDTH, bbg::TANK_HEIGHT};
		window.render(pegasus, NULL, &r);

		/* kiểm tra thời gian từ khi chạy chương trình có nhỏ hơn 1000 ms (1 giây) / Tần số của màn hình (60 frame / 1 giây). 
		VD: tần số quét của màn hình là 60Hz - trong 1 giây màn hình làm mới hình ảnh 60 lần. 1 s = 1000 ms
		=> trong 1000 ms làm mới hình ảnh 60 lần, vậy khoảng thời gian giữa các lần làm mới là 1000/60
		 */
		Uint32 frameTicks = SDL_GetTicks() - startTick;
		if(frameTicks < (Uint32) 1000 / window.getRefreshRate())
		{
			//nếu thời gian làm mới nhỏ hơn 1000/60 -> fps cao hơn 60, chạy chậm lại một xíu bằng SDL_Delay()
			/* việc đảm bảo rằng các khung hình được hiển thị với tốc độ phù hợp là rất quan trọng. 
			Nếu khung hình được hiển thị quá nhanh, một số phần của hình ảnh có thể chưa được cập nhật, 
			dẫn đến hiện tượng xé hình (screen tearing). Ngược lại, nếu khung hình được hiển thị quá chậm, 
			hình ảnh sẽ bị giật cục và không mượt mà.*/
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
		window.display();

	}
	window.cleanUp();
	SDL_Quit();
	//system("pause"); // stop console from exiting immediately for Windows; or cin.get(); for all.
	
	return 0;
}

bool initialize_the_necessary()
{
	bool success = true;
	if( !bbg::init_SDL() )
	{
		cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
		success = false;
	}

	if ( !bbg::init_SDL_image_JPG() )
	{
	    cout << "Failed to initialize SDL_image for JPG format: " << IMG_GetError() << endl;
	    success = false;
	}

	if( !bbg::init_SDL_image_PNG() )
	{
		cout << "Failed to initialize SDL_image for PNG format: " << IMG_GetError() << endl;
	    success = false;
	}

	if( !bbg::init_SDL_mixer() )
	{
		cout<< "Failed to init SDL_mixer: " <<  Mix_GetError() << endl;
		success = false;
	}

	if( !bbg::init_SDL_ttf() )
	{
		cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << endl;
		success = false;
	}

	return success;
}