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

bool Tank::checkTankCollisions( vector<Tank*> tanks)
{
    for (Tank* otherTank : tanks)
    {
        // Tránh kiểm tra va chạm với chính nó
        if (this == otherTank)
            continue;

        // Kiểm tra va chạm giữa tank hiện tại và tank khác
        if (bbg::checkCollision(this->mColliders, otherTank->getColliders()))
        {
            return true;  // Nếu có va chạm thì trả về true
        }
    }
    return false;  // Không có va chạm
}

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

Tank::~Tank()
{
    
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

}

void Tank::handleTankMovement(SDL_Event& event)
{

}

void Tank::move(int mapWidth, int mapHeight, vector<Tank*> tanks, vector<SDL_Rect> mapColliders, float deltaTime)
{

}

void Tank::handleBulletShooting(SDL_Event& event)
{

}

void Tank::AIControl(Team& enemyTeam, float deltaTime)
{

}

void Tank::getHit(Tank* enemyTank)
{
    if(enemyTank->type == PHYSICAL)
    {
        currentHP -= bbg::damageTaken(enemyTank->specification.dps, enemyTank->specification.piercing, this->specification.physical_armor);
    }
    else //còn lại type == ENERGY
    {
        currentHP -= bbg::damageTaken(enemyTank->specification.dps, enemyTank->specification.piercing, this->specification.energy_shield);
    }
    if(currentHP <= 0)  //để hp không phải là số âm
        currentHP = 0;
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

int Tank::getTeamId()
{
    return teamId;
}

void Tank::setTeamId(int id)
{
    teamId = id;
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