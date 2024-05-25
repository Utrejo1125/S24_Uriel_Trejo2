#pragma once

#include "Toad.h"
#include <chrono>

class PowerUp
{
public:
	PowerUp(float x_pos, float y_pos, int selector);

	void Update(float player_x_pos, float player_y_pos);
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

	int GetSelection() const;
private:
	Toad::Image speed_powerup{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/powerup_speed.png" };
	Toad::Image gun_powerup{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/powerup_gattling.png" };
	Toad::Image explosive_powerup{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/powerup_explosive.png" };
	Toad::Image shield_powerup{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/powerup_shield.png" };
	float x_pos, y_pos;

	int selector;
};