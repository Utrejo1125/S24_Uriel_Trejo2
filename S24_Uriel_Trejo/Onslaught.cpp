#include "Onslaught.h"

Onslaught::Onslaught()
{
	startLevel();
}


void Onslaught::restartGame()
{
	level = 1;
	wonLevel = false;
	victory = false;
	isDead = false;
	zombie_spawns = 0;
	charger_spawns = 0;
	exploder_spawns = 0;
	orc_spawns = 0;
	boss_spawns = 0;

	//reset powerups
	speedy = false;
	shooty = false;
	shielded = false;
	boomy = false;
	startLevel();
}

void Onslaught::startGame()
{
	SetKeyPressedCallback([this](const Toad::KeyPressed& e) {OnKeyPress(e); });
	SetKeyReleasedCallback([this](const Toad::KeyReleased& e) {OnKeyRelease(e); });

	// Set all default values
	zombie_timer = std::chrono::steady_clock::now();	// Start the timer
	charger_timer = std::chrono::steady_clock::now();	// Start the timer
	exploder_timer = std::chrono::steady_clock::now();	// Start the timer
	explosion_timer = std::chrono::steady_clock::now();	// Start the timer
	orc_timer = std::chrono::steady_clock::now();		// Start the timer
	boss_timer = std::chrono::steady_clock::now();		// Start the timer
	powerup_timer = std::chrono::steady_clock::now();	// Start the timer
	speed_limit = std::chrono::steady_clock::now();		// Start the timer

	srand(time(NULL));	//seed for random number
	srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

	isDead = false;
	sprite_x_pos = 450;
	sprite_y_pos = 400;
	num_keys_pressed = 0;
	current_state = UP;
	isMoving = false;
	player_health = 1;

}


void Onslaught::startLevel()
{
	LevelHandler(level);
	startGame();
}


void Onslaught::LevelHandler(int level)
{
	if (level == 0)
	{
		//TEST LEVEL, IS NOT A REAL LEVEL
		kills = 0;
		wonLevel = false;
		exploder_spawns = 1;
		exploder_spawn_rate = 1000;
		orc_spawns = 2;
		orc_spawn_rate = 2000;
		kill_goal = 10000;
	}
	else if (level == 1)
	{
		kills = 0;
		wonLevel = false;
		zombie_spawns = 20;
		zombie_spawn_rate = 1200;
		kill_goal = 20;
	}
	else if (level == 2)
	{
		kills = 0;
		wonLevel = false;
		zombie_spawns = 50;
		zombie_spawn_rate = 800;
		kill_goal = 50;
	}
	else if (level == 3)
	{
		kills = 0;
		wonLevel = false;
		zombie_spawns = 40;
		zombie_spawn_rate = 800;
		charger_spawns = 10;
		charger_spawn_rate = 1500;
		kill_goal = 50;
	}
	else if (level == 4)
	{
		kills = 0;
		wonLevel = false;
		zombie_spawns = 30;
		zombie_spawn_rate = 800;
		charger_spawns = 10;
		charger_spawn_rate = 1500;
		exploder_spawns = 20;
		exploder_spawn_rate = 1200;
		kill_goal = 60;
	}
	else if (level == 5)
	{
		kills = 0;
		wonLevel = false;
		zombie_spawns = 40;
		zombie_spawn_rate = 800;
		exploder_spawns = 15;
		exploder_spawn_rate = 1000;
		orc_spawns = 5;
		orc_spawn_rate = 3000;
		kill_goal = 60;
	}
	else if (level == 6)
	{
		kills = 0;
		wonLevel = false;
		orc_spawns = 20;
		orc_spawn_rate = 1500;
		kill_goal = 20;
	}
	else if (level == 7)
	{
		kills = 0;
		wonLevel = false;
		//zombie_spawns = -1;
		zombie_spawn_rate = 1000;
		boss_spawns = 1;
		boss_spawn_rate = 100;
		kill_goal = 10000;		// goal will be to kill boss which awards 10,000 kills
	}
	else
	{
		victory = true;
		//handle win
	}
}

void Onslaught::TrackKills()
{
	if (kills >= kill_goal)
	{
		wonLevel = true;
		level++;
		std::cout << "Going to next level: level " << level << std::endl;
		LevelHandler(level);
	}
}


void Onslaught::OnUpdate()
{
	if (victory)
	{
		Toad::Renderer::Draw(win_screen, 0, 0); // End the game
	}
	else if (!isDead)
	{
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_performance_check);

		if (elapsed_time.count() >= performance_check_interval)
		{
			PerformanceChecker();
			last_performance_check = current_time;  // Reset the timer
		}

		if(!wonLevel)
			TrackKills();
		//std::cout << "Player Health: " << player_health << std::endl;
		Toad::Renderer::Draw(background, 0, 0);
		hud.DrawLevel(level);

		for (PowerUp& powerup : powerupSpawner)
		{
			powerup.Draw();
		}


		for (BulletEntity& bullet : bulletSpawner)
		{
			bullet.Move();
			bullet.Draw();
		}

		for (ZombieEnemy& zombie : zombieSpawner)
		{
			zombie.Update(sprite_x_pos, sprite_y_pos);
			zombie.Draw();
		}

		for (ExploderEnemy& exploder : exploderSpawner)
		{
			exploder.Update(sprite_x_pos, sprite_y_pos);
			exploder.Draw();
		}

		for (Explosion& explosion : explosionSpawner)
		{
			explosion.Draw();
		}
		
		for (OrcEnemy& orc : orcSpawner)
		{
			orc.Update(sprite_x_pos, sprite_y_pos);
			orc.Draw();
		}
		
		for (ChargerEnemy& charger : chargerSpawner)
		{
			charger.Update(sprite_x_pos, sprite_y_pos);
			charger.Draw();
		}

		for (BossEnemy& boss : bossSpawner)
		{
			boss.Update(sprite_x_pos, sprite_y_pos);
			boss.Draw();
		}

		if (speedy)
		{
			speedyHandler();
		}
		if (shooty)
		{
			shootyHandler();
			HandleGattlingGun();
		}
		if (boomy)
		{
			boomHandler();
		}

		HandlePowerup();

		shieldHandler();

		HandleSpriteMovement();
		CheckIfMoving();

		HandlePlayerCollision();
		HandleZombieCollision();
		HandleChargerCollision();
		HandleExploderCollision();
		HandleExplosionCollision();
		HandleExplosions();
		HandleOrcCollision();
		HandleBossCollision();

		randomSpawnPowerup(powerup_spawn_rate);

		randomSpawnZombies(zombie_spawn_rate);
		randomSpawnChargers(charger_spawn_rate);
		randomSpawnExploders(exploder_spawn_rate);
		randomSpawnOrcs(orc_spawn_rate);
		randomSpawnBoss(boss_spawn_rate);

		CheckIfLost();
	}
	else
	{
		Toad::Renderer::Draw(loss_screen, 0, 0); // End the game
	}
}


