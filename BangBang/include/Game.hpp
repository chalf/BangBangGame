#pragma once
#include <memory>

#include "RenderWindow.hpp"
#include "Map.hpp"
#include "Tank.hpp"
#include "Camera.hpp"
#include "Team.hpp"

using namespace std;

enum GameState {
    IN_GAME,
    GAME_OVER,
    MENU
};

class Game : public RenderWindow
{
private:
	bool running;
	vector<Map> mapList;
    vector<Tank> tankList;
    unique_ptr<Camera> camera;
    vector<Team> team;

    void renderHealthBar(Tank* tank, int viewportX, int viewportY);   //thanh máu
public:
	Game(const char* p_title, int p_w, int p_h);
    ~Game();

    bool isRunning();

    void startGame();
    void drawPlayButton(SDL_Rect buttonRect);
    bool isReplayButtonClicked(SDL_Event& event, SDL_Rect buttonRect);
    void showReplayMenu(GameState& currentState);

    //load hình ảnh map, và khởi tạo camera
    bool loadMaps();
    //load hình ảnh các tank cho mỗi team
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