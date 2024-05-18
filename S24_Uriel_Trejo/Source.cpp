#include "Toad.h"
#include <iostream>


class MyGame : public Toad::ToadApplication
{
	virtual void Initialize() override
	{
		
	}

	virtual void OnUpdate() override
	{
		std::cout << "window width " << Toad::ToadWindow::GetWindow()->GetWidth() << std::endl;
	}

private:


};

START_GAME(MyGame)