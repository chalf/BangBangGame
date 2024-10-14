#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>	//sử dụng hàm shuffle
#include <random>


using namespace std;

const int TANK_WIDTH = 90;
const int TANK_HEIGHT = 90;

// Vai trò, thế mạnh của tank
enum Strength{
	DPS,
	TANKER,
	SUPPORT
};

enum TankType{
	PHYSICAL,	//tank vật lý
	ENERGY		//tank năng lượng
};

//chỉ số của 1 tank
struct Specification{
	int HP; 	//hp
	int dps;	//công	(nếu là tank vật lý thì công là sát thương vật lý, còn tank năng lượng thì công là sát thương năng lượng)
	int piercing;  //xuyên (tương tự như dps)
	int physical_armor; 	//giáp vật lý
	int energy_shield; 		//khiên năng lượng
	int movement_speed;		//di chuyển
	int bullet_speed;	//tốc độ bắn (tức là tốc độ đạn bay - mỗi tank có tốc độ đạn bay khác nhau)
	int range;		//tầm bắn
	//Tốc độ bắn còn phụ thuộc vào tầm bắn, tầm bắn càng ngắn, tốc độ bắn càng nhanh vì mỗi lần chỉ bắn 1 viên cùng lúc
	Specification();
	string to_string();

};

struct TankInfo
{
	string name;
	Strength strength;
	TankType type;
	Specification spec;
	vector<SDL_Rect> colliders;
	string spriteSheetPath;
	string bulletImagePath;
};

enum TANKCOLLECTION
{
	PEGASUS, GUNDAM
};

//bbg = bang bang game
namespace bbg
{
	// width, height của cửa sổ
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 740;
	extern const char* TITLE;

	//Chứa các thông tin về tank, cần load tank nào gọi tankCollection.at(TANKCOLLECTION indx)
	extern vector<TankInfo> tankCollection;
	void loadTankCollection();

	//khởi tạo timer, audio, video (cho việc render)
	bool init_SDL();

	//khởi tạo SDL_image cho định dạng JPG
	bool init_SDL_image_JPG();

	//khởi tạo SDL_image cho định dạng PNG
	bool init_SDL_image_PNG();

	//khởi tạo SDL_mixer
	bool init_SDL_mixer();

	//khởi tạo SDL_ttf
	bool init_SDL_ttf();

	//load texture truyền vào từ file
	bool loadTextureFromFile(SDL_Renderer* renderer, const char* path, SDL_Texture*& texture);

	//phát hiện va chạm
	bool checkCollision( std::vector<SDL_Rect>& a,  std::vector<SDL_Rect>& b);

	//tính khoảng cách giữa hai điểm
	float distanceBetweenTwoPoint(SDL_Point p1, SDL_Point p2);

	//hàm tính lượng máu phải mất nếu chịu sát thương từ đạn
	int damageTaken(int dpsOfEnemy, int piercingOfEnemy, int armorOrShield);

	//tạo số ngẫu nhiên
	int randomTank();
	bool randomSpawnSide();	//true là bên trái, false là bên phải
	vector<SDL_Point> randomSpawnPos(bool side); //truyền vào spawn side của team, từ đó random ra vị trí của side đó
	void initRandomSeed();	
	//hàm này chỉ gọi 1 lần đầu chương trình để mỗi lần gọi randomNumber() sẽ cho ra số khác nhau
	//hạt giống time(0) được đặt lại bằng thời gian hiện tại. nên nếu để nó trong vòng lặp
	// thì  giá trị của time(0) có thể giống nhau, dẫn đến các số ngẫu nhiên được tạo ra cũng giống nhau.

	//hủy khởi tạo các thư viện, gọi hàm này ngay trước khi thoát khỏi main()
	void deinitialize();

}

namespace colliders
{
	//bộ collider của tank
	vector<SDL_Rect> pegasusColliders();

	//bộ collider của map
	vector<SDL_Rect> hoangDaDaiDiaColliders();

	//bộ collider của bullet
	vector<SDL_Rect> pegasusBulletColliders();
}

namespace spec
{
	Specification SPEC_Pegasus();
}