#include "PlayerTank.hpp"

PlayerTank::PlayerTank(string name, Strength strength, TankType type, Specification spec, int x, int y, vector<SDL_Rect> tankCollider)
: Tank(name, strength, type, spec, x, y, tankCollider)
{
}

void PlayerTank::rotateHead(int mouseX, int mouseY)
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
void PlayerTank::handleTankMovement(SDL_Event& e)
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

void PlayerTank::move(int mapWidth, int mapHeight, vector<Tank*> tanks, vector<SDL_Rect> mapColliders, float deltaTime)
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
    if ((posX < 0) || (posX + TANK_WIDTH > mapWidth) || bbg::checkCollision(mColliders, mapColliders))
    {
        posX = newPosX - velX * deltaTime;
        velX = 0; // Dừng chuyển động theo trục X nếu va chạm
    }

    // Kiểm tra va chạm theo trục Y
    posY = newPosY;
    shiftColliders();
    if ((posY < 0) || (posY + TANK_HEIGHT > mapHeight) || bbg::checkCollision(mColliders, mapColliders))
    {
        posY = newPosY - velY * deltaTime;
        velY = 0; // Dừng chuyển động theo trục Y nếu va chạm
    }

    shiftColliders();
}


void PlayerTank::handleBulletShooting(SDL_Event& event)
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