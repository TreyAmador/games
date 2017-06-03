#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <queue>
#include <stack>
#include "global.h"
struct Node;


// keeps track of score for rows and columns
// probably don't need this, actually
struct Coordinate {
	char symbol_;
	int row_;
	int col_;
};


class Game {

public:
	Game();
	~Game();

	
	// pass in node, get all adjacent nodes
	std::vector<Node*> possible_configs(Node* root);

	Node* create_child_node(Node* parent, int row, int col, char symbol);

	// calc player from vectors
	int calculate_score_from_vectors(Node* node);

	int update_min_max_row(Node* node, int row, char player);
	int update_min_max_col(Node* node, int col, char player);
	
	void place_symbol_by_indeces(Node* node, char symbol, int row, int col);
	void place_symbol_from_prompt(Node* node, char symbol, int row, int col);
	void make_first_move(Node* node);

	// TODO don't pass by symbol, just iterate
	// any four in a row is a winner
	// maybe return -1 for loss, +1 for win
	// count blank squares, if 0, tie
	bool won_game(Node* node, char symbol);
	void reset_game_board();


private:
	// indicates if you go first or not
	// true when you go first
	// can be used to call alpha aka maximize methods
	bool is_alpha_;


};


#endif