void Onslaught::OnKeyPress(const Toad::KeyPressed& e)
{
	if (victory)
	{
		if (e.GetKeyCode() == TOAD_KEY_ENTER)
		{
			restartGame();
		}
	}
	else if (!isDead)
	{
		if (e.GetKeyCode() == TOAD_KEY_W || e.GetKeyCode() == TOAD_KEY_UP)
		{
			num_keys_pressed++;
			current_state = UP;
		}
		else if (e.GetKeyCode() == TOAD_KEY_A || e.GetKeyCode() == TOAD_KEY_UP)
		{
			num_keys_pressed++;
			current_state = LEFT;
		}
		else if (e.GetKeyCode() == TOAD_KEY_D || e.GetKeyCode() == TOAD_KEY_UP)
		{
			num_keys_pressed++;
			current_state = RIGHT;
		}
		else if (e.GetKeyCode() == TOAD_KEY_S || e.GetKeyCode() == TOAD_KEY_DOWN)
		{
			num_keys_pressed++;
			current_state = DOWN;
		}

		if (e.GetKeyCode() == TOAD_KEY_ENTER || e.GetKeyCode() == TOAD_KEY_SPACE)
		{
			if (!shooty)
			{
				HandleBullet();
			}
		}
	}
	else
	{
		if (e.GetKeyCode() == TOAD_KEY_ENTER)
		{
			restartGame();
		}
	}
}


void Onslaught::OnKeyRelease(const Toad::KeyReleased& e)
{
	if (e.GetKeyCode() == TOAD_KEY_W || e.GetKeyCode() == TOAD_KEY_UP)
	{
		num_keys_pressed--;
	}
	else if (e.GetKeyCode() == TOAD_KEY_A || e.GetKeyCode() == TOAD_KEY_LEFT)
	{
		num_keys_pressed--;
	}
	else if (e.GetKeyCode() == TOAD_KEY_D || e.GetKeyCode() == TOAD_KEY_RIGHT)
	{
		num_keys_pressed--;
	}
	else if (e.GetKeyCode() == TOAD_KEY_S || e.GetKeyCode() == TOAD_KEY_DOWN)
	{
		num_keys_pressed--;
	}
}


void Onslaught::HandleSpriteMovement()
{
	if (current_state == UP)
	{
		if (speedy)
		{
			Toad::Renderer::Draw(sprite_up_speed, sprite_x_pos, sprite_y_pos);
		}
		else if (shooty)
		{
			Toad::Renderer::Draw(sprite_up_gattling, sprite_x_pos, sprite_y_pos);
		}
		else if (boomy)
		{
			Toad::Renderer::Draw(sprite_up_boom, sprite_x_pos, sprite_y_pos);
		}
		else
		{
			Toad::Renderer::Draw(sprite_up, sprite_x_pos, sprite_y_pos);
		}

		if (CheckIfMoving() && sprite_y_pos < 740)
		{
			sprite_y_pos += speed;
		}
	}

	else if (current_state == LEFT)
	{
		if (speedy)
		{
			Toad::Renderer::Draw(sprite_left_speed, sprite_x_pos, sprite_y_pos);
		}
		else if (shooty)
		{
			Toad::Renderer::Draw(sprite_left_gattling, sprite_x_pos, sprite_y_pos);
		}
		else if (boomy)
		{
			Toad::Renderer::Draw(sprite_left_boom, sprite_x_pos, sprite_y_pos);
		}
		else
		{
			Toad::Renderer::Draw(sprite_left, sprite_x_pos, sprite_y_pos);
		}

		if (CheckIfMoving() && sprite_x_pos > 0)
		{
			sprite_x_pos -= speed;
		}
	}

	else if (current_state == RIGHT)
	{
		if (speedy)
		{
			Toad::Renderer::Draw(sprite_right_speed, sprite_x_pos, sprite_y_pos);
		}
		else if (shooty)
		{
			Toad::Renderer::Draw(sprite_right_gattling, sprite_x_pos, sprite_y_pos);
		}
		else if (boomy)
		{
			Toad::Renderer::Draw(sprite_right_boom, sprite_x_pos, sprite_y_pos);
		}
		else
		{
			Toad::Renderer::Draw(sprite_right, sprite_x_pos, sprite_y_pos);
		}

		if (CheckIfMoving() && sprite_x_pos < 940)
		{
			sprite_x_pos += speed;
		}
	}

	else if (current_state == DOWN)
	{
		if (speedy)
		{
			Toad::Renderer::Draw(sprite_down_speed, sprite_x_pos, sprite_y_pos);
		}
		else if (shooty)
		{
			Toad::Renderer::Draw(sprite_down_gattling, sprite_x_pos, sprite_y_pos);
		}
		else if (boomy)
		{
			Toad::Renderer::Draw(sprite_down_boom, sprite_x_pos, sprite_y_pos);
		}
		else
		{
			Toad::Renderer::Draw(sprite_down, sprite_x_pos, sprite_y_pos);
		}

		if (CheckIfMoving() && sprite_y_pos > 0)
		{
			sprite_y_pos -= speed;
		}
	}
}

bool Onslaught::CheckIfMoving()
{
	if (num_keys_pressed <= 0)
	{
		isMoving = false;
		return false;
	}

	isMoving = true;
	return true;
}

