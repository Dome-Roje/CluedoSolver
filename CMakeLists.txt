cmake_minimum_required(VERSION 3.20)

project(Cluedo
	VERSION 1.0
	DESCRIPTION "A Cluedo bot to play Cluedo optimally"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(game)
add_subdirectory(apps/CluedoSolver)