#include <iostream>
#include "io.h"
#include "node.h"
//#include "global.h"


IO::IO() {

}


IO::~IO() {

}


void IO::print_node(Node* node) {
	this->print_config(node);
	std::cout << "\n" <<
		"Alpha " << node->alpha_ << "\n" <<
		"Beta  " << node->beta_ << "\n" << std::endl;
}


void IO::print_config(Node* node) {
	std::cout << "  ";
	for (int i = 0; i < dim::SPAN; ++i)
		std::cout << i + 1 << " ";
	for (int i = 0; i < dim::SIZE; ++i) {
		if (i % dim::SPAN == 0)
			std::cout << "\n" <<
			static_cast<char>('A' + i / dim::SPAN) << " ";
		std::cout << node->config_[i] << " ";
	}
	std::cout << "\n" << std::endl;
}


// a messy method!
void IO::print_node_and_vec_score(Node* node) {

	std::cout << "Plr     ";
	for (int i = 0; i < dim::SPAN; ++i)
		std::cout << node->col_player_[i] << " ";
	std::cout << "\n\n" << "   Opp  ";
	for (int i = 0; i < dim::SPAN; ++i)
		std::cout << node->col_opponent_[i] << " ";
	std::cout << "\n\n" << "        ";

	for (int i = 0; i < dim::SPAN; ++i)
		std::cout << i + 1 << " ";
	for (int i = 0; i < dim::SIZE; ++i) {
		if (i % dim::SPAN == 0) {
			std::cout << "\n" << node->row_player_[i/dim::SPAN] << "  ";
			std::cout << node->row_opponent_[i/dim::SPAN] << "  ";
			std::cout << static_cast<char>('A'+i/dim::SPAN) << " ";
		}
		std::cout << node->config_[i] << " ";
	}
	std::cout << "\n\n" <<
		"Player score    " << node->player_score_ << "\n" <<
		"Opponent score  " << node->opponent_score_ << "\n\n" << std::endl;

}

