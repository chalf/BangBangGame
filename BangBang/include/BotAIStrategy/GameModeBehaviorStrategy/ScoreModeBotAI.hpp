#pragma once
#include "BotAIStrategy/GameModeBehavior.hpp"

class Tank;

class ScoreModeBotAI : public GameModeBehavior {
private:
	// Hàm tìm tank địch gần nhất
    Tank* findClosestEnemyTank(Tank* botTank, Map* map);
    
    bool isInShootingRange(Tank* botTank, Tank* targetTank);

    //tìm tank địch thấp máu nhất
    Tank* findLowestHealthEnemy(Tank* botTank, const std::vector<Tank*>& enemies);
public:
    void play(GAMEMOD mode, float deltaTime) override;
};
