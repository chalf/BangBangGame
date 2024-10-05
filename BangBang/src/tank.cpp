
#include "Tank.hpp"

Specification::Specification()
{
	HP = dps = piercing = physical_armor = energy_shield = rate_of_fire = range = 0;
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
           ",\nRate of Fire: " + std::to_string(rate_of_fire) + 
           ",\nRange: " + std::to_string(range);
}

Tank::Tank()
{
    Specification spec;
    this->specification = spec;
    posX = 65;
    posY = 162;
    velX = 0;
    velY = 0;
}

Tank::Tank(string name, Strength strength, TankType type, Specification spec, SDL_Texture* image)
{
	this->name = name;
	this->strength = strength;
	this->type = type;
	this->specification = spec;
	this->tex = image;
    posX = 65;
    posY = 162;
    velX = 0;
    velY = 0;
}

Tank::Tank(Strength strength, TankType type)
{
	name = "TEST";
	this->strength = strength;
	this->type = type;
	Specification temp;
	specification = temp;
	tex = NULL;
    posX = 65;
    posY = 162;
    velX = 0;
    velY = 0;
}

Tank::~Tank()
{
	SDL_DestroyTexture(this->tex);
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

SDL_Texture* Tank::getImage()
{
	return tex;
}

void Tank::setImage(SDL_Texture* image)
{
	this->tex = image;
}

string Tank::getSpecification()
{
	return this->specification.to_string();
}

void Tank::setSpecification(Specification sp)
{
	this->specification = sp;
}

SDL_Texture* Tank::getTex()
{
	return tex;
}

SDL_Rect Tank::getClip()
{
	return clip;
}

void Tank::setClip(SDL_Rect clip)
{
	this->clip = clip;
}

SDL_Texture* Tank::getTexInMatch()
{
	return texInMatch;
}

int Tank::getPosX()
{
    return posX;
}

int Tank::getPosY()
{
    return posY;
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

void Tank::set_rate_of_fire(int num)
{
	this->specification.rate_of_fire = num;
}

void Tank::set_range(int num)
{
	this->specification.range = num;
}

SDL_Texture* tankTex = NULL;
bool Tank::loadTextures(SDL_Renderer* renderer, const char* spriteSheetPath)
{
    SDL_Surface* spriteSheet = IMG_Load(spriteSheetPath);
    if(spriteSheet == NULL)
    	return false;

    // Tạo frame cho thân
    for (int i = 0; i < FrameNumber; i++) {
        SDL_Rect frame = { i * spriteSheet->w / FrameNumber, 0, TANK_WIDTH, TANK_HEIGHT };
        bodyFrames.push_back(frame);
    }

    // Tạo frame cho đầu
    for (int i = 0; i < FrameNumber; i++) {
        SDL_Rect frame = { i * spriteSheet->w / FrameNumber, TANK_HEIGHT, TANK_WIDTH, TANK_HEIGHT };
        headFrames.push_back(frame);
    }
    SDL_Texture* spriteSheetTex = SDL_CreateTextureFromSurface(renderer, spriteSheet);
    SDL_FreeSurface(spriteSheet);
    maxFrames = 4;
    currentFrame = 0;

    /* gán texture cho texInMatch*/
    tankTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TANK_WIDTH, TANK_HEIGHT);
    if(tankTex == NULL)
    {
    	cout << "Error at tank.cpp. Failed to create texture: " << SDL_GetError() << endl;
    	return false;
    }
    SDL_SetTextureBlendMode(tankTex, SDL_BLENDMODE_BLEND);
    	// set target thành tankTex
    if(SDL_SetRenderTarget(renderer, tankTex) < 0)
    {
    	cout << "Error at tank.cpp. Failed to set render target: " << SDL_GetError() << endl;
    	return false;
    }
    
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, spriteSheetTex, &bodyFrames.at(STATIC), NULL);
    SDL_RenderCopy(renderer, spriteSheetTex, &headFrames.at(STATIC), NULL);
    SDL_DestroyTexture(spriteSheetTex);
    	//render vào tankTex
    SDL_RenderPresent(renderer);
    this->texInMatch = tankTex;

    	//chuyển target về màn hình
    SDL_SetRenderTarget(renderer, NULL);
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
    
}

void Tank::move(int mapWidth, int mapHeight)
{
    posX += velX;
    //If the tank went too far to the left or right
    if( ( posX < 0 ) || ( posX + TANK_WIDTH > mapWidth ) )
    {
        //Move back
        posX -= velX;
    }
    posY += velY;

    //If the tank went too far up or down
    if( ( posY < 0 ) || ( posY + TANK_HEIGHT > mapHeight ) )
    {
        //Move back
        posY -= velY;
    }
}

void Tank::update()
{
    currentFrame++;
    if (currentFrame >= maxFrames)
    {
        currentFrame = 0; // Quay về frame đầu tiên sau khi kết thúc animation
    }
}

void Tank::clean()
{
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(texInMatch);
    //hủy các texture toàn cục
    SDL_DestroyTexture(tankTex);
}