#include <iostream>
#include "node.h"
#include "io.h"


IO::IO() {

}


IO::~IO() {

}


bool IO::player_moves_first() {
	do {
		std::cout << 
			"Who should move first, (p)layer or (o)pponent?" << "\n";
		std::string buffer;
		std::cin >> buffer;
		if (buffer[0] != 'p' && buffer[0] != 'o')
			std::cout << "Error, improper input" << "\n";
		else
			return buffer[0] == 'p';
	} while (true);
}


int IO::time_allowed() {
	do {
		std::cout << 
			"How much time should be allotted, 5 or 30 seconds?" << "\n";
		std::string buffer;
		std::cin >> buffer;
		if (buffer[0] == '5')
			return 5;
		else if (buffer[0] == '3' && buffer[1] == '0')
			return 30;
		else
			std::cout << "Error, imporper input" << "\n";
	} while (true);
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

