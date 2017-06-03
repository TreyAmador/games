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

	//Node* node = test_node_02();
	//io.print_node_and_vec_score(node);
	//Node* child = game.create_child_node(node, 4, 5, SYMBOL::OPPONENT);
	//io.print_node_and_vec_score(child);

	//test_find_max_element();

	test_max_row_col();


	return 0;

}

