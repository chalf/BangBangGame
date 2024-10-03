
#include "Game.hpp"
using namespace std;

Game::Game(const char* p_title, int p_w, int p_h) : RenderWindow( p_title, p_w, p_h )
{
	running = false;
	if(window != NULL && renderer != NULL)
		running = true;
}

Game::~Game()
{

}

std::vector<Map> Game::getMapList()
{
	return mapList;
}

std::vector<Tank> Game::getTankList()
{
	return tankList;
}

bool Game::loadMaps()
{
	Map hoang_da_dai_dia(1800, 1440);
	// load các layer của map
	if (!hoang_da_dai_dia.loadLayer(renderer, "res/gfx/HoangDaDaiDia_background.png", BACKGROUND) ||
        !hoang_da_dai_dia.loadLayer(renderer, "res/gfx/HoangDaDaiDia_floating.png", FLOATING) ||
        !hoang_da_dai_dia.loadLayer(renderer, "res/gfx/HoangDaDaiDia_obstacle.png", OBSTACLE))
    {
        return false;
    }
    else
    {
    	mapList.push_back(hoang_da_dai_dia);
		return true;
    }
}

bool Game::loadTanks()
{
	Tank pegasus(DPS, PHYSICAL);
	if( !pegasus.loadTextures(renderer, "res/gfx/pegasus.png") )
		return false;
	tankList.push_back(pegasus);
	return true;
}

void Game::render()
{
	//render map
	SDL_Rect mapScreen = {0, 0, this->getMapList().front().getWidth(), this->getMapList().front().getHeight()};
	RenderWindow::render(this->getMapList().front().getMapLayerArray()[BACKGROUND], NULL, &mapScreen);
	RenderWindow::render(this->getMapList().front().getMapLayerArray()[FLOATING], NULL, &mapScreen);
	RenderWindow::render(this->getMapList().front().getMapLayerArray()[OBSTACLE], NULL, &mapScreen);
	//map hoang da dai dia (60, 160) la ra khoi obstacle
	SDL_Rect tankSize = {65,165,TANK_WIDTH,TANK_HEIGHT};
	RenderWindow::render(this->getTankList().front().getTexInMatch(), NULL, &tankSize);
}

void Game::handleEvents(SDL_Event& event)
{
	if(event.type == SDL_QUIT)
	{
		running = false;
		return;
	}

}

void Game::destroyAll()
{
	for(long unsigned int mapIndx = 0; mapIndx < mapList.size(); mapIndx++)
	{
		mapList.at(mapIndx).clean();
	}
	for(long unsigned int tankIndx = 0; tankIndx < tankList.size(); tankIndx++)
	{
		tankList.at(tankIndx).clean();
	}
}

