#pragma once

#include "Toad.h"
#include "Enemy.h"
#include "Health.h"

class BossEnemy : public Enemy
{
public:
	BossEnemy(float x_pos, float y_pos);

	void Update(float player_x_pos, float player_y_pos) override;
	void Draw();

	float GetX() const { return x_pos; }
	float GetY() const { return y_pos; }

	double GetHealth() const;
	void SetHealth(double new_health);

private:
	Toad::Image boss_sprite{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/king_ogre.png" };
	Toad::Image hp_bar{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/king_ogre_hp_bar.png" };
	float x_pos, y_pos;
	double health = 49;
	std::vector<Health> healthSpawner;

	int x_offset, y_offset;
};