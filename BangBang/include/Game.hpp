#pragma once
#include <SDL2/SDL.h>

#include "RenderWindow.hpp"

class Game : public RenderWindow
{
private:
	bool running;
public:
	Game();
    ~Game();

    void update();
    bool isRunning() { return running; }
};