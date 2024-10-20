#pragma once

#include "Tank.hpp"

class Tank;

class Team
{
private:
	int teamId;
public:
	//mỗi đối tượng Tank đại diện cho 1 tank trong trận đấu
	std::vector <Tank*> tanks;
	unsigned short score;
	bool spawnSide; //true là bên trái, false là bên phải

	Team(int id);
	int getId();
	void clean();
};

