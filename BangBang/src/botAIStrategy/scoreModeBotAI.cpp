#include "BotAIStrategy/GameModeBehaviorStrategy/ScoreModeBotAI.hpp"

// Hàm tìm tank địch gần nhất
Tank* ScoreModeBotAI::findClosestEnemyTank(Tank* botTank, Map* map) 
{
    // Tank* closestTank = nullptr;
    // float minDistance = std::numeric_limits<float>::max();
    
    // for (Tank* enemyTank : map->getEnemyTanks(botTank->getTeam())) {
    //     float distance = bbg::distanceBetweenTwoPoint({botTank->getPosX(), botTank->getPosY()}, 
    //                                                   {enemyTank->getPosX(), enemyTank->getPosY()});
    //     if (distance < minDistance) {
    //         minDistance = distance;
    //         closestTank = enemyTank;
    //     }
    // }
    // return closestTank;
    return NULL;
}

bool ScoreModeBotAI::isInShootingRange(Tank* botTank, Tank* targetTank) 
{
    // Kiểm tra khoảng cách và góc bắn để xem bot có thể bắn trúng không
    return true;  // Ví dụ đơn giản
}

void ScoreModeBotAI::play(GAMEMOD mode, float deltaTime)
{

}