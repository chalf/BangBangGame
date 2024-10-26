#pragma once
#include "Map.hpp"
#include "Team.hpp"

class ScoreMap : public Map {
private:
    std::vector<int> teamScore;
public:
    ScoreMap(int w, int h, std::vector<SDL_Rect> mapCollider);

    void update(float deltaTime) override;
	bool checkVictoryCondition() override;
};
