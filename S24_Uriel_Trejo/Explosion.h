#pragma once

#include "Toad.h"
#include "Enemy.h"
#include <chrono>

class Explosion : public Enemy
{
public:
	Explosion(float x_pos, float y_pos, std::chrono::time_point<std::chrono::steady_clock> spawn_time);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }
	bool isExpired() const;

private:
	Toad::Image explosion_sprite{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/explosion.png" };
	float x_pos, y_pos;
	std::chrono::time_point<std::chrono::steady_clock> spawn_time;
};