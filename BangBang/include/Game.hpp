#pragma once
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>

#include "RenderWindow.hpp"
#include "Map.hpp"
#include "Tank.hpp"
#include "Camera.hpp"

using namespace std;

class Game : public RenderWindow
{
private:
	bool running;
	std::vector<Map> mapList;
    std::vector<Tank> tankList;
    std::unique_ptr<Camera> camera;

public:
	Game(const char* p_title, int p_w, int p_h);
    ~Game();
    std::vector<Map> getMapList();
    std::vector<Tank>& getTankList();

    bool isRunning();
    //load hình ảnh map, và khởi tạo camera
    bool loadMaps();
    //load hình ảnh tank
    bool loadTanks();
    // hide render() method of RenderWindow class, để render cả map và tank chung 1 method
    void render();
    // xử lý các thao tác trong game
    void handleEvents(SDL_Event& event);
    //update frame
    void update();


    //thu hồi vùng nhớ của tài nguyên: map, tank, 
    void destroyAll();
    

};