#pragma once
#include <string>
#include <cmath>

#include "Utils.hpp"
#include "Bullet.hpp"
#include "Team.hpp"

using namespace std;

class Bullet;
class Team;

class Tank
{
protected:
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
    //kiểm tra va chạm với tất cả các tank với nhau
    bool checkTankCollisions( vector<Tank*> tanks);
public:
	//hp hiện tại
	int currentHP;
	bool m_bGetHit; //true if get hit
	Tank(string name, Strength strength, TankType type, Specification spec, int x, int y, vector<SDL_Rect> tankCollider);
	virtual ~Tank();

	// Load textures for both body and head, and bullet
    bool loadTextures(SDL_Renderer* renderer, string spriteSheetPath, string bulletImagePath);
    //load thumbnail
    bool loadThumbnail(SDL_Renderer* renderer, string thumbnailPath);

    virtual void rotateHead(int mouseX, int mouseY);

    //xử lý sự kiện di chuyển cho tank
    virtual void handleTankMovement(SDL_Event& event);
    virtual void move(int mapWidth, int mapHeight, vector<Tank*> tanks, vector<SDL_Rect> mapColliders, float deltaTime);
    //xử lý sự kiện bắn đạn
    virtual void handleBulletShooting(SDL_Event& event);

    //CÁC XỬ LÝ BOTTANK
    virtual void AIControl(Tank* botTank, Team& enemyTeam, float deltaTime);


    //xử lý khi tank trúng đạn (tham số là công và xuyên của tank địch)
    void getHit(Tank* enemyTank);

    // giải phóng tài nguyên
	void clean();

	//getter và setter
	string getName();
	void setName(string name);
	string getStrength();
	string getTypeStr();
	TankType getType();
	SDL_Texture* getThumbnail();
	void setThumbnail(SDL_Texture* image);
	string getSpecificationStr();
	Specification getSpecification();
	void setSpecification(Specification sp);
	SDL_Texture* getBodyTex();
	SDL_Texture* getHeadTex();
	float getPosX();
	float getPosY();
	void setPosition(float x, float y);
    vector<SDL_Rect>& getColliders();
    float getBodyAngle();
    float getHeadAngle();
    Bullet* getBullet();

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