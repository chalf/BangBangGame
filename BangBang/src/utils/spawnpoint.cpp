#include "Utils.hpp"

vector<SDL_Point> spawnpoint::hoangDaDaiDiaSpawnPoint()
{
	vector<SDL_Point> spVector = {
		//bên trái
		{65, 162},
        {65, 162 + TANK_HEIGHT},
        {65 + TANK_WIDTH, 162},
        //bên phải
        {1650, 1270},
        {1650, 1270 - TANK_HEIGHT},
        {1650 - TANK_WIDTH, 1270}
	};
	return spVector;
}