#pragma once

#include"Toad.h"

class Health
{
public:
	Health(float x_pos, float y_pos);

	void Draw();

	void UpdatePosition(float x_pos, float y_pos);

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

private:
	Toad::Image health_tick{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/health_tick.png" };
	float x_pos, y_pos;
};