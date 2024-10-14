#include "Game.hpp"
#include "Timer.hpp"
#include "Utils.hpp"
using namespace std;

//khởi tạo các thư viện cần thiết
bool initialize_the_necessary();

int main(int argc, char* args[])
{
	//khởi tạo seed cho việc lấy số ngẫu nhiên
    bbg::initRandomSeed();
	if( !initialize_the_necessary() )
	{
		cout << "Unable to initialize required libraries!\n";
		system("pause");
		return -1;
	}
	cout << "Hope you happy with my game!!!" << endl;

	//tạo cửa sổ và renderer
	Game game(bbg::TITLE, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT);
	//khởi tạo thông tin cho tank
	bbg::loadTankCollection();
	game.fill_renderer();

	//Show menu
	GameState currentState = MENU;
	game.showReplayMenu(currentState);
	//người chơi bấm nút Play thì bắt đầu game
	game.startGame();
	
	SDL_Event event;
	Timer stepTimer;
	while(game.isRunning())
	{
		while(SDL_PollEvent(&event) == 1)
		{
			game.handleEvents(event);
		}
		//Calculate delta time đơn vị giây (Frame-independent movement)
        float timeStep = stepTimer.getTicks() / 1000.f;
		game.update(timeStep);
		stepTimer.start();
		//RENDER MAP AND TANKS
		game.render();
		game.display();
	}
	game.destroyAll();
	bbg::deinitialize();
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