#include "Utils.hpp"

vector<SDL_Rect> colliders::pegasusColliders()
{
	vector<SDL_Rect> pegasusColl = {};
	pegasusColl.resize(9);
	pegasusColl[ 0 ].w = 1;
    pegasusColl[ 0 ].h = 7;

    pegasusColl[ 1 ].w = 8;
    pegasusColl[ 1 ].h = 5;

    pegasusColl[ 2 ].w = 19;
    pegasusColl[ 2 ].h = 8;

    pegasusColl[ 3 ].w = 35;
    pegasusColl[ 3 ].h = 9;

    pegasusColl[ 4 ].w = 50;
    pegasusColl[ 4 ].h = 20;

    pegasusColl[ 5 ].w = 54;
    pegasusColl[ 5 ].h = 24;

    pegasusColl[ 6 ].w = 29;
    pegasusColl[ 6 ].h = 4;

    pegasusColl[ 7 ].w = 24;
    pegasusColl[ 7 ].h = 7;

    pegasusColl[ 8 ].w = 1;
    pegasusColl[ 8 ].h = 6;
    return pegasusColl;
}

vector<SDL_Rect> colliders::pegasusBulletColliders()
{
    vector<SDL_Rect> bulletColl = {};
    bulletColl.push_back({0, 0, 37, 17});
    return bulletColl;
}