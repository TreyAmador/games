#ifndef TEST_H_
#define TEST_H_
#include "game.h"
#include "node.h"
#include "io.h"


int test_add_elem(Node* node, int row, int col, char symbol);
void test_heuristic_diff();
void test_revise_strategy();
void test_node_ptr();
void test_exponent();
void test_calculate_config_score();
void test_survey_direction();



Node* test_node_01() {

	Node* node = new Node;

	node->config_[27] = SYMBOL::PLAYER;
	node->config_[28] = SYMBOL::OPPONENT;
	node->config_[19] = SYMBOL::PLAYER;
	node->config_[11] = SYMBOL::OPPONENT;

	return node;

}


Node* test_node_02() {

	Node* node = new Node;

	node->config_[27] = SYMBOL::PLAYER;
	node->config_[28] = SYMBOL::OPPONENT;
	node->config_[35] = SYMBOL::PLAYER;
	node->config_[43] = SYMBOL::OPPONENT;
	node->config_[19] = SYMBOL::PLAYER;
	node->config_[11] = SYMBOL::OPPONENT;
	node->config_[36] = SYMBOL::PLAYER;


	return node;

}


Node* test_node_03() {

	Node* node = new Node;
	
	test_add_elem(node, 3, 3, SYMBOL::PLAYER);
	test_add_elem(node, 3, 4, SYMBOL::OPPONENT);
	test_add_elem(node, 4, 3, SYMBOL::PLAYER);
	test_add_elem(node, 5, 3, SYMBOL::OPPONENT);
	test_add_elem(node, 2, 3, SYMBOL::PLAYER);
	test_add_elem(node, 3, 5, SYMBOL::OPPONENT);

	return node;

}


Node* test_node_04() {

	Node* node = new Node;

	test_add_elem(node, 3, 3, SYMBOL::PLAYER);
	test_add_elem(node, 3, 4, SYMBOL::PLAYER);
	test_add_elem(node, 3, 5, SYMBOL::PLAYER);
	test_add_elem(node, 3, 6, SYMBOL::PLAYER);
	test_add_elem(node, 6, 3, SYMBOL::PLAYER);
	test_add_elem(node, 5, 3, SYMBOL::PLAYER);
	
	return node;

}





void test_config_score_if() {


	IO io;
	Game game;

	Node* node = new Node;

	node->config_[dim::SPAN * 3 + 2] = SYMBOL::PLAYER;
	node->config_[dim::SPAN * 3 + 3] = SYMBOL::PLAYER;
	node->config_[dim::SPAN * 3 + 4] = SYMBOL::PLAYER;
	node->config_[dim::SPAN * 4 + 2] = SYMBOL::OPPONENT;
	node->config_[dim::SPAN * 5 + 4] = SYMBOL::PLAYER;
	node->config_[dim::SPAN * 4 + 7] = SYMBOL::OPPONENT;
	node->config_[dim::SPAN * 5 + 2] = SYMBOL::PLAYER;




	//node->config_[dim::SPAN * 3 + 3] = SYMBOL::PLAYER;
	//node->config_[dim::SPAN * 4 + 3] = SYMBOL::PLAYER;
	//node->config_[dim::SPAN * 5 + 3] = SYMBOL::PLAYER;
	//node->config_[dim::SPAN * 4 + 2] = SYMBOL::OPPONENT;
	//node->config_[dim::SPAN * 5 + 3] = SYMBOL::PLAYER;
	//node->config_[dim::SPAN * 4 + 2] = SYMBOL::OPPONENT;


	io.print_node(node);
	
	std::cout << "\n" << 
		game.calculate_config_score(node, SYMBOL::PLAYER) << "\n" << std::endl;

}


