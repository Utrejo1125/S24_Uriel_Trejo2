add_executable(Game game.cpp) 

include_directories("../Toad/Include")

target_link_libraries(Game Toad)