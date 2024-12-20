#include "Map.hpp"

Map::Map()
{}

Map::Map(int w, int h, GAMEMOD gameMod, std::vector<SDL_Rect> mapCollider, std::vector<SDL_Point> sp)
{
    MAP_WIDTH = w;
    MAP_HEIGHT = h;
    this->gameMod = gameMod;
    mColliders = mapCollider;
    spawnPoints = sp;
}

Map::~Map() {}

SDL_Texture** Map::getMapLayerArray()
{
	return map;
}

int Map::getWidth()
{
    return MAP_WIDTH;
}

int Map::getHeight()
{
    return MAP_HEIGHT;
}

GAMEMOD Map::getGameMod()
{
    return gameMod;
}

std::vector<SDL_Rect> Map::getColliders()
{
    return mColliders;
}

std::vector<SDL_Point> Map::getSpawnPoints()
{
    return spawnPoints;
}

bool Map::loadLayer(SDL_Renderer* renderer, const char* filePath, MapLayer layer)
{
    SDL_Surface* surface = IMG_Load(filePath); // Load file ảnh
    if (surface == NULL)
    {
        std::cout << "Unable to load image (map.cpp): " << IMG_GetError() << std::endl;
        return false;
    }
    map[layer] = SDL_CreateTextureFromSurface(renderer, surface); // Chuyển surface thành texture
    SDL_FreeSurface(surface); // Giải phóng surface
    if (map[layer] == NULL)
    {
        std::cout << "Unable to create texture (map.cpp): " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}


void Map::clean()
{
	for(int i = 0; i < MAPLAYERS; i++)
		SDL_DestroyTexture(map[i]);
}