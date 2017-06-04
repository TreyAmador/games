#ifndef GAME_H_
#define GAME_H_
#include <vector>
struct Node;


struct Coordinate {
	int row_;
	int col_;
};


class Game {


public:
	Game();
	~Game();

	void next_move(Node* node, int max_depth);
	int move_iteration(Node* node, int depth);

	int minimize(Node* node, int& alpha, int& beta, int depth);
	int maximize(Node* node, int& alpha, int& beta, int depth);
	
	std::vector<int> query_possible_moves(Node* node);
	int calculate_config_score(Node* node, char symbol);
	
	int update_min_max_row(Node* node, int row, char player);
	int update_min_max_col(Node* node, int col, char player);
	
	void make_first_move(Node* node);
	void insert_unique(std::vector<int>& vec, int elem);
	
	void place_symbol_by_indeces(Node* node, char symbol, int row, int col);
	void place_symbol_from_prompt(Node* node, char symbol, int row, int col);

	void clear_nodes(std::vector<Node*>& nodes);
	bool won_game(Node* node, char symbol);


private:
	


};


#endif

