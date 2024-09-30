#pragma once

#include <SDL2/SDL.h>
#include <string>

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
	string name;
	const bbg::Strength strength; 	
	/*thế mạnh của 1 tank không thể thay đổi, 
	chỉ có thể sửa chỉ số của tank để phù hợp với thế mạnh định sẵn của nó. 
	1 tank có strength là TANKER, thì chỉ số phải phù hợp
	*/

	const bbg::TankType type;
	Specification specification;
	SDL_Surface* image;

public:
	Tank(string name, const Strength strength, const TankType type, SDL_Surface* image);
	~Tank();

	//getter và setter
	string getName();
	void setName(string name);
	bbg::Strength getStrength();
	bbg::TankType getType();
	SDL_Surface* getImage();
	void setImage(SDL_Surface* image);
	Specification getSpecification();
	void setSpecification(Specification sp);

	//thay đổi từng chỉ số
	void set_HP();
	void set_dps();
	void set_piercing();
	void set_physical_armor();
	void set_energy_shield();

};



