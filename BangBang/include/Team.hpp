#pragma once
#include <vector>

#include "Tank.hpp"

class Team
{
private:
	int teamId;
public:
	std::vector <Tank*> tanks;
	
	Team(int id);
	int getId();
};

