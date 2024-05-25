#pragma once

#include "Toad.h"

class HUD
{
public:
	HUD();
	
	void DrawLevel(int level);

private:
	Toad::Image level_icon{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/level.png" };
	Toad::Image num_0{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/0.png" };
	Toad::Image num_1{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/1.png" };
	Toad::Image num_2{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/2.png" };
	Toad::Image num_3{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/3.png" };
	Toad::Image num_4{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/4.png" };
	Toad::Image num_5{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/5.png" };
	Toad::Image num_6{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/6.png" };
	Toad::Image num_7{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/7.png" };
	Toad::Image num_8{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/8.png" };
	Toad::Image num_9{ "../&{PROJECT_BINARY_DIR}/Assets/Textures/9.png" };
};