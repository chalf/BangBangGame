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

vector<SDL_Rect> colliders::hoangDaDaiDiaColliders()
{
    vector<SDL_Rect> hdddColl = {};
    //phần viền trên
    hdddColl.push_back({0,   0,  537, 159});
    hdddColl.push_back({540, 0,  10,  153});
    hdddColl.push_back({550, 0,  10,  149});
    hdddColl.push_back({560, 0,  10,  148});
    hdddColl.push_back({570, 0,  10,  145});
    hdddColl.push_back({580, 0,  10,  144});
    hdddColl.push_back({590, 0,  10,  142});
    hdddColl.push_back({600, 0,  10,  137});
    hdddColl.push_back({610, 0,  10,  134});
    hdddColl.push_back({620, 0,  10,  129});
    hdddColl.push_back({630, 0,  10,  125});
    hdddColl.push_back({640, 0,  10,  121});
    hdddColl.push_back({650, 0,  10,  117});
    hdddColl.push_back({660, 0,  10,  115});
    hdddColl.push_back({670, 0,  10,  111});
    hdddColl.push_back({680, 0,  10,  111});
    hdddColl.push_back({690, 0,  10,  109});
    hdddColl.push_back({700, 0,  10,  105});
    hdddColl.push_back({710, 0,  10,  101});
    hdddColl.push_back({720, 0,  10,  96 });
    hdddColl.push_back({730, 0,  10,  92 });
    hdddColl.push_back({740, 0,  10,  85 });
    hdddColl.push_back({750, 0,  10,  81 });
    hdddColl.push_back({760, 0,  10,  77 });
    hdddColl.push_back({770, 0,  10,  75 });
    hdddColl.push_back({780, 0,  10,  72 });
    hdddColl.push_back({790, 0,  10,  71 });
    hdddColl.push_back({800, 0,  10,  70 });
    hdddColl.push_back({810, 0,  10,  68 });
    hdddColl.push_back({820, 0,  10,  65 });
    hdddColl.push_back({830, 0,  10,  64 });
    hdddColl.push_back({840, 0,  134, 64 });
    hdddColl.push_back({975, 0,  755, 64 });
    
    return hdddColl;
}

vector<SDL_Rect> colliders::pegasusBulletColliders()
{
    vector<SDL_Rect> bulletColl = {};
    bulletColl.push_back({0, 0, 37, 17});
    return bulletColl;
}