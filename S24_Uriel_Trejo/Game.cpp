#include "Game.h"

Game::Game()
{
	srand(time(NULL));	//seed for random number
	choice = rand() % 2;

	SetKeyPressedCallback([this](const Toad::KeyPressed& e) {OnKeyPress(e); });
	SetKeyReleasedCallback([this](const Toad::KeyReleased& e) {OnKeyRelease(e); });

	//Default Constructor. lets set up our default positions and velocity
	obstacle_x_pos = obstacle_start_x_pos;
	player_y_pos = player_start_y_pos;
	player_velocity = 0.0f;
}

void Game::OnUpdate()
{
	//Override the OnUpdate() method to do what we need to do each frame
	Toad::Renderer::Draw(background, 0, 0);
	Toad::Renderer::Draw(main_sprite_base, 0, player_y_pos);

	if (!ObstacleOffScreen(obstacle_x_pos))
	{
		HandleObstacles(cactus, choice);
	}
	else
	{
		obstacle_x_pos = obstacle_start_x_pos;
	}

	//apply ruleset
	Gravity();
	HandlePlayerPosition();
	CheckCollisions();
	LevelUpper();
	CheckIfLost();

	//check positions
	//std::cout << "Player position: 0, " <<  player_y_pos << std::endl;
	//std::cout << "Cactus position: " << obstacle_x_pos << " " << std::endl;
	/*if(choice == 1)
		std::cout << "Vulture position: " << obstacle_x_pos << " " << std::endl;*/

	//update score
	score++;
}

void Game::HandleObstacles(Toad::Image& obstacle, int choice)
{
	if (choice == 0) // Cactus
	{
		Toad::Renderer::Draw(cactus, obstacle_x_pos, 75);
	}
	else			// Vulture
	{
		Toad::Renderer::Draw(vulture, obstacle_x_pos, 175);
	}
	obstacle_x_pos -= speed;
}


bool Game::ObstacleOffScreen(int obstacle_x_pos)
{
	if (obstacle_x_pos < -140)	//obstacle is now of screen
	{
		choice = rand() % 2;	//Re-roll obstacle
		return true;
	}
	else
		return false;
}


Toad::Image& Game::ObstacleChooser()
{
	int selector = rand() % 2;

	if (selector == 0)
	{
		return cactus;
	}
	else
	{
		return vulture;
	}
}
	

void Game::Jump()
{
	player_y_pos += 1;	     // move slightly off ground
	player_velocity = 15.0f; // Set the initial jump velocity
}


void Game::Gravity()
{
	if (!OnGround() && gravity_enabled)	//if player is not on ground and gravity is enabled
	{
		player_velocity -= 0.75f; // Apply gravity (decrease velocity) *Note* the higher the value, the "heavier" the player is
	}
	else
	{
		player_velocity = 0.0f; // Reset velocity when player reaches ground
		player_y_pos = player_start_y_pos; // Ensure player sprite is exactly in starting position (ground)
	}
}


void Game::HandlePlayerPosition()
{
	player_y_pos += player_velocity;	// Add position to sprite based on velocity

	if (player_y_pos < player_start_y_pos) // Prevent clipping in ground
	{
		player_y_pos = player_start_y_pos;
		player_velocity = 0.0f;
	}
}


bool Game::OnGround() const
{
	return player_y_pos == player_start_y_pos;	// Player is on ground if their current y pos is the starting pos
}


void Game::CheckCollisions()
{
	if (choice == 0) // Cactus logic
	{
		if ((obstacle_x_pos <= 60 && obstacle_x_pos > 20) && (player_y_pos >= 60 && player_y_pos < 160))
		{
			std::cout << "You Lost!";
			isDead = true;
		}
	}

	else	// Vulture Logic
	{
		/*if (obstacle_x_pos >= 40 && obstacle_x_pos < 200)
		{
			std::cout << "In range to hit player if they jump now!";
		}*/
		if ((obstacle_x_pos >= 0 && obstacle_x_pos < 100) && (player_y_pos >= 105 && player_y_pos < 210))
		{
			std::cout << "You Lost!";
			isDead = true;
		}
	}
}


void Game::OnKeyPress(const Toad::KeyPressed& e)
{
	if (e.GetKeyCode() == TOAD_KEY_SPACE && OnGround())
	{
		Jump();									// Make player jump
	}
}


void Game::OnKeyRelease(const Toad::KeyReleased& e)
{

}

void Game::LevelUpper()
{
	if (score != 0 && score % 200	 == 0)
	{
		std::cout << "Level Up!" << std::endl;
		speed += 1;
	}
}

bool Game::CheckIfLost()
{
	if (isDead)
	{
		Toad::ToadApplication::DefaultWindowCloseHandler(); // End the game
		return true;
	}
}

START_GAME(Game);