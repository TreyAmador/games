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


	const char TERMINATE = '\0';
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

	int utility = 0;

	for (int r = 0; r < dim::SPAN; ++r) {
		for (int c = 0; c < dim::SPAN; ++c) {

			int index = r*dim::SPAN + c;
			char symbol = node->config_[index];

			if (symbol == player) {

				int consec_plyr_left = 0, consec_plyr_right = 0;
				bool free_plyr_left = true, free_plyr_right = true;
				int consec_oppn_left = 0, consec_oppn_right = 0;
				bool free_oppn_left = true, free_oppn_right = true;
				int open_left = 0, open_right = 0;
				bool left_is_open = true, right_is_open = true;
				
				for (int i = 1; i < dim::MAX_ADJ; ++i) {
					if (c - i >= 0) {
						char left_sym = node->config_[index - i];
						this->compare_counter(
							left_sym, player, free_plyr_left, consec_plyr_left, 
							left_is_open, open_left, free_oppn_left, consec_oppn_left);
					}
					if (c + i < dim::SPAN) {
						char right_sym = node->config_[index + i];
						this->compare_counter(
							right_sym, player, free_plyr_right, consec_plyr_right, 
							right_is_open, open_right, free_oppn_right, consec_oppn_right);
					}
				}

				int consec_plyr_up = 0, consec_plyr_down = 0;
				bool free_plyr_up = true, free_plyr_down = true;
				int consec_oppn_up = 0, consec_oppn_down = 0;
				bool free_oppn_up = true, free_oppn_down = true;
				int open_up = 0, open_down = 0;
				bool up_is_open = true, down_is_open = true;

				for (int i = 1; i < dim::MAX_ADJ; ++i) {
					if (r - i >= 0) {
						char up_sym = node->config_[index - i*dim::SPAN];
						this->compare_counter(
							up_sym, player, free_plyr_up, consec_plyr_up, 
							up_is_open, open_up, free_oppn_up, consec_oppn_up);
					}
					if (r + i < dim::SPAN) {
						char down_sym = node->config_[index + i*dim::SPAN];
						this->compare_counter(
							down_sym, player, free_plyr_down, consec_plyr_down, 
							down_is_open, open_down, free_oppn_down, consec_oppn_down);
					}
				}

				utility += this->compass_utility(
					consec_plyr_left, consec_oppn_left, open_left);
				utility += this->compass_utility(
					consec_plyr_right, consec_oppn_right, open_right);
				utility += this->compass_utility(
					consec_plyr_up, consec_oppn_up, open_up);
				utility += this->compass_utility(
					consec_plyr_down, consec_oppn_down, open_down);

				utility += this->axis_utility(
					consec_plyr_left, consec_plyr_right, 
					consec_oppn_left, consec_oppn_right, 
					open_left, open_right);
				utility += this->axis_utility(
					consec_plyr_up, consec_plyr_down, 
					consec_oppn_up, consec_oppn_down, 
					open_up, open_down);


			}
		}
	}

	return utility;

}


int Game::compass_utility(int plyr_count, int oppn_count, int open_spaces) {
	int utility = 0;	
	if (plyr_count + open_spaces >= dim::MAX_ADJ-1)
		utility += this->pow(plyr_count, plyr_count);
	if (oppn_count > 1)
		utility += this->pow(oppn_count, oppn_count);
	return utility;
}


int Game::axis_utility(
	int plyr_left, int plyr_right,
	int oppn_left, int oppn_right,
	int spaces_left, int spaces_right)
{
	int utility = 0;
	if ((plyr_left + plyr_right + spaces_left + spaces_right) >= dim::MAX_ADJ) {
		utility += this->pow(plyr_left + plyr_right, plyr_left+plyr_right);
	}
	if (oppn_left + oppn_right > 1) {
		utility += this->pow(oppn_left + oppn_right, oppn_left + oppn_right);
	}
	return utility;
}



