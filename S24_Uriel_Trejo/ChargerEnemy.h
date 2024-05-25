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
	bool vertical;				// Flag to tell if the enemy is a vertical mover or horizontal mover
	bool movingDown = true;		// Bool to tell when enemy is moving up
	bool movingLeft = true;	// Bool to tell when the enemy is moving down
	bool charging = false;		// For charge behavior

	double normalSpeed = 2.5;
	double chargeSpeed = 10.5;
};