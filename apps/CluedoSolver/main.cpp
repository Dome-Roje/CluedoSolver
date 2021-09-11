#include <iostream>

#include <tGame.hpp>
#include <tObservedPlayer.hpp>

int main(int argc, char *argv[]) {
	tGame game;
	tObservedPlayer player1{"Jarred", game};
	game.addPlayer(player1);
	game.start();
	return 0;
}
