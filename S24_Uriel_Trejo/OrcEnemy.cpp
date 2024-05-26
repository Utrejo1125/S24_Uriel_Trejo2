#include "OrcEnemy.h"

OrcEnemy::OrcEnemy(float x_pos, float y_pos) : x_pos(x_pos), y_pos(y_pos)
{
    x_offset = 30; // Offset to make the orc follow you better
    y_offset = 30; // Offset to make the orc follow you better
}

void OrcEnemy::Update(float player_x_pos, float player_y_pos)
{
    // Calculate the difference in positions
    float diff_x = player_x_pos - x_pos - x_offset;
    float diff_y = player_y_pos - y_pos - y_offset;

    // Calculate the distance between the orc and the player
    float distance = std::sqrt(diff_x * diff_x + diff_y * diff_y);

    // Normalize the movement and multiply by the desired speed
    if (distance != 0)  // Avoid division by zero
    {
        diff_x = (diff_x / distance) * speed;
        diff_y = (diff_y / distance) * speed;
    }

    // Update the position of the orc
    x_pos += diff_x;
    y_pos += diff_y;
}

void OrcEnemy::Draw()
{
    Toad::Renderer::Draw(orc_sprite, x_pos, y_pos);
}

double OrcEnemy::GetHealth() const
{
    return health;
}

void OrcEnemy::SetHealth(double new_health)
{
    health = new_health;
}