void Onslaught::HandleBullet()
{
	if (current_state == UP)
	{
		SpawnBullet(sprite_x_pos + 42.5, sprite_y_pos + 35);
	}
	else if (current_state == LEFT)
	{
		SpawnBullet(sprite_x_pos, sprite_y_pos + 42.5);
	}
	else if (current_state == RIGHT)
	{
		SpawnBullet(sprite_x_pos + 47.5, sprite_y_pos + 12.5);
	}
	else if (current_state == DOWN)
	{
		SpawnBullet(sprite_x_pos + 10, sprite_y_pos);
	}
}

void Onslaught::HandleGattlingGun()
{
	auto current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_shoot_time);

	if (elapsed_time.count() >= shoot_interval)
	{
		last_shoot_time = current_time;
		float spread_x = static_cast<float>(rand() % 61 - 30); // Generate a random number between -30 and 30
		float spread_y = static_cast<float>(rand() % 61 - 30); // Generate a random number between -30 and 30


		if (current_state == UP)
		{
			SpawnBullet(sprite_x_pos + 42.5 + spread_x, sprite_y_pos + 35);
		}
		else if (current_state == LEFT)
		{
			SpawnBullet(sprite_x_pos, sprite_y_pos + 42.5 + spread_y);
		}
		else if (current_state == RIGHT)
		{
			SpawnBullet(sprite_x_pos + 47.5, sprite_y_pos + 12.5 + spread_y);
		}
		else if (current_state == DOWN)
		{
			SpawnBullet(sprite_x_pos + 10 + spread_x, sprite_y_pos);
		}
	}
}

void Onslaught::HandlePowerup()
{
	// Iterate through powerups vector
	for (auto powerupIterator = powerupSpawner.begin(); powerupIterator != powerupSpawner.end();)
	{
		// Check collision
		if (sprite_x_pos < powerupIterator->GetX() + 64 &&	// assuming 64 is the width of the powerup
			sprite_x_pos + 48 > powerupIterator->GetX() &&	// assuming 48 is the width of the player
			sprite_y_pos < powerupIterator->GetY() + 64 &&	// assuming 64 is the height of the powerup
			sprite_y_pos + 48 > powerupIterator->GetY())		// assuming 48 is the height of the player
		{
			PowerupDecider(powerupIterator->GetSelection());
			powerupIterator = powerupSpawner.erase(powerupIterator);
			break;
		}
		else
		{
			++powerupIterator;
		}
	}
}

void Onslaught::HandleZombieCollision()
{
	// Iterate through bullet vector
	for (auto bulletIterator = bulletSpawner.begin(); bulletIterator != bulletSpawner.end();)
	{
		bool bulletDestroyed = false;
		if (bulletIterator->GetX() > 1010 || bulletIterator->GetX() < -10)	// Bullet left the map on the x axis
			bulletDestroyed = true;
		if (bulletIterator->GetY() > 810 || bulletIterator->GetY() < -10)	// Bullet left the map on the y axis
			bulletDestroyed = true;

		// Iterate through zombies vector
		for (auto zombieIterator = zombieSpawner.begin(); zombieIterator != zombieSpawner.end();)
		{
			// Check collision
			if (bulletIterator->GetX() < zombieIterator->GetX() + 64 && // assuming 64 is the width of the zombie
				bulletIterator->GetX() + 10 > zombieIterator->GetX() && // assuming 10 is the width of the bullet
				bulletIterator->GetY() < zombieIterator->GetY() + 64 && // assuming 64 is the height of the zombie
				bulletIterator->GetY() + 10 > zombieIterator->GetY()) // assuming 10 is the height of the bullet
			{
				// Delete zombie
				zombieIterator = zombieSpawner.erase(zombieIterator);
				kills++;
				bulletDestroyed = true;
				break;
			}
			else
			{
				++zombieIterator;
			}
		}

		// Delete the bullet if it collided with a zombie
		if (bulletDestroyed)
		{
			if (boomy)	// If explosive ammo is active
			{
				SpawnExplosion(bulletIterator->GetX(), bulletIterator->GetY());
			}
			bulletIterator = bulletSpawner.erase(bulletIterator);
		}
		else
		{
			++bulletIterator;
		}
	}
}


void Onslaught::HandleChargerCollision()
{
	// Iterate through bullet vector
	for (auto bulletIterator = bulletSpawner.begin(); bulletIterator != bulletSpawner.end();)
	{
		bool bulletDestroyed = false;
		if (bulletIterator->GetX() > 1010 || bulletIterator->GetX() < -10)	// Bullet left the map on the x axis
			bulletDestroyed = true;
		if (bulletIterator->GetY() > 810 || bulletIterator->GetY() < -10)	// Bullet left the map on the y axis
			bulletDestroyed = true;

		// Iterate through chargers vector
		for (auto chargerIterator = chargerSpawner.begin(); chargerIterator != chargerSpawner.end();)
		{
			// Check collision
			if (bulletIterator->GetX() < chargerIterator->GetX() + 64 && // assuming 64 is the width of the charger
				bulletIterator->GetX() + 10 > chargerIterator->GetX() && // assuming 10 is the width of the bullet
				bulletIterator->GetY() < chargerIterator->GetY() + 64 && // assuming 64 is the height of the charger
				bulletIterator->GetY() + 10 > chargerIterator->GetY()) // assuming 10 is the height of the bullet
			{
				// Delete charger
				chargerIterator = chargerSpawner.erase(chargerIterator);
				kills++;
				bulletDestroyed = true;
				break;
			}
			else
			{
				++chargerIterator;
			}
		}

		// Delete the bullet if it collided with a charger
		if (bulletDestroyed)
		{
			if (boomy)	// If explosive ammo is active
			{
				SpawnExplosion(bulletIterator->GetX(), bulletIterator->GetY());
			}
			bulletIterator = bulletSpawner.erase(bulletIterator);
		}
		else
		{
			++bulletIterator;
		}
	}
}

