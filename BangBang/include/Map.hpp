#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

enum MapLayer
{
	BACKGROUND, //phần nền dưới cùng
	OBSTACLE, 	//chướng ngại vật
	FLOATING	//phần nổi ở trên tank khi đi qua nó
};

enum GAMEMOD
{
	SCORE,				//map tính điểm
	BASE_DESTRUCTION	//map phá căn cứ
};

const int MAPLAYERS = 3;

class Map
{
protected:
	//phần tử 0 là background, 1 là chướng ngại vật, 2 là phần nổi
	SDL_Texture* map[MAPLAYERS];
	// các map có kích thước khác nhau: map vuông hoặc hcn
	int MAP_WIDTH, MAP_HEIGHT;
	//chế độ chơi của map
	GAMEMOD gameMod;
	//Collider của map (cụ thể là lớp OBSTACLE)
	std::vector<SDL_Rect> mColliders;
	//điểm spawn
	std::vector<SDL_Point> spawnPoints;

public:
	Map();
	Map(int w, int h, GAMEMOD mod, std::vector<SDL_Rect> mapCollider, std::vector<SDL_Point> sp);
	virtual ~Map();
	//getter
	SDL_Texture** getMapLayerArray();
	int getWidth();
	int getHeight();
	GAMEMOD getGameMod();
	std::vector<SDL_Rect> getColliders();
	std::vector<SDL_Point> getSpawnPoints();

	// load hình ảnh của map cho từng layer
	bool loadLayer(SDL_Renderer* renderer, const char* filePath, MapLayer layer);
	virtual void update(float deltaTime) = 0;  // Hàm cập nhật game loop, tùy vào chế độ chơi
    virtual bool checkVictoryCondition() = 0;  // Hàm kiểm tra điều kiện chiến thắng, tùy vào chế độ

	//Hủy các texture của map để giải phóng vùng nhớ
	void clean();
	
};