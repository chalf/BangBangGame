#include "Utils.hpp"

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
    //phần viền trái
    hdddColl.push_back({0,   160,60,  1050 });
    //phần viền dưới
    hdddColl.push_back({0,   1211,  740, 230 });
    hdddColl.push_back({745, 1320,  15,  120 });
    hdddColl.push_back({760, 1322,  5,   117 });
    hdddColl.push_back({765, 1325,  5,   115 });
    hdddColl.push_back({770, 1333,  5,   106 });
    hdddColl.push_back({775, 1340,  5,   100 });
    hdddColl.push_back({780, 1345,  5,   95 });
    hdddColl.push_back({785, 1351,  5,   88 });
    hdddColl.push_back({790, 1356,  5,   84 });
    hdddColl.push_back({795, 1358,  10,  82 });
    hdddColl.push_back({805, 1362,  10,  78 });
    hdddColl.push_back({815, 1366,  10,  74 });
    hdddColl.push_back({825, 1372,  5,   68 });
    hdddColl.push_back({830, 1379,  5,   60 });
    hdddColl.push_back({835, 1385,  5,   55 });
    hdddColl.push_back({840, 1390,  5,   50 });
    hdddColl.push_back({845, 1394,  10,  46 });
    hdddColl.push_back({855, 1400,  10,  40 });
    hdddColl.push_back({865, 1402,  10,  38 });
    hdddColl.push_back({875, 1405,  10,  35 });
    hdddColl.push_back({885, 1407,  10,  33 });
    hdddColl.push_back({895, 1410,  10,  30 });
    hdddColl.push_back({905, 1412,  12,  28 });
    hdddColl.push_back({917, 1412,  23,  28 });
    hdddColl.push_back({940, 1416,  10,  26 });
    hdddColl.push_back({950, 1422,  10,  18 });
    hdddColl.push_back({960, 1423,  285, 16 });
    hdddColl.push_back({1245,1340,  125, 100 });
    hdddColl.push_back({1370,1367,  375, 70 });
    //phần viền phải
    hdddColl.push_back({1730,65,    70,  210 });
    hdddColl.push_back({1555,315,   5,   100 });
    hdddColl.push_back({1560,302,   5,   113 });
    hdddColl.push_back({1565,290,   35,  120 });
    hdddColl.push_back({1600,295,   50,  117 });
    hdddColl.push_back({1650,290,   10,  140 });
    hdddColl.push_back({1660,288,   10,  152 });
    hdddColl.push_back({1670,282,   60,  298 });
    hdddColl.push_back({1730,282,   70,  300 });
    hdddColl.push_back({1760,582,   40,  93 });
    hdddColl.push_back({1770,675,   30,  150 });
    hdddColl.push_back({1760,825,   40,  25 });
    hdddColl.push_back({1746,850,   54,  517 });
    //khúc cây
    hdddColl.push_back({1590,725,   60,  45 });
    hdddColl.push_back({1650,730,   45,  40 });
    //cái chòi bằng xương
    hdddColl.push_back({1220,470,   78,  20 });
    hdddColl.push_back({1208,494,   112, 32 });
    hdddColl.push_back({1202,525,   108, 70 });
    hdddColl.push_back({1200,599,   120, 36 });
    hdddColl.push_back({1125,640,   210, 25 });
    hdddColl.push_back({1080,665,   285, 105 });
    hdddColl.push_back({1095,770,   240, 35 });
    hdddColl.push_back({1150,810,   170, 20 });
    hdddColl.push_back({1175,835,   135, 40 });
    hdddColl.push_back({1185,880,   115, 15 });
    hdddColl.push_back({1205,900,   75,  10 });
    //cục đá
    hdddColl.push_back({1010, 290,  10,  33 });
    hdddColl.push_back({1020, 283,  38,  39 });
    hdddColl.push_back({1050, 247,  10,  37 });
    hdddColl.push_back({1060, 230,  105, 94 });
    hdddColl.push_back({1010, 323,  112, 15 });
    hdddColl.push_back({1125, 323,  30,  12 });
    hdddColl.push_back({1166, 236,  10,  88 });
    //bộ xương thú có sừng
    hdddColl.push_back({275, 400,   20, 50 });
    hdddColl.push_back({295, 400,   199,50 });
    hdddColl.push_back({495, 355,   71, 99 });
    hdddColl.push_back({512, 322,   313,28 });
    hdddColl.push_back({571, 352,   234,13 });
    hdddColl.push_back({525, 305,   30, 15 });
    hdddColl.push_back({557, 288,   33, 32 });
    hdddColl.push_back({592, 294,   18, 26 });
    hdddColl.push_back({615, 310,   210,9 });
    hdddColl.push_back({695, 300,   130,9 });
    hdddColl.push_back({728, 278,   72, 18 });
    //tượng đá
    hdddColl.push_back({200, 760,   115,70 });
    hdddColl.push_back({292, 830,   19, 27 });
    hdddColl.push_back({315, 750,   362,180 });
    hdddColl.push_back({330, 933,   345,19 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });
    // hdddColl.push_back({1245,1340,  125, 100 });

    
    return hdddColl;
}