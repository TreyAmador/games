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

	void next_move(Node* node);
	
	int minimax(Node* node, int depth);
	int minimize(Node* node, int& alpha, int& beta, int depth);
	int maximize(Node* node, int& alpha, int& beta, int depth);
	
	std::vector<int> query_possible_moves(Node* node);

	int calculate_config_score(Node* node, char player);
	int calculate_config_rows(Node* node, char player);
	int calcualte_config_cols(Node* node, char player);

	int utility_offensive(Node* node);
	int utility_defensive(Node* node);

	int update_min_max_row(Node* node, int row, char player);
	int update_min_max_col(Node* node, int col, char player);
	
	void make_first_move(Node* node);
	void insert_unique(std::vector<int>& vec, int elem);
	
	void place_symbol_by_indeces(Node* node, char symbol, int row, int col);


	char* survey_direction(Node* node, int span, int iter, int offset);

	void compare_counter(
		char curr_sym, char player_sym, 
		bool& free_player, int& player_count, 
		bool& is_open, int& open_spaces, 
		bool& free_oppn, int& oppn_count);

	void create_compass(char symbols[], int index, char curr_sym, char player_sym);

	
	int compass_utility(int plyr_count, int oppn_count, int open_spaces);
	int axis_utility(
		int plyr_left, int plyr_right,
		int oppn_left, int oppn_right,
		int spaces_left, int spaces_right);

	int utility_stream(char player,
		char left[], char right[], 
		char up[], char down[]);

	int utility_player_axis(char player, char dir_a[], char dir_b[]);
	int utility_array_player(char player, char dir[], 
		int& plyr, int& oppn, int& empty);

	int utility_opponent_axis(char player, char dir[], int& oppn);
	int specific_utility(char player, char dir[]);

	int utility_array(char player, char symbol, 
		int& consec_player, bool& uninter_player, int& consec_oppn, 
		int& consec_spaces, bool& uninter_spaces);


	void set_time_allowed(int time_allowed);
	void set_strategy_offensive();
	void set_strategy_defensive();
	void set_max_depth(int depth);
	
	bool get_offensive_strategy();
	void revise_strategy(Node* node);

	int pow(int base, int exp);
	void clear_nodes(std::vector<Node*>& nodes);
	bool won_game(Node* node, char symbol);


private:
	int max_depth_;
	int time_allowed_;
	bool offensive_strategy_;


};


#endif

