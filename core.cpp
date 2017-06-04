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
	io.print_node(node);
	std::cout << "score " << score << std::endl;
	game.next_move(node,50);
	score = game.calculate_config_score(node, SYMBOL::PLAYER);
	io.print_node(node);
	std::cout << "score " << score << std::endl;


	//Node* node = new Node;
	//this->determine_move_order(game,io,node);
	//while (true) {
	//	node = new Node(node);
	//}




	return 0;

}


void Core::determine_move_order(Game& game, IO& io, Node* node) {
	if (io.computer_moves_first()) {
		node = new Node(node);
		game.make_first_move(node);
	}
}


