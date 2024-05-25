add_executable(Game onslaught.cpp) 

include_directories("../Toad/Include")

set(HEADER_FILES
	/BossEnemy.h
	/BulletEntity.h
	/ChargerEnemy.h
	/Enemy.h
	/ExploderEnemy.h
	/Explosion.h
	/HUD.h
	/Onslaught.h
	/OrcEnemy.h
	/PowerUp.h
	/ZombieEnemy.h
)

set(SOURCE_FILES
	/BossEnemy.cpp
	/BulletEntity.cpp
	/ChargerEnemy.cpp
	/Enemy.cpp
	/ExploderEnemy.cpp
	/Explosion.cpp
	/HUD.cpp
	/Onslaught.cpp
	/OrcEnemy.cpp
	/PowerUp.cpp
	/ZombieEnemy.cpp
)

target_link_libraries(Game Toad)