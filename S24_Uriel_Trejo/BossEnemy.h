#pragma once

#include "Toad.h"
#include "Enemy.h"

class BossEnemy : public Enemy
{
public:
	BossEnemy(float x_pos, float y_pos);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

	int GetHealth() const;
	void SetHealth(double new_health);

private:
	Toad::Image boss_sprite{ "../Assets/Textures/Onslaught/king_ogre.png" };
	float x_pos, y_pos;
	int health = 250;

	int x_offset, y_offset;
};