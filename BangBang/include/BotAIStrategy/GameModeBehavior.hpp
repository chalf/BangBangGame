#pragma once
#include "Map.hpp"

//interface, không có file .cpp nào của header này
//Các lớp con phải hiện thực method play()
class GameModeBehavior {
public:
    virtual void play(GAMEMOD mode, float deltaTime) = 0;  // Cập nhật hành động của bot
    virtual ~GameModeBehavior() {}
};