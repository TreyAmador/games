#include "core.h"
#include "test.h"
#include "node.h"
#include "game.h"
#include "io.h"


Core::Core() {
	
}


Core::~Core() {

}


int Core::run() {

	Game game;
	IO io;

	//test_child_configs();

	game.minimax(test_node_02(), 2, true);

	//Node* node = new Node;
	//game.make_first_move(node);
	//io.print_node_and_vec_score(node);


	//test_max_row_col();
	//test_next_move_choice();
	//time_next_choice();

	return 0;

}

