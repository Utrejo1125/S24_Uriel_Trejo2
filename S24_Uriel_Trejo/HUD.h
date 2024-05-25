#pragma once

#include "Toad.h"

class HUD
{
public:
	HUD();
	
	void DrawLevel(int level);

private:
	Toad::Image level_icon{ "../Assets/Textures/Onslaught/level.png" };
	Toad::Image num_0{ "../Assets/Textures/Onslaught/0.png" };
	Toad::Image num_1{ "../Assets/Textures/Onslaught/1.png" };
	Toad::Image num_2{ "../Assets/Textures/Onslaught/2.png" };
	Toad::Image num_3{ "../Assets/Textures/Onslaught/3.png" };
	Toad::Image num_4{ "../Assets/Textures/Onslaught/4.png" };
	Toad::Image num_5{ "../Assets/Textures/Onslaught/5.png" };
	Toad::Image num_6{ "../Assets/Textures/Onslaught/6.png" };
	Toad::Image num_7{ "../Assets/Textures/Onslaught/7.png" };
	Toad::Image num_8{ "../Assets/Textures/Onslaught/8.png" };
	Toad::Image num_9{ "../Assets/Textures/Onslaught/9.png" };
};