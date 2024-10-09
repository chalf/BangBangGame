
#include "Tank.hpp"

Specification::Specification()
{
	HP = dps = piercing = physical_armor = energy_shield = bullet_speed = range = 0;
    movement_speed = 5;
}

string Specification::to_string()
{
	return "HP: " + std::to_string(HP) + 
           ",\nDPS: " + std::to_string(dps) +
           ",\nPiercing: " + std::to_string(piercing) + 
           ",\nPhysical Armor: " + std::to_string(physical_armor) + 
           ",\nEnergy Shield: " + std::to_string(energy_shield) + 
           ",\nMovement Speed: " + std::to_string(movement_speed) + 
           ",\nBullet Speed: " + std::to_string(bullet_speed) + 
           ",\nRange: " + std::to_string(range);
}

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
        //render vào tankTexForRenderTanksBody và gán cho bodyTex
    SDL_RenderPresent(renderer);
    this->headTex = tankTexForRenderTanksHead;
        //chuyển target về màn hình
    if( SDL_SetRenderTarget(renderer, NULL) < 0)
        return false;
    return true;
}

Tank::Tank(string name, Strength strength, TankType type, Specification spec, SDL_Texture* image, int x, int y, vector<SDL_Rect> tankCollider) : posX(x), posY(y)
{
	this->name = name;
	this->strength = strength;
	this->type = type;
	this->specification = spec;
	this->thumbnail = image;
    velX = 0;
    velY = 0;
    mColliders = tankCollider;
    
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
    
    this->shiftColliders();
}

bool Tank::loadTextures(SDL_Renderer* renderer, const char* spriteSheetPath)
{
    SDL_Surface* spriteSheetSurface = IMG_Load(spriteSheetPath);
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
    return true;
}

void Tank::handleTankMovement(SDL_Event& e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: velY -= this->specification.movement_speed; break;
            case SDLK_s: velY += this->specification.movement_speed; break;
            case SDLK_a: velX -= this->specification.movement_speed; break;
            case SDLK_d: velX += this->specification.movement_speed; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: velY += this->specification.movement_speed; break;
            case SDLK_s: velY -= this->specification.movement_speed; break;
            case SDLK_a: velX += this->specification.movement_speed; break;
            case SDLK_d: velX -= this->specification.movement_speed; break;
        }
    }
    // Nếu có chuyển động, tính góc xoay
    if (velX != 0 || velY != 0)
    {
        bodyAngle = -atan2(velX, velY) * 180 / M_PI;
    }
    
}

void Tank::move(int mapWidth, int mapHeight, vector<SDL_Rect>& tankColliders, vector<SDL_Rect> mapColliders, float deltaTime)
{
    posX += velX * deltaTime;
    shiftColliders();
    //If the tank went too far to the left or right
    if( ( posX < 0 ) || ( posX + TANK_WIDTH > mapWidth) || bbg::checkCollision(mColliders, tankColliders) || bbg::checkCollision(mColliders, mapColliders) )
    {
        //Move back
        posX -= velX;
        shiftColliders();
    }

    posY += velY * deltaTime;
    shiftColliders();
    //If the tank went too far up or down
    if( (posY < 0) || ( posY + TANK_HEIGHT > mapHeight ) || bbg::checkCollision(mColliders, tankColliders ) || bbg::checkCollision(mColliders, mapColliders) )
    {
        //Move back
        posY -= velY;
        shiftColliders();
    }
}

void Tank::handleBulletShooting(SDL_Event& event)
{
    // if(event.type == SDL_MOUSEBUTTONDOWN)
    // {
    //     Bullet* bullet = new Bullet(m_nBulletWidth, m_nBulletHeight);
    //     if(event.button.button == SDL_BUTTON_LEFT)
    //     {

    //     }
    // }
}

void Tank::rotateHead(int mouseX, int mouseY)
{
    // Lấy tọa độ trung tâm của tank
    int centerX = posX + TANK_WIDTH / 2;
    int centerY = posY + TANK_HEIGHT / 2;
    // Tính góc từ trung tâm tank tới vị trí con trỏ chuột
    headAngle = atan2(mouseY - centerY, mouseX - centerX) * 180 / M_PI - 90;
}

void Tank::clean()
{
    SDL_DestroyTexture(thumbnail);
    SDL_DestroyTexture(bodyTex);
    SDL_DestroyTexture(headTex);
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

string Tank::getType()
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

SDL_Texture* Tank::getThumbnail()
{
    return thumbnail;
}

void Tank::setThumbnail(SDL_Texture* image)
{
    this->thumbnail = image;
}

string Tank::getSpecification()
{
    return this->specification.to_string();
}

void Tank::setSpecification(Specification sp)
{
    this->specification = sp;
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

void Tank::setBulletWidthHeight(int w, int h)
{
    m_nBulletWidth = w;
    m_nBulletHeight = h;
}

vector<Bullet*> Tank::getBulletVector()
{
    return m_pBulletVector;
}

void Tank::setBulletVector(vector<Bullet*> bulletVector)
{
    m_pBulletVector = bulletVector;
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