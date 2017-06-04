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

	//Node* parent = test_node_02();
	//io.print_config(parent);

	//int max = game.minimax(parent, 6, true);
	//std::cout << max << std::endl;

	//Node* next_move = game.get_best_node();
	//io.print_config(next_move);




	//if (io.player_moves_first()) {
	//	std::cout << "player moves first" << std::endl;
	//}
	//else {
	//	std::cout << "opponent moves first" << std::endl;
	//}

	std::cout << io.time_allowed() << std::endl;


	return 0;

}

