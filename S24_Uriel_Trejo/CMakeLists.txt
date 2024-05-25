cmake_minimum_required(VERSION 3.10)
project(GameEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories("../Toad/Include")

# Set header and source files
set(HEADER_FILES
    BossEnemy.h
    BulletEntity.h
    ChargerEnemy.h
    Enemy.h
    ExploderEnemy.h
    Explosion.h
    HUD.h
    Onslaught.h
    OrcEnemy.h
    PowerUp.h
    ZombieEnemy.h
)

set(SOURCE_FILES
    BossEnemy.cpp
    BulletEntity.cpp
    ChargerEnemy.cpp
    Enemy.cpp
    ExploderEnemy.cpp
    Explosion.cpp
    HUD.cpp
    Onslaught.cpp
    OrcEnemy.cpp
    PowerUp.cpp
    ZombieEnemy.cpp
)

# Add the executable
add_executable(Game ${SOURCE_FILES})

# Link the libraries
target_link_libraries(Game Toad)
