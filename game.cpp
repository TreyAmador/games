#include "game.h"
#include "node.h"
#include "io.h"
#include <iostream>


namespace {
	const int MAX_LEAVES = 5;
}


typedef Node* GameBoard;


Game::Game() {

}


Game::~Game() {
	
}



// TODO pass a bool to determine if you as a player
//		are the maximizing or minimizing player
void Game::next_move(Node* node, int depth) {
	
	int best = INT_MIN;
	int score = 0;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	int element = -1;

	std::vector<int> moves = this->query_possible_moves(node);
	for (size_t i = 0; i < moves.size(); ++i) {
		node->config_[moves[i]] = SYMBOL::PLAYER;
		score = this->minimize(node, alpha, beta, depth - 1);
		if (score > best) {
			best = score;
			element = moves[i];
		}
		node->config_[moves[i]] = SYMBOL::EMPTY;
	}
	node->config_[element] = SYMBOL::PLAYER;
}


int Game::minimize(Node* node, int& alpha, int& beta, int depth) {

	int best = INT_MAX;
	int score;

	if (this->won_game(node, SYMBOL::PLAYER)) {
		return
			this->calculate_config_score(node, SYMBOL::PLAYER);
	}
	if (this->won_game(node, SYMBOL::OPPONENT)) {
		return
			this->calculate_config_score(node, SYMBOL::PLAYER);
	}
	if (depth == 0) {
		return
			this->calculate_config_score(node, SYMBOL::PLAYER);
	}

	std::vector<int> moves = this->query_possible_moves(node);
	for (size_t i = 0; i < moves.size(); ++i) {
		node->config_[moves[i]] = SYMBOL::OPPONENT;
		score = this->maximize(node, alpha, beta, depth - 1);
		if (score < best) {
			best = score;
		}
		node->config_[moves[i]] = SYMBOL::EMPTY;
		alpha = alpha > score ? alpha : score;
		if (alpha > beta) {
			break;
		}
	}
	return best;
}


int Game::maximize(Node* node, int& alpha, int& beta, int depth) {

	int best = INT_MIN;
	int score;

	if (this->won_game(node, SYMBOL::PLAYER)) {
		return
			this->calculate_config_score(node, SYMBOL::PLAYER);
	}
	if (this->won_game(node, SYMBOL::OPPONENT)) {
		return 
			this->calculate_config_score(node, SYMBOL::PLAYER);
	}
	if (depth == 0) {
		return 
			this->calculate_config_score(node, SYMBOL::PLAYER);
	}

	std::vector<int> moves = this->query_possible_moves(node);
	for (size_t i = 0; i < moves.size(); ++i) {
		node->config_[moves[i]] = SYMBOL::PLAYER;
		score = this->minimize(node, alpha, beta, depth - 1);
		if (score > best) {
			best = score;
		}
		node->config_[moves[i]] = SYMBOL::EMPTY;
		beta = beta < score ? beta : score;
		if (alpha > beta) {
			break;
		}
	}
	return best;
}



int Game::calculate_config_score(Node* node, char symbol) {
	int score = 0;
	for (int i = 0; i < dim::SPAN; ++i) {
		score += this->update_min_max_row(node, i, symbol);
		score += this->update_min_max_col(node, i, symbol);
	}
	return score;
}


// TODO make something smarter here!
std::vector<int> Game::query_possible_moves(Node* node) {
	std::vector<int> moves;
	for (int r = 0; r < dim::SPAN; ++r) {
		for (int c = 0; c < dim::SPAN; ++c) {
			int index = r*dim::SPAN+c;
			if (node->config_[index] != SYMBOL::EMPTY) {
				if (r != 0 && node->config_[index - 1] == SYMBOL::EMPTY)
					this->insert_unique(moves, index - 1);
				if (r != dim::SPAN && node->config_[index + 1] == SYMBOL::EMPTY)
					this->insert_unique(moves, index + 1);
				if (c != 0 && node->config_[index - dim::SPAN] == SYMBOL::EMPTY)
					this->insert_unique(moves, index - dim::SPAN);
				if (c != dim::SPAN && node->config_[index + dim::SPAN] == SYMBOL::EMPTY)
					this->insert_unique(moves, index + dim::SPAN);
			}
		}
	}
	return moves;
}


void Game::insert_unique(std::vector<int>& vec, int elem) {
	for (size_t i = 0; i < vec.size(); ++i)
		if (vec[i] == elem)
			return;
	vec.push_back(elem);
}


// this works
int Game::update_min_max_row(Node* node, int row, char player) {
	int row_score = 0;
	int r = row*dim::SPAN;
	for (int c = 0; c <= dim::MAX_ADJ; ++c) {
		int uninterrupted = 0;
		for (int i = 0; i < dim::MAX_ADJ && uninterrupted != -1; ++i) {
			char symbol = node->config_[r+c+i];
			if (symbol == player)
				++uninterrupted;
			else if (symbol != SYMBOL::EMPTY)
				uninterrupted = -1;
		}
		row_score += (uninterrupted != -1 ? uninterrupted : 0);
	}
	return row_score;
}


// this works
int Game::update_min_max_col(Node* node, int col, char player) {
	int c = col;
	int column_score = 0;
	for (int r = 0; r <= dim::MAX_ADJ; ++r) {
		int uninterrupted = 0;
		for (int i = 0; i < dim::MAX_ADJ && uninterrupted != -1; ++i) {
			char symbol = node->config_[c+dim::SPAN*(r+i)];
			if (symbol == player)
				++uninterrupted;
			else if (symbol != SYMBOL::EMPTY)
				uninterrupted = -1;
		}
		column_score += (uninterrupted != -1 ? uninterrupted : 0);
	}
	return column_score;
}


// TODO optimize this based on what leads to victory!
//		perhaps:
//			row = rand() % 2 == 0 ? 3 : 4;
//			col = rand() % 2 == 0 ? 3 : 4;
void Game::make_first_move(Node* node) {
	int row = 3, col = 3;
	this->place_symbol_by_indeces(node, SYMBOL::PLAYER, row, col);
}


// should be used when placing symbols using the row and col numbers
// that are indeces in the array
void Game::place_symbol_by_indeces(Node* node, char symbol, int row, int col) {
	node->config_[row*dim::SPAN+col] = symbol;
}


// does this really need to be included..?
void Game::place_symbol_from_prompt(Node* node, char symbol, int row, int col) {
	node->config_[(row-1)*dim::SPAN+(col-1)] = symbol;
}



void Game::clear_nodes(std::vector<Node*>& nodes) {
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i] != nullptr) {
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
}


// this works
bool Game::won_game(Node* node, char symbol) {

	for (int r = 0; r < dim::SPAN; ++r) {
		int consecutive = 0;
		for (int c = 0; c < dim::SPAN; ++c) {
			if (node->config_[r*dim::SPAN+c] == symbol) {
				++consecutive;
				if (consecutive == dim::MAX_ADJ) {
					return true;
				}
			}
			else {
				consecutive = 0;
			}
		}
	}

	for (int c = 0; c < dim::SPAN; ++c) {
		int consecutive = 0;
		for (int r = 0; r < dim::SPAN; ++r) {
			if (node->config_[r*dim::SPAN + c] == symbol) {
				++consecutive;
				if (consecutive == dim::MAX_ADJ) {
					return true;
				}
			}
			else {
				consecutive = 0;
			}
		}
	}

	return false;
}


