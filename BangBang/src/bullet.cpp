#include "Bullet.hpp"

void Bullet::loadTexture(SDL_Renderer* renderer, std::string path)
{
    this->texture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "At bullet.cpp: Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        this->texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( this->texture == NULL )
        {
            printf( "At bullet.cpp: Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            this->rect.w = loadedSurface->w;
            this->rect.h = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
}

void Bullet::shiftColliders()
{
    int r = 0;
    for (SDL_Rect& collider : colliders) {
        collider.x = rect.x + (rect.w - collider.w) / 2;
        collider.y = rect.y + r;
        r += collider.h;
    }
}

Bullet::Bullet(SDL_Renderer* renderer, std::string imagePath, std::vector<SDL_Rect> colliders)
{
    active = false;
    touch = false;
    rect = {0, 0, 0, 0};
    loadTexture(renderer, imagePath);
    this->colliders = colliders;
    wasShot = false;
}

void Bullet::fly(const int bulletSpeed, const int range, Tank* enemyTank, std::vector<SDL_Rect> mapColliders, float deltaTime)
{   
    if(active == true)    //nếu đạn đang bay và không có chạm vào vật cản
    {
        float angleRad = angle * M_PI / 180.0f; //chuyển sang radian
        float dx = cos(angleRad) * bulletSpeed * deltaTime;
        float dy = sin(angleRad) * bulletSpeed * deltaTime;
        rect.x += dx;
        rect.y += dy;
        shiftColliders();
        //nếu đạn trúng tank địch, và trúng lần đầu (ở mỗi lần bắn) lúc này wasShot = false
        if(bbg::checkCollision(this->colliders, enemyTank->getColliders()) && !wasShot)
        {
            touch = true;
            enemyTank->m_bGetHit = true;
            wasShot = true;
        }
    /*vì đạn sẽ liên tục cập nhật vị trí cho dù gặp vật cản cho tới khi đi hết tầm (mặc dù không render, để đảm bảo tốc độ bắn)
        nên wasShot = true nếu trong 2 trường hợp dưới đúng, 
        tức là lúc đó đạn đã bay qua các rect của tank địch*/
        
        //nếu chạm vật cản trên map
        if(bbg::checkCollision(this->colliders, mapColliders))
        {
            touch = true;
            wasShot = false;
        }
        //nếu vượt quá tầm bắn
        if(bbg::distanceBetweenTwoPoint({initPosX, initPosY}, {rect.x, rect.y}) >= range*1.0)
        {
            active = false;
            wasShot = false;
        }
    }
}

void Bullet::clean()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* Bullet::getTexture()
{
	return texture;
}

bool Bullet::isActive()
{
    return active;
}

void Bullet::setActive(bool flag)
{
    active = flag;
}

bool Bullet::isTouch()
{
    return touch;
}

void Bullet::setTouch(bool flag)
{
    touch = flag;
}

SDL_Rect Bullet::getRect()
{
    return rect;
}

void Bullet::setRect(SDL_Rect rect)
{
    this->rect = rect;
}

void Bullet::setInitPos(int x, int y)
{
    initPosX = x;
    initPosY = y;
}

int Bullet::getWidth()
{
    return rect.w;
}

int Bullet::getHeight()
{
    return rect.h;
}

float Bullet::getAngle()
{
    return angle;
}

void Bullet::setAngle(float angle)
{
    this->angle = angle;
}

std::vector<SDL_Rect>& Bullet::getColliders()
{
    return colliders;
}