/*

void Game::create_compass(Node* node, char player, int r, int c) {


	int index = r*dim::SPAN + c;
	char symbol = node->config_[index];

	if (symbol == player) {

		// look horizontally
		int consec_plyr_left = 0, consec_plyr_right = 0;
		bool free_plyr_left = true, free_plyr_right = true;
		int consec_oppn_left = 0, consec_oppn_right = 0;
		bool free_oppn_left = true, free_oppn_right = true;
		int open_left = 0, open_right = 0;
		bool left_is_open = true, right_is_open = true;

		for (int i = 1; i < dim::MAX_ADJ; ++i) {
			if (c - i >= 0) {
				char left_sym = node->config_[index - i];
				this->compare_counter(
					left_sym, player, free_plyr_left, consec_plyr_left,
					left_is_open, open_left, free_oppn_left, consec_oppn_left);
			}
			if (c + i < dim::SPAN) {
				char right_sym = node->config_[index + i];
				this->compare_counter(
					right_sym, player, free_plyr_right, consec_plyr_right,
					right_is_open, open_right, free_oppn_right, consec_oppn_right);
			}
		}


		// calculate vert here
		int consec_plyr_up = 0, consec_plyr_down = 0;
		bool free_plyr_up = true, free_plyr_down = true;
		int consec_oppn_up = 0, consec_oppn_down = 0;
		bool free_oppn_up = true, free_oppn_down = true;
		int open_up = 0, open_down = 0;
		bool up_is_open = true, down_is_open = true;

		for (int i = 1; i < dim::MAX_ADJ; ++i) {
			if (r - i >= 0) {
				char up_sym = node->config_[index - i*dim::SPAN];
				this->compare_counter(
					up_sym, player, free_plyr_up, consec_plyr_up,
					up_is_open, open_up, free_oppn_up, consec_oppn_up);
			}
			if (r + i < dim::SPAN) {
				char down_sym = node->config_[index + i*dim::SPAN];
				this->compare_counter(
					down_sym, player, free_plyr_down, consec_plyr_down,
					down_is_open, open_down, free_oppn_down, consec_oppn_down);
			}
		}


		std::cout << "row " << r << ", col " << c << "  U D L R" << std::endl;
		std::cout << "Consec player " <<
		consec_plyr_up << " " << consec_plyr_down << " " <<
		consec_plyr_left << " " << consec_plyr_right << std::endl;
		std::cout << "Consec oppn   " <<
		consec_oppn_up << " " << consec_oppn_down << " " <<
		consec_oppn_left << " " << consec_oppn_right << std::endl;
		std::cout << "open dir      " <<
		open_up << " " << open_down << " " <<
		open_left << " " << open_right << "\n\n" << std::endl;

	}
}

*/


void Game::compare_counter(
	char curr_sym, char player_sym, 
	bool& free_player, int& player_count,
	bool& is_open, int& open_spaces, 
	bool& free_oppn, int& oppn_count)
{
	if (curr_sym == player_sym) {
		if (free_player) {
			++player_count;
		}
	}
	else if (curr_sym == SYMBOL::EMPTY) {
		if (is_open) {
			++open_spaces;
		}
	}
	else {
		++oppn_count;
		free_player = is_open = false;
	}
}




