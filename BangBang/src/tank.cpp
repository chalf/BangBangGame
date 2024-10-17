
#include "Tank.hpp"

void Tank::shiftColliders()
{
    int r = 0;
    for (SDL_Rect& collider : mColliders) {
        collider.x = posX + (TANK_WIDTH - collider.w) / 2;
        collider.y = posY + r;
        r += collider.h;
    }
}

SDL_Texture* tankTexForRenderTanksBody = NULL;
bool Tank::loadBodyTex(SDL_Renderer* renderer, SDL_Texture* spriteSheetTex)
{
    tankTexForRenderTanksBody = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TANK_WIDTH, TANK_HEIGHT);
    if(tankTexForRenderTanksBody == NULL)
    {
        cout << "Error at tank.cpp. Failed to create texture for tankTexForRenderTanksBody: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetTextureBlendMode(tankTexForRenderTanksBody, SDL_BLENDMODE_BLEND);
        // set target thành tankTexForRenderTanksBody
    if(SDL_SetRenderTarget(renderer, tankTexForRenderTanksBody) < 0)
    {
        cout << "Error at tank.cpp. Failed to set render target to tankTexForRenderTanksBody: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, spriteSheetTex, &bodyFrames.at(STATIC), NULL);
        //render vào tankTexForRenderTanksBody và gán cho bodyTex
    SDL_RenderPresent(renderer);
    this->bodyTex = tankTexForRenderTanksBody;
        //chuyển target về màn hình
    if( SDL_SetRenderTarget(renderer, NULL) < 0)
        return false;
    return true;
}

SDL_Texture* tankTexForRenderTanksHead = NULL;
bool Tank::loadHeadTex(SDL_Renderer* renderer, SDL_Texture* spriteSheetTex)
{
    tankTexForRenderTanksHead = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TANK_WIDTH, TANK_HEIGHT);
    if(tankTexForRenderTanksHead == NULL)
    {
        cout << "Error at tank.cpp. Failed to create texture for tankTexForRenderTanksHead: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetTextureBlendMode(tankTexForRenderTanksHead, SDL_BLENDMODE_BLEND);
        // set target thành tankTexForRenderTanksHead
    if(SDL_SetRenderTarget(renderer, tankTexForRenderTanksHead) < 0)
    {
        cout << "Error at tank.cpp. Failed to set render target to tankTexForRenderTanksHead: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, spriteSheetTex, &headFrames.at(STATIC), NULL);
        //render vào tankTexForRenderTanksHead và gán cho headTex
    SDL_RenderPresent(renderer);
    this->headTex = tankTexForRenderTanksHead;
        //chuyển target về màn hình
    if( SDL_SetRenderTarget(renderer, NULL) < 0)
        return false;
    return true;
}

Tank::Tank(){}

Tank::Tank(string name, Strength strength, TankType type, Specification spec, int x, int y, vector<SDL_Rect> tankCollider) : posX(x), posY(y)
{
	this->name = name;
	this->strength = strength;
	this->type = type;
	this->specification = spec;
	thumbnail = NULL;
    velX = 0;
    velY = 0;
    mColliders = tankCollider;
    bullet = NULL;
    currentHP = specification.HP;
    m_bGetHit = false;
    
    this->shiftColliders();
}

Tank::Tank(Strength strength, TankType type, int x, int y, vector<SDL_Rect> tankCollider) 
    : posX(x), posY(y)
{
	name = "TEST";
	this->strength = strength;
	this->type = type;
	Specification temp;
	specification = temp;
	thumbnail = NULL;
    velX = 0;
    velY = 0;
    mColliders = tankCollider;
    bullet = NULL;
    currentHP = specification.HP;
    m_bGetHit = false;
    
    this->shiftColliders();
}

bool Tank::loadTextures(SDL_Renderer* renderer, string spriteSheetPath, string bulletImagePath)
{
    SDL_Surface* spriteSheetSurface = IMG_Load(spriteSheetPath.c_str());
    if(spriteSheetSurface == NULL)
    	return false;

    // Tạo frame cho thân
    for (int i = 0; i < FrameNumber; i++) 
    {
        SDL_Rect frame = { i * spriteSheetSurface->w / FrameNumber, 0, TANK_WIDTH, TANK_HEIGHT };
        bodyFrames.push_back(frame);
    }

    // Tạo frame cho đầu
    for (int i = 0; i < FrameNumber; i++) 
    {
        SDL_Rect frame = { i * spriteSheetSurface->w / FrameNumber, TANK_HEIGHT, TANK_WIDTH, TANK_HEIGHT };
        headFrames.push_back(frame);
    }
    SDL_Texture* spriteSheetTex = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
    SDL_FreeSurface(spriteSheetSurface);

    /* gán texture cho bodyTex*/
    if( !loadBodyTex(renderer, spriteSheetTex) )
        return false;

    /* gán texture cho headTex*/
    if( !loadHeadTex(renderer, spriteSheetTex) )
        return false;

    //sau khi làm việc xong với spriteSheetTex thì hủy
    SDL_DestroyTexture(spriteSheetTex);

    /* KHỞI TẠO BULLET*/
    this->bullet = new Bullet(renderer, bulletImagePath, colliders::pegasusBulletColliders());

    return true;
}

bool Tank::loadThumbnail(SDL_Renderer* renderer, string thumbnailPath)
{
    return bbg::loadTextureFromFile(renderer, thumbnailPath.c_str(), this->thumbnail);
}

void Tank::rotateHead(int mouseX, int mouseY)
{
    // Lấy tọa độ trung tâm của tank
    int centerX = posX + TANK_WIDTH / 2;
    int centerY = posY + TANK_HEIGHT / 2;
    // Tính góc từ trung tâm tank tới vị trí con trỏ chuột, atan2 trả về giá trị thuộc (-pi, pi]
    headAngle = atan2(mouseY - centerY, mouseX - centerX) * 180 / M_PI - 90;
    //vì đầu tank thiết kế hướng xuống nên -90 độ để xoay nó xoay ngược lại 90 độ, vì hệ tọa đồ đồ họa trục tung hướng xuống
    /*
    chuột bên trên: atan2 = -90 => xoay -90 -90 = -180  //tại sao chuột bên trên atan2 lại nhỏ hơn 0, hãy xem hình trong báo cáo
    chuột bên dưới: atan2 = 90  => xoay 0
    chuot ben phai: atan2 = 0   => xoay -90
    chuot ben trai: atan2 = 180 => xoay 90
    */
}
bool movingUp, movingDown, movingLeft, movingRight;
void Tank::handleTankMovement(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w: movingUp = true; break;
            case SDLK_s: movingDown = true; break;
            case SDLK_a: movingLeft = true; break;
            case SDLK_d: movingRight = true; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_w: movingUp = false; break;
            case SDLK_s: movingDown = false; break;
            case SDLK_a: movingLeft = false; break;
            case SDLK_d: movingRight = false; break;
        }
    }
}

