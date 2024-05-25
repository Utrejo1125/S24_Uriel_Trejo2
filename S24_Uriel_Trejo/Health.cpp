#include "Health.h"

Health::Health(float x_pos, float y_pos) : x_pos{x_pos}, y_pos{y_pos}
{

}

void Health::Draw()
{

	Toad::Renderer::Draw(health_tick, x_pos, y_pos);
}

void Health::UpdatePosition(float new_x_pos, float new_y_pos)
{
	x_pos = new_x_pos;
	y_pos = new_y_pos;
}
