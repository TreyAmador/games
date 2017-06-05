#include "game.h"
#include "node.h"
#include "io.h"
#include <iostream>
#include <cmath>


namespace {
	const int COMPUTER_WIN = 5000;
	const int PLAYER_WIN = -5000;

	// 63 should be the theoretical upper limit ? 
	const int MAX_DEPTH = 25;
}


typedef Node* GameBoard;


Game::Game() {

}


Game::~Game() {
	
}


// TODO implement minimizing or maximizing player ability
void Game::next_move(Node* node) {

	int best_score = 0;
	int best_element = -1;
	int depth = 1;

	while (depth < MAX_DEPTH) {
		int element = this->minimax(node, depth);
		int score = this->calculate_config_score(node, SYMBOL::PLAYER);
		if (score > best_score) {
			best_score = score;
			best_element = element;
		}
		node->config_[element] = SYMBOL::EMPTY;
		++depth;
	}

	node->config_[best_element] = SYMBOL::PLAYER;
}


// TODO next move tailoring
//
//
//		update heuristic!
//			it's crap!
//			perhaps calculate heuristic in same function searching moves
//
//

int Game::minimax(Node* node, int depth) {
	
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
	return element;
}


// NOTE it is questionable if there is some better value to return
//		upon a victory / defeat ...  what would work best?
//		this should be revised, a computer win was this before:
//			return this->calculate_config_score(node, SYMBOL::PLAYER);
int Game::minimize(Node* node, int& alpha, int& beta, int depth) {

	int best = INT_MAX;
	int score;

	if (this->won_game(node, SYMBOL::PLAYER))
		return this->calculate_config_score(node, SYMBOL::PLAYER);
	if (this->won_game(node, SYMBOL::OPPONENT))
		return -this->calculate_config_score(node, SYMBOL::OPPONENT);
	if (depth == 0)
		//return this->calculate_config_score(node, SYMBOL::PLAYER);
		return 
			this->calculate_config_score(node, SYMBOL::PLAYER) - 
			this->calculate_config_score(node,SYMBOL::OPPONENT);

	bool unpruned = true;
	std::vector<int> moves = this->query_possible_moves(node);
	for (size_t i = 0; i < moves.size() && unpruned; ++i) {

		node->config_[moves[i]] = SYMBOL::OPPONENT;
		score = this->maximize(node, alpha, beta, depth - 1);
		if (score < best)
			best = score;
		node->config_[moves[i]] = SYMBOL::EMPTY;

		alpha = alpha > score ? alpha : score;
		if (alpha > beta)
			unpruned = false;
	}
	return best;
}


int Game::maximize(Node* node, int& alpha, int& beta, int depth) {

	int best = INT_MIN;
	int score;

	if (this->won_game(node, SYMBOL::PLAYER))
		return this->calculate_config_score(node, SYMBOL::PLAYER);
	if (this->won_game(node, SYMBOL::OPPONENT))
		return -this->calculate_config_score(node, SYMBOL::OPPONENT);
	if (depth == 0)
		//return this->calculate_config_score(node, SYMBOL::PLAYER);
		return
			this->calculate_config_score(node, SYMBOL::PLAYER) -
			this->calculate_config_score(node, SYMBOL::OPPONENT);

	bool unpruned = true;
	std::vector<int> moves = this->query_possible_moves(node);
	for (size_t i = 0; i < moves.size() && unpruned; ++i) {
		
		node->config_[moves[i]] = SYMBOL::PLAYER;
		score = this->minimize(node, alpha, beta, depth - 1);
		if (score > best)
			best = score;
		node->config_[moves[i]] = SYMBOL::EMPTY;

		beta = beta < score ? beta : score;
		if (alpha > beta)
			unpruned = false;
	}
	return best;
}



