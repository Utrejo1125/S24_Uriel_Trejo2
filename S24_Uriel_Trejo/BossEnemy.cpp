#include "BossEnemy.h"

BossEnemy::BossEnemy(float x_pos, float y_pos) : x_pos(x_pos), y_pos(y_pos)
{
    // Define offsets based on boss size
    x_offset = 100; // Assuming the boss is 256x256, half of the width
    y_offset = 100; // Assuming the boss is 256x256, half of the height
}

void BossEnemy::Update(float player_x_pos, float player_y_pos)
{
    // Calculate the difference in positions
    float diff_x = player_x_pos - x_pos - x_offset;
    float diff_y = player_y_pos - y_pos - y_offset;

    // Calculate the distance between the boss and the player
    float distance = std::sqrt(diff_x * diff_x + diff_y * diff_y);

    // Normalize the movement and multiply by the desired speed
    float speed = 1.5f;
    if (distance != 0)  // Avoid division by zero
    {
        diff_x = (diff_x / distance) * speed;
        diff_y = (diff_y / distance) * speed;
    }

    // Update the position of the boss
    x_pos += diff_x;
    y_pos += diff_y;
}

void BossEnemy::Draw()
{
    Toad::Renderer::Draw(boss_sprite, x_pos, y_pos);
}

int BossEnemy::GetHealth() const
{
    return health;
}

void BossEnemy::SetHealth(double new_health)
{
    health = new_health;
}
