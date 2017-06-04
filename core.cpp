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

	//test_node_ptr();

	
	Game game;
	IO io;
	Node* node = new Node;
	this->set_time_allowed(game, io);
	this->determine_move_order(game, node, io);

	while (true) {

		this->opponent_turn(node,io);
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
		io.print_node(node);
	}
}


void Core::set_time_allowed(Game& game, IO& io) {
	game.set_time_allowed(io.time_allowed());
}


void Core::computer_turn(Game& game, Node*& node, IO& io) {
	node = new Node(node);
	game.next_move(node, 50);
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


void Core::clear_nodes(std::vector<Node*>& nodes) {
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i] != nullptr) {
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
}


void Core::print_nodes(Node* node, IO& io) {
	while (node != nullptr) {
		io.print_node(node);
		node = node->parent_;
	}
}



