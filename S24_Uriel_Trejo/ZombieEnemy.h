#pragma once

#include"Toad.h"
#include"Enemy.h"

class ZombieEnemy : public Enemy
{
public:
	ZombieEnemy(float x_pos, float y_pos);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

private:
	Toad::Image zombie_sprite{ "../Assets/Textures/Onslaught/zombie.png" };
	float x_pos, y_pos;
};