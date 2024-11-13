#include "Game.hpp"

void Game::renderHealthBar(Tank* tank, int viewportX, int viewportY) 
{
    // Kích thước của thanh máu
    int barWidth = TANK_WIDTH - 10;
    int barHeight = 10;
    int barPosX = static_cast<int>(tank->getPosX() + 5) - viewportX;
     //vì barwidth = tank width -10, nên +5 để ở giữa (mỗi bên dư ra 5 là 10)
    int barPosY = static_cast<int>(tank->getPosY() + TANK_HEIGHT + 5) - viewportY; // Đặt dưới tank

    // Tính toán chiều dài của thanh HP hiện tại
    //barWidth --> maxHP
    //currentBarWidth =?  --->     currentHP   (nhân chéo chia đối)
    int currentBarWidth = static_cast<int>(tank->currentHP * barWidth / tank->getSpecification().HP);

    // Vẽ thanh HP nền (màu đen)
    SDL_Rect healthBarBG = { barPosX, barPosY, barWidth, barHeight };
    SDL_SetRenderDrawColor(renderer, 32, 41, 44, 255); // Màu đỏ
    SDL_RenderFillRect(renderer, &healthBarBG);

    // Vẽ thanh HP hiện tại
    SDL_Rect healthBarFG = { barPosX, barPosY, currentBarWidth, barHeight };
    // Kiểm tra nếu tank là đồng đội hoặc kẻ địch
    if (tank->getTeamId() == team.at(0).getId()) 
        // Màu xanh lá cho đồng đội
        SDL_SetRenderDrawColor(renderer, 39, 143, 55, 255);
    else
        // Màu đỏ cho kẻ địch
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBarFG);
}

void Game::registerAllTankBehaviors() 
{
    // TankBehaviorFactory& factory = TankBehaviorFactory::getInstance();
    // factory.registerTankBehavior(PEGASUS, []() { return new PegasusBehavior(); });
    // Đăng ký thêm các loại tank khác ở đây
}


Game::Game(const char* p_title, int p_w, int p_h) : RenderWindow( p_title, p_w, p_h )
{
	running = false;
	if(window != NULL && renderer != NULL)
		running = true;
    Team team1(1);
    Team team2(2);
    team.push_back(team1);
    team.push_back(team2);
}

Game::~Game()
{

}

bool Game::isRunning() { return running; }

void Game::startGame()
{
    if(loadMaps() == false)
        cout << "Failed to load maps: " << SDL_GetError() << endl;
    if(loadTanks() == false)
        cout << "Failed to load tanks: " << SDL_GetError() << endl;
}

void Game::drawPlayButton(SDL_Rect buttonRect)
{
    SDL_Texture* bg = IMG_LoadTexture(renderer, "res/gfx/background.png");
    int imgWidth = 875;
    int imgHeight = 500;
    SDL_Rect bgRect = {(bbg::SCREEN_WIDTH - imgWidth) / 2, (bbg::SCREEN_HEIGHT - imgHeight) / 2, imgWidth, imgHeight};
    SDL_SetRenderDrawColor(renderer, 255, 208, 86, 255); //màu vàng làm màu nền cho hình ảnh background
    fill_renderer();
    SDL_RenderCopy(renderer, bg, NULL, &bgRect);

    // Vẽ hình chữ nhật
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
    SDL_RenderFillRect(renderer, &buttonRect);

    // Vẽ hình tam giác bên trong nút
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Màu vàng

    // Tạo tọa độ cho 3 điểm của tam giác
    SDL_Point points[4];
    points[0] = {buttonRect.x + buttonRect.w / 4, buttonRect.y + buttonRect.h / 4};
    points[1] = {buttonRect.x + buttonRect.w / 4, buttonRect.y + 3 * buttonRect.h / 4};
    points[2] = {buttonRect.x + 3 * buttonRect.w / 4, buttonRect.y + buttonRect.h / 2};
    points[3] = points[0]; // Điểm cuối khép kín tam giác

    // Vẽ tam giác
    SDL_RenderDrawLines(renderer, points, 4);

    SDL_DestroyTexture(bg);
}

