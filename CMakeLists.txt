cmake_minimum_required(VERSION 3.16)
project(NAUQ_game_engine)

#set(CMAKE_C_COMPILER /usr/bin/gcc-10)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(NAUQ)
add_subdirectory(Sandbox)
add_subdirectory(Editor)
add_subdirectory(FlappyBird)