void Onslaught::HandleExploderCollision()
{
	// Iterate through bullet vector
	for (auto bulletIterator = bulletSpawner.begin(); bulletIterator != bulletSpawner.end();)
	{
		bool bulletDestroyed = false;
		if (bulletIterator->GetX() > 1010 || bulletIterator->GetX() < -10)	// Bullet left the map on the x axis
			bulletDestroyed = true;
		if (bulletIterator->GetY() > 810 || bulletIterator->GetY() < -10)	// Bullet left the map on the y axis
			bulletDestroyed = true;

		// Iterate through exploders vector
		for (auto exploderIterator = exploderSpawner.begin(); exploderIterator != exploderSpawner.end();)
		{
			// Check collision
			if (bulletIterator->GetX() < exploderIterator->GetX() + 64 && // assuming 64 is the width of the exploder
				bulletIterator->GetX() + 10 > exploderIterator->GetX() && // assuming 10 is the width of the bullet
				bulletIterator->GetY() < exploderIterator->GetY() + 64 && // assuming 64 is the height of the exploder
				bulletIterator->GetY() + 10 > exploderIterator->GetY()) // assuming 10 is the height of the bullet
			{
				// Delete exploder
				SpawnExplosion(exploderIterator->GetX(), exploderIterator->GetY());	//Spawns explosion where exploder died
				std::cout << "killed exploder!" << std::endl;
				exploderIterator = exploderSpawner.erase(exploderIterator);
				kills++;
				bulletDestroyed = true;
				break;
			}
			else
			{
				++exploderIterator;
			}
		}

		// Delete the bullet if it collided with a exploder
		if (bulletDestroyed)
		{
			if (boomy)	// If explosive ammo is active
			{
				SpawnExplosion(bulletIterator->GetX(), bulletIterator->GetY());
			}
			bulletIterator = bulletSpawner.erase(bulletIterator);
		}
		else
		{
			++bulletIterator;
		}
	}
}

void Onslaught::HandleExplosionCollision()
{
	for (size_t explosion_iterator = 0; explosion_iterator < explosionSpawner.size(); ++explosion_iterator)
	{
		// Access the current explosion based on index
		auto& currentExplosion = explosionSpawner[explosion_iterator];

		// Check collisions with the player
		if (sprite_x_pos < currentExplosion.GetX() + 240 &&   // Assuming 240 is the width of the explosion
			sprite_x_pos + 48 > currentExplosion.GetX() &&   // Assuming 48 is the width of the player
			sprite_y_pos < currentExplosion.GetY() + 230 &&   // Assuming 230 is the height of the explosion
			sprite_y_pos + 48 > currentExplosion.GetY())     // Assuming 48 is the height of the player
		{
			if(!boomy)
				player_health--;  // Player loses one HP
		}

		// Check collisions with zombies
		for (size_t zombie_iterator = 0; zombie_iterator < zombieSpawner.size();)
		{
			auto& currentZombie = zombieSpawner[zombie_iterator];
			if (currentZombie.GetX() < currentExplosion.GetX() + 240 &&  // Assuming 240 is the width of the explosion
				currentZombie.GetX() + 48 > currentExplosion.GetX() &&  // Assuming 48 is the width of the zombie
				currentZombie.GetY() < currentExplosion.GetY() + 230 &&  // Assuming 230 is the height of the explosion
				currentZombie.GetY() + 48 > currentExplosion.GetY())    // Assuming 48 is the height of the zombie
			{
				zombieSpawner.erase(zombieSpawner.begin() + zombie_iterator);  // Remove the zombie
				kills++;
			}
			else
			{
				++zombie_iterator;
			}
		}

		// Check collisions with chargers
		for (size_t charger_iterator = 0; charger_iterator < chargerSpawner.size();)
		{
			auto& currentCharger = chargerSpawner[charger_iterator];
			if (currentCharger.GetX() < currentExplosion.GetX() + 240 &&  // Assuming 240 is the width of the explosion
				currentCharger.GetX() + 48 > currentExplosion.GetX() &&  // Assuming 48 is the width of the charger
				currentCharger.GetY() < currentExplosion.GetY() + 230 &&  // Assuming 230 is the height of the explosion
				currentCharger.GetY() + 48 > currentExplosion.GetY())    // Assuming 48 is the height of the charger
			{
				chargerSpawner.erase(chargerSpawner.begin() + charger_iterator);  // Remove the charger
				kills++;
			}
			else
			{
				++charger_iterator;
			}
		}

		// Check collisions with exploders
		for (size_t exploder_iterator = 0; exploder_iterator < exploderSpawner.size();)
		{
			auto& currentExploder = exploderSpawner[exploder_iterator];
			if (currentExploder.GetX() < currentExplosion.GetX() + 240 &&  // Assuming 240 is the width of the explosion
				currentExploder.GetX() + 48 > currentExplosion.GetX() &&  // Assuming 48 is the width of the exploder
				currentExploder.GetY() < currentExplosion.GetY() + 230 &&  // Assuming 230 is the height of the explosion
				currentExploder.GetY() + 48 > currentExplosion.GetY())    // Assuming 48 is the height of the exploder
			{
				SpawnExplosion(currentExploder.GetX(), currentExploder.GetY());
				exploderSpawner.erase(exploderSpawner.begin() + exploder_iterator);  // Remove the exploder
				kills++;
			}
			else
			{
				++exploder_iterator;
			}
		}

		// Check collisions with orcs
		for (size_t orc_iterator = 0; orc_iterator < orcSpawner.size();)
		{
			auto& currentorc = orcSpawner[orc_iterator];
			if (currentorc.GetX() < currentExplosion.GetX() + 240 &&  // Assuming 240 is the width of the explosion
				currentorc.GetX() + 48 > currentExplosion.GetX() &&  // Assuming 128 is the width of the orc
				currentorc.GetY() < currentExplosion.GetY() + 230 &&  // Assuming 230 is the height of the explosion
				currentorc.GetY() + 48 > currentExplosion.GetY())    // Assuming 128 is the height of the orc
			{
				DamageOrc(currentorc, 0.4);
				if (currentorc.GetHealth() < 1)
				{
					orcSpawner.erase(orcSpawner.begin() + orc_iterator);  // delete the orc
					kills++;
				}
				break;
			}
			else
			{
				++orc_iterator;
			}
		}

		// Check collisions with boss
		for (size_t boss_iterator = 0; boss_iterator < bossSpawner.size();)
		{
			auto& currentboss = bossSpawner[boss_iterator];
			if (currentboss.GetX() < currentExplosion.GetX() + 240 &&  // Assuming 240 is the width of the explosion
				currentboss.GetX() + 48 > currentExplosion.GetX() &&  // Assuming 256 is the width of the boss
				currentboss.GetY() < currentExplosion.GetY() + 230 &&  // Assuming 230 is the height of the explosion
				currentboss.GetY() + 48 > currentExplosion.GetY())    // Assuming 256 is the height of the boss
			{
				DamageBoss(currentboss, 0.015);
				if (currentboss.GetHealth() < 1)
				{
					bossSpawner.erase(bossSpawner.begin() + boss_iterator);  // delete the orc
					kills += 10000;
				}
				break;
			}
			else
			{
				++boss_iterator;
			}
		}
	}
}




