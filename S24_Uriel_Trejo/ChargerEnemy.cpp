#include "ChargerEnemy.h"

ChargerEnemy::ChargerEnemy(float x_pos, float y_pos, bool vertical) : x_pos(x_pos), y_pos(y_pos), vertical(vertical)
{
}

void ChargerEnemy::Update(float player_x_pos, float player_y_pos)
{
    const float alignmentRange = 10.0f;  // Define the range for alignment checking

    if (vertical)   // This enemy will patrol up and down
    {
        // Check for alignment with the player on the y position within a range while patrolling
        if (!charging && std::abs(player_y_pos - y_pos) <= alignmentRange)  // Found a player within range!
        {
            charging = true;                                                // Begin charging!
            if (player_x_pos < x_pos)
                movingLeft = true;                                          // Move left

            else
                movingLeft = false;                                         // Move right
        }

        // Enemy was spotted! time to charge
        if (charging)
        {
            if (movingLeft)                         // If charging left
            {
                x_pos -= chargeSpeed;               // Move left based on charge speed                                   
                if (x_pos <= -15)                   // If the enemy reaches the edge,
                {
                    x_pos = -15;                    // Make sure the charger goes back to the right spot                     
                    charging = false;               // Disable charging             
                }
            }
            else if (!movingLeft)                   // If charging right
            {
                x_pos += chargeSpeed;               // Move right based on charge speed
                if (x_pos >= 950)                   // If the enemy reaches the edge,
                {
                    x_pos = 950;                    // Make sure the charger goes back to the right spot
                    charging = false;               // Disable charging
                }
            }
        }

        // Enemy is just patrolling
        else if (!charging)
        {
            if (y_pos >= 775)                       // Enemy has reached the top of the map
                movingDown = true;                  // Start moving down

            else if (y_pos <= 0)                    // Enemy has reached the bottom of the map  
                movingDown = false;                 // Start moing up


            if (movingDown)                         // Move down
                y_pos -= normalSpeed;            

            else if (!movingDown)                   // Move up
                y_pos += normalSpeed;                           
        }
    }
    else if (!vertical)  // This enemy will patrol left and right
    {
        // Check for alignment with the player on the y position within a range while patrolling
        if (!charging && std::abs(player_x_pos - x_pos) <= alignmentRange)
        {
            charging = true;
            if (player_y_pos < y_pos)               // Begin Charging!
                movingDown = true;                  // Move down
            else
                movingDown = false;                 // Move up
        }

        // Enemy was spotted! time to charge
        if (charging)
        {
            if (movingDown)                         // If charging down
            {
                y_pos -= chargeSpeed;               // Move down based on charge speed
                if (y_pos <= -15)                   // If the enemy reaches the edge
                {
                    y_pos = -15;                    // Make sure the charger goes back to the right spot
                    charging = false;               // Disable charging
                }
            }
            else if (!movingDown)                   // If charging up
            {
                y_pos += chargeSpeed;               // Move up based on charge speed
                if (y_pos >= 750)                   // If the enemy reaches the edge
                {
                    y_pos = 750;                    // Make sure the charger goes back to the right spot
                    charging = false;               // Disable charging
                }
            }
        }

        // Enemy is just patrolling
        else if (!charging)
        {
            // Reverse direction at the edges
            if (x_pos >= 975)                       // Enemy has reached the right edge
                movingLeft = true;                  // Start moving left

            else if (x_pos <= 0)                    // Enemy has reached the left edge
                movingLeft = false;                 // Start moving right


            if (movingLeft)                         // Move left
                x_pos -= normalSpeed; 

            else if (!movingLeft)                   // Move right
                x_pos += normalSpeed; 
        }
    }
}

void ChargerEnemy::Draw()
{
    Toad::Renderer::Draw(charger_sprite, x_pos, y_pos);
}