bool Game::isReplayButtonClicked(SDL_Event& event, SDL_Rect buttonRect) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // Kiểm tra xem chuột có nằm trong nút "Chơi lại" không
        if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
            return true;
        }
    }
    return false;
}

void Game::showReplayMenu(GameState& currentState)
{
    SDL_Rect replayButtonRect = {bbg::SCREEN_WIDTH/2 - 160/2, 540, 160, 80}; // Vị trí và kích thước nút "Chơi lại"

    // Vòng lặp hiển thị menu "Chơi lại"
    bool quitMenu = false;
    SDL_Event event;
    while (!quitMenu) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                quitMenu = true;
                this->running = false;
                break;
            }

            // Kiểm tra nếu nút "Chơi lại" được nhấn
            if (isReplayButtonClicked(event, replayButtonRect)) 
            {
                // thoát khỏi vòng lặp để vào game loop
                quitMenu = true;
            }
        }

        // Vẽ nút "Chơi lại"
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu nền đen
        SDL_RenderClear(renderer);
        drawPlayButton(replayButtonRect);
        SDL_RenderPresent(renderer);
    }
}

bool Game::loadMaps()
{
	Map* hoang_da_dai_dia = new ScoreMap(1800, 1440, SCORE, colliders::hoangDaDaiDiaColliders(), spawnpoint::hoangDaDaiDiaSpawnPoint());
	// load các layer của map
	if (!hoang_da_dai_dia->loadLayer(renderer, "res/gfx/map/HoangDaDaiDia_background.png", BACKGROUND) ||
        !hoang_da_dai_dia->loadLayer(renderer, "res/gfx/map/HoangDaDaiDia_obstacle.png", OBSTACLE) ||
        !hoang_da_dai_dia->loadLayer(renderer, "res/gfx/map/HoangDaDaiDia_floating.png", FLOATING) )
    {
        return false;
    }
    else
    {
    	mapList.push_back(hoang_da_dai_dia);
    	//camera scrolling
    	int mapWidth = mapList.front()->getWidth();
	    int mapHeight = mapList.front()->getHeight();
	    camera = std::make_unique<Camera>(mapWidth, mapHeight, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT);
    	
		return true;
    }
}

bool Game::loadTanks()
{
    //khởi tạo vị trí cho team.at(0)
    team.at(0).spawnSide = bbg::randomSpawnSide();
    vector<SDL_Point> spawnPos = bbg::randomSpawnPos(team.at(0).spawnSide, mapList.front()->getSpawnPoints());
    unsigned int spawnPosIndex = 0;
    // tạo tank cho người chơi
    Tank* player = new PlayerTank(bbg::tankCollection.at(PEGASUS).name, bbg::tankCollection.at(PEGASUS).strength, bbg::tankCollection.at(PEGASUS).type, bbg::tankCollection.at(PEGASUS).spec, spawnPos.at(spawnPosIndex).x, spawnPos.at(spawnPosIndex).y, bbg::tankCollection.at(PEGASUS).colliders);
    player->setTeamId(team.at(0).getId());
    
	if( !player->loadTextures(renderer, bbg::tankCollection.at(PEGASUS).spriteSheetPath, bbg::tankCollection.at(PEGASUS).bulletImagePath) )
		return false;
	team.at(0).tanks.push_back(player);
    // tạo 2 tankbot đồng đội của người chơi, spawnSide.size() - 1 là vì gán front() cho player rồi
    for (int i = 1; i <= 2 && spawnPosIndex <= spawnPos.size() - 1; ++i) 
    {
        spawnPosIndex++;
        int randomTank = bbg::randomTank();
        Tank* botTank = new BotTank(bbg::tankCollection.at(randomTank).name, bbg::tankCollection.at(randomTank).strength, bbg::tankCollection.at(randomTank).type, bbg::tankCollection.at(randomTank).spec, spawnPos.at(spawnPosIndex).x, spawnPos.at(spawnPosIndex).y, bbg::tankCollection.at(randomTank).colliders);
        botTank->setTeamId(team.at(0).getId());

        if( !botTank->loadTextures(renderer, bbg::tankCollection.at(randomTank).spriteSheetPath, bbg::tankCollection.at(randomTank).bulletImagePath) )
            return false;
        team.at(0).tanks.push_back(botTank);
    }

    //TẠO 3 TANKBOT CHO TEAM ĐỊCH - team.at(1)
    spawnPosIndex = 0;  //khởi tạo lại vị trí để truy cập spawnPos từ đầu
    team.at(1).spawnSide = !team.at(0).spawnSide;   //team còn lại sẽ ở phía đối diện
    spawnPos = bbg::randomSpawnPos(team.at(1).spawnSide, mapList.front()->getSpawnPoints());
    for(int i = 0; i < 3 && spawnPosIndex < spawnPos.size(); i++)
    {
        int randomTank = bbg::randomTank();
        Tank* botTank = new BotTank(bbg::tankCollection.at(randomTank).name, bbg::tankCollection.at(randomTank).strength, bbg::tankCollection.at(randomTank).type, bbg::tankCollection.at(randomTank).spec, spawnPos.at(spawnPosIndex).x, spawnPos.at(spawnPosIndex).y, bbg::tankCollection.at(randomTank).colliders);
        botTank->setTeamId(team.at(1).getId());

        if( !botTank->loadTextures(renderer, bbg::tankCollection.at(randomTank).spriteSheetPath, bbg::tankCollection.at(randomTank).bulletImagePath) )
            return false;
        team.at(1).tanks.push_back(botTank);
        spawnPosIndex++;
    }
    return true;
}

