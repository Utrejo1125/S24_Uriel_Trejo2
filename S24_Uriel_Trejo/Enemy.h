#pragma once
#include "Toad.h"

class Enemy
{
public:
	Enemy(float x_pos = 0, float y_pos = 0, double health = 1.0, const std::string& spritePath = "../Assets/Textures/Onslaught/default.png"); // Default constructor with default parameters

	virtual void Update(float player_x_pos, float player_y_pos) = 0;
	virtual void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

	double GetHealth() const { return health; }
	void SetHealth(double new_health) { health = new_health; }

private:
	Toad::Image sprite;
	float x_pos, y_pos;
	double health;
};