#include <iostream>
#include "core.h"
#include "node.h"
#include "game.h"
#include "test.h"
#include "io.h"


Core::Core() {
	
}


Core::~Core() {

}


int Core::run() {

	Game game;
	IO io;
	Node* node = test_node_01();
	
	int score = game.calculate_config_score(node, SYMBOL::PLAYER);
	io.print_config(node);
	std::cout << "score " << score << std::endl;

	game.next_move(node, 5);
	
	score = game.calculate_config_score(node, SYMBOL::PLAYER);
	io.print_config(node);
	std::cout << "score " << score << std::endl;

	return 0;

}

