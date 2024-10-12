#include "Game.hpp"

Game::Game(const char* p_title, int p_w, int p_h) : RenderWindow( p_title, p_w, p_h )
{
	running = false;
	if(window != NULL && renderer != NULL)
		running = true;
}

Game::~Game()
{

}

std::vector<Map> Game::getMapList()
{
	return mapList;
}

std::vector<Tank>& Game::getTankList()
{
	return tankList;
}

bool Game::isRunning() { return running; }

bool Game::loadMaps()
{
	Map hoang_da_dai_dia(1800, 1440, colliders::hoangDaDaiDiaColliders());
	// load các layer của map
	if (!hoang_da_dai_dia.loadLayer(renderer, "res/gfx/map/HoangDaDaiDia_background.png", BACKGROUND) ||
        !hoang_da_dai_dia.loadLayer(renderer, "res/gfx/map/HoangDaDaiDia_obstacle.png", OBSTACLE) ||
        !hoang_da_dai_dia.loadLayer(renderer, "res/gfx/map/HoangDaDaiDia_floating.png", FLOATING) )
    {
        return false;
    }
    else
    {
    	mapList.push_back(hoang_da_dai_dia);
    	//camera scrolling
    	int mapWidth = mapList.front().getWidth();
	    int mapHeight = mapList.front().getHeight();
	    camera = std::make_unique<Camera>(mapWidth, mapHeight, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT);
    	
		return true;
    }
}

bool Game::loadTanks()
{
	Tank pegasus(DPS, PHYSICAL, 65, 162, colliders::pegasusColliders()); //vị trí không bị vướng vật cản trên bản đồ
	if( !pegasus.loadTextures(renderer, "res/gfx/tank/pegasus.png", "res/gfx/tank/pegasus_bullet.png") )
		return false;
	pegasus.set_movement_speed(120);
	tankList.push_back(pegasus);

	//TEST
	Tank gundam(DPS, PHYSICAL, 65, 600, colliders::pegasusColliders());
	gundam.loadTextures(renderer, "res/gfx/tank/pegasus.png", "res/gfx/tank/pegasus_bullet.png");
	tankList.push_back(gundam);
	return true;
}

void Game::render()
{	cout << "render\n";
	if (!camera) 
		return;
	//lấy viewport (nó có tọa độ của camera) hiện tại của camera
	SDL_Rect viewport = camera->getViewport();
	// Render map layers
    for (int layer = 0; layer < MAPLAYERS; ++layer) 
    {
    	//nếu như render đến lớp FLOATING thì bỏ qua (không render), nó sẽ được render ở display()
    	if(layer == FLOATING)
    		continue;
        SDL_Rect src = viewport;
        SDL_Rect dest = {0, 0, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT};
        // truyền src vô: chỉ phần map nằm trong viewport mới được render
        RenderWindow::render(mapList.front().getMapLayerArray()[layer], &src, &dest);
    }
	//map hoang da dai dia (60, 160) la ra khoi obstacle
	// Render tank, điều chỉnh vị trí của nó dựa trên viewport
	/*tức là posX - viewport.x = số px trục x từ cửa sổ đến tank, vì viewport.x có giá trị bằng từ cạnh trái của map đến viền trái của camera (tức là phần khuất bên trái của map khi render lên cửa sổ)*/
    SDL_Rect tankSize = {
        (int)tankList.front().getPosX() - viewport.x,
        (int)tankList.front().getPosY() - viewport.y,
        TANK_WIDTH,
        TANK_HEIGHT
    };
    renderEx(tankList.front().getBodyTex(), NULL, &tankSize, tankList.front().getBodyAngle(), NULL);
    renderEx(tankList.front().getHeadTex(), NULL, &tankSize, tankList.front().getHeadAngle(), NULL);
    //nếu người chơi bấm nút bắn -> lúc đó mới render đạn
    if( tankList.front().getBullet()->isActive() && !tankList.front().getBullet()->isTouch())
    {
    	SDL_Rect bulletRect = tankList.front().getBullet()->getRect();
    	bulletRect.x -= viewport.x;
    	bulletRect.y -= viewport.y;
    	renderEx(tankList.front().getBullet()->getTexture(), NULL, &bulletRect, tankList.front().getBullet()->getAngle(), NULL);
    }
    //render thanh máu
    renderHealthBar(&tankList.front(), viewport.x, viewport.y);

    //TEST, Render các tank khác
    for (size_t i = 1; i < tankList.size(); ++i) 
    {
        SDL_Rect tankOther = {
            (int)tankList[i].getPosX() - viewport.x,
            (int)tankList[i].getPosY() - viewport.y,
            TANK_WIDTH,
            TANK_HEIGHT
        };
        RenderWindow::render(tankList[i].getBodyTex(), NULL, &tankOther);
    }
}

