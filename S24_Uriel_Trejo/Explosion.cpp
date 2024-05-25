#include "Explosion.h"


Explosion::Explosion(float x_pos, float y_pos, std::chrono::time_point<std::chrono::steady_clock> spawn_time) :
	x_pos{ x_pos }, y_pos{ y_pos }, spawn_time{ spawn_time }
{

}

void Explosion::Update(float player_x_pos, float player_y_pos)
{

}

void Explosion::Draw()
{
	Toad::Renderer::Draw(explosion_sprite, x_pos, y_pos);
}

bool Explosion::isExpired() const
{
	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - spawn_time).count();
	return elapsed >= 500;	//Signal that some time has passed
}
