#pragma once
#include "Map.hpp"
#include "Team.hpp"

class ScoreMap : public Map {
private:
    std::vector<int> teamScore;
public:
    ScoreMap(int w, int h, GAMEMOD mod, std::vector<SDL_Rect> mapCollider, std::vector<SDL_Point> sp);
    ~ScoreMap();
    void update(float deltaTime) override;
	bool checkVictoryCondition() override;
};
