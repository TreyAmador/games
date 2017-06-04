#include <iostream>
#include "core.h"
#include "test.h"
#include "node.h"
#include "game.h"
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

	game.next_move(node, 5, true);
	
	score = game.calculate_config_score(node, SYMBOL::PLAYER);
	io.print_config(node);
	std::cout << "score " << score << std::endl;

	


	/*
	Node* parent = test_node_02();
	io.print_config(parent);
	int max = game.minimax(parent,5, true);
	std::cout << max << std::endl;
	io.print_config(parent);
	int move = game.get_best_move();
	parent->config_[move] = '!';
	io.print_config(parent);
	*/


	return 0;

}

