#include "Utils.hpp"

Specification::Specification()
{   //các con số ngẫu nhiên
    HP = 500;
    dps = 153;
    piercing = 73;
    physical_armor = 111;
    energy_shield = 99;
    bullet_speed = 400;
    range = 415;
    movement_speed = 100;
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

const char* bbg::TITLE = "BangBang v1.0";

vector<TankInfo> bbg::tankCollection = {};
void bbg::loadTankCollection()
{
    // TANKCOLLECTION = PEGASUS
    TankInfo pegasus = {"Pegasus", DPS, ENERGY, spec::SPEC_Pegasus(), colliders::pegasusColliders(), "res/gfx/tank/pegasus.png", "res/gfx/tank/pegasus_bullet.png"};
    bbg::tankCollection.push_back(pegasus);
    // TANKCOLLECTION = GUNDAM
}

bool bbg::init_SDL()
{
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		return false;
	}
	return true;
}

//khởi tạo SDL_image cho định dạng JPG
bool bbg::init_SDL_image_JPG()
{
	if( IMG_Init( IMG_INIT_JPG ) == 0 )
	{
		return false;
	}
	return true;
}

//khởi tạo SDL_image cho định dạng PNG
bool bbg::init_SDL_image_PNG()
{
	if( IMG_Init(IMG_INIT_PNG) == 0 )
		return false;

	return true;
}

//khởi tạo SDL_mixer
bool bbg::init_SDL_mixer()
{
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) == -1 )
		return false;
	return true;
}

//khởi tạo SDL_ttf
bool bbg::init_SDL_ttf()
{
	if( TTF_Init() == -1)
		return false;
	return true;
}

bool bbg::loadTextureFromFile(SDL_Renderer* renderer, const char* path, SDL_Texture*& texture)
{
    texture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
        cout << "At utils.cpp: Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( texture == NULL )
        {
            cout << "At utils.cpp: Unable to create texture from " << path << "! SDL Error: " <<SDL_GetError() << endl;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return texture != NULL;
}

bool bbg::checkCollision( std::vector<SDL_Rect>& a,  std::vector<SDL_Rect>& b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    //Go through the A boxes
    for( long unsigned int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;
        //Go through the B boxes
        for( long unsigned int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //Calculate the sides of rect B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            //If no sides from A are outside of B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //A collision is detected
                return true;
            }
        }
    }

    //If neither set of collision boxes touched
    return false;
}

float bbg::distanceBetweenTwoPoint(SDL_Point p1, SDL_Point p2)
{
    return sqrt( pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) );
}

int bbg::damageTaken(int dpsOfEnemy, int piercingOfEnemy, int armorOrShield)
{
    /* 100 đóng vai trò là một hằng số để chuẩn hóa phép tính. 
    Để đảm bảo rằng sát thương giảm dần một cách hợp lý khi giáp hoặc kháng phép của đối thủ tăng lên*/
    float damageTakenCal = dpsOfEnemy * 100 / ( 100 + armorOrShield - piercingOfEnemy );
    return round(damageTakenCal); //hàm làm tròn số trong <cmath>
}

int bbg::randomTank()
{
    // Tạo số ngẫu nhiên từ 0 đến TankInfo size - 1
    int random_number = rand() % bbg::tankCollection.size();
    return random_number;
}

bool bbg::randomSpawnSide()
{
    if(rand() % 2 == 0) //random từ 0 đến 1
    {
        return true;
    }
    else
        return false;
}

vector<SDL_Point> bbg::randomSpawnPos(bool side, vector<SDL_Point> spawnPoints)
{
    auto mid = spawnPoints.begin() + spawnPoints.size() / 2;
    vector<SDL_Point> spVector;
    if (side) // Bên trái
    {  
        spVector = vector<SDL_Point>(spawnPoints.begin(), mid);
    } 
    else // Bên phải
    {  
        spVector = vector<SDL_Point>(mid, spawnPoints.end());
    }

    // Xáo trộn vị trí của spVector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(spVector.begin(), spVector.end(), gen);

    return spVector;
}

void bbg::initRandomSeed()
{
    // Sử dụng thời gian hiện tại làm hạt giống để tạo dãy số ngẫu nhiên khác nhau mỗi lần gọi hàm
    srand(time(0));
}

void bbg::deinitialize()
{
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}