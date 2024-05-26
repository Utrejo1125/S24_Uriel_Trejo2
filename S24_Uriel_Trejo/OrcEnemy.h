#pragma once

#include "Toad.h"
#include "Enemy.h"

class OrcEnemy : public Enemy
{
public:
	OrcEnemy(float x_pos, float y_pos);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

	double GetHealth() const;
	void SetHealth(double new_health);

private:
	Toad::Image orc_sprite{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/orc.png" };
	float x_pos, y_pos;
	float x_offset, y_offset;
	double health = 10.0;
	double speed = 1.0f;
};