void Tank::move(int mapWidth, int mapHeight, vector<Tank>& tanks, vector<SDL_Rect> mapColliders, float deltaTime)
{
    velX = velY = 0;
    if (movingUp) velY -= 1.0f;
    if (movingDown) velY += 1.0f;
    if (movingLeft) velX -= 1.0f;
    if (movingRight) velX += 1.0f;

    // Chuẩn hóa vector vận tốc
    float magnitude = sqrt(velX * velX + velY * velY);
    if (magnitude > 0)
    {
        velX = (velX / magnitude) * specification.movement_speed;
        velY = (velY / magnitude) * specification.movement_speed;
    }

    // Cập nhật góc xoay nếu có chuyển động
    if (velX != 0 || velY != 0)
    {
        bodyAngle = -atan2(velX, velY) * 180 / M_PI;
    }
    float newPosX = posX + velX * deltaTime;
    float newPosY = posY + velY * deltaTime;

    // Kiểm tra va chạm theo trục X
    posX = newPosX;
    shiftColliders();
    if ((posX < 0) || (posX + TANK_WIDTH > mapWidth) || checkTankCollisions(tanks) || bbg::checkCollision(mColliders, mapColliders))
    {
        posX = newPosX - velX * deltaTime;
        velX = 0; // Dừng chuyển động theo trục X nếu va chạm
    }

    // Kiểm tra va chạm theo trục Y
    posY = newPosY;
    shiftColliders();
    if ((posY < 0) || (posY + TANK_HEIGHT > mapHeight) || checkTankCollisions(tanks) || bbg::checkCollision(mColliders, mapColliders))
    {
        posY = newPosY - velY * deltaTime;
        velY = 0; // Dừng chuyển động theo trục Y nếu va chạm
    }

    shiftColliders();
}
// void Tank::handleTankMovement(SDL_Event& e)
// {
//     // Tính toán hướng di chuyển
//     float dirX = 0, dirY = 0;
//     if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
//     {
//         //Adjust the velocity
//         switch( e.key.keysym.sym )
//         {
//             case SDLK_w: velY -= this->specification.movement_speed; break;
//             case SDLK_s: velY += this->specification.movement_speed; break;
//             case SDLK_a: velX -= this->specification.movement_speed; break;
//             case SDLK_d: velX += this->specification.movement_speed; break;
//         }
//     }
//     else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
//     {
//         //Adjust the velocity
//         switch( e.key.keysym.sym )
//         {
//             case SDLK_w: velY += this->specification.movement_speed; break;
//             case SDLK_s: velY -= this->specification.movement_speed; break;
//             case SDLK_a: velX += this->specification.movement_speed; break;
//             case SDLK_d: velX -= this->specification.movement_speed; break;
//         }
//     }
//     // Nếu có chuyển động, tính góc xoay
//     if (velX != 0 || velY != 0)
//     {
//         bodyAngle = -atan2(velX, velY) * 180 / M_PI;
//     }
    
