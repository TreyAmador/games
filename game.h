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

	void make_first_move(Node* node);


	// pass in node, get all adjacent nodes
	std::vector<Node*> possible_configs(Node* root);

	Node* create_child_node(Node* parent, int row, int col, char symbol);

	
	Node* dfs_next_move(Node* root);


	Node* query_next_move(Node* root);
	
	void query_adjacent(Node* node, int i);

	void query_right(Node* node, Coordinate& coord, int offset, bool& open);

	bool won_game(Node* node, char symbol);

	void query_up(Node* node, Coordinate& coord, int offset, bool& open);
	void query_down(Node* node, Coordinate& coord, int offset, bool& open);
	void query_left(Node* node, Coordinate& coord, int offset, bool& open);


	int calculate_alpha_from_vectors(Node* node);
	int update_min_max_row(Node* node, int row, char player);
	int update_min_max_col(Node* node, int col, char player);

	int sum_score_new_row_col(Node* node, int row, int col);
	int sum_score_tracker();

	void place_symbol_by_indeces(Node* node, char symbol, int row, int col);
	void place_symbol_from_prompt(Node* node, char symbol, int row, int col);

	void reset_game_board();


	void reset_next_turn();

	void reset_score_counter();
	void reset_node_stack();
	void reset_taken_spaces();


private:
	// TODO remove this, it probably isn't more efficient
	//std::vector<Coordinate> taken_spaces_;

	
	// could use cut off search
	//std::stack<Node*> node_dfs_;
	


};

#endif //GAME_H_

