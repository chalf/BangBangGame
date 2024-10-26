#include "ScoreMap.hpp"

ScoreMap::ScoreMap(int w, int h, std::vector<SDL_Rect> mapCollider) : Map(w, h, mapCollider)
{
	teamScore.push_back(0);	//khởi tạo điểm cho team 1
	teamScore.push_back(0);	//khởi tạo điểm cho team 2
}

void ScoreMap::update(float deltaTime) 
{
    // Cập nhật vị trí các tank, đạn, và logic tính điểm
    // Ví dụ: cộng điểm khi bắn trúng đối phương
}

bool ScoreMap::checkVictoryCondition() 
{
    // if (player1Score >= scoreLimit) {
    //     std::cout << "Player 1 wins!" << std::endl;
    //     return true;
    // }
    // if (player2Score >= scoreLimit) {
    //     std::cout << "Player 2 wins!" << std::endl;
    //     return true;
    // }
    return false;
}