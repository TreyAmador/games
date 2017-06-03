#include "game.h"
#include "node.h"
#include "io.h"
#include "global.h"
#include <iostream>


typedef Node* GameBoard;


namespace {
	const int MAX_ITER = 5;
}



Game::Game() {

}


Game::~Game() {
	
}



// call this method after response from other player
// TODO fill this method, which will try all the adjacent
//		moves from a selection of moves
Node* Game::query_next_move(Node* root) {
	
	std::vector<Node*> configs = this->possible_configs(root);



	return nullptr;
}



// TODO implement this where you go across row and column
//	to get next good value, yay
std::vector<Node*> Game::possible_configs(Node* root) {

	std::vector<Node*> nodes;

	return nodes;
}



// TODO test this
Node* Game::create_child_node(Node* parent, int row, int col, char symbol) {
	
	Node* child = new Node(parent);
	child->config_[row*dim::SPAN+col] = symbol;
	child->col_score_[col] = this->update_min_max_col(child, col, SYMBOL::PLAYER);
	child->row_score_[row] = this->update_min_max_row(child, row, SYMBOL::PLAYER);
	child->parent_ = parent;
	return child;

}



/*

// TODO implement cut-off dfs which returns next
//		most adventageous move
//		should probably query opponent score first
//		and go with that if it's too high
//		go with your own if it's better

//		once you make a move, put it in the taken_spaces_ vector
Node* Game::dfs_next_move(Node* root) {
	int iter = 0;
	node_dfs_.push(root);
	while (!node_dfs_.empty() && iter < MAX_ITER) {
		Node* node = node_dfs_.top();
		node_dfs_.pop();
		for (size_t i = 0; i < taken_spaces_.size(); ++i) {
			this->query_adjacent(node,i);
		}
		++iter;
	}
	// TODO implement another data structure which stores 
	//		nodes based on heuristic and return top one
	//		or just have a running best and return that
	//		priority queue?
	return nullptr;
}

*/


/*
// check left, right, up, down for next best move
void Game::query_adjacent(Node* node, int i) {
	Coordinate coord = taken_spaces_[i];
	bool up = true, down = true, left = true, right = true;
	for (int i = 1; i <= 3; ++i) {
		this->query_right(node, coord, i, right);
	}
}
*/



// TODO simply place these in a stack
void Game::query_right(Node* node, Coordinate& coord, int offset, bool& open) {
	int index = coord.row_*dim::SPAN + coord.col_ + offset;
	if (index % dim::SPAN == 0)
		open = false;
	//else if (open && node->config_[index] == SYMBOL::EMPTY)
	//	taken_spaces_.push_back({ SYMBOL::EMPTY, coord.row_, coord.col_ + offset });
}





/*


// check left, right, up, down for next best move
void Game::query_adjacent(Node* node) {
	Coordinate coord = adjacent_spaces_.front();
	bool up = true, down = true, left = true, right = true;
	for (int i = 1; i <= 3; ++i) {
		this->query_right(node, coord, i, right);
		this->query_left(node, coord, i*(-1), left);
		this->query_up(node, coord, i*(-1), up);
		this->query_down(node, coord, i, down);
	}
}



// are these less efficient than just checking?

// TODO simply place these in a stack
void Game::query_right(Node* node, Coordinate& coord, int offset, bool& open) {
	int index = coord.row_*dim::SPAN+coord.col_+offset;
	if (index % dim::SPAN == 0)
		open = false;
	else if (open && node->config_[index] == SYMBOL::EMPTY)
		adjacent_spaces_.push({ SYMBOL::EMPTY, coord.row_, coord.col_+offset });
	// can just push a new node here
}

*/

void Game::query_left(Node* node, Coordinate& coord, int offset, bool& open) {
	int index = coord.row_*dim::SPAN + coord.col_ + offset;
	if (index % dim::SPAN == dim::SPAN-1)
		open = false;
	//else if (open && node->config_[index] == SYMBOL::EMPTY)
	//	taken_spaces_.push_back({ SYMBOL::EMPTY, coord.row_, coord.col_+offset });
}