// }

// void Tank::move(int mapWidth, int mapHeight, vector<Tank>& tanks, vector<SDL_Rect> mapColliders, float deltaTime)
// {
//     posX += velX * deltaTime;
//     shiftColliders();
//     //If the tank went too far to the left or right hoặc va chạm vật thể khác
//     if( ( posX < 0 ) || ( posX + TANK_WIDTH > mapWidth) || checkTankCollisions(tanks) || bbg::checkCollision(mColliders, mapColliders) )
//     {
//         //Move back
//         posX -= velX * deltaTime;
//         shiftColliders();
//     }

//     posY += velY * deltaTime;
//     shiftColliders();
//     //If the tank went too far up or down
//     if( ( posY < 0 ) || ( posY + TANK_HEIGHT > mapHeight) || checkTankCollisions(tanks) || bbg::checkCollision(mColliders, mapColliders) )
//     {
//         posY -= velY * deltaTime;
//         shiftColliders();
//     }
// }

bool Tank::checkTankCollisions( vector<Tank>& tanks)
{
    for (Tank& otherTank : tanks)
    {
        // Tránh kiểm tra va chạm với chính nó
        if (this == &otherTank)
            continue;

        // Kiểm tra va chạm giữa tank hiện tại và tank khác
        if (bbg::checkCollision(this->mColliders, otherTank.getColliders()))
        {
            return true;  // Nếu có va chạm thì trả về true
        }
    }
    return false;  // Không có va chạm
}

