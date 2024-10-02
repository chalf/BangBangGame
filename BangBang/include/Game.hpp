#pragma once
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Map.hpp"
#include "Tank.hpp"

class Game : public RenderWindow
{
private:
	bool running;
	std::vector<Map> mapList;
    std::vector<Tank> tankList;

public:
	Game(const char* p_title, int p_w, int p_h);
    ~Game();
    std::vector<Map> getMapList();
    std::vector<Tank> getTankList();

    bool isRunning() { return running; }
    void quitGame();
    bool loadMaps();
    bool loadTanks();

    void handleEvents();

    //thu hồi vùng nhớ của tài nguyên
    void destroyMap();
    

};