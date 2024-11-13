#include "Utils.hpp"

Specification spec::SPEC_Pegasus()
{
	Specification spec;
	spec.HP = 1948;
	spec.dps = 192;
	spec.piercing = 16;
	spec.physical_armor = 65;
	spec.energy_shield = 79;
	// spec.movement_speed = 120;
	spec.movement_speed = 200;
	spec.bullet_speed = 380;
	spec.range = 460;
	spec.to_string();
	return spec;
}