#include "BulletEntity.h"

BulletEntity::BulletEntity(float x_pos, float y_pos, int direction) : x_pos(x_pos), y_pos(y_pos), direction(direction)
{

}


void BulletEntity::Move()
{
	if (direction == 0)					//UP
	{
		y_pos += speed;
	}
	else if (direction == 1)			//LEFT
	{
		x_pos -= speed;
	}
	else if (direction == 2)			//RIGHT
	{
		x_pos += speed;
	}
	else if (direction == 3)			//DOWN
	{
		y_pos -= speed;
	}
}


void BulletEntity::Draw()
{
	Toad::Renderer::Draw(bullet_sprite, x_pos, y_pos);
}