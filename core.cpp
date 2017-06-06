#include <iostream>
#include "core.h"
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
	Node* node = new Node;

	io.salutations();
	this->set_time_allowed(game, io);
	this->determine_move_order(game, node, io);

	while (true) {

		this->opponent_turn(node,io);
		if (this->has_won(game, node, SYMBOL::OPPONENT))
			return this->complete(game, node, SYMBOL::OPPONENT, io);

		this->computer_turn(game, node, io);
		if (this->has_won(game, node, SYMBOL::PLAYER))
			return this->complete(game, node, SYMBOL::PLAYER, io);

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
	return game.won_game(node, symbol) || game.tied_game(node);
}


int Core::complete(Game& game, Node*& node, char symbol, IO& io) {
	
	Node* out = node;
	std::vector<Node*> nodes;
	while (node != nullptr) {
		nodes.insert(nodes.begin(), node);
		node = node->parent_;
	}

	if (game.won_game(out, SYMBOL::PLAYER)) {
		io.complete(nodes, SYMBOL::PLAYER);
	}
	else if (game.won_game(out, SYMBOL::OPPONENT)) {
		io.complete(nodes, SYMBOL::OPPONENT);
	}
	else if (game.tied_game(out)) {
		io.complete(nodes, SYMBOL::EMPTY);
	}
	game.clear_nodes(nodes);

	return 0;
}


void Core::retroactive_moves(std::vector<Node*>& nodes, IO& io) {


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