void Onslaught::HandleOrcCollision()
{
	// Iterate through bullet vector
	for (auto bulletIterator = bulletSpawner.begin(); bulletIterator != bulletSpawner.end();)
	{
		bool bulletDestroyed = false;
		if (bulletIterator->GetX() > 1010 || bulletIterator->GetX() < -10)	// Bullet left the map on the x axis
			bulletDestroyed = true;
		if (bulletIterator->GetY() > 810 || bulletIterator->GetY() < -10)	// Bullet left the map on the y axis
			bulletDestroyed = true;

		// Iterate through orcs vector
		for (auto orcIterator = orcSpawner.begin(); orcIterator != orcSpawner.end();)
		{
			// Check collision
			if (bulletIterator->GetX() < orcIterator->GetX() + 128 && // assuming 128 is the width of the orc
				bulletIterator->GetX() + 10 > orcIterator->GetX() && // assuming 10 is the width of the bullet
				bulletIterator->GetY() < orcIterator->GetY() + 128 && // assuming 128 is the height of the orc
				bulletIterator->GetY() + 10 > orcIterator->GetY()) // assuming 10 is the height of the bullet
			{
				// Delete orc
				if (orcIterator->GetHealth() < 1)
				{
					kills++;
					orcIterator = orcSpawner.erase(orcIterator);
				}
				else
					orcIterator->SetHealth((orcIterator->GetHealth()) - 1);

				bulletDestroyed = true;
				break;
			}
			else
			{
				++orcIterator;
			}
		}

		// Delete the bullet if it collided with a orc
		if (bulletDestroyed)
		{
			if (boomy)	// If explosive ammo is active
			{
				SpawnExplosion(bulletIterator->GetX(), bulletIterator->GetY());
			}
			bulletIterator = bulletSpawner.erase(bulletIterator);
		}
		else
		{
			++bulletIterator;
		}
	}
}


void Onslaught::HandleBossCollision()
{
	// Iterate through bullet vector
	for (auto bulletIterator = bulletSpawner.begin(); bulletIterator != bulletSpawner.end();)
	{
		bool bulletDestroyed = false;
		if (bulletIterator->GetX() > 1010 || bulletIterator->GetX() < -10)	// Bullet left the map on the x axis
			bulletDestroyed = true;
		if (bulletIterator->GetY() > 810 || bulletIterator->GetY() < -10)	// Bullet left the map on the y axis
			bulletDestroyed = true;

		// Iterate through bosss vector
		for (auto bossIterator = bossSpawner.begin(); bossIterator != bossSpawner.end();)
		{
			// Check collision
			if (bulletIterator->GetX() < bossIterator->GetX() + 256 && // assuming 256 is the width of the boss
				bulletIterator->GetX() + 10 > bossIterator->GetX() && // assuming 10 is the width of the bullet
				bulletIterator->GetY() < bossIterator->GetY() + 256 && // assuming 256 is the height of the boss
				bulletIterator->GetY() + 10 > bossIterator->GetY()) // assuming 10 is the height of the bullet
			{
				// Delete boss
				if (bossIterator->GetHealth() < 1)
				{
					kills += 10000;
					bossIterator = bossSpawner.erase(bossIterator);
				}
				else
				{
					bossIterator->SetHealth((bossIterator->GetHealth()) - 0.20);
				}
				bulletDestroyed = true;
				break;
			}
			else
			{
				++bossIterator;
			}
		}

		// Delete the bullet if it collided with a boss
		if (bulletDestroyed)
		{
			if (boomy)	// If explosive ammo is active
			{
				SpawnExplosion(bulletIterator->GetX(), bulletIterator->GetY());
			}
			bulletIterator = bulletSpawner.erase(bulletIterator);
		}
		else
		{
			++bulletIterator;
		}
	}
}


