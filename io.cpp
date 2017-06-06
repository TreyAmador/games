#include <iostream>
#include "node.h"
#include "io.h"



namespace {
	const int IMPROPER_INPUT = -1;
}


IO::IO() {

}


IO::~IO() {

}


void IO::salutations() {
	std::cout << "\n" <<
		"Greetings, welcome a rather unintelligent" << 
		" 4-in-a-line solver.  See if you can beat it!" << "\n" << std::endl;
}


bool IO::computer_moves_first() {
	do {
		std::cout << 
			"Who should move first, (c)omputer or (h)uman?" << "\n";
		std::string buffer;
		std::cin >> buffer;
		if (buffer[0] != 'c' && buffer[0] != 'h')
			std::cout << "Error, improper input!" << "\n";
		else
			return buffer[0] == 'c';
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
			std::cout << "Error, imporper input!" << "\n";
	} while (true);
}


int IO::enter_next_move(Node* node) {
	do {
		std::cout <<
			"Enter your next move." << "\n" <<
			"First, a row between 'a' and 'h', and then" << 
			" a column between '1' and '8'." << "\n";
		std::string input;
		std::cin >> input;
		int next_move = IMPROPER_INPUT;
		if ((next_move = this->next_move_validity(node, input)) != IMPROPER_INPUT)
			return next_move;
		else
			std::cout << "Error, improper input!" << "\n\n";
	} while (true);
}


int IO::next_move_validity(Node* node, std::string& input) {
	
	if (input.size() < 2)
		return IMPROPER_INPUT;
	char row_c = input[0], col_c = input[1];
	if (row_c < 'a' || row_c > 'h')
		return IMPROPER_INPUT;
	if (col_c < '1' || col_c > '8')
		return IMPROPER_INPUT;

	int row = static_cast<int>(row_c-'a');
	int col = static_cast<int>(col_c-'1');

	int element = row*dim::SPAN+col;
	if (node->config_[element] != SYMBOL::EMPTY)
		return IMPROPER_INPUT;
	else
		return element;

}


void IO::print_node(Node* node) {
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


void IO::complete(std::vector<Node*>& nodes, char symbol) {

	if (symbol == SYMBOL::PLAYER)
		std::cout << "The computer has won." << "\n\n" << std::endl;
	else if (symbol == SYMBOL::OPPONENT)
		std::cout << "Congratulations, you have won." << "\n\n" << std::endl;
	else if (symbol == SYMBOL::EMPTY)
		std::cout << "The game is a tie." << "\n\n" << std::endl;

	std::cout << "The winning moves: " << std::endl;
	for (size_t n = 1; n < nodes.size(); ++n) {
		bool incomplete = true;
		for (int i = 0; i < dim::SIZE && incomplete; ++i) {
			if (nodes[n - 1]->config_[i] != nodes[n]->config_[i]) {
				std::cout << "\n" <<
					nodes[n]->config_[i] << " at " <<
					static_cast<char>(i/dim::SPAN + 'A') <<
					(i%dim::SPAN) + 1 << " ";
				incomplete = false;
			}
		}
	}
	std::cout << "\n" << std::endl;
}


