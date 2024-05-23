#pragma once

#include "toad.h"
#include <ctime>       /* time */
#include <cstdlib>     /* srand, rand */

class Game : public Toad::ToadApplication
{
public:
	Game();	//game constructor

	void OnUpdate() override; //overriding update class to do whatever i want my game to do each frame

	void HandleObstacles(Toad::Image& obstacle, int choice);
	bool ObstacleOffScreen(int obstacle_x_pos);
	Toad::Image& ObstacleChooser();	// Picks which obstacle will spawn

	void Jump();
	void Gravity();
	void HandlePlayerPosition();
	bool OnGround() const;

	void CheckCollisions();

	void OnKeyPress(const Toad::KeyPressed& e);
	void OnKeyRelease(const Toad::KeyReleased& e);

	void LevelUpper();

	bool CheckIfLost();
private:
	//rules
	bool isDead = false;
	bool gravity_enabled = true;	// Used to enable and disable gravity, gravity is enabled by default

	//positions and velocities
	int obstacle_start_x_pos = 950;
	int obstacle_x_pos;
	int player_start_y_pos = 60;
	float player_y_pos;
	float player_velocity; // player velocity

	//Score-related
	int score = 0;
	int speed = 10;

	//Assets
	Toad::Image main_sprite_base{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/jeff.png" };
	Toad::Image background{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/backdrop.png" };
	Toad::Image cactus{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/cactus.png" };
	Toad::Image vulture{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/vulture.png" };

	//Chooser
	int choice;
};





/*
Positions: 
Player position will range from (0, 60) - (0,205).
Player sprite is 98 pixels tall and roughly 40 pixels wide

Cactus position will range from (950, 75) - (-100, 75)

Vulture is about 115 pixels wide
*/