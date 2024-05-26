#pragma once

#include "Toad.h"
#include "Onslaught.h"

#include <cmath>

class BulletEntity
{
public:
	BulletEntity(float x_pos, float y_pos, int direction);

	void Move();
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

private:
	Toad::Image bullet_sprite{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/bullet.png" };
	float x_pos, y_pos;
	float speed = 12.0f;	//speed of bullet
	int direction;
};