void Onslaught::HandlePlayerCollision()
{
	// Iterate through zombies vector
	for (auto zombieIterator = zombieSpawner.begin(); zombieIterator != zombieSpawner.end();)
	{
		// Check collision
		if (sprite_x_pos < zombieIterator->GetX() + 64 &&	// assuming 64 is the width of the zombie
			sprite_x_pos + 48 > zombieIterator->GetX() &&	// assuming 48 is the width of the player
			sprite_y_pos < zombieIterator->GetY() + 64 &&	// assuming 64 is the height of the zombie
			sprite_y_pos + 48 > zombieIterator->GetY())		// assuming 48 is the height of the player
		{
			zombieIterator = zombieSpawner.erase(zombieIterator);
			kills++;
			if (shielded)
			{
				shielded = false;							// Remove shield
			}
			else
			{
				player_health--;
			}
			break;
		}
		else
		{
			++zombieIterator;
		}
	}

	// Iterate through charger vector
	for (auto chargerIterator = chargerSpawner.begin(); chargerIterator != chargerSpawner.end();)
	{
		// Check collision
		if (sprite_x_pos < chargerIterator->GetX() + 48 &&	// assuming 48 is the width of the charger
			sprite_x_pos + 48 > chargerIterator->GetX() &&	// assuming 48 is the width of the player
			sprite_y_pos < chargerIterator->GetY() + 48 &&	// assuming 48 is the height of the charger
			sprite_y_pos + 48 > chargerIterator->GetY())		// assuming 48 is the height of the player
		{
			chargerIterator = chargerSpawner.erase(chargerIterator);
			kills++;
			if (shielded)
			{
				shielded = false;							// Remove shield
			}
			else
			{
				player_health--;
			}
			break;
		}
		else
		{
			++chargerIterator;
		}
	}

	// Iterate through exploders vector
	for (auto exploderIterator = exploderSpawner.begin(); exploderIterator != exploderSpawner.end();)
	{
		// Check collision
		if (sprite_x_pos < exploderIterator->GetX() + 64 &&	// assuming 64 is the width of the exploder
			sprite_x_pos + 48 > exploderIterator->GetX() &&	// assuming 48 is the width of the player
			sprite_y_pos < exploderIterator->GetY() + 64 &&	// assuming 64 is the height of the exploder
			sprite_y_pos + 48 > exploderIterator->GetY())		// assuming 48 is the height of the player
		{
			exploderIterator = exploderSpawner.erase(exploderIterator);
			kills++;
			if (shielded)
			{
				shielded = false;							// Remove shield
			}
			else
			{
				player_health--;
			}
			break;
		}
		else
		{
			++exploderIterator;
		}
	}

	// Iterate through orc vector
	for (auto orcIterator = orcSpawner.begin(); orcIterator != orcSpawner.end();)
	{
		// Check collision
		if (sprite_x_pos < orcIterator->GetX() + 128 &&	// assuming 128 is the width of the orc
			sprite_x_pos + 48 > orcIterator->GetX() &&	// assuming 48 is the width of the player
			sprite_y_pos < orcIterator->GetY() + 128 &&	// assuming 128 is the height of the orc
			sprite_y_pos + 48 > orcIterator->GetY())		// assuming 48 is the height of the player
		{
			if (shielded)
			{
				shielded = false;							// Remove shield
			}
			else
			{
				player_health--;
			}
			break;
		}
		else
		{
			++orcIterator;
		}
	}

	// Iterate through boss vector
	for (auto bossIterator = bossSpawner.begin(); bossIterator != bossSpawner.end();)
	{
		// Check collision
		if (sprite_x_pos < bossIterator->GetX() + 200 &&	// assuming 200 is the width of the boss
			sprite_x_pos + 48 > bossIterator->GetX() &&	// assuming 48 is the width of the player
			sprite_y_pos < bossIterator->GetY() + 200 &&	// assuming 200 is the height of the boss
			sprite_y_pos + 48 > bossIterator->GetY())		// assuming 48 is the height of the player
		{
			if (shielded)
			{
				shielded = false;							// Remove shield
			}
			else
			{
				player_health--;
			}
			break;
		}
		else
		{
			++bossIterator;
		}
	}
}


void Onslaught::DamageOrc(OrcEnemy& currentorc, double damage)
{
	currentorc.SetHealth(currentorc.GetHealth() - damage);
}

void Onslaught::DamageBoss(BossEnemy& currentboss, double damage)
{
	currentboss.SetHealth(currentboss.GetHealth() - damage);
}


void Onslaught::CheckIfLost()
{
	if (player_health < 1)
	{
		isDead = true;

		int bullet_instances = bulletSpawner.size();

		int zombie_spawns = zombieSpawner.size();
		int orc_spawns = orcSpawner.size();
		int exploder_spawns = exploderSpawner.size();
		int charger_spawns = chargerSpawner.size();
		int boss_spawns = bossSpawner.size();

		if(powerupSpawner.size() > 0)
			powerupSpawner.pop_back();								// Remove powerup if there is one up

		while (bullet_instances > 0)
		{
			bulletSpawner.pop_back();
			bullet_instances = bulletSpawner.size();
		}
		while (zombie_spawns > 0)									// Delete all zombies
		{
			zombieSpawner.pop_back();
			zombie_spawns = zombieSpawner.size();
		}
		while (charger_spawns > 0)									// Delete all chargers
		{
			chargerSpawner.pop_back();
			charger_spawns = chargerSpawner.size();
		}
		while (exploder_spawns > 0)									// Delete all exploders
		{
			exploderSpawner.pop_back();
			exploder_spawns = exploderSpawner.size();
		}
		while (orc_spawns > 0)										// Delete all orcs
		{
			orcSpawner.pop_back();
			orc_spawns = orcSpawner.size();
		}
		while (boss_spawns > 0)										// Delete all bosses
		{
			bossSpawner.pop_back();
			boss_spawns = bossSpawner.size();
		}

		//reset powerups
		speedy = false;
		shooty = false;
		shielded = false;
		boomy = false;
		
		
		Toad::Renderer::Draw(loss_screen, 0, 0); // End the game
	}
}

void Onslaught::CheckIfWon()
{
	zombie_spawns = 0;
	kill_goal = 0;
	bool victory = true;
	Toad::Renderer::Draw(win_screen, 0, 0); // End the game
}

void Onslaught::SpawnBullet(float bullet_x_pos, float bullet_y_pos)
{
	bulletSpawner.emplace_back(bullet_x_pos, bullet_y_pos, current_state);
}

void Onslaught::randomSpawnPowerup(float milliseconds)
{
	int choice = rand() % 4;					// Pick a number from 0 - 3
	int x_axis_picker = rand() % 900;			// Will choose a location on the horizontal axis between 0 and 900
	int y_axis_picker = rand() % 700;			// Will choose a location on the vertical axis between 0 and 700

	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - powerup_timer);

	// Check if x milliseconds have passed
	if (elapsed_time.count() >= milliseconds)
	{
		powerup_timer = current_time;

		if (choice == 0)											// Speed powerup
		{
			powerup_x_pos = x_axis_picker;	
			powerup_y_pos = y_axis_picker;			
			SpawnPowerup(powerup_x_pos, powerup_y_pos, choice);
		}
		else if (choice == 1)										// Gattling gun powerup
		{
			powerup_x_pos = x_axis_picker;	
			powerup_y_pos = y_axis_picker;				
			SpawnPowerup(powerup_x_pos, powerup_y_pos, choice);
		}
		else if (choice == 2)										// Explosive ammo powerup	
		{
			powerup_x_pos = x_axis_picker;			
			powerup_y_pos = y_axis_picker;	
			SpawnPowerup(powerup_x_pos, powerup_y_pos, choice);
		}
		else if (choice == 3)										// Shield powerup
		{
			powerup_x_pos = x_axis_picker;			
			powerup_y_pos = y_axis_picker;	
			SpawnPowerup(powerup_x_pos, powerup_y_pos, choice);
		}
	}
}

