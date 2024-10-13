#pragma once
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
	vector<Map> mapList;
    vector<Tank> tankList;
    unique_ptr<Camera> camera;

    void renderHealthBar(Tank* tank, int viewportX, int viewportY);   //thanh máu
public:
	Game(const char* p_title, int p_w, int p_h);
    ~Game();
    vector<Map> getMapList();
    vector<Tank>& getTankList();

    bool isRunning();
    //load hình ảnh map, và khởi tạo camera
    bool loadMaps();
    //load hình ảnh tank
    bool loadTanks();
    // hide render() method of RenderWindow class, để render cả map và tank chung 1 method
    void render();
    // hide display() method of RenderWindow class, để render phần FLOATING lên trên cùng
    void display();
    // xử lý các thao tác trong game
    void handleEvents(SDL_Event& event);
    //update frame
    void update(float deltaTime);


    //thu hồi vùng nhớ của tài nguyên: map, tank, 
    void destroyAll();
    

};