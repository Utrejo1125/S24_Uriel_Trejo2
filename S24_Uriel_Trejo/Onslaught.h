#pragma once

#include "Toad.h"
#include <vector>
#include <chrono>
#include <cstdlib>

#include "BulletEntity.h"
#include "PowerUp.h"
#include "OrcEnemy.h"
#include "ZombieEnemy.h"
#include "ChargerEnemy.h"
#include "ExploderEnemy.h"
#include "Explosion.h"
#include "BossEnemy.h"

#include "HUD.h"

class BulletEntity; // Forward declaration

class Onslaught : public Toad::ToadApplication
{
public:
	Onslaught();

	void restartGame();
	void startGame();
	void startLevel();
	void LevelHandler(int level);
	void TrackKills();

	void OnUpdate() override;

	void OnKeyPress(const Toad::KeyPressed& e);
	void OnKeyRelease(const Toad::KeyReleased& e);

	void HandleSpriteMovement();
	bool CheckIfMoving();

	void HandleBullet();
	void HandleGattlingGun();

	void HandlePowerup();
	
	void HandleZombieCollision();
	void HandleChargerCollision();
	void HandleExploderCollision();
	void HandleExplosionCollision();
	void HandleOrcCollision();
	void HandleBossCollision();
	void HandlePlayerCollision();

	void DamageOrc(OrcEnemy& currentorc, double damage);
	void DamageBoss(BossEnemy& currentboss, double damage);

	void CheckIfLost();
	void CheckIfWon();

	//Spawners
	void SpawnBullet(float bullet_x_pos, float bullet_y_pos);

	void randomSpawnPowerup(float milliseconds);
	void SpawnPowerup(float powerup_x_pos, float powerup_y_pos, int selector);

	void randomSpawnZombies(float milliseconds);
	void SpawnZombie(float zombie_x_pos, float zombie_y_pos);
	void randomSpawnChargers(float milliseconds);
	void SpawnCharger(float charger_x_pos, float charger_y_pos, bool chargerIsVertical);
	void randomSpawnExploders(float milliseconds);
	void SpawnExploder(float exploder_x_pos, float exploder_y_pos);
	void HandleExplosions();
	void SpawnExplosion(float explosion_x_pos, float explosion_y_pos);
	void randomSpawnOrcs(float milliseconds);
	void SpawnOrc(float orc_x_pos, float orc_y_pos);
	void randomSpawnBoss(float milliseconds);
	void SpawnBoss(float boss_x_pos, float boss_y_pos);


	//Powerups
	void PowerupDecider(int decision);
	void SpeedPowerup();
	void GattlingGunPowerup();
	void ExplosiveAmmoPowerup();
	void ShieldPowerup();

	enum SPRITE_STATE
	{
		UP, LEFT, RIGHT, DOWN
	};

private:
	// Assets:
	Toad::Image background{ "../Assets/Textures/Onslaught/background.png" };
	Toad::Image loss_screen{ "../Assets/Textures/Onslaught/lose.png" };
	Toad::Image win_screen{ "../Assets/Textures/Onslaught/win.png" };
	Toad::Image bullet{ "../Assets/Textures/Onslaught/sprite_down.png" };

	Toad::Image shield{ "../Assets/Textures/Onslaught/shield.png" };

	Toad::Image sprite_up{ "../Assets/Textures/Onslaught/sprite_up.png" };
	Toad::Image sprite_left{ "../Assets/Textures/Onslaught/sprite_left.png" };
	Toad::Image sprite_right{ "../Assets/Textures/Onslaught/sprite_right.png" };
	Toad::Image sprite_down{ "../Assets/Textures/Onslaught/sprite_down.png" };

	Toad::Image sprite_up_speed{ "../Assets/Textures/Onslaught/sprite_up_speed.png" };
	Toad::Image sprite_left_speed{ "../Assets/Textures/Onslaught/sprite_left_speed.png" };
	Toad::Image sprite_right_speed{ "../Assets/Textures/Onslaught/sprite_right_speed.png" };
	Toad::Image sprite_down_speed{ "../Assets/Textures/Onslaught/sprite_down_speed.png" };

	Toad::Image sprite_up_gattling{ "../Assets/Textures/Onslaught/sprite_up_gattling.png" };
	Toad::Image sprite_left_gattling{ "../Assets/Textures/Onslaught/sprite_left_gattling.png" };
	Toad::Image sprite_right_gattling{ "../Assets/Textures/Onslaught/sprite_right_gattling.png" };
	Toad::Image sprite_down_gattling{ "../Assets/Textures/Onslaught/sprite_down_gattling.png" };

	Toad::Image sprite_up_boom{ "../Assets/Textures/Onslaught/sprite_up_boom.png" };
	Toad::Image sprite_left_boom{ "../Assets/Textures/Onslaught/sprite_left_boom.png" };
	Toad::Image sprite_right_boom{ "../Assets/Textures/Onslaught/sprite_right_boom.png" };
	Toad::Image sprite_down_boom{ "../Assets/Textures/Onslaught/sprite_down_boom.png" };

