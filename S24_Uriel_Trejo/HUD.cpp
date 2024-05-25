#include "HUD.h"

HUD::HUD()
{

}


void HUD::DrawLevel(int level)
{
	Toad::Renderer::Draw(level_icon, 0, 725);

	if (level == 1)
	{
		Toad::Renderer::Draw(num_1, 245, 745);
	}
	if (level == 2)
	{
		Toad::Renderer::Draw(num_2, 245, 745);
	}
	if (level == 3)
	{
		Toad::Renderer::Draw(num_3, 245, 745);
	}
	if (level == 4)
	{
		Toad::Renderer::Draw(num_4, 245, 745);
	}
	if (level == 5)
	{
		Toad::Renderer::Draw(num_5, 245, 745);
	}
	if (level == 6)
	{
		Toad::Renderer::Draw(num_6, 245, 745);
	}
	if (level == 7)
	{
		Toad::Renderer::Draw(num_7, 245, 745);
	}
}