void Tank::handleBulletShooting(SDL_Event& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT && !bullet->isActive())
        {
            bullet->setActive(true);
            bullet->setTouch(false);
            // Tính toán vị trí bắt đầu của đạn
            float tankCenterX = this->posX + TANK_WIDTH / 2;
            float tankCenterY = this->posY + TANK_HEIGHT / 2;
            SDL_Rect bulletRect = { 
                (int)(tankCenterX - bullet->getWidth() / 2), 
                (int)(tankCenterY - bullet->getHeight() / 2), 
                bullet->getWidth(), 
                bullet->getHeight()
            };
            bullet->setRect(bulletRect);
            bullet->setAngle(headAngle + 90);   //lấy theo góc của headAngle để luôn bắn theo góc của đầu tank, vì đầu đạn hướng sang bên phải (đúng với trục hoành nên cộng lại 90)
            bullet->setInitPos(bulletRect.x, bulletRect.y);
        }
    }
}

void Tank::getHit(Tank enemyTank)
{
    if(enemyTank.type == PHYSICAL)
    {
        currentHP -= bbg::damageTaken(enemyTank.specification.dps, enemyTank.specification.piercing, this->specification.physical_armor);
    }
    else //còn lại type == ENERGY
    {
        currentHP -= bbg::damageTaken(enemyTank.specification.dps, enemyTank.specification.piercing, this->specification.energy_shield);
    }
    if(currentHP <= 0)  //để hp không phải là số âm
        currentHP = 0;
}

void Tank::moveTowards(const SDL_Point targetPosition, float deltaTime) 
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
    this->posY += directionY * this->specification.movement_speed * deltaTime;
}


// void Tank::shoot() {
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
// bool Tank::canShoot() {
//     // Giả sử có một khoảng thời gian chờ giữa các lần bắn
//     const int shootCooldown = 500; // 500ms giữa các lần bắn
//     return SDL_GetTicks() - lastShootTime >= shootCooldown;
// }

// bool Tank::isInRange(Tank* target) {
//     // Tính khoảng cách giữa xe tăng hiện tại và mục tiêu
//     float distance = calculateDistance(this->position, target->getPosition());

//     // So sánh với phạm vi tấn công (range)
//     return distance <= this->specification.range;
// }

// void AIControl(Tank* botTank, Team& enemyTeam, float deltaTime) {
//     // Tìm tank đối thủ gần nhất
//     Tank* targetTank = nullptr;
//     float minDistance = 1e9;

//     for (Tank* enemyTank : enemyTeam.tanks) {
//         float distance = bbg::distanceBetweenTwoPoint(
//             {botTank->getPosX(), botTank->getPosY()},
//             {enemyTank->getPosX(), enemyTank->getPosY()}
//         );
//         if (distance < minDistance) {
//             minDistance = distance;
//             targetTank = enemyTank;
//         }
//     }

//     if (targetTank != nullptr) {
//         // Di chuyển về phía mục tiêu
//         botTank->moveTowards(targetTank->getPosX(), targetTank->getPosY(), deltaTime);

//         // Xoay đầu để ngắm mục tiêu
//         botTank->rotateHead(targetTank->getPosX(), targetTank->getPosY());

//         // Bắn đạn nếu mục tiêu nằm trong tầm
//         if (minDistance <= botTank->getSpecification().range) {
//             botTank->handleBulletShooting();
//         }
//     }
// }

void Tank::updateState() 
{
    if (isUnderAttack()) {
        currentState = EVADE;
    } else if (currentTarget && isInRange()) {
        currentState = ATTACK;
    } else {
        currentState = SEEK_ENEMY;
    }
}

void Tank::seekEnemy(vector<Tank> enemyTeam, float deltaTime) 
{
    currentTarget = findNearestEnemy(enemyTeam);
    if (currentTarget) {
        targetPosition = {currentTarget->getPosX() + TANK_WIDTH / 2, currentTarget->getPosY() + TANK_HEIGHT / 2};
        moveTowards(targetPosition, deltaTime);
    }
}

void Tank::attack() 
{
    if (currentTarget) {
        rotateHead(currentTarget->getPosX() + TANK_WIDTH / 2, currentTarget->getPosY() + TANK_HEIGHT / 2);
        if (canShoot()) {
            shoot();
        }
    }
}

