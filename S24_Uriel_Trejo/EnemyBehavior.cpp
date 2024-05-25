#include "EnemyBehavior.h"


void EnemyBehavior::ZombieBehavior(float player_x_pos, float player_y_pos, float& zombie_x_pos, float& zombie_y_pos)
{
	if (zombie_x_pos < player_x_pos)
	{
		zombie_x_pos++;
	}
	
	if (zombie_x_pos > player_x_pos)
	{
		zombie_x_pos--;
	}

	if (zombie_y_pos < player_y_pos)
	{
		zombie_y_pos++;
	}
	
	if (zombie_y_pos > player_y_pos)
	{
		zombie_y_pos--;
	}
}

Toad::Image& EnemyBehavior::getZombie()
{
	return zombie;
}
