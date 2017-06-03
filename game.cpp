#include "game.h"
#include "node.h"
#include "io.h"
#include <iostream>


namespace {
	const int MAX_LEAVES = 5;
}


typedef Node* GameBoard;


//struct IndexElement {
//	int index_;
//	int element_;
//};


Game::Game() {

}


Game::~Game() {
	
}


// TODO implement this where you go across row and column
//		to get next good value
//		perhaps check score in increments of four,
//			then place node in position which maximizes utility
//			relative to that four increment value
std::vector<Node*> Game::possible_configs(Node* root) {

	std::vector<Node*> nodes;


	return nodes;
}



// TODO implement this method!
//
//
//		returns the index of the next potential moves
//		this should be different depending on alpha/beta
//
//		push pairs of coords onto vector
//		decide which has the greatest weight
//			determined by score of row and col
//		a way to weight the values would be nice
//		and it's probably adventageous to give priority
//			to more centered moves ?
//
//		if you are alpha
//			choose the highest value for player
//		if you are beta
//			choose highest value for opponent
//		test while vector.size <= 5 ?


std::vector<int> Game::query_moves_alpha(Node* node) {

	// perhaps allocate memory right off the bat
	std::vector<int> indices;

	
	int idx = -1;
	int fst_row = this->greatest_index(node->row_player_, idx);
	int sec_row = this->greatest_index(node->row_player_, idx);
	idx = -1;
	int fst_col = this->greatest_index(node->col_player_, idx);
	int sec_col = this->greatest_index(node->col_player_, idx);
	

	return indices;
	
}



// this works
int Game::greatest_index(int* config, int& bypass) {
	int max_elem = -1, max_indx = -1;
	for (int i = 0; i < dim::SPAN; ++i) {
		int cur_elem = config[i];
		if (cur_elem > max_elem && i != bypass) {
			max_elem = cur_elem;
			max_indx = i;
		}
	}
	bypass = max_indx;
	return max_indx;
}


/*
int Game::greatest_index(char* config, int& bypass) {
	char max_elem = -1;
	int max_indx = -1;
	for (int i = 0; i < dim::SPAN; ++i) {
		char cur_elem = config[i];
		if (cur_elem > max_elem && i != bypass) {
			max_elem = cur_elem;
			max_indx = i;
		}
	}
	bypass = max_indx;
	return max_indx;
}
*/


// TODO test this
Node* Game::create_child_node(Node* parent, int row, int col, char symbol) {
	Node* child = new Node(parent);
	child->config_[row*dim::SPAN+col] = symbol;
	this->calculate_vector_scores(child, row, col);
	this->calculate_score_from_vectors(
		child, child->player_score_, child->opponent_score_);
	child->parent_ = parent;
	return child;
}


void Game::calculate_vector_scores(Node* node, int row, int col) {
	node->row_player_[row] = this->update_min_max_row(node, row, SYMBOL::PLAYER);
	node->col_player_[col] = this->update_min_max_col(node, col, SYMBOL::PLAYER);
	node->row_opponent_[row] = this->update_min_max_row(node, row, SYMBOL::OPPONENT);
	node->col_opponent_[col] = this->update_min_max_col(node, col, SYMBOL::OPPONENT);
}



// pass player and opponent scores by reference
// return player score, not opponent score
void Game::calculate_score_from_vectors(Node* node, int& player, int& opponent) {
	player = opponent = 0;
	for (int i = 0; i < dim::SPAN; ++i) {
		player += node->row_player_[i] + node->col_player_[i];
		opponent += node->row_opponent_[i] + node->col_opponent_[i];
	}
}



// TODO perhaps replace the player opponent args with
//		if symbol != player
//		else if symbol != SYMBOL::EMPTY
//			uninterrupted = -1;
//		then set to zero

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




// call after each game
// it will reset everything
void Game::reset_game_board() {
	

}


