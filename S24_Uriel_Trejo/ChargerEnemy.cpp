#include "ChargerEnemy.h"

ChargerEnemy::ChargerEnemy(float x_pos, float y_pos, bool vertical) : x_pos(x_pos), y_pos(y_pos), vertical(vertical)
{
}

void ChargerEnemy::Update(float player_x_pos, float player_y_pos)
{
    const float alignmentRange = 10.0f;  // Define the range for alignment checking

    if (vertical)   // Moves up and down
    {
        // Check for alignment with the player on the y position within a range
        if (!charging && std::abs(player_y_pos - y_pos) <= alignmentRange)  // Found a player!
        {
            charging = true;                                                
            if (player_x_pos < x_pos) 
                movingHorizontally = true;                                 
            else                
                movingVertically = false;                                   
        }

        if (charging)
        {
            if (movingVertically)
            {
                x_pos -= chargeSpeed;                                       
                if (x_pos <= -15)
                {
                    x_pos = -15;                                            
                    charging = false;                                       
                }
            }
            else
            {
                x_pos += chargeSpeed;                                       
                if (x_pos >= 950)
                {
                    x_pos = 950;                                            
                    charging = false;                                       
                }
            }
        }
        else
        {
            // Reverse direction at the edges
            if (y_pos >= 775)
            {
                movingVertically = true;
            }
            else if (y_pos <= 0)
            {
                movingVertically = false;
            }

            if (movingVertically)
            {
                y_pos -= normalSpeed;                                       
            }
            else
            {
                y_pos += normalSpeed;                                       
            }
        }
    }
    else // Moves left and right
    {
        // Check for alignment with the player on the x position within a range
        if (!charging && std::abs(player_x_pos - x_pos) <= alignmentRange)
        {
            charging = true;
            if (player_y_pos > y_pos) 
                movingVertically = false; 
            else 
                movingHorizontally = true;
        }

        if (charging)
        {
            if (movingHorizontally)
            {
                y_pos -= chargeSpeed; 
                if (y_pos <= -15)
                {
                    y_pos = -15; 
                    charging = false; 
                }
            }
            else
            {
                y_pos += chargeSpeed; 
                if (y_pos >= 750)
                {
                    y_pos = 750; 
                    charging = false; 
                }
            }
        }
        else
        {
            // Reverse direction at the edges
            if (x_pos >= 975)
            {
                movingHorizontally = true;
            }
            else if (x_pos <= 0)
            {
                movingHorizontally = false;
            }

            if (movingHorizontally)
            {
                x_pos -= normalSpeed; 
            }
            else
            {
                x_pos += normalSpeed; 
            }
        }
    }
}

void ChargerEnemy::Draw()
{
    Toad::Renderer::Draw(charger_sprite, x_pos, y_pos);
}