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



	test_config_score_if();
	if (true) return 0;





	Game game;
	IO io;
	Node* node = new Node;

	// re-comment this in
	this->set_time_allowed(game, io);
	this->determine_move_order(game, node, io);

	//node = new Node(node);
	//node->config_[3 * dim::SPAN + 3] = SYMBOL::PLAYER;

	
	while (true) {

		// automated
		// uncommend below to run for real
		this->opponent_turn(node,io);

		// uncomment this to run crappy test
		//this->opponent_turn_test(node, io);

		if (this->has_won(game, node, SYMBOL::OPPONENT))
			return this->complete(node, SYMBOL::OPPONENT, io);

		this->computer_turn(game, node, io);
		if (this->has_won(game, node, SYMBOL::PLAYER))
			return this->complete(node, SYMBOL::PLAYER, io);

	}

	return 0;

}


void Core::determine_move_order(Game& game, Node*& node, IO& io) {
	if (io.computer_moves_first()) {
		node = new Node(node);
		game.make_first_move(node);
		game.set_strategy_offensive();
	}
	else {
		game.set_strategy_defensive();
	}
	io.print_node(node);
}


void Core::set_time_allowed(Game& game, IO& io) {
	game.set_time_allowed(io.time_allowed());
}


void Core::computer_turn(Game& game, Node*& node, IO& io) {
	node = new Node(node);
	game.next_move(node);
	io.print_node(node);
}


void Core::opponent_turn(Node*& node, IO& io) {
	node = new Node(node);
	int element = io.enter_next_move(node);
	node->config_[element] = SYMBOL::OPPONENT;
	io.print_node(node);
}


bool Core::has_won(Game& game, Node* node, char symbol) {
	return game.won_game(node, symbol);
}


// TODO implement to print nodes and find moves taken
int Core::complete(Node*& node, char symbol, IO& io) {
	std::vector<Node*> nodes;
	while (node != nullptr) {
		nodes.insert(nodes.begin(), node);
		node = node->parent_;
	}
	io.complete(nodes,symbol);
	return 0;
}


void Core::retroactive_moves(std::vector<Node*>& nodes, IO& io) {
	std::vector<int> moves;
	for (size_t i = 0; i < nodes.size()-1; ++i) {



	}

}


void Core::clear_nodes(std::vector<Node*>& nodes) {
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i] != nullptr) {
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
}




void Core::opponent_turn_test(Node*& node, IO& io) {
	node = new Node(node);
	for (int i = 0; i < dim::SIZE; ++i) {
		if (node->config_[i] == SYMBOL::EMPTY) {
			node->config_[i] = SYMBOL::OPPONENT;
			break;
		}
	}
	io.print_node(node);
}

