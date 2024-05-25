#pragma once

#include "Toad.h"

class EnemyBehavior
{
public:
	void ZombieBehavior(float player_x_pos, float player_y_pos, float& zombie_x_pos, float& zombie_y_pos);
	Toad::Image& getZombie();

private:
	//Enemy Assets:
	Toad::Image zombie{ "../Assets/Textures/Onslaught/Zombie.png" };
};