void Game::renderHealthBar(Tank* tank, int viewportX, int viewportY) 
{
    // Kích thước của thanh máu
    int barWidth = TANK_WIDTH - 10;
    int barHeight = 10;
    int barPosX = static_cast<int>(tank->getPosX() + 5) - viewportX;
     //vì barwidth = tank width -10, nên +5 để ở giữa (mỗi bên dư ra 5 là 10)
    int barPosY = static_cast<int>(tank->getPosY() + TANK_HEIGHT + 5) - viewportY; // Đặt dưới tank

    // Tính toán chiều rộng của thanh HP hiện tại
    //barWidth --> maxHP
    //currentBarWidth =?  --->     currentHP   (nhân chéo chia đối)
    tank->currentHP = 455;
    int currentBarWidth = static_cast<int>(tank->currentHP * barWidth / tank->getSpecification().HP);

    // Vẽ thanh HP nền (màu đen)
    SDL_Rect healthBarBG = { barPosX, barPosY, barWidth, barHeight };
    SDL_SetRenderDrawColor(renderer, 32, 41, 44, 255); // Màu đỏ
    SDL_RenderFillRect(renderer, &healthBarBG);

    // Vẽ thanh HP hiện tại (màu xanh lá)
    SDL_Rect healthBarFG = { barPosX, barPosY, currentBarWidth, barHeight };
    SDL_SetRenderDrawColor(renderer, 39, 143, 55, 255); // Màu xanh lá
    SDL_RenderFillRect(renderer, &healthBarFG);
}

void Game::display()
{
	//render phần FLOATING của map cuối cùng, xong mới gọi display()
	SDL_Rect viewport = camera->getViewport();
	SDL_Rect src = viewport;
    SDL_Rect dest = {0, 0, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT};
    RenderWindow::render(mapList.front().getMapLayerArray()[FLOATING], &src, &dest);
    RenderWindow::display();
}

void Game::handleEvents(SDL_Event& event)
{
	if(event.type == SDL_QUIT)
	{
		running = false;
		return;
	}
	this->getTankList().front().handleTankMovement(event);
	
	// sự kiện chuột
	int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    // Chuyển đổi tọa độ chuột từ screen space sang world space bằng phép cộng tọa độ camera
	this->getTankList().front().rotateHead(mouseX + camera->getViewport().x, mouseY + camera->getViewport().y);
	//sau khi xác định được góc headAngle từ rotateHead() thì lúc này mới xác định góc cho đạn, vì cả 2 đều xoay theo con trỏ chuột
	this->getTankList().front().handleBulletShooting(event);
}

void Game::update(float deltaTime)
{
    cout << "Game::update\n";
	if (!camera) 
		return;
	Tank& tank = tankList.front();
	tank.move(mapList.front().getWidth(), mapList.front().getHeight(), tankList.at(1).getColliders(), mapList.front().getColliders(), deltaTime );
    /*đạn đang bay hoặc đạn không va chạm, cũng liên tục cập nhật vị trí cho nó
    chỉ là khi đạn trúng vật cản thì sẽ không render mà thôi => đảm bảo tốc độ bắn không thay đổi */
	if(tank.getBullet()->isActive() || !tank.getBullet()->isTouch())
	{
		tank.getBullet()->fly(tank.getSpecification().bullet_speed, tank.getSpecification().range, tankList.at(1).getColliders(), mapList.front().getColliders(), deltaTime);
	}
        
    // Update camera position based on tank position: tâm điểm của tank
    camera->update(tank.getPosX() + TANK_WIDTH / 2, tank.getPosY() + TANK_HEIGHT / 2);
	
}

void Game::destroyAll()
{
	for(long unsigned int mapIndx = 0; mapIndx < mapList.size(); mapIndx++)
	{
		mapList.at(mapIndx).clean();
	}
	for(long unsigned int tankIndx = 0; tankIndx < tankList.size(); tankIndx++)
	{
		tankList.at(tankIndx).clean();
	}
	// hủy window và renderer
	cleanUp();
}

