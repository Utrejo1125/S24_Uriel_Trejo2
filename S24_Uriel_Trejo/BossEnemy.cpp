#include "BossEnemy.h"

BossEnemy::BossEnemy(float x_pos, float y_pos) : x_pos(x_pos), y_pos(y_pos)
{
    // Define offsets based on boss size
    x_offset = 100; // Assuming the boss is 256x256, half of the width
    y_offset = 100; // Assuming the boss is 256x256, half of the height

    int tick_count = 49;  // Number of health ticks
    float tick_spacing = 4.0f;  // Spacing between each tick
    float initial_x_pos = x_pos + 45;  // Initial position of the health bar
    float initial_y_pos = y_pos + 250;

    for (int i = 0; i < tick_count; i++)
    {
        healthSpawner.emplace_back(initial_x_pos + i * tick_spacing, initial_y_pos);    //add health ticks
    }
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

    // Update health ticks positions based on boss position
    float tick_spacing = 4.0f;  // Spacing between each tick
    float initial_x_pos = x_pos + 47;  // Initial position of the health bar
    float initial_y_pos = y_pos + 254;

    for (int i = 0; i < healthSpawner.size(); i++)
    {
        if (i < health)  // Only update ticks up to the current health
        {
            healthSpawner[i].UpdatePosition(initial_x_pos + i * tick_spacing, initial_y_pos);
        }
    }
}

void BossEnemy::Draw()
{
    Toad::Renderer::Draw(boss_sprite, x_pos, y_pos);
    Toad::Renderer::Draw(hp_bar, x_pos + 45, y_pos + 250);

    for (int i = 0; i < health; i++)  // Only draw ticks up to the current health
    {
        healthSpawner[i].Draw();                                        //Display health
    }
}

double BossEnemy::GetHealth() const
{
    return health;
}

void BossEnemy::SetHealth(double new_health)
{
    health = new_health;
}
