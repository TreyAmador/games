#include "core.h"
#include "test.h"
#include "node.h"
#include "game.h"
#include "io.h"


Core::Core() {
	
}


Core::~Core() {

}


// return negative value upon program failure
// return 0 upon program success
// note this is not relevant to whether you win the game or not
int Core::run() {

	Game game;
	IO io;

	Node* node = test_node_02();
	io.print_node_and_vec_score(node);
	//Node* child = game.create_child_node(node, 4, 5, SYMBOL::OPPONENT);
	//io.print_node_and_vec_score(child);

	return 0;
}

