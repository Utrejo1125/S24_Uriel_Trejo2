#include "Toad.h"
#include <iostream>


class MyGame : public Toad::ToadApplication
{
	virtual void OnUpdate() override
	{
		std::cout << "engine is running" << std::endl;
	}

};

START_GAME(MyGame)