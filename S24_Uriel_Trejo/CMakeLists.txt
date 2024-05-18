add_executable(Game Source.cpp)

include_directories("../Toad/Include")

target_link_libraries(Game Toad)