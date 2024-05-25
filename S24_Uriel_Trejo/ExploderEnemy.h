#pragma once

#include "Toad.h"
#include "Enemy.h"

class ExploderEnemy : public Enemy
{
public:
	ExploderEnemy(float x_pos, float y_pos);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

private:
	Toad::Image exploder_sprite{ "../Assets/Textures/Onslaught/exploder.png" };
	float x_pos, y_pos;
};