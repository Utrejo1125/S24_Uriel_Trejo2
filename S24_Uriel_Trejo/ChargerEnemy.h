#pragma once

#include "Toad.h"
#include "Enemy.h"

class ChargerEnemy : public Enemy
{
public:
	ChargerEnemy(float x_pos, float y_pos, bool vertical);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

private:
	Toad::Image charger_sprite{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/charger.png" };
	float x_pos, y_pos;
	bool vertical;
	bool movingVertically = true;		// For vertical movement
	bool movingHorizontally = true;	// For horizontal movement
	bool charging = false;		// For charge behavior

	double normalSpeed = 5.0;
	double chargeSpeed = 12.0;
};