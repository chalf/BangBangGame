#include <iostream>

#include "Game.hpp"
#include "Utils.hpp"
#include "Tank.hpp"
using namespace std;

//khởi tạo các thư viện cần thiết
bool initialize_the_necessary();
//hủy khởi tạo các thư viện, gọi hàm này ngay trước khi thoát khỏi main()
void deinitialize();

int main(int argc, char* args[])
{
    	
	if( !initialize_the_necessary() )
	{
		cout << "Unable to initialize required libraries!\n";
		system("pause");
		return -1;
	}
	cout << "Hope you happy with my game!!!" << endl;

	//tạo cửa sổ và renderer
	Game game(bbg::TITLE, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT);
	game.fill_renderer();
	if(game.loadMaps() == false)
		cout << "Failed to load maps: " << SDL_GetError() << endl;
	SDL_Rect renderScreen = {0, 0, game.getMapList().front().getWidth(), game.getMapList().front().getHeight()};
	game.render(game.getMapList().front().getMapLayerArray()[BACKGROUND], NULL, &renderScreen);
	game.render(game.getMapList().front().getMapLayerArray()[FLOATING], NULL, &renderScreen);
	game.render(game.getMapList().front().getMapLayerArray()[OBSTACLE], NULL, &renderScreen);

	if(game.loadTanks() == false)
		cout << "Failed to load tanks: " << SDL_GetError() << endl;
	SDL_Rect tankSize = {0,0,TANK_WIDTH,TANK_HEIGHT};
	game.render(game.getTankList().front().getTexInMatch(), NULL, &tankSize);

	game.display();
	SDL_Event event;

	while(game.isRunning())
	{
		while(SDL_PollEvent(&event) == 1)
		{
			if(event.type == SDL_QUIT)
				game.quitGame();
		}
		
	}
	game.destroyMap();
	// hủy window và renderer
	game.cleanUp();
	deinitialize();
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

void deinitialize()
{
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}