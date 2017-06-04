#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <queue>
#include <stack>
#include "io.h"
struct Node;


// keeps track of score for rows and columns
// probably don't need this, actually
struct Coordinate {
	int row_;
	int col_;
};


class Game {

public:
	Game();
	~Game();

	
	// seems to be working...
	// TODO need to sort through the code to see where
	//		scores should be attributed to player vs opponent
	//		and calculate utility function
	int minimax(Node* node, int depth, bool maximize);


	
	// pass in node, get all adjacent nodes
	std::vector<Node*> possible_configs(Node* root);

	// should probably pass in SYMBOL::SYMBOL ? 
	std::vector<int> query_moves_alpha(Node* node);
	
	void insert_unique(std::vector<int>& vec, int elem);

	void create_row_coordinates(
		Node* node, std::vector<int>& coords, int row);
	void create_col_coordinates(
		Node* ndoe, std::vector<int>& coords, int col);

	Node* create_child_node(Node* parent, int row, int col, char symbol);
	void calculate_vector_scores(Node* node, int row, int col);



	int greatest_index(int* span, int& bypass);


	// calc player from vectors
	void calculate_score_from_vectors(
		Node* node, int& player, int& opponent);

	int update_min_max_row(Node* node, int row, char player);
	int update_min_max_col(Node* node, int col, char player);
	
	void place_symbol_by_indeces(Node* node, char symbol, int row, int col);
	void place_symbol_from_prompt(Node* node, char symbol, int row, int col);
	void make_first_move(Node* node);

	void clear_nodes(std::vector<Node*>& nodes);

	void copy_config(Node* target, Node* source);

	Node* get_best_node();


	// TODO don't pass by symbol, just iterate
	//		any four in a row is a winner
	//		maybe return -1 for loss, +1 for win
	//		count blank squares, if 0, tie
	bool won_game(Node* node, char symbol);


	// returns	+1 for player win
	//			-1 for opponent win
	//			 0 ambiguous... spaces left
	//			 or perhaps something more discrete
	//int winning_config(Node* node);


	void reset_game_board();


private:
	IO io_;
	
	// indicates if you go first or not
	// true when you go first
	// can be used to call alpha aka maximize methods
	bool is_alpha_;

	Node* best_node_;


};


#endif