void Tank::evade(float deltaTime) 
{
    SDL_Point safePosition = findSafePosition();
    moveTowards(safePosition, deltaTime);
}

Tank* Tank::findNearestEnemy(vector<Tank> enemyTeam) 
{
    Tank* foundEnemy;
    return foundEnemy;
}

bool Tank::isInRange() 
{
    // Check if the target is within shooting range
    return true;
}

bool Tank::isUnderAttack() 
{
    // Check if any enemy bullets are nearby
    return true;
}

SDL_Point Tank::findSafePosition() 
{
    // Find a safe position to evade to
    return {0,0};
}

bool Tank::canShoot() 
{
    // Check if the tank can shoot (cooldown, etc.)
    return true;
}

void Tank::shoot() 
{
    // Implement shooting logic
}

void Tank::action(vector<Tank> enemyTeam, float deltaTime)
{
    updateState();
    switch (currentState) 
    {
        case SEEK_ENEMY:
            seekEnemy(enemyTeam, deltaTime);
            break;
        case ATTACK:
            attack();
            break;
        case EVADE:
            evade(deltaTime);
            break;
    }
}

void Tank::clean()
{
    SDL_DestroyTexture(thumbnail);
    SDL_DestroyTexture(bodyTex);
    SDL_DestroyTexture(headTex);
    bullet->clean();
    delete bullet;
    //hủy các texture toàn cục
    SDL_DestroyTexture(tankTexForRenderTanksBody);
    SDL_DestroyTexture(tankTexForRenderTanksHead);
}

string Tank::getName()
{
    return name;
}

void Tank::setName(string name)
{
    this->name = name;
}

string Tank::getStrength()
{
    string power = "NULL";
    switch (this->strength) 
    {
        case DPS:
            power = "DPS";
            break;
        case TANKER:
            power = "TANKER";
            break;
        case SUPPORT:
            power = "SUPPORT";
            break;
    }
    return power;
}

string Tank::getTypeStr()
{
    string power = "NULL";
    switch (this->type) 
    {
        case PHYSICAL:
            power = "PHYSICAL";
            break;
        case ENERGY:
            power = "ENERGY";
            break;
    }
    return power;
}

TankType Tank::getType()
{
    return type;
}

SDL_Texture* Tank::getThumbnail()
{
    return thumbnail;
}

void Tank::setThumbnail(SDL_Texture* image)
{
    this->thumbnail = image;
}

string Tank::getSpecificationStr()
{
    return this->specification.to_string();
}

Specification Tank::getSpecification()
{
    return specification;
}

void Tank::setSpecification(Specification sp)
{
    this->specification = sp;
    this->currentHP = this->specification.HP;
}

SDL_Texture* Tank::getBodyTex()
{
    return bodyTex;
}

SDL_Texture* Tank::getHeadTex()
{
    return headTex;
}

float Tank::getPosX()
{
    return posX;
}

float Tank::getPosY()
{
    return posY;
}

void Tank::setPosition(float x, float y) 
{
    posX = x;
    posY = y;
}

std::vector<SDL_Rect>& Tank::getColliders()
{
    return mColliders;
}

float Tank::getBodyAngle()
{
    return bodyAngle;
}

float Tank::getHeadAngle()
{
    return headAngle;
}

Bullet* Tank::getBullet()
{
    return bullet;
}

void Tank::set_HP(int num)
{
    this->specification.HP = num;
}

void Tank::set_dps(int num)
{
    this->specification.dps = num;
}

void Tank::set_piercing(int num)
{
    this->specification.piercing = num;
}

void Tank::set_physical_armor(int num)
{
    this->specification.physical_armor = num;
}

void Tank::set_energy_shield(int num)
{
    this->specification.energy_shield = num;
}

void Tank::set_movement_speed(int num)
{
    this->specification.movement_speed = num;
}

void Tank::set_bullet_speed(int num)
{
    this->specification.bullet_speed = num;
}

void Tank::set_range(int num)
{
    this->specification.range = num;
}