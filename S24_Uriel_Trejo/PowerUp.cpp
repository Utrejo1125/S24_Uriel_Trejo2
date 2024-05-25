#include "PowerUp.h"

PowerUp::PowerUp(float x_pos, float y_pos, int selector) : x_pos{ x_pos }, y_pos{ y_pos }, selector{ selector }
{
}


void PowerUp::Update(float player_x_pos, float player_y_pos)
{
}


void PowerUp::Draw()
{
	if (selector == 0)
	{
		Toad::Renderer::Draw(speed_powerup, x_pos, y_pos);
	}
	else if (selector == 1)
	{
		Toad::Renderer::Draw(gun_powerup, x_pos, y_pos);
	}
	else if (selector == 2)
	{
		Toad::Renderer::Draw(explosive_powerup, x_pos, y_pos);
	}
	else if (selector == 3)
	{
		Toad::Renderer::Draw(shield_powerup, x_pos, y_pos);
	}
}

int PowerUp::GetSelection() const
{
	return selector;
}
