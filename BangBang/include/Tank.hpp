#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


using namespace std;

//chỉ số của 1 tank
struct Specification{
	int HP; 	//hp
	int dps;	//công
	int piercing;  //xuyên
	int physical_armor; 	//giáp vật lý
	int energy_shield; 		//khiên năng lượng
	int movement_speed;		//di chuyển
	int rate_of_fire;	//tốc độ bắn
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
	int currentFrame;
	int maxFrames;
    vector<SDL_Rect> bodyFrames; // Các frame của thân xe tăng
    vector<SDL_Rect> headFrames; // Các frame của đầu xe tăng
    SDL_Texture* texInMatch;	//hình ảnh trong trận đấu

	string name;
	Strength strength; 	
	/*thế mạnh của 1 tank không thể thay đổi, 
	chỉ có thể sửa chỉ số của tank để phù hợp với thế mạnh định sẵn của nó. 
	1 tank có strength là TANKER, thì chỉ số phải phù hợp, vì thế nên không có setter
	*/

	TankType type; //như strength
	Specification specification;
	SDL_Texture* tex; //thumbnail
	SDL_Rect clip;
public:
	Tank();
	Tank(string name, Strength strength, TankType type, Specification spec, SDL_Texture* image);
	Tank(Strength strength, TankType type);
	~Tank();

	//getter và setter
	string getName();
	void setName(string name);
	string getStrength();
	string getType();
	SDL_Texture* getImage();
	void setImage(SDL_Texture* image);
	string getSpecification();
	void setSpecification(Specification sp);
	SDL_Texture* getTex();
	SDL_Rect getClip();
	void setClip(SDL_Rect clip);
	SDL_Texture* getTexInMatch();

	//thay đổi từng chỉ số
	void set_HP(int num);
	void set_dps(int num);
	void set_piercing(int num);
	void set_physical_armor(int num);
	void set_energy_shield(int num);
	void set_movement_speed(int num);
	void set_rate_of_fire(int num);
	void set_range(int num);

	/*load hình ảnh*/
	// Load textures for both body and head
    bool loadTextures(SDL_Renderer* renderer, const char* spriteSheetPath);

    // Set the frame for shooting recoil animation
    void setShootFrame(int frame);

    // Update the animation
    void update();
	// giải phóng tài nguyên
	void clean();
};

enum FRAME
{
	STATIC,	//không bắn
	FIRE 	// đang bắn
};

const int FrameNumber = 2;

const int TANK_WIDTH = 90;
const int TANK_HEIGHT = 90;