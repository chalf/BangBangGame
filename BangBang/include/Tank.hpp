#pragma once
#include <string>
#include <cmath>

#include "Utils.hpp"
#include "Bullet.hpp"

using namespace std;

//chỉ số của 1 tank
struct Specification{
	int HP; 	//hp
	int dps;	//công
	int piercing;  //xuyên
	int physical_armor; 	//giáp vật lý
	int energy_shield; 		//khiên năng lượng
	int movement_speed;		//di chuyển
	int bullet_speed;	//tốc độ bắn (tức là tốc độ đạn bay - mỗi tank có tốc độ đạn bay khác nhau)
	int range;		//tầm bắn
	Specification();
	string to_string();

};

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

class Tank{
private:
    vector<SDL_Rect> bodyFrames; // Các frame của thân xe tăng
    vector<SDL_Rect> headFrames; // Các frame của đầu xe tăng
    SDL_Texture* bodyTex;	//hình ảnh trong trận đấu
    SDL_Texture* headTex;
    float bodyAngle;	//góc quay cho phần thân khi di chuyển
    float headAngle;	//góc quay cho phần đầu khi di chuyển

	string name;
	Strength strength; 	
	/*thế mạnh của 1 tank không thể thay đổi, 
	chỉ có thể sửa chỉ số của tank để phù hợp với thế mạnh định sẵn của nó. 
	1 tank có strength là TANKER, thì chỉ số phải phù hợp, vì thế nên không có setter
	*/

	TankType type; //như strength
	Specification specification;
	SDL_Texture* thumbnail; //thumbnail

	// độ dời của tank khi di chuyển
	float posX, posY;
	//vận tốc của tank trên mỗi trục
	float velX, velY; 

	//Tank's collision boxes
	vector<SDL_Rect> mColliders;
	//tank's bullet
	Bullet* bullet;

    //fuction
    void shiftColliders(); //hàm này liên tục cập nhất x và y của các colliders để bộ colliders của tank luôn đi theo tank
    bool loadBodyTex(SDL_Renderer* renderer, SDL_Texture* spriteSheetTex);
    bool loadHeadTex(SDL_Renderer* renderer, SDL_Texture* spriteSheetTex);
public:
	//x và y là vị trí ban đầu của tank
	Tank(string name, Strength strength, TankType type, Specification spec, SDL_Texture* image, int x, int y, vector<SDL_Rect> tankCollider);
	Tank(Strength strength, TankType type, int x, int y, vector<SDL_Rect> tankCollider);

	// Load textures for both body and head, and bullet
    bool loadTextures(SDL_Renderer* renderer, const char* spriteSheetPath, string bulletImagePath);
    //xử lý sự kiện di chuyển cho tank
    void handleTankMovement(SDL_Event& event);
    void move(int mapWidth, int mapHeight, vector<SDL_Rect>& otherColliders, vector<SDL_Rect> mapColliders, float deltaTime);

    //xử lý sự kiện bắn đạn
    void handleBulletShooting(SDL_Event& event);

    //xoay theo con trỏ chuột
    void rotateHead(int mouseX, int mouseY);

	// giải phóng tài nguyên
	void clean();

	//getter và setter
	string getName();
	void setName(string name);
	string getStrength();
	string getType();
	SDL_Texture* getThumbnail();
	void setThumbnail(SDL_Texture* image);
	string getSpecification();
	void setSpecification(Specification sp);
	SDL_Texture* getBodyTex();
	SDL_Texture* getHeadTex();
	float getPosX();
	float getPosY();
	void setPosition(float x, float y);
    vector<SDL_Rect>& getColliders();
    float getBodyAngle();
    float getHeadAngle();

	//thay đổi từng chỉ số
	void set_HP(int num);
	void set_dps(int num);
	void set_piercing(int num);
	void set_physical_armor(int num);
	void set_energy_shield(int num);
	void set_movement_speed(int num);
	void set_bullet_speed(int num);
	void set_range(int num);
};

enum FRAME
{
	STATIC,	//không bắn
	FIRE 	// đang bắn
};

const int FrameNumber = 2;

const int TANK_WIDTH = 90;
const int TANK_HEIGHT = 90;