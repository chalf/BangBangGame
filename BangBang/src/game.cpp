
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

std::vector<Tank>& Game::getTankList()
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
    	//camera scrolling
    	int mapWidth = mapList.front().getWidth();
	    int mapHeight = mapList.front().getHeight();
	    camera = std::make_unique<Camera>(mapWidth, mapHeight, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT);
    	
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
	if (!camera) 
		return;
	//lấy viewport (nó có tọa độ của camera) hiện tại của camera
	SDL_Rect viewport = camera->getViewport();
	// Render map layers
    for (int layer = 0; layer < MAPLAYERS; ++layer) {
        SDL_Rect src = viewport;
        SDL_Rect dest = {0, 0, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT};
        // truyền src vô: chỉ phần map nằm trong viewport mới được render
        RenderWindow::render(mapList.front().getMapLayerArray()[layer], &src, &dest);
    }
	//map hoang da dai dia (60, 160) la ra khoi obstacle
	// Render tank, điều chỉnh vị trí của nó dựa trên viewport
	/*tức là posX - viewport.x = số px trục x từ cửa sổ đến tank, vì viewport.x có giá trị bằng từ cạnh trái của map đến viền trái của camera (tức là phần khuất bên trái của map khi render lên cửa sổ)*/
    SDL_Rect tankSize = {
        tankList.front().getPosX() - viewport.x,
        tankList.front().getPosY() - viewport.y,
        TANK_WIDTH,
        TANK_HEIGHT
    };
    RenderWindow::render(tankList.front().getTexInMatch(), NULL, &tankSize);
}

void Game::handleEvents(SDL_Event& event)
{
	if(event.type == SDL_QUIT)
	{
		running = false;
		return;
	}
	this->getTankList().front().handleTankMovement(event);
	

}

void Game::update()
{
	if (!camera) 
		return;
	Tank& tank = tankList.front();
	tank.move(mapList.front().getWidth(), mapList.front().getHeight());
        
    // Update camera position based on tank position: tâm điểm của tank
    camera->update(tank.getPosX() + TANK_WIDTH / 2, tank.getPosY() + TANK_HEIGHT / 2);
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

