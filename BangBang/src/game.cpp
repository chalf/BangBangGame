
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

void Game::quitGame()
{
	running = false;
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

void Game::destroyMap()
{
	for(long unsigned int i = 0; i < mapList.size(); i++)
	{
		mapList.at(i).clean();
	}
}