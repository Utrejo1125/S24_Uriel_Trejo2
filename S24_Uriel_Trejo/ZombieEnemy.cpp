#include "ZombieEnemy.h"

ZombieEnemy::ZombieEnemy(float x_pos, float y_pos) : x_pos(x_pos), y_pos(y_pos)
{

}

void ZombieEnemy::Update(float player_x_pos, float player_y_pos)
{
    // Calculate the difference in positions
    float diff_x = player_x_pos - x_pos;
    float diff_y = player_y_pos - y_pos;

    // Calculate the distance between the zombie and the player
    float distance = std::sqrt(diff_x * diff_x + diff_y * diff_y);

    // Normalize the movement and multiply by the desired speed
    float speed = 2.5f;
    if (distance != 0)  // Avoid division by zero
    {
        diff_x = (diff_x / distance) * speed;
        diff_y = (diff_y / distance) * speed;
    }

    // Update the position of the zombie
    x_pos += diff_x;
    y_pos += diff_y;
}

void ZombieEnemy::Draw()
{
	Toad::Renderer::Draw(zombie_sprite, x_pos, y_pos);
}
