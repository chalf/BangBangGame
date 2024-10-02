#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

enum MapLayer
{
	BACKGROUND, //phần nền dưới cùng
	OBSTACLE, 	//chướng ngại vật
	FLOATING	//phần nổi ở trên tank khi đi qua nó
};

const int MAPLAYERS = 3;

class Map
{
private:
	//phần tử 0 là background, 1 là chướng ngại vật, 2 là phần nổi
	SDL_Texture* map[MAPLAYERS];
	// các map có kích thước khác nhau: map vuông hoặc hcn
	int MAP_WIDTH, MAP_HEIGHT;
public:
	Map();
	Map(int w, int h);
	//getter
	SDL_Texture** getMapLayerArray();
	int getWidth();
	int getHeight();

	// load hình ảnh của map cho từng layer
	bool loadLayer(SDL_Renderer* renderer, const char* filePath, MapLayer layer);
	//Hủy các texture của map để giải phóng vùng nhớ
	void clean();
	
};