void Game::query_up(Node* node, Coordinate& coord, int offset, bool& open) {
	int index = (coord.row_ + offset)*dim::SPAN + coord.col_;
	if (index / dim::SPAN == -1)
		open = false;
	//else if (open && node->config_[index] == SYMBOL::EMPTY)
	//	taken_spaces_.push_back({ SYMBOL::EMPTY, coord.row_ + offset, coord.col_ });
}


void Game::query_down(Node* node, Coordinate& coord, int offset, bool& open) {
	int index = (coord.row_+offset)*dim::SPAN + coord.col_;
	if (index / dim::SPAN == dim::SPAN)
		open = false;
	//else if (open && node->config_[index] == SYMBOL::EMPTY)
	//	taken_spaces_.push_back({ SYMBOL::EMPTY, coord.row_ + offset, coord.col_ });
}


// TODO implement this
//		allow node to be passed, sum the row and column
//		of change of node with the rows and columns of score_tracker_
int Game::sum_score_new_row_col(Node* node, int row, int col) {
	int sum = 0;
	for (int r = 0; r < dim::SPAN; ++r) {
		
	}
	return 0;
}


int Game::calculate_alpha_from_vectors(Node* node) {
	int sum = 0;
	for (int i = 0; i < dim::SPAN; ++i)
		sum += node->row_score_[i] + node->col_score_[i];
	return sum;
}



// TODO perhaps replace the player opponent args with
//		if symbol != player
//		else if symbol != SYMBOL::EMPTY
//			uninterrupted = -1;
//		then set to zero
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
	//taken_spaces_.push_back({ symbol, row, col });
}


// does this really need to be included..?
void Game::place_symbol_from_prompt(Node* node, char symbol, int row, int col) {
	node->config_[(row-1)*dim::SPAN+(col-1)] = symbol;
}



// this works well!
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
	
	//while (!node_dfs_.empty()) {
	//	Node* node = node_dfs_.top();
	//	node_dfs_.pop();
	//	if (node != nullptr) {
	//		delete node;
	//		node = nullptr;
	//	}
	//}
	
	// clear all the taken nodes
	//taken_spaces_.clear();
	//taken_spaces_.shrink_to_fit();

}




/*
// TESTING FUNCTIONS

void Game::test_fill_score_tracker(Node* node) {

	for (int i = 0; i < dim::SPAN; ++i) {
		score_counter_.row_[i] = this->update_min_max_row(node, i, SYMBOL::PLAYER, SYMBOL::OPPONENT);
		score_counter_.col_[i] = this->update_min_max_col(node, i, SYMBOL::PLAYER, SYMBOL::OPPONENT);
	}

	std::cout << "  ";
	for (int i = 0; i < dim::SPAN; ++i)
		std::cout << score_counter_.col_[i] << " ";
	std::cout << "\n";
	for (int i = 0; i < dim::SPAN; ++i)
		std::cout << score_counter_.row_[i] << "\n";

}


Node* Game::test_node_01() {
	IO io;
	Node* node = new Node;
	GameBoard board = node;
	std::cout << "game board node" << std::endl;
	io.print_node(static_cast<Node*>(board));
	node->config_[3] = SYMBOL::PLAYER;
	node->config_[11] = SYMBOL::PLAYER;
	node->config_[19] = SYMBOL::PLAYER;
	node->config_[12] = SYMBOL::PLAYER;
	node->config_[13] = SYMBOL::PLAYER;
	node->config_[54] = SYMBOL::PLAYER;
	node->config_[56] = SYMBOL::PLAYER;
	node->config_[60] = SYMBOL::PLAYER;
	node->config_[4] = SYMBOL::OPPONENT;
	node->config_[5] = SYMBOL::OPPONENT;
	node->config_[13] = SYMBOL::OPPONENT;
	node->config_[42] = SYMBOL::OPPONENT;
	node->config_[43] = SYMBOL::OPPONENT;
	node->config_[44] = SYMBOL::OPPONENT;
	node->config_[51] = SYMBOL::OPPONENT;
	return node;
}


void Game::test_node_querying() {
	IO io;
	Node* node = this->test_node_01();
	io.print_node(node);
	this->test_fill_score_tracker(node);
	delete node;
}

*/
