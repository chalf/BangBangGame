#include "Utils.hpp"

const char* bbg::TITLE = "BangBang v1.0";

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

bool bbg::checkCollision(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b)
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

void bbg::deinitialize()
{
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}