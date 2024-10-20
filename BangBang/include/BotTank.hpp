#pragma once

#include "Tank.hpp"

enum AIState 
{
    SEEK_ENEMY, //tìm địch
    ATTACK, //tấn công
    EVADE   //tránh né
};

class BotTank : public Tank
{
    /*------------------------------------------*/
    //METHOD CHO TANK BOT. Các bước đơn giản:
    /*Di chuyển về phía tank của đối thủ
	 *Xác định khi nào bắn đạn (khi ở trong tầm bắn)
	 *Tránh né hoặc di chuyển ra khỏi vùng nguy hiểm.
    */
    
private:
    AIState currentState;
    Tank* currentTarget;
    SDL_Point targetPosition;
    void updateState();
    void seekEnemy(vector<Tank> enemyTeam, float deltaTime);
    void attack();
    void evade(float deltaTime);
    //
    Tank* findNearestEnemy(vector<Tank> enemyTeam);
    bool isInRange();
    bool isUnderAttack();
    SDL_Point findSafePosition();
    bool canShoot();
    void shoot();
public:
    BotTank(string name, Strength strength, TankType type, Specification spec, int x, int y, vector<SDL_Rect> tankCollider);
    ~BotTank();
    void action(vector<Tank> enemyTeam, float deltaTime);
    /*------------------------------------------*/

    void moveTowards(const SDL_Point targetPosition, float deltaTime);
    // void shoot();
    // bool isInRange(Tank* target);
    //------------------
    void AIControl(Tank* botTank, Team& enemyTeam, float deltaTime) override;
    //-------------------

};