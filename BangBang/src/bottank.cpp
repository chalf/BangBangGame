#include "BotTank.hpp"

void BotTank::moveTowards(const SDL_Point targetPosition, float deltaTime) 
{
    // Tính khoảng cách từ vị trí hiện tại đến mục tiêu
    float distance = bbg::distanceBetweenTwoPoint(targetPosition, {(int)posX, (int)posY});

    // Nếu tank đã đến gần mục tiêu, không cần di chuyển nữa
    if (distance < this->specification.range*1.0)
        return;

    // Tính vector hướng từ vị trí hiện tại đến vị trí mục tiêu
    float deltaX = targetPosition.x - this->posX;
    float deltaY = targetPosition.y - this->posY;
    // Tính toán vector đơn vị để xác định hướng di chuyển
    float directionX = deltaX / distance;
    float directionY = deltaY / distance;

    // Di chuyển xe tăng với tốc độ đã định theo hướng tính được
    this->posX += directionX * this->specification.movement_speed * deltaTime;
    shiftColliders();
    this->posY += directionY * this->specification.movement_speed * deltaTime;
    shiftColliders();
}

BotTank::BotTank(string name, Strength strength, TankType type, Specification spec, int x, int y, vector<SDL_Rect> tankCollider) 
: Tank(name, strength, type, spec, x, y, tankCollider)
{
}

BotTank::~BotTank()
{}

void BotTank::setGameModeBehavior(GameModeBehavior* gm)
{
    gameModeBehavior = gm;
}

// void BotTank::shoot() {
//     // Kiểm tra nếu có thể bắn (có thể thêm thời gian chờ giữa các lần bắn)
//     if (canShoot()) {
//         // Tạo một viên đạn mới, khởi tạo vị trí và hướng bắn
//         Bullet* newBullet = new Bullet(this->position, this->getCurrentDirection());
        
//         // Thêm viên đạn vào danh sách các viên đạn hiện có
//         bullets.push_back(newBullet);
        
//         // Cập nhật thời gian lần bắn cuối
//         lastShootTime = SDL_GetTicks();
//     }
// }

// Hàm kiểm tra có thể bắn hay không
// bool BotTank::canShoot() {
//     // Giả sử có một khoảng thời gian chờ giữa các lần bắn
//     const int shootCooldown = 500; // 500ms giữa các lần bắn
//     return SDL_GetTicks() - lastShootTime >= shootCooldown;
// }

// bool BotTank::isInRange(Tank* target) {
//     // Tính khoảng cách giữa xe tăng hiện tại và mục tiêu
//     float distance = calculateDistance(this->position, target->getPosition());

//     // So sánh với phạm vi tấn công (range)
//     return distance <= this->specification.range;
// }

void BotTank::AIControl(Team& enemyTeam, float deltaTime) {
    Tank* testTank = enemyTeam.tanks.front();
    moveTowards({(int)testTank->getPosX(), (int)testTank->getPosY()}, deltaTime);

    // // Tìm tank đối thủ gần nhất
    // Tank* targetTank = nullptr;
    // float minDistance = 1e9;

    // for (Tank* enemyTank : enemyTeam.tanks) {
    //     float distance = bbg::distanceBetweenTwoPoint(
    //         {botTank->getPosX(), botTank->getPosY()},
    //         {enemyTank->getPosX(), enemyTank->getPosY()}
    //     );
    //     if (distance < minDistance) {
    //         minDistance = distance;
    //         targetTank = enemyTank;
    //     }
    // }

    // if (targetTank != nullptr) {
    //     // Di chuyển về phía mục tiêu
    //     botTank->moveTowards(targetTank->getPosX(), targetTank->getPosY(), deltaTime);

    //     // Xoay đầu để ngắm mục tiêu
    //     botTank->rotateHead(targetTank->getPosX(), targetTank->getPosY());

    //     // Bắn đạn nếu mục tiêu nằm trong tầm
    //     if (minDistance <= botTank->getSpecification().range) {
    //         botTank->handleBulletShooting();
    //     }
    // }
}

// void BotTank::updateState() 
// {
//     if (isUnderAttack()) {
//         currentState = EVADE;
//     } else if (currentTarget && isInRange()) {
//         currentState = ATTACK;
//     } else {
//         currentState = SEEK_ENEMY;
//     }
// }

// void BotTank::seekEnemy(vector<Tank> enemyTeam, float deltaTime) 
// {
//     currentTarget = findNearestEnemy(enemyTeam);
//     if (currentTarget) {
//         targetPosition = {currentTarget->getPosX() + TANK_WIDTH / 2, currentTarget->getPosY() + TANK_HEIGHT / 2};
//         moveTowards(targetPosition, deltaTime);
//     }
// }

// void BotTank::attack() 
// {
//     if (currentTarget) {
//         rotateHead(currentTarget->getPosX() + TANK_WIDTH / 2, currentTarget->getPosY() + TANK_HEIGHT / 2);
//         if (canShoot()) {
//             shoot();
//         }
//     }
// }

// void BotTank::evade(float deltaTime) 
// {
//     SDL_Point safePosition = findSafePosition();
//     moveTowards(safePosition, deltaTime);
// }

// Tank* BotTank::findNearestEnemy(vector<Tank> enemyTeam) 
// {
//     Tank* foundEnemy;
//     return foundEnemy;
// }

// bool BotTank::isInRange() 
// {
//     // Check if the target is within shooting range
//     return true;
// }

// bool BotTank::isUnderAttack() 
// {
//     // Check if any enemy bullets are nearby
//     return true;
// }

// SDL_Point BotTank::findSafePosition() 
// {
//     // Find a safe position to evade to
//     return {0,0};
// }

// bool BotTank::canShoot() 
// {
//     // Check if the tank can shoot (cooldown, etc.)
//     return true;
// }

// void BotTank::shoot() 
// {
//     // Implement shooting logic
// }

// void BotTank::action(vector<Tank> enemyTeam, float deltaTime)
// {
//     updateState();
//     switch (currentState) 
//     {
//         case SEEK_ENEMY:
//             seekEnemy(enemyTeam, deltaTime);
//             break;
//         case ATTACK:
//             attack();
//             break;
//         case EVADE:
//             evade(deltaTime);
//             break;
//     }
// }