int Game::calculate_config_score(Node* node, char player) {


	int heuristic = 0;


	for (int r = 0; r < dim::SPAN; ++r) {
		for (int c = 0; c < dim::SPAN; ++c) {

			int index = r*dim::SPAN+c;
			char symbol = node->config_[index];

			if (node->config_[index] == player) {



				//std::cout << "row x col " << 
				//	index / dim::SPAN << " " << 
				//	index%dim::SPAN << std::endl;



				int plyr_l = 0, plyr_r = 0, plyr_u = 0, plyr_d = 0;
				int oppn_l = 0, oppn_r = 0, oppn_u = 0, oppn_d = 0;
				int free_l = 2, free_r = 2, free_u = 2, free_d = 2;
				
				if (c > 0 && node->config_[index-1] != SYMBOL::EMPTY) {
					if (node->config_[index-1] == player) {
						++plyr_l;
					}
					else {
						++oppn_l;
					}
				}
				if (c > 1 && node->config_[index-2] != SYMBOL::EMPTY) {
					if (node->config_[index-2] == player) {
						++plyr_l;
					}
					else {
						++oppn_l;
					}
				}
				//std::cout << "left  " << plyr_l << " " << oppn_l << std::endl;



				if (c < dim::SPAN-1 && node->config_[index+1] != SYMBOL::EMPTY) {
					if (node->config_[index+1] == player) {
						++plyr_r;
					}
					else {
						++oppn_r;
					}
				}
				if (c < dim::SPAN-2 && node->config_[index+2] != SYMBOL::EMPTY) {
					if (node->config_[index+2] == player) {
						++plyr_r;
					}
					else {
						++oppn_r;
					}
				}
				//std::cout << "right " << plyr_r << " " << oppn_r << std::endl;



				if (r > 0 && node->config_[index-dim::SPAN] != SYMBOL::EMPTY) {
					if (node->config_[index-dim::SPAN] == player) {
						++plyr_u;
					}
					else {
						++oppn_u;
					}
				}
				if (r > 1 && node->config_[index-2*dim::SPAN] != SYMBOL::EMPTY) {
					if (node->config_[index-2*dim::SPAN] == player) {
						++plyr_u;
					}
					else {
						++oppn_u;
					}
				}
				//std::cout << "up    " << plyr_u << " " << oppn_u << std::endl;



				if (r < dim::SPAN-1 && node->config_[index+dim::SPAN] != SYMBOL::EMPTY) {
					if (node->config_[index + dim::SPAN] == player) {
						++plyr_d;
					}
					else {
						++oppn_d;
					}
				}
				if (r < dim::SPAN-2 && node->config_[index+2*dim::SPAN] != SYMBOL::EMPTY) {
					if (node->config_[index+2*dim::SPAN] == player) {
						++plyr_d;
					}
					else {
						++oppn_d;
					}
				}
				//std::cout << "down  " << plyr_d << " " << oppn_d << std::endl;
				//std::cout << "\n" << std::endl;



				if (plyr_l == 2) {
					heuristic += 8;
				}
				else if (plyr_l == 1) {
					heuristic += 4;
				}
				else {
					heuristic += 2;
				}


				if (plyr_r == 2) {
					heuristic += 8;
				}
				else if (plyr_r == 1) {
					heuristic += 4;
				}
				else {
					heuristic += 2;
				}


				if (plyr_u == 2) {
					heuristic += 8;
				}
				else if (plyr_u == 1) {
					heuristic += 4;
				}
				else {
					heuristic += 2;
				}


				if (plyr_d == 2) {
					heuristic += 8;
				}
				else if (plyr_d == 1) {
					heuristic += 4;
				}
				else {
					heuristic += 2;
				}




				if (oppn_l == 2) {
					heuristic += 4;
				}
				else if (oppn_l == 1) {
					heuristic += 2;
				}
				else {
					heuristic += 1;
				}


				if (oppn_r == 2) {
					heuristic += 4;
				}
				else if (oppn_r == 1) {
					heuristic += 2;
				}
				else {
					heuristic += 1;
				}


				if (oppn_u == 2) {
					heuristic += 4;
				}
				else if (oppn_u == 1) {
					heuristic += 2;
				}
				else {
					heuristic += 1;
				}


				if (oppn_d == 2) {
					heuristic += 4;
				}
				else if (oppn_d == 1) {
					heuristic += 2;
				}
				else {
					heuristic += 1;
				}




			}

			
		}

	}

	return heuristic;

}