void Onslaught::SpawnPowerup(float powerup_x_pos, float powerup_y_pos, int selector)
{
	if (powerupSpawner.size() < 1)	// Only spawn if there is no powerup on ground
	{
		powerupSpawner.emplace_back(powerup_x_pos, powerup_y_pos, selector);
		std::cout << "spawning powerup! " << std::endl;
	}
}


void Onslaught::randomSpawnZombies(float milliseconds)
{
	int choice = rand() % 4;					// Pick a number from 0 - 3
	int x_axis_picker = rand() % 1000;			// Will choose a location on the horizontal axis between 0 and 1000
	int y_axis_picker = rand() % 800;			// Will choose a location on the vertical axis between 0 and 800

	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - zombie_timer);

	// Check if x milliseconds have passed
	if (elapsed_time.count() >= milliseconds)
	{
		zombie_timer = current_time;

		if (choice == 0)					// Spawn from top
		{
			zombie_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			zombie_y_pos = 900;				// Spawns above the "map"
			SpawnZombie(zombie_x_pos, zombie_y_pos);
		}
		else if (choice == 1)				// Spawn from bottom
		{
			zombie_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			zombie_y_pos = -100;			// Spawns below the "map"
			SpawnZombie(zombie_x_pos, zombie_y_pos);
		}
		else if (choice == 2)				// Spawn from left
		{
			zombie_x_pos = -100;			// Spawns to the left of the "map"
			zombie_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnZombie(zombie_x_pos, zombie_y_pos);
		}
		else if (choice == 3)				// Spawn from right
		{
			zombie_x_pos = 1100;			// Spawns to the right of the "map"
			zombie_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnZombie(zombie_x_pos, zombie_y_pos);
		}
	}
}

void Onslaught::SpawnCharger(float charger_x_pos, float charger_y_pos, bool chargerIsVertical)
{
	if (charger_spawns > 0)
	{
		chargerSpawner.emplace_back(charger_x_pos, charger_y_pos, chargerIsVertical);
		charger_spawns--;
		std::cout << "spawning charger! " << charger_spawns << " spawns left!" << std::endl;
	}
}


void Onslaught::randomSpawnExploders(float milliseconds)
{
	int choice = rand() % 4;					// Pick a number from 0 - 3
	int x_axis_picker = rand() % 1000;			// Will choose a location on the horizontal axis between 0 and 1000
	int y_axis_picker = rand() % 800;			// Will choose a location on the vertical axis between 0 and 800

	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - exploder_timer);

	// Check if x milliseconds have passed
	if (elapsed_time.count() >= milliseconds)
	{
		exploder_timer = current_time;

		if (choice == 0)					// Spawn from top
		{
			exploder_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			exploder_y_pos = 900;				// Spawns above the "map"
			SpawnExploder(exploder_x_pos, exploder_y_pos);
		}
		else if (choice == 1)				// Spawn from bottom
		{
			exploder_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			exploder_y_pos = -100;			// Spawns below the "map"
			SpawnExploder(exploder_x_pos, exploder_y_pos);
		}
		else if (choice == 2)				// Spawn from left
		{
			exploder_x_pos = -100;			// Spawns to the left of the "map"
			exploder_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnExploder(exploder_x_pos, exploder_y_pos);
		}
		else if (choice == 3)				// Spawn from right
		{
			exploder_x_pos = 1100;			// Spawns to the right of the "map"
			exploder_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnExploder(exploder_x_pos, exploder_y_pos);
		}
	}
}


void Onslaught::SpawnExploder(float exploder_x_pos, float exploder_y_pos)
{
	if (exploder_spawns > 0)
	{
		exploderSpawner.emplace_back(exploder_x_pos, exploder_y_pos);
		exploder_spawns--;
		std::cout << "spawning exploder! " << exploder_spawns << " spawns left!" << std::endl;
	}
}

void Onslaught::HandleExplosions()
{
	for (auto explosionIterator = explosionSpawner.begin(); explosionIterator != explosionSpawner.end();)	// Track through each explosion object
	{
		if (explosionIterator->isExpired())	// If some time has passed after spawning
		{
			explosionIterator = explosionSpawner.erase(explosionIterator);	// Delete this explosion instance
		}
		else
		{
			++explosionIterator;	// Track next
		}
	}
}


void Onslaught::SpawnExplosion(float explosion_x_pos, float explosion_y_pos)
{
	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	explosionSpawner.emplace_back(explosion_x_pos - 95, explosion_y_pos - 90, current_time);
	std::cout << "Spawning explosion at (" << explosion_x_pos << ", " << explosion_y_pos << ")" << std::endl;
}


void Onslaught::randomSpawnOrcs(float milliseconds)
{
	int choice = rand() % 4;					// Pick a number from 0 - 3
	int x_axis_picker = rand() % 1000;			// Will choose a location on the horizontal axis between 0 and 1000
	int y_axis_picker = rand() % 800;			// Will choose a location on the vertical axis between 0 and 800

	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - orc_timer);

	// Check if x milliseconds have passed
	if (elapsed_time.count() >= milliseconds)
	{
		orc_timer = current_time;

		if (choice == 0)					// Spawn from top
		{
			orc_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			orc_y_pos = 900;				// Spawns above the "map"
			SpawnOrc(orc_x_pos, orc_y_pos);
		}
		else if (choice == 1)				// Spawn from bottom
		{
			orc_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			orc_y_pos = -100;			// Spawns below the "map"
			SpawnOrc(orc_x_pos, orc_y_pos);
		}
		else if (choice == 2)				// Spawn from left
		{
			orc_x_pos = -100;			// Spawns to the left of the "map"
			orc_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnOrc(orc_x_pos, orc_y_pos);
		}
		else if (choice == 3)				// Spawn from right
		{
			orc_x_pos = 1100;			// Spawns to the right of the "map"
			orc_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnOrc(orc_x_pos, orc_y_pos);
		}
	}
}

void Onslaught::SpawnZombie(float zombie_x_pos, float zombie_y_pos)
{
	if (zombie_spawns != 0)
	{
		zombieSpawner.emplace_back(zombie_x_pos, zombie_y_pos);
		zombie_spawns--;
		std::cout << "spawning zombie! " << zombie_spawns << " spawns left!" << std::endl;
	}
}