/*

int Game::calculate_config_score(Node* node, char player) {


	int heuristic = 0;


	for (int r = 0; r < dim::SPAN; ++r) {
		for (int c = 0; c < dim::SPAN; ++c) {

			int index = r*dim::SPAN+c;
			char symbol = node->config_[index];

			if (node->config_[index] == player) {



				std::cout << "row x col " << 
					static_cast<char>((index/dim::SPAN)+'A') << " " << 
					(index%dim::SPAN)+1 << std::endl;



				int plyr_l = 0, plyr_r = 0, plyr_u = 0, plyr_d = 0;
				int oppn_l = 0, oppn_r = 0, oppn_u = 0, oppn_d = 0;
				//int free_l = 3, free_r = 3, free_u = 3, free_d = 3;
				

				if (c > 0) {
					if (node->config_[index-1] == player) {
						++plyr_l;
					}
					else if (node->config_[index - 1] != SYMBOL::EMPTY) {
						++oppn_l;
					}
				}
				
				if (c > 1) {
					if (node->config_[index-2] == player) {
						++plyr_l;
					}
					else if (node->config_[index - 2] != SYMBOL::EMPTY) {
						++oppn_l;
					}
				}
				
				
				if (c > 2) {
					if (node->config_[index - 3] == player) {
						++plyr_l;
					}
					else if (node->config_[index - 3] != SYMBOL::EMPTY) {
						++oppn_l;
					}
					
				}
				
				
				std::cout << "      P O "  << std::endl;

				std::cout << "left  " << plyr_l << " " << oppn_l << std::endl;



				if (c < dim::SPAN-1) {
					if (node->config_[index+1] == player) {
						++plyr_r;
					}
					else if (node->config_[index + 1] != SYMBOL::EMPTY) {
						++oppn_r;
					}
					
				}
				
				if (c < dim::SPAN-2) {
					if (node->config_[index+2] == player) {
						++plyr_r;
					}
					else if (node->config_[index + 2] != SYMBOL::EMPTY) {
						++oppn_r;
					}
				}
				
				if (c < dim::SPAN - 3) {
					if (node->config_[index + 3] == player) {
						++plyr_r;
					}
					else if (node->config_[index + 3] != SYMBOL::EMPTY) {
						++oppn_r;
					}
				}
				
				std::cout << "right " << plyr_r << " " << oppn_r << std::endl;
				



				if (r > 0) {
					if (node->config_[index-dim::SPAN] == player) {
						++plyr_u;
					}
					else if (node->config_[index - dim::SPAN] != SYMBOL::EMPTY) {
						++oppn_u;
					}
				}
				
				if (r > 1) {
					if (node->config_[index-2*dim::SPAN] == player) {
						++plyr_u;
					}
					else if (node->config_[index - 2 * dim::SPAN] != SYMBOL::EMPTY) {
						++oppn_u;
					}
				}
				
				if (r > 2) {
					if (node->config_[index - 3 * dim::SPAN] == player) {
						++plyr_u;
					}
					else if (node->config_[index - 3 * dim::SPAN] != SYMBOL::EMPTY) {
						++oppn_u;
					}
				}
				
				std::cout << "up    " << plyr_u << " " << oppn_u << std::endl;



				if (r < dim::SPAN-1) {
					if (node->config_[index + dim::SPAN] == player) {
						++plyr_d;
					}
					else if (node->config_[index + dim::SPAN] != SYMBOL::EMPTY) {
						++oppn_d;
					}
				}
				
				if (r < dim::SPAN-2) {
					if (node->config_[index+2*dim::SPAN] == player) {
						++plyr_d;
					}
					else if (node->config_[index + 2 * dim::SPAN] != SYMBOL::EMPTY) {
						++oppn_d;
					}
				}
				
				if (r < dim::SPAN - 3) {
					if (node->config_[index + 3 * dim::SPAN] == player) {
						++plyr_d;
					}
					else if (node->config_[index + 3 * dim::SPAN] != SYMBOL::EMPTY) {
						++oppn_d;
					}
				}
				
				std::cout << "down  " << plyr_d << " " << oppn_d << std::endl;
				std::cout << "\n" << std::endl;

			}

			
		}

	}

	return heuristic;

}

*/









// span is column or row, iter is +1 for up or -1 for down
// offset refers to +1/-1 for cols, +8/-8 for rows
char* Game::survey_direction(Node* node, int span, int iter, int offset) {
	int init = span;
	//char symbols[dim::MAX_ADJ-1];

	char* symbols = new char[dim::MAX_ADJ - 1];

	for (int i = 0; i < dim::MAX_ADJ - 1; ++i) {
		span += iter;
		char symbol = node->config_[(init+i)*offset];
		if (span < 0 || span > dim::SPAN - 1) {
			symbols[i] = TERMINATE;
		}
		else {
			symbols[i] = symbol;
		}
	}
	return symbols;
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