	// Asset positions
	float sprite_x_pos = 450;
	float sprite_y_pos = 400;	
	SPRITE_STATE current_state = UP;

	float powerup_x_pos = 0;
	float powerup_y_pos = 0;

	float zombie_x_pos = 1000;
	float zombie_y_pos = 800;
	float orc_x_pos = 1000;
	float orc_y_pos = 800;
	float charger_x_pos = 1000;
	float charger_y_pos = 800;	
	float exploder_x_pos = 800;	
	float exploder_y_pos = 1000;	
	float explosion_x_pos = 800;	
	float explosion_y_pos = 1000;	
	float boss_x_pos = 800;	
	float boss_y_pos = 1000;

	// Ruleset
	int num_keys_pressed = 0;
	bool isMoving = false;
	bool isDead = false;
	bool wonLevel = false;
	bool victory = false;

	// Spawners
	std::vector<BulletEntity> bulletSpawner;
	std::vector<ZombieEnemy> zombieSpawner;
	std::vector<ExploderEnemy> exploderSpawner;
	std::vector<Explosion> explosionSpawner;
	std::vector<ChargerEnemy> chargerSpawner;
	std::vector<OrcEnemy> orcSpawner;
	std::vector<BossEnemy> bossSpawner;
	std::vector<PowerUp> powerupSpawner;

	// Number of spawns
	int zombie_spawns;
	int charger_spawns;
	int exploder_spawns;
	int orc_spawns;
	int boss_spawns;

	// Spawn Rates
	double zombie_spawn_rate = 1000;
	double charger_spawn_rate = 1000;
	double exploder_spawn_rate = 1000;
	double orc_spawn_rate = 1000;
	double boss_spawn_rate = 5000;
	double powerup_spawn_rate = 30000;	// 30 seconds

	// Timers
	std::chrono::time_point<std::chrono::steady_clock> zombie_timer;
	std::chrono::time_point<std::chrono::steady_clock> charger_timer;
	std::chrono::time_point<std::chrono::steady_clock> exploder_timer;
	std::chrono::time_point<std::chrono::steady_clock> explosion_timer;
	std::chrono::time_point<std::chrono::steady_clock> orc_timer;
	std::chrono::time_point<std::chrono::steady_clock> boss_timer;
	std::chrono::time_point<std::chrono::steady_clock> powerup_timer;

	std::chrono::time_point<std::chrono::steady_clock> speed_limit;

	std::chrono::time_point<std::chrono::steady_clock> shoot_limit;
	std::chrono::time_point<std::chrono::steady_clock> last_shoot_time;


	std::chrono::time_point<std::chrono::steady_clock> explosive_ammo_limit;



	//Powerup stuff
	int player_health;

	void speedyHandler();
	int speed = 5;
	const double speed_duration = 20000;	// Lasts 20 seconds
	bool speedy = false;

	void shootyHandler();
	const double gattling_duration = 30000;		// Lasts 30 seconds
	bool shooty = false;
	const double shoot_interval = 80; // Interval between shots

	void boomHandler();
	const double explosive_ammo_duration = 15000;	// Lasts 15 seconds
	bool boomy = false;

	void shieldHandler();
	bool shielded = false;


	//Level
	int level = 1;
	int kills = 0;
	int kill_goal;

	//HUD
	HUD hud;
};



/*
Sprite info for reference:
sprite is a 64x64 dude
if (0, 0) is top left corner; (48, 0) - (49, 1) (4 pixels) is barrel location (UP sprite)
character is 50 pixels wide, and 50 pixels tall. It is a circle.


Enemy Types:
Zombie -> Follows player 
Chargers -> Move either horizontally or vertically and charge at the player if they "see" you
Exploders -> Move slow but will explode if you get too close and have large AOE
Orc -> Slower than regular zombie, but takes multiple hits
Boss -> Level does not end until the boss dies, has a lot of health

Power Ups:
Speed Bonus -> Player will move faster for 60s
Machine Gun -> Player can hold shoot and rapid-fire for 60s
Explosive Bullets -> Bullets will explode on enemy impact for 30s, be careful!
Shield -> Player can take an extra hit, will not work on orcs or bosses

Levels:
Level 1 -> Easiest level, zombies only, slower spawn rate, 20 zombies
Level 2 -> zombies only, faster spawn rate, 50 zombies
Level 3 -> zombies and chargers: 40 zombies, 10 chargers
Level 4 -> zombies, chargers, and exploders: 40 zombies, 10 chargers, 20 exploders
Level 5 -> zombies, exploders, and a few orcs: 40 zombies, 15 exploders, 5 orcs
Level 6 -> orcs orcs orcs: 20 orcs, faster spawn rate
Level 7 -> boss fight: infinite zombies and the Boss
*/