/*

int Game::calculate_config_score(Node* node, char player) {
	return 
		this->calculate_config_rows(node, player) + 
		this->calcualte_config_cols(node, player);
}

*/

int Game::calculate_config_rows(Node* node, char player) {
	int row_score = 0;
	for (int row = 0; row < dim::SPAN; ++row) {
		int r = row*dim::SPAN;
		for (int c = 0; c <= dim::MAX_ADJ; ++c) {
			int uninterrupted = 0, consec_sym = 0, consec_counter = 0;
			for (int i = 0; i < dim::MAX_ADJ && uninterrupted != -1; ++i) {
				char symbol = node->config_[r+c+i];
				if (symbol == player) {
					++uninterrupted;
					++consec_sym;
					if (consec_sym > 1)
						++consec_counter;
					if (uninterrupted > 2)
						++consec_counter;
				}
				else if (symbol == SYMBOL::EMPTY) {
					consec_sym = 0;
				}
				else {
					uninterrupted = -1;
				}
			}
			if (uninterrupted > 0)
				row_score += this->pow(uninterrupted, consec_counter);
		}
	}
	return row_score;
}


int Game::calcualte_config_cols(Node* node, char player) {
	int column_score = 0;
	for (int c = 0; c < dim::SPAN; ++c) {
		for (int r = 0; r <= dim::MAX_ADJ; ++r) {
			int uninterrupted = 0, consec_sym = 0, consec_counter = 0;
			for (int i = 0; i < dim::MAX_ADJ && uninterrupted != -1; ++i) {
				char symbol = node->config_[c+dim::SPAN*(r+i)];
				if (symbol == player) {
					++uninterrupted;
					++consec_sym;
					if (consec_sym > 1)
						++consec_counter;
					if (uninterrupted > 2)
						++consec_counter;
				}
				else if (symbol == SYMBOL::EMPTY) {
					consec_sym = 0;
				}
				else {
					uninterrupted = -1;
				}
			}
			if (uninterrupted > 0)
				column_score += this->pow(uninterrupted, consec_counter);
		}
	}
	return column_score;
}


int Game::utility_offensive(Node* node) {
	return
		this->calculate_config_score(node, SYMBOL::PLAYER) -
		this->calculate_config_score(node, SYMBOL::OPPONENT);
}


int Game::utility_defensive(Node* node) {
	return 
		(-this->calculate_config_score(node,SYMBOL::OPPONENT));
}


std::vector<int> Game::query_possible_moves(Node* node) {
	std::vector<int> moves;
	for (int i = 0; i < dim::SIZE; ++i)
		if (node->config_[i] == SYMBOL::EMPTY)
			moves.push_back(i);
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


void Game::make_first_move(Node* node) {
	int row = 3, col = 3;
	node->config_[row*dim::SPAN+col] = SYMBOL::PLAYER;
}


// should be used when placing symbols using the row and col numbers
// that are indeces in the array
void Game::place_symbol_by_indeces(Node* node, char symbol, int row, int col) {
	node->config_[row*dim::SPAN+col] = symbol;
}


bool Game::get_offensive_strategy() {
	return this->offensive_strategy_;
}


void Game::set_max_depth(int depth) {
	
}


void Game::set_time_allowed(int time_allowed) {
	this->time_allowed_ = time_allowed;
}


void Game::set_strategy_offensive() {
	this->offensive_strategy_ = true;
}


void Game::set_strategy_defensive() {
	this->offensive_strategy_ = false;
}


void Game::revise_strategy(Node* node) {
	
	int player_score = this->calculate_config_score(node, SYMBOL::PLAYER);
	int opponent_score = this->calculate_config_score(node, SYMBOL::OPPONENT);
	this->offensive_strategy_ = player_score >= opponent_score;

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


int Game::pow(int base, int exp) {
	int p = 1;
	for (int i = 0; i < exp; ++i)
		p *= base;
	return p;
}