void Game::render()
{	
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
        RenderWindow::render(mapList.front()->getMapLayerArray()[layer], &src, &dest);
    }
	//map hoang da dai dia (60, 160) la ra khoi obstacle
	// Render tank, điều chỉnh vị trí của nó dựa trên viewport
	/*tức là posX - viewport.x = số px trục x từ cửa sổ đến tank, vì viewport.x có giá trị bằng từ cạnh trái của map đến viền trái của camera (tức là phần khuất bên trái của map khi render lên cửa sổ)*/
    SDL_Rect tankSize = {
        (int)team.at(0).tanks.front()->getPosX() - viewport.x,
        (int)team.at(0).tanks.front()->getPosY() - viewport.y,
        TANK_WIDTH,
        TANK_HEIGHT
    };
    renderEx(team.at(0).tanks.front()->getBodyTex(), NULL, &tankSize, team.at(0).tanks.front()->getBodyAngle(), NULL);
    renderEx(team.at(0).tanks.front()->getHeadTex(), NULL, &tankSize, team.at(0).tanks.front()->getHeadAngle(), NULL);
    //nếu người chơi bấm nút bắn -> lúc đó mới render đạn
    if( team.at(0).tanks.front()->getBullet()->isActive() && !team.at(0).tanks.front()->getBullet()->isTouch())
    {
    	SDL_Rect bulletRect = team.at(0).tanks.front()->getBullet()->getRect();
    	bulletRect.x -= viewport.x;
    	bulletRect.y -= viewport.y;
    	renderEx(team.at(0).tanks.front()->getBullet()->getTexture(), NULL, &bulletRect, team.at(0).tanks.front()->getBullet()->getAngle(), NULL);
    }
    //render thanh máu
    renderHealthBar(team.at(0).tanks.front(), viewport.x, viewport.y);

    // Render các tank đồng đội
    for (size_t i = 1; i < team.at(0).tanks.size(); ++i) 
    {
        SDL_Rect tankOther = {
            (int)team.at(0).tanks.at(i)->getPosX() - viewport.x,
            (int)team.at(0).tanks.at(i)->getPosY() - viewport.y,
            TANK_WIDTH,
            TANK_HEIGHT
        };
        RenderWindow::render(team.at(0).tanks.at(i)->getBodyTex(), NULL, &tankOther);
        renderHealthBar(team.at(0).tanks.at(i), viewport.x, viewport.y);
    }

    //Render các tank địch
    for (size_t i = 0; i < team.at(1).tanks.size(); ++i) 
    {
        SDL_Rect tankOther = {
            (int)team.at(1).tanks.at(i)->getPosX() - viewport.x,
            (int)team.at(1).tanks.at(i)->getPosY() - viewport.y,
            TANK_WIDTH,
            TANK_HEIGHT
        };
        RenderWindow::render(team.at(1).tanks.at(i)->getBodyTex(), NULL, &tankOther);
        renderHealthBar(team.at(1).tanks.at(i), viewport.x, viewport.y);
    }
    
}