void Onslaught::randomSpawnChargers(float milliseconds)
{
	int choice = rand() % 4;					// Pick a number from 0 - 1
	int x_axis_picker = rand() % 1000;			// Will choose a location on the horizontal axis between 0 and 1000
	int y_axis_picker = rand() % 800;			// Will choose a location on the vertical axis between 0 and 800

	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - charger_timer);

	// Check if x milliseconds have passed
	if (elapsed_time.count() >= milliseconds)
	{
		charger_timer = current_time;

		if (choice == 0)					// Spawn at the top
		{
			charger_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			charger_y_pos = 750;			// Spawns at the top of the "map"
			SpawnCharger(charger_x_pos, charger_y_pos, false);
		}
		else if (choice == 1)				// Spawn at the bottom
		{
			charger_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			charger_y_pos = -15;				// Spawns at the bottom of the "map"
			SpawnCharger(charger_x_pos, charger_y_pos, false);
		}
		else if (choice == 2)				// Spawn at the left
		{
			charger_x_pos = -15;			// Spawns at the left of the "map"
			charger_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnCharger(charger_x_pos, charger_y_pos, true);
		}
		else if (choice == 3)				// Spawn at the right
		{
			charger_x_pos = 950;			// Spawns at the right of the "map"
			charger_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnCharger(charger_x_pos, charger_y_pos, true);
		}
	}
}


void Onslaught::SpawnOrc(float orc_x_pos, float orc_y_pos)
{
	if (orc_spawns > 0)
	{
		orcSpawner.emplace_back(orc_x_pos, orc_y_pos);
		orc_spawns--;
		std::cout << "spawning orc! " << orc_spawns << " spawns left!" << std::endl;
	}
}

void Onslaught::randomSpawnBoss(float milliseconds)
{
	int choice = rand() % 4;					// Pick a number from 0 - 3
	int x_axis_picker = rand() % 1100;			// Will choose a location on the horizontal axis between 0 and 1100
	int y_axis_picker = rand() % 900;			// Will choose a location on the vertical axis between 0 and 900

	std::chrono::time_point<std::chrono::steady_clock> current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - boss_timer);

	// Check if x milliseconds have passed
	if (elapsed_time.count() >= milliseconds)
	{
		boss_timer = current_time;

		if (choice == 0)					// Spawn from top
		{
			boss_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			boss_y_pos = 900;				// Spawns above the "map"
			SpawnBoss(boss_x_pos, boss_y_pos);
		}
		else if (choice == 1)				// Spawn from bottom
		{
			boss_x_pos = x_axis_picker;	// Pick a random spot on the x axis to spawn from
			boss_y_pos = -200;			// Spawns below the "map"
			SpawnBoss(boss_x_pos, boss_y_pos);
		}
		else if (choice == 2)				// Spawn from left
		{
			boss_x_pos = -200;			// Spawns to the left of the "map"
			boss_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnBoss(boss_x_pos, boss_y_pos);
		}
		else if (choice == 3)				// Spawn from right
		{
			boss_x_pos = 1100;			// Spawns to the right of the "map"
			boss_y_pos = y_axis_picker;	// Pick a random spot on the y axis to spawn from
			SpawnBoss(boss_x_pos, boss_y_pos);
		}
	}
}


void Onslaught::SpawnBoss(float boss_x_pos, float boss_y_pos)
{
	if (boss_spawns > 0)
	{
		bossSpawner.emplace_back(boss_x_pos, boss_y_pos);
		boss_spawns--;
		std::cout << "spawning boss! " << boss_spawns << " spawns left!" << std::endl;
	}
}


//POWERUPS
void Onslaught::PowerupDecider(int decision)
{
	if (decision == 0)
	{
		SpeedPowerup();
	}
	else if (decision == 1)
	{
		GattlingGunPowerup();
	}
	else if (decision == 2)
	{
		ExplosiveAmmoPowerup();
	}
	else if (decision == 3)
	{
		ShieldPowerup();
	}
}


void Onslaught::SpeedPowerup()
{
	speed = 10; // Boosted speed
	speed_limit = std::chrono::steady_clock::now();
	speedy = true;
	std::cout << "Speed Boost Activated!" << std::endl;
}


void Onslaught::GattlingGunPowerup()
{
	shooty = true;
	shoot_limit = std::chrono::steady_clock::now();
	std::cout << "Gattling Gun Activated!" << std::endl;
}

void Onslaught::ExplosiveAmmoPowerup()
{
	boomy = true;
	explosive_ammo_limit = std::chrono::steady_clock::now();
	std::cout << "Explosive Ammo Activated!" << std::endl;
}


void Onslaught::ShieldPowerup()
{
	shielded = true;
	std::cout << "Shield Activated!" << std::endl;
}


void Onslaught::speedyHandler()
{
	auto current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - speed_limit);

	if (elapsed_time.count() >= speed_duration)
	{
		std::cout << "Speed Boost Ended!" << std::endl;
		speed = 5; // Reset to default speed
		speedy = false;
	}
}


void Onslaught::shootyHandler()
{
	auto current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - shoot_limit);

	if (elapsed_time.count() >= gattling_duration)
	{
		std::cout << "Gattling Gun Ended!" << std::endl;
		shooty = false;
	}
}


void Onslaught::boomHandler()
{
	auto current_time = std::chrono::steady_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - explosive_ammo_limit);

	if (elapsed_time.count() >= explosive_ammo_duration)
	{
		std::cout << "Explosive Ammo Ended!" << std::endl;
		boomy = false;
	}
}


void Onslaught::shieldHandler()
{
	if (shielded)
	{
		Toad::Renderer::Draw(shield, sprite_x_pos - 8, sprite_y_pos - 8);
	}
}


void Onslaught::PerformanceChecker()
{
	std::cout << bulletSpawner.size() << " bullets currently on the map!\n";
	std::cout << zombieSpawner.size() << " zombies currently on the map!\n";
	std::cout << chargerSpawner.size() << " chargers currently on the map!\n";
	std::cout << exploderSpawner.size() << " exploders currently on the map!\n";
	std::cout << explosionSpawner.size() << " explosion currently on the map!\n";
	std::cout << orcSpawner.size() << " orcs currently on the map!\n";
	std::cout << bossSpawner.size() << " bosses currently on the map!\n";
}



START_GAME(Onslaught);