void test_survey_direction() {

	IO io;
	Game game;
	
	Node* node = test_node_02();
	io.print_node(node);
	

	char* a = game.survey_direction(node, 4, 1, dim::SPAN);
	for (int i = 0; i < dim::MAX_ADJ; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

}






void test_calc_config_score() {

	IO io;
	Game game;

	Node* node = new Node;
	node->config_[42] = SYMBOL::PLAYER;
	node->config_[43] = SYMBOL::PLAYER;
	node->config_[35] = SYMBOL::PLAYER;

	
	io.print_node(node);

	int score = game.calculate_config_score(node, SYMBOL::PLAYER);
	std::cout << score << std::endl;

}


void test_calculate_config_score() {

	Game game;
	IO io;

	Node* node = new Node;
	test_add_elem(node, 3, 3, SYMBOL::PLAYER);
	test_add_elem(node, 3, 4, SYMBOL::PLAYER);
	test_add_elem(node, 3, 5, SYMBOL::PLAYER);


	int score = game.calculate_config_score(node, SYMBOL::PLAYER);
	io.print_node(node);
	std::cout << "\n" << "score " << score << "\n\n" << std::endl;



}


void test_exponent() {

	Game game;

	int a = 4, b = 5;
	int c = 3, d = 6;
	int e = 4, f = 0;
	int g = -5, h = 3;
	int i = 4, j = -3;

	std::cout << game.pow(a,b) << std::endl;
	std::cout << game.pow(c,d) << std::endl;
	std::cout << game.pow(e,f) << std::endl;
	std::cout << game.pow(g,h) << std::endl;
	std::cout << game.pow(i,j) << std::endl;


}




void test_node_ptr() {

	IO io;
	
	Node* node = new Node;
	node->config_[0] = 'X';
	node = new Node(node);
	node->config_[1] = 'O';
	node = new Node(node);
	node->config_[2] = 'X';
	node = new Node(node);
	node->config_[3] = 'O';
	node = new Node(node);
	node->config_[4] = 'X';
	node = new Node(node);
	node->config_[5] = 'O';
	node = new Node(node);
	node->config_[6] = 'X';
	node = new Node(node);
	node->config_[7] = 'O';
	node = new Node(node);
	node->config_[8] = 'X';
	node = new Node(node);
	node->config_[9] = 'O';

	while (node != nullptr) {
		io.print_node(node);
		node = node->parent_;
	}

}



void test_revise_strategy() {


	Game game;
	IO io;


	Node* node = test_node_01();
	node->config_[4] = SYMBOL::PLAYER;
	io.print_node(node);
	std::cout << game.calculate_config_score(node, SYMBOL::PLAYER) << std::endl;
	std::cout << game.calculate_config_score(node, SYMBOL::OPPONENT) << std::endl;
	game.revise_strategy(node);
	bool strategy = game.get_offensive_strategy();
	if (strategy)
		std::cout << "offensive strategy" << "\n" << std::endl;
	else
		std::cout << "not offensive strategy" << "\n" << std::endl;


	node->config_[12] = SYMBOL::OPPONENT;
	io.print_node(node);
	std::cout << game.calculate_config_score(node, SYMBOL::PLAYER) << std::endl;
	std::cout << game.calculate_config_score(node, SYMBOL::OPPONENT) << std::endl;
	game.revise_strategy(node);
	strategy = game.get_offensive_strategy();
	if (strategy)
		std::cout << "offensive strategy" << "\n" << std::endl;
	else
		std::cout << "not offensive strategy" << "\n" << std::endl;


}



void test_heuristic_diff() {


	Game game;
	IO io;

	Node* node = test_node_01();
	
	node->config_[35] = SYMBOL::PLAYER;
	io.print_node(node);
	std::cout << 
		game.calculate_config_score(node, SYMBOL::PLAYER) << "\n" << std::endl;
	node->config_[35] = SYMBOL::EMPTY;

	node->config_[36] = SYMBOL::PLAYER;
	io.print_node(node);
	std::cout << 
		game.calculate_config_score(node, SYMBOL::PLAYER) << "\n" << std::endl;
	node->config_[36] = SYMBOL::EMPTY;


}


int test_add_elem(Node* node, int row, int col, char symbol) {
	node->config_[row*dim::SPAN + col] = symbol;
	return row*dim::SPAN + col;
}


#endif

/*

#ifndef TEST_H_
#define TEST_H_
#include "node.h"
#include "game.h"
#include "io.h"
#include <iostream>
#include <chrono>


struct Vec2D {

	int x_;
	int y_;

	Vec2D(int x, int y) :
		x_(x), y_(y)
	{}

};


long long get_init_time();
long long time_span_nanoseconds(long long init);
long long time_span_milliseconds(long long init);

Node* test_node_01();
Node* test_node_02();

void test_row_and_col_heuristic();
void test_row_heuristic_01();
void test_row_heuristic_02(int row);
void test_row_heuristic_03(int row);
void test_col_heuristic_01(int col);
void test_col_heuristic_02(int col);
void test_efficiency();
void test_victory();
void test_max_row_col();
void test_child_node();
void test_next_move_choice(Game& game, IO& io, Node* node);
void time_next_choice();
void test_child_configs();
void test_query_possible_moves();






void test_query_possible_moves() {

	Game game;
	IO io;

	Node* node = new Node;

	node->config_[27] = SYMBOL::PLAYER;
	node->config_[28] = SYMBOL::OPPONENT;
	node->config_[35] = SYMBOL::PLAYER;
	node->config_[43] = SYMBOL::OPPONENT;
	node->config_[19] = SYMBOL::PLAYER;
	node->config_[11] = SYMBOL::OPPONENT;
	node->config_[36] = SYMBOL::PLAYER;

	game.calculate_config_score(node);
	io.print_config(node);
	std::cout << std::endl;

	std::vector<int> moves = game.query_possible_moves(node);

	std::cout << "\n" << std::endl;
	for (size_t i = 0; i < moves.size(); ++i) {
		std::cout << 
			"row: " << static_cast<char>(moves[i]/dim::SPAN+'A') << "  " << 
			"col: " << (moves[i]%dim::SPAN)+1 << "\n";
	}
	std::cout << std::endl;

}




void test_calc_config() {
	
	Game game;
	IO io;

	Node* node = new Node;

	node->config_[27] = SYMBOL::PLAYER;
	node->config_[28] = SYMBOL::OPPONENT;
	node->config_[35] = SYMBOL::PLAYER;
	node->config_[43] = SYMBOL::OPPONENT;
	node->config_[19] = SYMBOL::PLAYER;
	node->config_[11] = SYMBOL::OPPONENT;
	node->config_[36] = SYMBOL::PLAYER;

	game.calculate_config_score(node);

	io.print_config(node);

	std::cout << "Player score   " << node->player_score_ << std::endl;
	std::cout << "Opponent score " << node->opponent_score_ << std::endl;

}



void test_child_configs() {

	Game game;
	IO io;

	Node* node = test_node_02();
	io.print_node_and_vec_score(node);

	std::vector<Node*> offspring = game.possible_configs(node,SYMBOL::PLAYER);
	for (size_t i = 0; i < offspring.size(); ++i) {
		io.print_config(offspring[i]);
	}

}




void time_next_choice() {

	Game game;
	IO io;

	Node* parent = test_node_02();

	long long init = get_init_time();
	for (int i = 0; i < 100000; ++i) {
		test_next_move_choice(game,io,parent);
		//std::vector<int> coords = game.query_moves_alpha(node);
		//Node* node = game.create_child_node(
		//	parent, i%dim::SPAN, i%dim::SPAN, SYMBOL::EMPTY);
		//delete node;
	}
	std::cout << "milliseconds: " << time_span_milliseconds(init) << std::endl;

}



void test_next_move_choice(Game& game, IO& io, Node* node) {

	//Node* node = test_node_01();
	//Node* node = test_node_02();
	//io.print_node_and_vec_score(node);

	std::vector<int> coords = game.query_moves_alpha(node,SYMBOL::PLAYER);

	for (size_t i = 0; i < coords.size(); ++i) {
		int row = coords[i] / dim::SPAN;
		int col = coords[i] % dim::SPAN;
		//std::cout << row << " " << col << std::endl;
	}

}


void test_max_row_col() {

	Game game;
	IO io;

	Node* node = test_node_02();
	io.print_node_and_vec_score(node);

	int idx = -1;
	int fst_row = game.greatest_index(node->row_player_, idx);
	int sec_row = game.greatest_index(node->row_player_, idx);
	idx = -1;
	int fst_col = game.greatest_index(node->col_player_, idx);
	int sec_col = game.greatest_index(node->col_player_, idx);

	std::cout << "row indices " << fst_row << ", " << sec_row << "\n";
	std::cout << "col indices " << fst_col << ", " << sec_col << "\n\n";

}



void test_find_max_element() {

	Game game;
	char* idx = new char[dim::SPAN];
	for (int i = 0; i < dim::SPAN; ++i) {
		idx[i] = ((i*11) % 31);
		std::cout << static_cast<int>(idx[i]) << std::endl;
	}
	int bypass_index = -1;

	//int index_a = game.find_greatest_index(idx, bypass_index);
	//std::cout << "bypass " << bypass_index << ", found " << index_a << "\n";
	//int index_b = game.find_greatest_index(idx, bypass_index);
	//std::cout << "bypass " << bypass_index << ", found " << index_b << "\n";

}


void test_pass_args(Vec2D& vec) {
	int x = vec.x_;
	int y = vec.y_;
}


void test_pass_args(Vec2D* vec) {
	int x = vec->x_;
	int y = vec->y_;
}


void test_pass_args(int x, int y) {
	int a = x;
	int b = y;
}


void test_pass_ref_ptr_int() {


	// round one
	long long init = get_init_time();
	for (int i = 0; i < 1000000; ++i) {
		//int a = i, b = i+1;
		//test_pass_args(a, b);
		int a[100];
		for (int i = 0; i < 100; ++i) {
			a[i] = i + 1;
		}
	}
	std::cout << "int args  " << time_span_milliseconds(init) << std::endl;




	// round two
	init = get_init_time();
	for (int i = 0; i < 1000000; ++i) {
		//Vec2D vec(i, i+1);
		//test_pass_args(vec);
		int* a = new int[100];
		for (int i = 0; i < 100; ++i) {
			a[i] = i + 1;
		}
	}
	std::cout << "ref args  " << time_span_milliseconds(init) << std::endl;



	// round three
	init = get_init_time();
	for (int i = 0; i < 1000000; ++i) {
		//Vec2D* vec = new Vec2D(i, i + 1);
		//test_pass_args(vec);
		//delete vec;
	}
	std::cout << "ptr args  " << time_span_milliseconds(init) << std::endl;


}


void test_child_node() {

	Game game;
	IO io;

	Node* parent = test_node_01();
	io.print_node_and_vec_score(parent);

}


void test_victory() {
	
	Game game;
	IO io;

	Node* node = new Node;

	node->config_[7] = 'O';
	node->config_[15] = 'X';
	node->config_[23] = 'X';
	node->config_[31] = 'O';
	node->config_[39] = 'X';
	node->config_[48] = 'O';


	node->config_[20] = 'X';
	//node->config_[28] = 'X';
	node->config_[44] = 'X';
	node->config_[52] = 'X';

	node->config_[25] = 'O';
	node->config_[26] = 'O';
	node->config_[27] = 'O';
	node->config_[28] = 'O';

	if (game.won_game(node, 'O')) {
		std::cout << "this won!" << std::endl;
		io.print_node(node);
	}
	else {
		std::cout << "this didn't win" << std::endl;
		io.print_node(node);
	}

}





void test_efficiency() {
	Game game;

	long long init = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	Node* first_node = test_node_01();
	int SAMPLE_SIZE = 10;
	for (int i = 0; i < SAMPLE_SIZE; ++i) {
		Node* copy = new Node(first_node);
		for (int i = 0; i < dim::SPAN; ++i) {
			int row = game.update_min_max_row(copy, i, SYMBOL::PLAYER);
			int col = game.update_min_max_col(copy, i, SYMBOL::PLAYER);
		}
		delete copy;
	}
	delete first_node;

	long long end = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	std::cout << "This took " << (end - init) / 1000000 << std::endl;

}



void test_row_heuristic_01() {

	Game game;
	IO io;
	Node* node = test_node_01();
	//io.print_node(node);
	int row = 2;
	int row_score = game.update_min_max_row(node, row, SYMBOL::PLAYER);
	std::cout << "row " << row << ", heuristic row score: " << row_score << "\n" << std::endl;
	delete node;

}



void test_row_and_col_heuristic() {

	IO io;
	Node* node = test_node_01();
	//io.print_node(node);
	std::cout << "\n";

	std::cout << "  ";
	for (int i = 0; i < dim::SPAN; ++i)
		test_col_heuristic_01(i);
	std::cout << "\n";
	for (int i = 0; i < dim::SPAN; ++i)
		test_row_heuristic_02(i);
	std::cout << "\n";

	
	
}


void test_row_heuristic_02(int row) {

	Game game;
	IO io;
	Node* node = test_node_01();
	//io.print_node(node);
	int row_score = game.update_min_max_row(node, row, SYMBOL::PLAYER);
	std::cout << row_score << "  " << std::endl;
	delete node;

}



void test_row_heuristic_03(int row) {

	Game game;
	IO io;
	Node* node = test_node_01();
	//io.print_node(node);
	int row_score = game.update_min_max_row(node, row, SYMBOL::OPPONENT);
	std::cout << "row " << row << ", heuristic row score: " << row_score << "\n" << std::endl;
	delete node;

}



void test_col_heuristic_01(int col) {

	Game game;
	IO io;
	Node* node = test_node_01();
	//io.print_node(node);
	int col_score = game.update_min_max_col(node, col, SYMBOL::PLAYER);
	
	std::cout << col_score << " ";
	delete node;

}


void test_col_heuristic_02(int col) {

	Game game;
	IO io;
	Node* node = test_node_01();
	//io.print_node(node);
	int col_score = game.update_min_max_col(node, col, SYMBOL::OPPONENT);
	std::cout << "col " << col << ", heuristic col score: " << col_score << "\n" << std::endl;
	delete node;

}


Node* test_node_01() {

	Node* node = new Node;

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

	Game game;
	for (int i = 0; i < dim::SPAN; ++i)
		game.calculate_vector_scores(node, i, i);
	game.calculate_score_from_vectors(
		node, node->player_score_, node->opponent_score_);

	return node;

}


Node* test_node_02() {

	Node* node = new Node;

	node->config_[27] = SYMBOL::PLAYER;
	node->config_[28] = SYMBOL::OPPONENT;
	node->config_[35] = SYMBOL::PLAYER;
	node->config_[43] = SYMBOL::OPPONENT;
	node->config_[19] = SYMBOL::PLAYER;
	node->config_[11] = SYMBOL::OPPONENT;
	node->config_[36] = SYMBOL::PLAYER;

	Game game;
	for (int i = 0; i < dim::SPAN; ++i)
		game.calculate_vector_scores(node, i, i);
	game.calculate_score_from_vectors(
		node, node->player_score_, node->opponent_score_);

	return node;

}



long long get_init_time() {
	return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}


long long time_span_nanoseconds(long long init) {
	return std::chrono::high_resolution_clock::now().time_since_epoch().count() - init;
}


long long time_span_milliseconds(long long init) {
	return time_span_nanoseconds(init) / 1000000;
}


//void test_junk() {
//Node* node = test_node_04();
//int score = game.calculate_config_score(node, SYMBOL::PLAYER);
//io.print_node(node);
//std::cout << "score " << score << "\n\n" << std::endl;
//game.next_move(node,50);
//score = game.calculate_config_score(node, SYMBOL::PLAYER);
//io.print_node(node);
//std::cout << "score " << score << "\n\n" << std::endl;
//}



#endif

*/


