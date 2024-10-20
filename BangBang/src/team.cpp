#include "Team.hpp"

Team::Team(int id) : teamId(id), score(0)
{
}

int Team::getId()
{
	return teamId;
}

void Team::clean()
{
	for(long unsigned int tank = 0; tank < tanks.size(); tank++)
	{
		tanks.at(tank)->clean();
		delete tanks.at(tank);
	}
}