void Game::display()
{
	//render phần FLOATING của map cuối cùng, xong mới gọi display()
	SDL_Rect viewport = camera->getViewport();
	SDL_Rect src = viewport;
    SDL_Rect dest = {0, 0, bbg::SCREEN_WIDTH, bbg::SCREEN_HEIGHT};
    RenderWindow::render(mapList.front()->getMapLayerArray()[FLOATING], &src, &dest);
    RenderWindow::display();
}

void Game::handleEvents(SDL_Event& event)
{
	if(event.type == SDL_QUIT)
	{
		running = false;
		return;
	}
	team.at(0).tanks.front()->handleTankMovement(event);
	
	// sự kiện chuột
	int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    // Chuyển đổi tọa độ chuột từ screen space sang world space bằng phép cộng tọa độ camera
	team.at(0).tanks.front()->rotateHead(mouseX + camera->getViewport().x, mouseY + camera->getViewport().y);
	//sau khi xác định được góc headAngle từ rotateHead() thì lúc này mới xác định góc cho đạn, vì cả 2 đều xoay theo con trỏ chuột
	team.at(0).tanks.front()->handleBulletShooting(event);
}

void Game::update(float deltaTime)
{
	if (!camera) 
		return;
    vector<Tank*> allTanks;
    allTanks.insert(allTanks.end(), team.at(0).tanks.begin(), team.at(0).tanks.end()); // Thêm các tank của team 0
    allTanks.insert(allTanks.end(), team.at(1).tanks.begin(), team.at(1).tanks.end()); // Thêm các tank của team 1

	Tank* playerTank = team.at(0).tanks.front();
	playerTank->move(mapList.front()->getWidth(), mapList.front()->getHeight(), allTanks, mapList.front()->getColliders(), deltaTime );
    /*đạn đang bay hoặc đạn không va chạm, cũng liên tục cập nhật vị trí cho nó
    chỉ là khi đạn trúng vật cản thì sẽ không render mà thôi => đảm bảo tốc độ bắn không thay đổi */
	if(playerTank->getBullet()->isActive() || !playerTank->getBullet()->isTouch())
	{
		playerTank->getBullet()->fly(playerTank->getSpecification().bullet_speed, playerTank->getSpecification().range, team.at(1).tanks, mapList.front()->getColliders(), deltaTime);
        //sau khi ra fly(), xem getHit có phải bị đổi thành true không, lúc đó mới trừ máu
        for(Tank* enemy : team.at(1).tanks)
        {
            if(enemy->m_bGetHit)
            {
                enemy->getHit(playerTank); //trừ máu
                enemy->m_bGetHit = false;
            }
        }
	}

    //TANK BOT
    Tank* enemyBotTank1 = team.at(1).tanks.front();
    // enemyBotTank1->moveTowards({(int)playerTank->getPosX(), (int)playerTank->getPosY()}, deltaTime);
        
    // Update camera position based on tank position: tâm điểm của tank
    camera->update(playerTank->getPosX() + TANK_WIDTH / 2, playerTank->getPosY() + TANK_HEIGHT / 2);
	
}

void Game::destroyAll()
{
	for(long unsigned int mapIndx = 0; mapIndx < mapList.size(); mapIndx++)
	{
		mapList.at(mapIndx)->clean();
	}
    for(long unsigned int teamIndx = 0; teamIndx < team.size(); teamIndx++)
    {
        team.at(teamIndx).clean();
    }
	// hủy window và renderer
	cleanUp();
}

